# Functions and closures

A tree-walk callable exposes arity and call behavior. A user function stores its declaration and declaration-time environment. Calling creates a child environment, binds parameters, executes the body, and converts an internal return signal to a value. Native functions use the same boundary.

Use `shared_ptr<Environment>` only if environment lifetime is truly shared. Draw the ownership graph. A closure must never retain a stack-local reference. If closures stored in environments create cycles, prefer a runtime arena or deliberate weak edges; verify destruction.

In a VM, compiled functions own chunks and arity metadata. A frame holds a closure/function, instruction pointer, and base stack slot. Relative slots support recursion.

An upvalue refers to a live slot while open. Deduplicate capture of the same slot. Keep open upvalues ordered by position. On scope/frame exit, move the value into owned closed storage and redirect the upvalue. Nested compilers flatten captures by referencing a parent's local or upvalue.

Test arity errors, recursion, nested calls, early return, natives, capture after creator return, captured mutation, independent closure instances, and closures sharing a capture. VM tests also cover stack traces and frame overflow.
