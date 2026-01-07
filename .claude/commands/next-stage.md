---
description: Move to the next stage in the current project
allowed-tools: Read, Edit, Write, Bash(make:*), Bash(./tests/*.sh:*), Bash(valgrind:*)
model: sonnet
---

# Next Stage Command

Move to the next stage in the current project.

## Instructions

1. First, validate the current stage is complete:
   - Run all tests for current stage
   - Check for memory issues with valgrind
   - Run regression tests for previous stages
   - **IMPORTANT**: If validation passes, automatically create a git commit for the completed stage and push to remote

2. If validation passes:
   - Update the project's CLAUDE.md to increment the stage number
   - Mark the completed stage in the Progress Tracking section
   - Add the new stage's requirements to CLAUDE.md
   - Commit the CLAUDE.md and new test files separately (Stage X preparation commit)

3. Generate tests for the new stage:
   - Use the test-generator agent
   - Create test file in tests/test_stage_X.sh
   - Explain what each test validates

4. Brief the user on:
   - What the new stage involves
   - Key concepts they'll need
   - Suggested approach (without spoiling)

## Output Format

```
## Moving to Stage X

### Previous Stage Validation
- Tests: [PASS/FAIL]
- Memory: [PASS/FAIL]
- Regressions: [PASS/FAIL]

### Stage X: [Name]
[Brief description of what this stage involves]

### Key Concepts
- [Concept 1]
- [Concept 2]

### Tests Generated
Created: tests/test_stage_X.sh

### Getting Started
[Suggested first step without spoiling]
```
