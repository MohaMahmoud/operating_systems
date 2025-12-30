#!/usr/bin/env python3

import argparse
import tarfile
import shutil
import sys
import re
from pathlib import Path


ARCHIVE_RE = re.compile(r"^asst(\d{2})-templates\.tar\.gz$")


def die(msg: str) -> None:
    print(f"Error: {msg}", file=sys.stderr)
    sys.exit(1)


def find_assignment_name(assignment_dir: Path) -> str:
    assignment_files = sorted(f for f in assignment_dir.glob("*.c") if f.name != "main.c")
    
    if not assignment_files:
        die(f"{assignment_dir}: No assignment .c files found (excluding main.c).")
    
    return assignment_files[0].stem

def import_archive(archive: Path, assignments_dir: Path, dry_run: bool) -> None:
    m = ARCHIVE_RE.match(archive.name)
    if not m:
        print(f"Skipping unrecognized archive file: {archive.name}")
        return

    assignment = f"A{m.group(1)}"
    target_root = assignments_dir / assignment
    extract_dir = archive.parent / f".extract_{archive.stem}"
    
    print(f"Extracting {archive} to {extract_dir}...")
    
    if target_root.exists():
        print(f"Target assignment directory {target_root} already exists.")
        return
    
    if extract_dir.exists():
        die(f"Temporary extraction directory {extract_dir} already exists.")
        
    if not dry_run:
        with tarfile.open(archive, "r:gz") as tar:
            tar.extractall(path=extract_dir)
    
    roots = list(extract_dir.iterdir()) if not dry_run else []
    if not dry_run and len(roots) != 1:
        die(f"Expected exactly one root directory in the archive, found {len(roots)}.")
    
    template_root = roots[0] if not dry_run else None
    
    if not dry_run:
        target_root.mkdir(parents=True)
    
    # Import testlib
    testlib_src = template_root / "testlib"
    if not dry_run:
        if not testlib_src.exists():
            die(f"testlib directory not found in the archive.")
            
        testlib_dst = target_root / "testlib"
        if testlib_dst.exists():
            die(f"testlib directory already exists at {testlib_dst}.")
        
        print(f"Moving testlib from {testlib_src} to {testlib_dst}...")
        shutil.move(str(testlib_src), str(testlib_dst))

    # Import assignment directories
    for assignment_dir in sorted(template_root.iterdir()):
        if not assignment_dir.is_dir() or assignment_dir.name == "testlib":
            continue
        
        assignment_name = find_assignment_name(assignment_dir)
        dest = target_root / assignment_name
        
        if dest.exists():
            die(f"Assignment directory {dest} already exists.")
        
        print(f"Importing assignment {assignment_name} to {dest}...")
        
        if not dry_run:
            vscode_dir = assignment_dir / ".vscode"
            if vscode_dir.exists():
                shutil.rmtree(vscode_dir)
            
            shutil.move(str(assignment_dir), str(dest))
    
    if not dry_run:
        shutil.rmtree(extract_dir)


def main() -> None:
    parser = argparse.ArgumentParser(
        description="Import OS assignment templates into the workspace."
    )
    parser.add_argument(
        "--import-dir",
        type=Path,
        default=Path("import"),
        help="Directory containing the archive to import (default: import/)"
    )
    parser.add_argument(
        "--assignments-dir",
        type=Path,
        default=Path("assignments"),
        help="Assignments root directory (default: assignments/)"
    )
    parser.add_argument(
        "--dry-run",
        action="store_true",
        help="Show actions without modifying anything"
    )
    
    args = parser.parse_args()
    
    import_dir = args.import_dir
    if not import_dir.exists() or not import_dir.is_dir():
        die(f"Import directory {import_dir} does not exist or is not a directory.")
        
    archives = sorted(import_dir.glob("*.tar.gz"))
    if not archives:
        die(f"No archive files found in {import_dir}.")
        
    for archive in archives:
        import_archive(archive, args.assignments_dir, args.dry_run)

    print("Import completed successfully.")


if __name__ == "__main__":
    main()
