# Packet Sniffer in C - CodeCrafters Style

## Current Stage: Stage 1 - Capture Basics

**Language**: C (C11)
**Build System**: Make
**Key Library**: libpcap

---

## Stage Requirements

### Stage 1: Initialize libpcap and Capture Packets
**Goal**: Set up libpcap, open a network interface, and print "Packet captured!" for each packet.

**You will learn**:
- Installing/linking libpcap on macOS
- Opening a network interface
- Basic capture loop
- Compiling and running with proper permissions

**Test**: Open your sniffer, then `ping google.com` in another terminal. You should see "Packet captured!" messages appearing.

**Key functions to research**:
- `pcap_lookupdev()` or `pcap_findalldevs()`
- `pcap_open_live()`
- `pcap_loop()` or `pcap_next()`
- `pcap_close()`

---

## All Stages Overview

### Phase 1: Capture Basics
- [x] **Stage 1**: Initialize libpcap, capture packets, print "Packet captured!"
- [ ] **Stage 2**: Print basic packet info (timestamp, length)
- [ ] **Stage 3**: Decode Ethernet headers (MAC addresses)

### Phase 2: Network Layer
- [ ] **Stage 4**: Decode IP headers (source/dest IP, protocol)
- [ ] **Stage 5**: Filter for ICMP packets only
- [ ] **Stage 6**: Decode ICMP packets (ping requests/replies)

### Phase 3: Transport Layer
- [ ] **Stage 7**: Decode TCP headers (ports, flags, seq numbers)
- [ ] **Stage 8**: Decode UDP headers
- [ ] **Stage 9**: Filter by port number

### Phase 4: Application Layer
- [ ] **Stage 10**: Extract DNS queries/responses
- [ ] **Stage 11**: Extract HTTP requests (URLs, methods)
- [ ] **Stage 12**: Pretty-print packet summaries

---

## Build & Test Commands

```bash
# Build
make clean && make

# Run (requires sudo for raw socket access)
sudo ./sniffer

# Run specific stage test
./tests/test_stage_1.sh

# Run all tests
./tests/run_all.sh

# Memory check
sudo valgrind --leak-check=full ./sniffer

# Generate traffic for testing
ping google.com              # ICMP
nslookup example.com         # DNS
curl http://example.com      # HTTP
```

---

## C-Specific Guidelines

### Compiler Flags
```makefile
CFLAGS = -Wall -Wextra -Werror -std=c11 -g
LDFLAGS = -lpcap
```

### Memory Management
- Every `malloc()` needs a corresponding `free()`
- Check return values of allocation functions
- Use valgrind before marking stages complete

### Network Byte Order
- Network data is big-endian
- Use `ntohs()` for 16-bit values
- Use `ntohl()` for 32-bit values
- Never assume host byte order matches network

### Header Sizes
| Header | Size |
|--------|------|
| Ethernet | 14 bytes |
| IPv4 | 20-60 bytes (check IHL) |
| TCP | 20-60 bytes (check data offset) |
| UDP | 8 bytes |
| ICMP | 8+ bytes |

---

## Useful Resources

- `man pcap` - libpcap manual
- `man 7 ip` - IP protocol
- `man 7 tcp` - TCP protocol
- `man 7 udp` - UDP protocol
- `man 7 icmp` - ICMP protocol

---

## Progress Notes

### Stage 1 Notes:
- macOS: libpcap is pre-installed
- Need sudo to capture packets
- Use `en0` for WiFi, `lo0` for loopback on macOS
