# Strings, objects, upvalues, and memory

Use C++ values and smart pointers while semantics change. A custom heap/GC is a separate milestone justified by cyclic language objects, VM control, or performance. RAII still owns the heap manager, vectors, tables, and external resources.

Interning shares string identity but can retain every string. Under tracing GC, make the intern table weak and remove unmarked keys. With host ownership, use weak handles or explicitly accept process-lifetime retention for a small prototype. Start with `unordered_map`; custom open addressing is an optimization or learning goal.

For precise mark-sweep, roots include value/frame stacks, globals, open upvalues, compiler constants/temporary roots, natives, and host-visible handles. Mark roots, trace object edges with a gray worklist, then sweep. Reset survivor marks.

Allocation may collect, so root a new object before any later allocation; provide a temporary-root guard. Stress collection at every allocation and log allocation/free to expose hidden roots. Tune thresholds from live bytes while balancing latency and throughput.

Avoid movable storage for address-based handles and pointers into growing vectors. Destructors must not re-enter collection. Reference counting is deterministic but misses cycles; tracing handles cycles but requires complete roots/edges.

Run ASan/UBSan and GC stress over closures, interning/concatenation, class cycles, failed compilation, and temporary constants.
