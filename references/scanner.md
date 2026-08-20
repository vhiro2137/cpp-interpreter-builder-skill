# Scanner

Input is an immutable source buffer with stable identity. Output is a token sequence or one token on demand, plus lexical diagnostics. Tokens carry half-open byte spans; centralize byte-to-line/column mapping when Unicode or tabs matter.

Maintain `start` and `current`. Skip trivia, set `start`, advance, then dispatch. Use maximal munch for operators, identifiers, numbers, and strings. Recognize an identifier before exact keyword classification. Make `advance`, `peek`, `peek_next`, and `match` bounds-safe.

Decide and test encoding/identifier policy, newline normalization, comment nesting, numeric grammar, escapes, and trivia retention. A token may hold `string_view` only when source lifetime is stable; otherwise store a span or owned spelling. Use `from_chars` when selected-standard support is adequate and verify complete consumption.

Test every token, ambiguous prefix, keyword boundary, EOF inside each construct, multiline input, invalid characters, and exact locations. Acceptance: scanning always progresses or returns EOF, never reads out of bounds, and can report multiple independent lexical errors under the chosen policy.

Common failures: not resetting `start`, consuming before `match`, keyword-prefix bugs, dangling views, and mixing byte offsets with code-point columns.
