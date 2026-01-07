---
description: Review the user's implementation for the current stage
allowed-tools: Read, Grep, Glob, Bash(make:*)
model: sonnet
---

# Review Code Command

Review the user's implementation for the current stage.

## Instructions

1. Read the project's CLAUDE.md to understand:
   - Current stage
   - Stage requirements
   - Language/build system

2. Read the implementation files in src/

3. Perform code review using code-reviewer agent guidelines:
   - Correctness (meets requirements?)
   - Memory safety (leaks, buffer issues?)
   - Code style (readability, naming?)
   - Best practices (C/C++ idioms?)

4. Provide constructive feedback

## Review Format

```markdown
## Code Review: Stage X

### Summary
[1-2 sentence overview]

### What's Working Well
- [Positive point 1]
- [Positive point 2]

### Suggestions

#### [Priority: High/Medium/Low] [Issue Title]
**What**: [Description of issue]
**Why**: [Why it matters]
**Consider**: [Direction to think about - not the solution]

### Memory Safety
- [x] No obvious leaks
- [x] Bounds checking present
- [ ] Consider: [if any concerns]

### Next Steps
[What to focus on improving, if anything]
```

## Guidelines
- Start with positives
- Be specific about issues
- Don't rewrite their code
- Explain WHY something is an issue
- Suggest directions, not solutions
- Be encouraging
