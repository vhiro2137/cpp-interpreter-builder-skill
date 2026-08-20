# Resolver and lexical scopes

Mutable environment chains alone can give closures surprising bindings when later declarations alter the same environment object. A resolver makes lexical binding explicit before execution and catches context errors early.

Walk the AST with a stack of scope maps. Track names as declared then defined; an initializer may not read its own local before definition. For each variable/assignment, search outward and record lexical distance or a binding/slot ID. Unresolved names are globals by policy.

Track function context (`none`, function, method, initializer) and class context (`none`, class, subclass). Diagnose top-level `return`, forbidden initializer value returns, `this` outside a class, `super` without a superclass, duplicate locals, and self-inheritance.

Tree-walk environments implement `get_at(distance, name)` and `assign_at`; globals have their own map. A bytecode compiler can resolve directly to local/upvalue/global operands instead of using a separate AST pass.

Test shadowing, self-initialization, closure capture across later shadowing, recursive local functions, outer assignment, and invalid contexts. Acceptance: a lexical occurrence always reaches the same declaration regardless of later environment mutation.

Common bugs: omitting the parameter scope, confusing distance zero with globals, retaining AST-pointer map keys after AST destruction, or depending on runtime values.
