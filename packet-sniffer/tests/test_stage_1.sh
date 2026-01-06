#!/bin/bash
# Stage 1 Test: Basic packet capture

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR/.."

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

pass() { echo -e "${GREEN}PASS${NC}: $1"; }
fail() { echo -e "${RED}FAIL${NC}: $1"; exit 1; }
info() { echo -e "${YELLOW}INFO${NC}: $1"; }

echo "========================================="
echo "Stage 1: Basic Packet Capture"
echo "========================================="
echo

# Check if binary exists
if [ ! -f "./sniffer" ]; then
    fail "Binary not found. Run 'make' first."
fi

# Test 1: Program starts without crashing
info "Test 1: Program starts successfully"
timeout 2 sudo ./sniffer > /tmp/sniffer_output.txt 2>&1 &
SNIFFER_PID=$!
sleep 1

if ! ps -p $SNIFFER_PID > /dev/null 2>&1; then
    # Process died, check if it was intentional or crash
    wait $SNIFFER_PID 2>/dev/null || true
    if grep -q "Packet captured" /tmp/sniffer_output.txt; then
        pass "Program ran and captured packets"
    else
        cat /tmp/sniffer_output.txt
        fail "Program crashed or exited unexpectedly"
    fi
else
    pass "Program starts and runs"
fi

# Test 2: Generates traffic and check for capture
info "Test 2: Captures ICMP packets (ping)"

# Generate some ICMP traffic
ping -c 3 127.0.0.1 > /dev/null 2>&1 &
PING_PID=$!
sleep 2

# Kill sniffer
sudo kill $SNIFFER_PID 2>/dev/null || true
wait $SNIFFER_PID 2>/dev/null || true
wait $PING_PID 2>/dev/null || true

# Check output
if grep -q "Packet captured" /tmp/sniffer_output.txt; then
    PACKET_COUNT=$(grep -c "Packet captured" /tmp/sniffer_output.txt || echo "0")
    pass "Captured $PACKET_COUNT packets"
else
    info "Output was:"
    cat /tmp/sniffer_output.txt
    fail "No 'Packet captured!' messages found"
fi

# Cleanup
rm -f /tmp/sniffer_output.txt

echo
echo "========================================="
echo -e "${GREEN}Stage 1: All tests passed!${NC}"
echo "========================================="
