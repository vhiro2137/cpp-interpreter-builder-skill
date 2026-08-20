# Bytecode compiler

Use a byte vector or typed instruction representation, a `vector<Value>` constant pool, and a source-location table. Define operand widths, byte order, constant limit, jump range, and stack effect for every opcode. Add checked emit/read helpers and a disassembler before growing the instruction set.

A compact compiler scans on demand and uses a Pratt table; prefix/infix parse functions emit code instead of AST nodes. Track parser panic separately from compilation failure. Declarations/statements drive compiler routines.

Locals are stack slots described by name, depth, and captured flag. Reject a local read in its own initializer. Globals can use name-constant operands. Emit placeholder jumps and patch them later; loops emit backward jumps. All control-flow paths must agree on stack depth.

Nested functions use stacked compiler contexts. Each has its own chunk/local table and resolves outer names to upvalue descriptors. Emit closure capture metadata after the function constant.

Choose AST-to-bytecode when separate analysis/optimization/tooling needs syntax trees. Direct emission is smaller. Do not build an AST with no consumer.

Golden-test disassembly and execute the code. Test constant limits, operand boundaries, jump patching, stack balance, nested locals, closures, and malformed syntax recovery. Verify bytecode if it can be loaded from untrusted storage.
