#!/usr/bin/env python3
"""Copy the skill's modern C++ starter into a new, empty destination."""

from __future__ import annotations

import argparse
import shutil
from pathlib import Path


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("destination", type=Path, help="new or empty project directory")
    parser.add_argument("--force", action="store_true", help="allow an existing empty directory")
    args = parser.parse_args()

    source = Path(__file__).resolve().parent.parent / "assets" / "project-template"
    destination = args.destination.resolve()
    if destination.exists():
        entries = list(destination.iterdir()) if destination.is_dir() else [destination]
        if entries:
            parser.error(f"destination is not empty: {destination}")
        if not args.force:
            parser.error("destination exists; pass --force only after confirming it is empty")
    else:
        destination.mkdir(parents=True)

    shutil.copytree(source, destination, dirs_exist_ok=True)
    print(f"Created C++ interpreter starter at {destination}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
