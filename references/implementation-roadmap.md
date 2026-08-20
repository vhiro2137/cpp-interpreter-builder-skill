# Dependency-ordered roadmap

Each stage is separately shippable; stop at the requested capability.

## Shared front end

1. **Shell/spec** — Examples -> CMake targets, runner, diagnostics, grammar subset. Accept when configure/build/test/run work.
2. **Scanner** — Source -> tokens/spans/errors. Types: source, token, scanner. Accept token dump, EOF/bounds, exact-span tests.
3. **Parser/syntax** — Tokens -> AST or emitted expression bytecode. Minimum literals/grouping/unary/arithmetic. Accept precedence, associativity, and recovery tests.

## A. Tree-walk

4. **Expression evaluation** — AST -> `Value`; truthiness/type errors and evaluation-order tests.
5. **Statements/state** — Print, variables, assignment, blocks, environments; shadowing/undefined-name tests.
6. **Control flow** — Condition, short-circuit, loops; side-effect and termination tests.
7. **Resolver** — AST -> lexical bindings/static diagnostics; closure-shadowing and context tests.
8. **Functions/closures** — Callable, call environment, return, natives; recursion/capture/lifetime/sanitizer tests.
9. **Classes/inheritance** — Class/instance/fields/methods, `this`, initializer, superclass, `super`, each as a separate slice.

Suggested files: `source`, `token`, `scanner`, `ast`, `parser`, `resolver`, `value`, `environment`, `callable`, `interpreter`, `diagnostic`, `main`; mirror modules in tests plus `tests/language`.

## B. Bytecode VM

4. **Chunk/disassembler** — Instructions, constants, sources; checked round-trip and readable dump.
5. **Minimal VM** — Hand-built chunk -> stack result; constants/arithmetic/return/bounds/type tests.
6. **Direct compiler** — Scanner + Pratt -> expression bytecode; source-to-result plus disassembly.
7. **Statements/globals/control flow** — Print/global/jumps/loops; verify stack balance on every path.
8. **Locals/functions/frames** — Slots, functions, calls/returns/natives; recursion, arity, overflow, traces.
9. **Closures/upvalues** — Capture/flatten/close; lifetime, mutation, sharing, stress tests.
10. **Objects/classes/inheritance** — Interning, tables, bound methods, incremental object opcodes.
11. **Managed heap/optimization** — Precise GC, weak intern table, stress mode, then profile-led changes. GC need not block an early host-owned learning VM.

Suggested VM files: shared front end plus `opcode`, `chunk`, `disassembler`, `compiler`, `value`, `object`, `table`, `vm`, `memory`.

For every current stage record goal, input/output, interfaces, files, algorithm, exclusions, exact acceptance command, success/error tests, failure probes, and the invariant required by the next stage. If there is no observable end-to-end case, reduce the milestone.
