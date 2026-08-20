# Parser and AST

Write an unambiguous grammar first. A recursive-descent precedence ladder uses one function per level: assignment, logical-or, logical-and, equality, comparison, term, factor, unary, call, primary. Left-associative levels loop; right-associative assignment recurses. Validate assignment targets after parsing the left side.

For extensible expressions or direct bytecode emission, use a Pratt table mapping token types to prefix parser, infix parser, and binding power. Associativity follows right binding power. Keep this table as the single precedence source.

Model syntax, not runtime values. Expressions commonly include literal/unary/binary/grouping, variable/assignment/logical/call, get/set, `this`, and `super`. Statements include expression/print/variable/block/if/while/function/return/class. Attach operator/name spans needed for diagnostics.

Classic visitors make adding operations easy but adding nodes noisy. Variant visitation makes the closed node set exhaustive but recompiles consumers. Virtual dispatch favors plugin/open hierarchies; arenas favor compact stable storage.

On declaration-level errors, enter panic mode and advance to semicolon, block boundary, or a declaration/statement starter. Suppress cascades until synchronized. Provide an AST structural printer independent of evaluation.

Test precedence, associativity, nested calls, bad assignment targets, missing delimiters, and multiple recoverable errors. Acceptance: the parser reaches EOF without no-progress loops and dumps grouping explicitly.
