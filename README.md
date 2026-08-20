# C++ Interpreter Builder Skill

A Codex Skill for designing, implementing, extending, and debugging interpreters in modern C++17/20. It turns the engineering methods from *Crafting Interpreters* into dependency-ordered, test-driven C++ workflows for tree-walk interpreters and bytecode virtual machines.

## Install

Copy this repository into the personal Codex skills directory:

```powershell
Copy-Item -Recurse cpp-interpreter-builder-skill "$env:USERPROFILE\.codex\skills\cpp-interpreter-builder"
```

The destination folder name should match the Skill name, `cpp-interpreter-builder`.

## Use

Invoke it explicitly in a new Codex task:

```text
$cpp-interpreter-builder inspect this C++ interpreter and implement the next verifiable stage.
```

It can also be selected automatically for C++ scanner, parser, AST, resolver, closure, tree-walk interpreter, bytecode compiler, VM, and related debugging work.

## Contents

- `SKILL.md` contains the routing and workflow instructions.
- `references/` provides stage-specific engineering guidance loaded on demand.
- `assets/project-template/` is a compilable C++20/CMake starter.
- `scripts/` contains safe project-scaffolding and AST-generation helpers.

## Validation

The starter has been configured and built with CMake and tested with CTest. The bytecode route was forward-tested against the applicable *Crafting Interpreters* language suite; exact pass/skip counts and backend compatibility must still be rechecked whenever implementation code or its upstream test revision changes.

## License

MIT
