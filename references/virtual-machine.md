# Stack virtual machine

The VM contains module/chunk, value stack, frame stack, globals, natives, heap manager, intern table, and I/O/diagnostic sinks. A frame has code identity, instruction pointer, and base slot. Never retain pointers into a vector across reallocation.

The dispatch loop fetches, checked-decodes, reads operands, executes, and maintains a documented stack effect. A switch is portable; computed goto or tables are measured optimizations. Preserve optional disassembly/trace modes.

Arithmetic preserves language evaluation order, validates dynamic types, and pushes results. Calls validate callee/arity, create frames without invalidating live references, and return by restoring the caller and replacing callee/arguments with the result.

Branches use relative offsets. Validate targets and instruction boundaries for externally supplied bytecode. Runtime errors attach source location and walk frames for a stack trace, then reset execution state without discarding globals unless specified.

Hand-build chunks before adding a compiler. Test constants, arithmetic, errors, stack bounds, calls, recursion, jumps, and traces in isolation; then add compiler+VM end-to-end cases.

Optimize only from repeatable release benchmarks/profiles: specialized opcodes, caches, probing, folding, and alternate value encodings are later options.
