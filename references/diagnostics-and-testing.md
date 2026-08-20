# Diagnostics, debugging, testing, and performance

Use one diagnostic structure with separate phases: lexical, syntactic, static-resolution, bytecode/compile, and runtime. Include severity, optional stable code, message, primary span, labels/notes, and source identity. Render separately so tests assert structure rather than terminal formatting.

Scanner errors usually continue. Parsers use panic mode and statement/declaration synchronization. Resolver errors accumulate before execution. Runtime errors stop the current run, attach stack trace, and restore state.

## Test pyramid

- Unit: tokens, precedence/AST shape, binding distances, value operations, opcode encoding, tables.
- Component: token/AST dumps, resolver maps, disassembly, hand-built chunks.
- Language: source with expected stdout, diagnostics, and result class.
- Regression: a minimal program for each bug.
- Property/fuzz: scanner/parser termination, spans, decoder bounds, and tree-walk/VM differential behavior when semantics match.

Organize language cases by feature and error phase. Avoid tests coupled to private layout.

Confirm the test command actually discovers tests. `ctest` returning success with “No tests were found” is not evidence of correctness. When a repository delegates conformance tests to an external runner, execute that runner or reproduce its documented cases and clearly report any unavailable dependency. For a multi-backend interpreter, run shared semantic programs through every supported parser/backend combination and compare values, output, diagnostics, and exit status.

For GCC/Clang debug builds use `-fsanitize=address,undefined -fno-omit-frame-pointer` with matching link flags. On MSVC enable supported AddressSanitizer and separate UB checks. Keep token, AST, bytecode, stack, and GC traces disabled by default.

Benchmark startup, expressions, calls, allocations, and objects in release builds. Profile before representation changes; measure memory plus GC pause/collection behavior. Preserve correctness tests across optimization.
