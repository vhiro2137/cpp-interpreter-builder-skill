# Tree-walk interpreter

Visit expressions to produce `Value`; execute statements for effects. Centralize truthiness, equality, numeric checks, display, and callable dispatch. Maintain globals and current environment. Restore the previous environment with an RAII guard after a block, including on errors or returns.

Evaluation order is language semantics. Define left-to-right operands, short-circuit logic, assignment result, and side-effect order. `for` may desugar to block plus `while` if source spans and `continue` behavior stay correct.

## Minimal slices

1. Literals, grouping, unary/binary expressions, expression/print statements.
2. Variables, lookup, assignment, and blocks.
3. Conditions, logical operators, and loops.
4. Functions/closures, then classes if requested.

Each slice adds syntax, interpretation, diagnostics, and language tests together.

Runtime type/name/call errors carry the responsible span. Use `Result<Value, RuntimeError>` or throw only inside the interpreter and catch at the run boundary. Environment restoration must be exception-safe.

Test observable output, evaluation order, short-circuit side effects, nested blocks, shadowing, loops, and separate REPL submissions. A failed run must not leave the current environment corrupted.
