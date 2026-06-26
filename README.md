# NetScope
### Network Traffic Analysis and Diagnostics Platform

NetScope is a C++ based networking project aimed at understanding how communication happens across the Internet by implementing core networking utilities from scratch.

Instead of relying on existing networking tools, this project builds the underlying functionality to explore concepts such as DNS resolution, routing, packet capture, TCP/IP communication, and protocol analysis.

---

## Project Goals

- Understand the TCP/IP networking stack through implementation.
- Learn socket programming and network APIs.
- Explore how packets travel across the Internet.
- Build a modular network diagnostics toolkit.

---

## Features

### Module 1 – DNS Resolver

Resolve domain names into IPv4 addresses using the Windows networking API.

**Implemented Features**

- Domain name resolution
- IPv4 address lookup
- Multiple IP address handling
- DNS lookup time measurement
- Clean command-line interface

Example:

```text
==========================
NetScope DNS Resolver
==========================

Domain: amazon.com

Lookup Time: 5 ms

IPv4 Addresses:
1. 98.82.161.185
2. 98.87.170.74
3. 98.87.170.71

Total IPs: 3
```

---

### Module 2 – Traceroute

Discover the route taken by packets from the local machine to a destination.

**Planned Features**

- Hop-by-hop route discovery
- TTL manipulation
- ICMP Time Exceeded handling
- Round-trip time measurement

---

### Module 3 – Packet Analyzer

Capture and inspect packets flowing through the network.

**Planned Features**

- Packet capture
- IPv4 packet parsing
- TCP packet analysis
- UDP packet analysis
- ICMP packet analysis
- Packet statistics

---

## Technologies

- C++
- Winsock API
- Socket Programming
- TCP/IP
- DNS
- ICMP
- Git
- GitHub

**Future Technologies**

- libpcap / Npcap
- Linux Support

---

## Concepts Explored

- DNS Resolution
- Socket Programming
- Client-Server Communication
- IPv4 Addressing
- TCP
- UDP
- ICMP
- TTL
- Routing
- Packet Capture

---

## Project Structure

```
NetScope/
│
├── dns_resolver.cpp
├── README.md
└── .gitignore
```

---

## Motivation

Networking is often taught as a theoretical subject. NetScope aims to bridge the gap between theory and implementation by building networking tools from scratch and understanding how data travels across the Internet.

The project focuses on developing practical knowledge of networking concepts through hands-on implementation rather than relying on existing utilities.

---

## Future Improvements

- IPv6 support
- Reverse DNS Lookup
- DNS Record Types (A, AAAA, MX, CNAME)
- Interactive command-line interface
- Graphical dashboard
- Cross-platform support
- Network performance visualization
