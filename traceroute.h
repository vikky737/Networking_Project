#ifndef TRACEROUTE_H
#define TRACEROUTE_H

#include <string>
#include <cstdint>
#include <netinet/ip.h>

// Standard ICMP Header structure
struct icmphdr {
    uint8_t  type;       // ICMP message type
    uint8_t  code;       // Subtype code
    uint16_t checksum;
    union {
        struct {
            uint16_t id;
            uint16_t sequence;
        } echo;
        uint32_t gateway;
        struct {
            uint16_t unused;
            uint16_t mtu;
        } frag;
    } un;
};

// Structure to hold the result of a single probe hop
struct HopResult {
    int hop_count;
    std::string ip_address;
    double rtt_ms;       // Round-trip time in milliseconds
    bool target_reached;
    bool timed_out;
};

// Core traceroute function prototype
void run_traceroute(const std::string& destination_ip, int max_hops = 30);

#endif // TRACEROUTE_H