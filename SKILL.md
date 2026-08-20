---
name: cpp-interpreter-builder
description: Design, implement, extend, or debug interpreters in modern C++17/20, including scanners, parsers, ASTs, resolvers, tree-walk evaluators, closures, classes, bytecode compilers, and stack VMs. Use for new language projects, existing C++ interpreter work, Crafting Interpreters migrations, or planning the next verified implementation stage; do not use for general C++ work unrelated to language implementation.
---

# C++ Interpreter Builder

Build the smallest verified interpreter increment that fits the user's current stage. Preserve the user's language semantics and project conventions; treat Lox as a design case study, not code to translate line by line.

## Start with project evidence

1. Inspect `AGENTS.md`, build files, source layout, tests, grammar/specification, and recent diagnostics. Search before editing.
2. Classify the repository as new, tree-walk, bytecode VM, hybrid/migrating, or unclear. Identify the furthest working boundary: source, tokens, syntax, resolution, evaluation, bytecode, or VM execution.
3. Infer the C++ standard and test framework. Ask only when a missing choice materially changes semantics or architecture; otherwise record a low-risk assumption.
4. Run the narrowest existing build/test command before editing when practical. Do not overwrite an established architecture with this skill's template.

Read [architecture.md](references/architecture.md) for phase boundaries and data flow. For a new project or milestone planning, also read [implementation-roadmap.md](references/implementation-roadmap.md).

## Choose a route and load only relevant guidance

- Common front end: read [scanner.md](references/scanner.md), then [parser-and-ast.md](references/parser-and-ast.md), only when those stages are in scope.
- Tree-walk: read [tree-walk-interpreter.md](references/tree-walk-interpreter.md). Add [resolver-and-scopes.md](references/resolver-and-scopes.md), [functions-and-closures.md](references/functions-and-closures.md), or [classes-and-inheritance.md](references/classes-and-inheritance.md) only for those features.
- Bytecode VM: read [bytecode-compiler.md](references/bytecode-compiler.md) and [virtual-machine.md](references/virtual-machine.md). Read [memory-management.md](references/memory-management.md) when objects, interning, upvalues, GC, or ownership are involved.
- C++ representation or ownership choice: read [cpp-design.md](references/cpp-design.md).
- Failures, recovery, tests, sanitizers, or performance work: read [diagnostics-and-testing.md](references/diagnostics-and-testing.md).
- Reusing or adapting another implementation: read [open-source-reuse.md](references/open-source-reuse.md) before copying code or adding a dependency.

Tree-walk is the default for rapid semantics work, teaching, and prototypes. Choose bytecode when the request targets VM concepts or measured execution cost justifies a denser representation. Do not require users to implement both.

## Implement one vertical slice

Before editing, state a compact plan with observable behavior, input/output boundary, affected core types, ownership/error decisions, and build/unit/end-to-end checks. Implement in dependency order. Keep tokens and source spans stable across phases. Keep syntax errors recoverable where useful and runtime errors from corrupting state. Prefer explicit interfaces and RAII. Avoid raw owning pointers, dangling AST/source views, shared ownership everywhere, exception-driven ordinary parser control flow, and a custom GC until the runtime object graph requires one.

For greenfield work, `scripts/scaffold_project.py` can copy the compilable starter in `assets/project-template`; inspect the destination first and never use it over existing files without explicit overwrite intent. `scripts/generate_ast.py` may generate repetitive variant-based AST declarations from a small JSON schema.

Open-source reference implementations may accelerate a slice, but reuse is complete only when licensing, provenance, representation/ownership assumptions, platform dependencies, and semantic compatibility have been checked. Prefer portable standard C++ at the boundary. Adapt or rewrite incompatible parts, and require both upstream-relevant tests and this project's regression/language tests to pass. Never transplant GC, upvalue, stack-slot, bytecode, or AST-lifetime code without reconciling its complete ownership and invalidation model.

## Verify and iterate

1. Configure and build with the project's CMake workflow.
2. Run focused unit tests, then language-level success and expected-failure cases.
3. Exercise at least one diagnostic containing a source span and phase.
4. For ownership, closure, object, bytecode, or VM changes, run ASan/UBSan where supported.
5. Fix failures and rerun the smallest relevant checks before broadening.

Do not claim completion from compilation alone. Report changed behavior, design choices, exact verification, assumptions, and the next dependency-ordered slice.

## Invariants

- Separate lexical, syntactic, static-resolution, and runtime diagnostics.
- Define precedence and associativity in one auditable table or grammar layer.
- Resolve lexical bindings before execution or encode equivalent distances/slots during compilation.
- A closure must keep captured state alive without references to destroyed stack frames.
- Bytecode operands, constant indexes, jump offsets, stack effects, and source tables must be bounds-checked or structurally guaranteed.
- Optimize only after representative benchmarks and profiles; preserve a debug disassembler/trace mode.
- Summarize and adapt the book's methods. Do not reproduce long passages or its implementation verbatim.
