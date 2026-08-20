# Portable open-source reuse

Use other interpreters as evidence and implementation sources only after checking the following gates.

## Before reuse

1. Record repository URL, immutable commit/tag, relevant files, and license. Confirm the license is compatible with the destination and preserve required notices/attribution.
2. Identify the reusable semantic contract, not merely similar-looking code: token/span convention, grammar, evaluation order, value representation, error behavior, bytecode layout, stack effects, and object lifetime.
3. Map platform and toolchain assumptions: POSIX APIs, byte order, pointer width, character encoding, compiler extensions, generated files, package downloads, and sanitizer availability.
4. Compare ownership graphs. Treat AST nodes, source views, closures/environments, upvalues, interned strings, VM stack slots, and GC roots as high-risk boundaries.

## Adaptation strategy

- Prefer a narrow interface-preserving port. Replace platform-specific resources with RAII and standard C++ where practical—for example, an owned file buffer behind the existing source-stream interface.
- Keep dependency versions pinned and make network acquisition optional/reproducible when possible.
- Reuse complete invariants rather than isolated functions. If the source assumes a moving-stable stack, tracing heap, or visitor-generated node layout that the destination lacks, rewrite the component against the destination model.
- Avoid formatting-only rewrites that obscure provenance. Keep adaptation changes reviewable and explain intentional semantic differences.

## Verification gate

Reuse is not accepted until:

- the destination configures and builds on its supported toolchains;
- focused unit/component tests cover the adapted boundary;
- upstream tests relevant to the reused behavior pass;
- destination language-level success and expected-error cases pass;
- every supported parser/backend combination is exercised when behavior is shared;
- ASan/UBSan or suitable platform tools cover changed ownership/lifetime code;
- the test runner reports discovered/executed counts—an empty successful run is a failure of validation.

If an upstream runner or dependency cannot be executed, do not claim all tests passed. Report the exact unavailable prerequisite, run a documented substitute set, and leave a reproducible command for completing the gate.

Treat compatibility as a matrix, not a repository-wide adjective. Run each supported
frontend/backend combination independently and report exact pass, fail, and skip counts.
Passing the bytecode suite does not prove that a tree-walk backend matches reference
diagnostic wording, source-line conventions, recovery behavior, or evaluation order.
Such a component is reusable only behind an adapted diagnostic and semantic contract;
do not hide mismatches with a permissive runner unless that looser contract is an
explicit project requirement.
