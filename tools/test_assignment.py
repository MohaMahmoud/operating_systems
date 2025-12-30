#!/usr/bin/env python3

import subprocess
import sys
import re
from pathlib import Path


ASSIGNMENT_RE = re.compile(r"A\d{2}")


def die(msg: str) -> None:
    print(f"Error: {msg}", file=sys.stderr)
    sys.exit(1)


def run(cmd, cwd: Path) -> int:
    try:
        return subprocess.run(cmd, cwd=cwd).returncode
    except FileNotFoundError:
        die(f"Command not found: {cmd[0]}")


def main() -> None:
    cwd = Path.cwd()

    # Enforce correct usage location
    if not ASSIGNMENT_RE.fullmatch(cwd.name):
        die("test_assignment.py must be run from an AXX directory (e.g. assignments/A01)")

    failures = 0

    for task_dir in sorted(cwd.iterdir()):
        if not task_dir.is_dir():
            continue
        if task_dir.name == "testlib":
            continue

        print("\n" + "=" * 30)
        print(f"TASK: {task_dir.name}")
        print("=" * 30)

        # Pre-clean
        run(["make", "-s", "clean"], task_dir)

        # Build
        if run(["make", "-s"], task_dir) != 0:
            failures += 1
            continue

        # Run tests
        if run(["make", "run-tests"], task_dir) != 0:
            failures += 1
        
        # Post-clean
        run(["make", "-s", "clean"], task_dir)

    if failures:
        sys.exit(1)


if __name__ == "__main__":
    main()
