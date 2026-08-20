# Modern C++ design decisions

Use scoped enums, with explicit underlying types when packed:

```cpp
enum class TokenType : std::uint16_t { left_paren, identifier, number, eof_token };
enum class OpCode : std::uint8_t { constant, add, return_ };
```

Decode bytes through checked helpers; never reinterpret arbitrary bytes as an enum.

Start values with `std::variant<Nil, bool, double, std::string, ObjectHandle>`. Hide truthiness, equality, and display behind functions so the representation can change. Tagged unions or NaN boxing are profile-led VM optimizations with documented platform assumptions and a portable fallback.

## AST choices

- Virtual base + `std::unique_ptr`: open hierarchy, stable addresses, conventional visitors; more allocations/boilerplate.
- Recursive `std::variant` + `std::visit`: closed/exhaustive node set; indirection is still needed and compile cost grows.
- Arena + `NodeId`: compact and bulk-owned; needs explicit access APIs.

Default to unique ownership or arena IDs. Use references only while an owner provably outlives the operation. Use `shared_ptr` only for truly shared lifetime, such as captured environments; do not make every edge shared.

Expected user errors belong in diagnostics/results (`std::expected` in C++23, a small `Result`, or project library). Exceptions may implement non-local `return` in a small tree-walker if caught at the public interpreter boundary; never use them for token matching.

Tree-walk closures must not capture `Environment&`. `shared_ptr<Environment>` is simple but can form cycles through stored closures; use weak back-edges or a runtime-owned object arena when needed. VM upvalues point to live stack slots while open and to owned closed storage after scope exit.

Use vectors for code/constants/stacks/frames and validate indexes. Use `unordered_map` for initial environments/globals. Interning requires stable handles and a weak-entry policy under tracing GC. RAII owns files, buffers, tables, runtime services, and environment-restoration guards.
