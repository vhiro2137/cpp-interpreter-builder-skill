#!/usr/bin/env python3
"""Generate simple C++ struct declarations and a variant alias from JSON.

Schema: {"namespace":"lang", "base":"Expr", "nodes":{"Literal":[["Value","value"]]}}
The output is written only to stdout so callers can inspect it before saving.
"""

from __future__ import annotations

import argparse
import json
from pathlib import Path


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("schema", type=Path)
    args = parser.parse_args()
    data = json.loads(args.schema.read_text(encoding="utf-8"))
    namespace = data.get("namespace", "lang")
    base = data["base"]
    nodes = data["nodes"]
    if not isinstance(nodes, dict) or not nodes:
        parser.error("nodes must be a non-empty object")

    print("#pragma once\n\n#include <variant>\n")
    print(f"namespace {namespace} {{\n")
    for name, fields in nodes.items():
        print(f"struct {name} final {{")
        for field_type, field_name in fields:
            print(f"  {field_type} {field_name};")
        print("};\n")
    print(f"using {base} = std::variant<{', '.join(nodes)}>;")
    print(f"\n}}  // namespace {namespace}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
