# Classes and inheritance

A class is a callable method table with optional superclass. Calling allocates an instance and invokes `init`. An instance owns fields and references its class. Lookup checks fields before methods; a method access returns a bound method pairing receiver and function.

`this` is a resolved implicit binding or reserved local slot. `super.method` needs superclass and receiver, resolved/compiled explicitly. Initializers return the receiver; diagnose value returns if forbidden.

Use stable runtime handles. With `shared_ptr`, model cycles among classes, closures, environments, and instances. A tracing heap naturally handles cyclic language graphs; host smart pointers are simpler for prototypes but reference counting cannot collect cycles.

Order: class declaration/construction -> fields -> methods/binding -> `this` -> initializer -> superclass lookup -> `super`. Test field shadowing, extracted methods, inherited/overridden methods, `super`, initializer arity, invalid contexts, self-inheritance, and superclass type errors.
