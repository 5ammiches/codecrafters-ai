#!/bin/bash
# Run all stage tests

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR/.."

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

echo "========================================="
echo "Running All Stage Tests"
echo "========================================="
echo

# Build first
echo -e "${YELLOW}Building...${NC}"
make clean && make
echo

# Find and run all test scripts
PASSED=0
FAILED=0
SKIPPED=0

for test_file in tests/test_stage_*.sh; do
    if [ -f "$test_file" ]; then
        stage=$(basename "$test_file" | sed 's/test_stage_\([0-9]*\).sh/\1/')
        echo -e "${YELLOW}Stage $stage:${NC} $test_file"

        if bash "$test_file"; then
            echo -e "${GREEN}PASS${NC}"
            ((PASSED++))
        else
            echo -e "${RED}FAIL${NC}"
            ((FAILED++))
        fi
        echo
    fi
done

if [ $PASSED -eq 0 ] && [ $FAILED -eq 0 ]; then
    echo -e "${YELLOW}No test files found${NC}"
    echo "Generate tests using: /test-stage"
    exit 0
fi

# Summary
echo "========================================="
echo "Summary"
echo "========================================="
echo -e "${GREEN}Passed:${NC} $PASSED"
echo -e "${RED}Failed:${NC} $FAILED"
echo

if [ $FAILED -gt 0 ]; then
    exit 1
fi
