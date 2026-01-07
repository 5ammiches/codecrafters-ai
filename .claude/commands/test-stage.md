---
description: Run tests for the current stage and report results
allowed-tools: Bash(make:*), Bash(make clean:*), Bash(./tests/test_stage_*.sh:*)
model: sonnet
---

# Test Stage Command

Run tests for the current stage and report results.

## Instructions

1. Read the project's CLAUDE.md to determine current stage
2. Build the project: `make clean && make`
3. Run the stage test: `./tests/test_stage_X.sh`
4. Report results clearly

## If Tests Pass
- Congratulate briefly
- Ask if they want a code review
- Suggest running memory check with valgrind

## If Tests Fail
- Show the failure output clearly
- Do NOT explain why it failed (let them debug)
- Ask: "Would you like a hint?"
- Remind them of available resources (man pages, etc.)

## Output Format

### On Success:
```
## Stage X Tests: PASS

All tests passed!

Next steps:
- Run `valgrind ./sniffer` to check for memory issues
- Want me to review your code? Use /review-code
- Ready for next stage? Use /next-stage
```

### On Failure:
```
## Stage X Tests: FAIL

Test output:
[actual test output]

Failed: [test name]
Expected: [expected]
Got: [actual]

What would you like to do?
- Debug it yourself (recommended!)
- Get a hint (ask me)
- Review relevant concepts (ask me about [topic])
```
