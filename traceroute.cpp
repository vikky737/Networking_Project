#include "traceroute.h"
#include <iostream>
#include <chrono>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>

// Helper to calculate time differences in milliseconds
double get_dt(std::chrono::steady_clock::time_point start) {
    auto end = std::chrono::steady_clock::now();
    return std::chrono::duration<double, std::milli>(end - start).count();
}

void run_traceroute(const std::string& destination_ip, int max_hops) {
    int send_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    int recv_sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);

    if (send_sock < 0 || recv_sock < 0) {
        std::cerr << "Error: Could not create sockets. Did you run with 'sudo'?\n";
        if (send_sock >= 0) close(send_sock);
        if (recv_sock >= 0) close(recv_sock);
        return;
    }

    // Setup destination address
    struct sockaddr_in dest_addr;
    std::memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    inet_pton(AF_INET, destination_ip.c_str(), &dest_addr.sin_addr);

    std::cout << "traceroute to " << destination_ip << " (" << destination_ip << "), " << max_hops << " hops max\n";

    // Main Traceroute Loop
    for (int ttl = 1; ttl <= max_hops; ++ttl) {
        // Set the TTL for this iteration
        if (setsockopt(send_sock, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) < 0) {
            std::cerr << "Failed to set TTL\n";
            break;
        }

        // Vary the port per hop (standard traceroute convention)
        dest_addr.sin_port = htons(33434 + ttl);

        // Send probe packet
        const char* payload = "PING";
        auto start_time = std::chrono::steady_clock::now();
        sendto(send_sock, payload, strlen(payload), 0, (struct sockaddr*)&dest_addr, sizeof(dest_addr));

        // Use select() to implement a 2-second timeout mechanism
        fd_set read_fds;
        FD_ZERO(&read_fds);
        FD_SET(recv_sock, &read_fds);

        struct timeval timeout;
        timeout.tv_sec = 2; 
        timeout.tv_usec = 0;

        int activity = select(recv_sock + 1, &read_fds, nullptr, nullptr, &timeout);
        
        if (activity <= 0) {
            // Timeout occurred or error
            std::cout << ttl << "  * * * (Timeout)\n";
            continue;
        }

        // Read the incoming raw packet buffer
        char buffer[512];
        struct sockaddr_in sender_addr;
        socklen_t addr_len = sizeof(sender_addr);
        
        ssize_t packet_len = recvfrom(recv_sock, buffer, sizeof(buffer), 0, (struct sockaddr*)&sender_addr, &addr_len);
        double rtt = get_dt(start_time);

        if (packet_len < 0) {
            std::cout << ttl << "  * * *\n";
            continue;
        }

        // Parse IPv4 Header
        struct iphdr* ip_hdr = (struct iphdr*)buffer;
        int ip_hdr_len = ip_hdr->ihl * 4; // Length of the outer IP Header

        // Parse ICMP Header (located directly after the outer IP header)
        struct icmphdr* icmp_hdr = (struct icmphdr*)(buffer + ip_hdr_len);

        char sender_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(sender_addr.sin_addr), sender_ip, INET_ADDRSTRLEN);

        // Print Hop Information
        std::cout << ttl << "  " << sender_ip << "  " << rtt << " ms\n";

        // Check ICMP Types:
        // Type 3, Code 3 means "Port Unreachable" -> We successfully hit our actual target!
        if (icmp_hdr->type == 3 && icmp_hdr->code == 3) {
            std::cout << "Destination reached successfully.\n";
            break;
        }
    }

    close(send_sock);
    close(recv_sock);
}