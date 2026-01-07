---
description: Thoroughly validate the current stage before proceeding
allowed-tools: Bash(make:*), Bash(make clean:*), Bash(./tests/*.sh:*), Bash(valgrind:*)
model: sonnet
---

# Validate Stage Command

Thoroughly validate the current stage before proceeding.

## Instructions

1. Run all tests for current stage
2. Run valgrind for memory check
3. Run all previous stage tests (regression)
4. Ask understanding questions

## Validation Steps

```bash
# Build
make clean && make

# Current stage tests
./tests/test_stage_X.sh

# Memory check
valgrind --leak-check=full --error-exitcode=1 ./sniffer [test args]

# Regression tests
./tests/run_all.sh
```

## Output Format

```
## Stage X Validation

### Tests
- [PASS/FAIL] Current stage tests
- Output: [summary]

### Memory Safety
- [PASS/WARN/FAIL] Valgrind
- Issues: [if any]

### Regression
- [PASS/FAIL] Stages 1 through X-1
- Issues: [if any]

### Verdict: [READY / NEEDS WORK]

[If READY]
Congratulations! Use /next-stage to continue.

[If NEEDS WORK]
Please fix:
1. [Issue 1]
2. [Issue 2]
```
