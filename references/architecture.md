# Architecture and data flow

Treat an interpreter as connected transformations with explicit contracts:

`SourceBuffer -> Scanner -> Token stream -> Parser/compiler -> AST or Chunk -> Resolver/VM -> result`

Diagnostics are a side channel carrying phase, severity, message, and source span. The runtime owns globals, natives, heap objects, and output policy.

The tree-walk route materializes tokens and an AST, resolves bindings, then evaluates nodes. It is inspectable and easy to evolve, at the cost of allocation, pointer chasing, and dispatch. The bytecode route may scan one token at a time and use Pratt parse functions that emit instructions directly. A dense `Chunk` and constant pool feed a stack VM; execution is faster and more compact, while transformations and diagnostics are harder.

## Dependency rules

- Source storage outlives borrowed lexemes, or tokens own spelling/use stable spans.
- Scanner knows characters and token categories, not grammar.
- Parser owns grammar and syntax, not runtime environments.
- Resolver knows lexical declarations and context rules, not runtime values.
- Evaluator/VM implements dynamic semantics and calls runtime services.
- Allocation/collection are runtime services, not parser concerns.

Shared types usually include `SourceId`, half-open `SourceSpan`, scoped token/opcode enums, `Token`, structured `Diagnostic`, `Value`, callable/object handles, and explicit result state.

Choose tree-walk when semantics are unsettled, tooling needs an AST, or clarity dominates throughput. Choose bytecode for VM learning or when profiles justify compact code and predictable stack operations. A migration can reuse scanner, spans, diagnostics, language tests, and semantic specification; do not force an AST into a direct compiler.

Advance by vertical language slices. Each slice defines grammar, AST/opcodes, runtime behavior, diagnostics, and tests together. This catches integration failures earlier than completing isolated layers wholesale.
