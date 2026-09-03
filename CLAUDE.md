# CLAUDE.md

This file gives Claude Code context on this project. Read it before making changes.

## Project Overview

trip-log is a solo learning project to practice a C++ toolchain before a group
Data Structures project (European Vacation App). It's a small desktop app for
logging trips: destination, country, dates, notes, and optional coordinates.

Goal: build fluency with Git, Qt, SQLite, Doxygen, and CMake — not to ship a
polished app. Prefer simple, well-commented code over clever code.

## Tech Stack

- Language: C++20
- GUI: Qt 6 (Widgets)
- Database: SQLite (via sqlite3 C API, or SQLiteCpp — TBD)
- Build: CMake
- Docs: Doxygen (`/** ... */` comments on all public classes/functions)
- VCS: Git, feature-branch workflow

## Build & Run

<!-- Fill these in once step 1 (CMake + Qt build) is working -->
- Configure: `cmake -B build -S .`
- Build: `cmake --build build`
- Run: `./build/trip-log`
- Generate docs: `doxygen Doxyfile`

## How I want to work with you

- I'm learning these tools, not outsourcing them. Don't write whole features
  unprompted — explain the approach first, or write a small piece and let me
  extend it.
- When introducing a new concept (e.g. Qt signals/slots, prepared statements),
  briefly explain *why* it works that way, not just the syntax.
- Ask before touching files outside what we're currently discussing.
- Prefer small, incremental commits over large ones.

## Conventions

- Every public class/function gets a Doxygen comment before it's committed.
- One feature per branch: `feature/<short-name>`.
- Header/source split: `.h` in `include/`, `.cpp` in `src/` (once that
  structure exists).
- No SQL string concatenation — use prepared statements.

## Toolchain (Windows)

- Compiler: MinGW (via Qt installer), not MSVC — chosen for consistency with
  the Ubuntu laptop, which also uses GCC.
- Package manager: vcpkg, installed at C:\vcpkg
- vcpkg triplet: x64-mingw-dynamic (must match MinGW, not the vcpkg default
  MSVC triplet)
- SQLite installed via: `vcpkg install sqlite3:x64-mingw-dynamic`
- CMake must be configured with both the vcpkg toolchain file and the triplet:

## Toolchain (Ubuntu, secondary machine)

<!-- Fill in once set up there — likely GCC + system SQLite via apt, or
     vcpkg with the default Linux triplet for consistency -->

## Current Status

<!-- Keep this updated as you go, so future sessions have context -->
- [ ] `Coordinate` class (lat/lon)
- [ ] CMake + Qt: empty window builds
- [ ] SQLite: `trips` table, hardcoded insert/read via console
- [ ] Qt form → SQLite insert
- [ ] Qt table view showing all trips
- [ ] Edit/delete
- [ ] Doxygen pass
- [ ] (stretch) sort trips by distance using `Coordinate`