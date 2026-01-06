# Hint Command

Provide a progressive hint for the current stage.

## Instructions

1. Check what hints have been given (track in conversation)
2. Start at Level 1 (conceptual)
3. Only escalate if user asks for more hints

## Hint Levels

### Level 1: Conceptual Direction
Point toward the concept area without specifics.

### Level 2: Narrowing Focus
Reference specific documentation or function names.

### Level 3: Specific Guidance
More concrete direction, still not the answer.

### Level 4: Near-Solution
Very close to answer. Use sparingly.

## Output Format

```
## Hint [Level X/4]

[Your hint here]

---
**Try this**: [Specific action to take]

Need more help? Ask for another hint.
```

## Rules
- Never skip levels
- Ask what they've tried first
- Use Socratic questions when possible
- Never write code, even partial
