#include <iostream>
#include <string>
#include "traceroute.h"

// TODO: Include your DNS Resolver header file here!
// #include "dns_resolver.h"

std::string resolve_hostname_to_ip(const std::string& hostname) {
    // ----------------------------------------------------------------
    // PASS YOUR EXISTING DNS CODE HERE!
    // Call your custom DNS module to resolve a standard A record.
    // ----------------------------------------------------------------
    
    // Fallback/Placeholder if you haven't wired your DNS module yet:
    return "8.8.8.8"; 
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: sudo " << argv[0] << " <hostname/IP>\n";
        return 1;
    }

    std::string target = argv[1];
    std::string target_ip;

    // Check if user entered an IP or hostname (simple heuristic)
    if (isdigit(target[0])) {
        target_ip = target;
    } else {
        std::cout << "[DNS] Resolving domain via your custom resolver module...\n";
        target_ip = resolve_hostname_to_ip(target);
        std::cout << "[DNS] Resolved " << target << " to " << target_ip << "\n\n";
    }

    // Fire off the traceroute logic
    run_traceroute(target_ip);

    return 0;
}