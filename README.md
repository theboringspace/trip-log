# trip-log
This repository is meant to prep me for using VSCode, GitHub, Doxygen, SQLite, Qt, and Claude Code in a single project.

## Session log: getting an empty Qt window to build (2026-09-03)

Goal: minimal CMake + Qt6 (Widgets) + MinGW project that opens an empty window.

### What we set up

- `CMakeLists.txt`: `find_package(Qt6 REQUIRED COMPONENTS Widgets)`, `CMAKE_AUTOMOC ON`
  (needed for Qt's `moc` codegen behind signals/slots), `qt_add_executable`, and
  `target_link_libraries(... Qt6::Widgets)`.
- `src/main.cpp`: `QApplication` + a bare `QMainWindow` + `window.show()` +
  `app.exec()`.

### Errors hit, and the fix

1. **`find_package(Qt6 ...)` failed — "Could not find a package configuration
   file provided by Qt6"**
   CMake only looks in its default paths plus `CMAKE_PREFIX_PATH`. Qt (installed
   via the Qt installer, not vcpkg) lives at `C:\Qt\6.11.2\mingw_64` and was never
   on that path. Fixed by passing it at configure time:

   ```powershell
   cmake -B build -S . `
     -G "MinGW Makefiles" `
     -DCMAKE_PREFIX_PATH="C:/Qt/6.11.2/mingw_64" `
     -DCMAKE_TOOLCHAIN_FILE="C:/vcpkg/scripts/buildsystems/vcpkg.cmake" `
     -DVCPKG_TARGET_TRIPLET=x64-mingw-dynamic
   ```

   Qt (installer-based) and vcpkg (for SQLite later) are two separate install
   locations, each needing its own flag — neither is implied by the other.

2. **Compile error on `QApplication app(argc, argv)` — "no instance of
   constructor"**
   `main` was declared `int main(int argc, char * argv)` — a single `char*`
   instead of `char *argv[]` (array of C-strings). Fixed the signature to
   `int main(int argc, char *argv[])`.

3. **Exe built but no window appeared; exit code `-1073741511`
   (`0xC0000135`, `STATUS_DLL_NOT_FOUND`)**
   `trip-log.exe` dynamically links Qt's DLLs (`Qt6Core`, `Qt6Gui`,
   `Qt6Widgets`, ...) plus the MinGW runtime, and none of those were
   discoverable on `PATH`, so Windows killed the process before `main()` ran —
   silently, no dialog. Fixed with `windeployqt`, which copies exactly the
   DLLs and plugins (e.g. `platforms/qwindows.dll`) a given exe needs into its
   own folder, so it runs standalone without touching global `PATH`:

   ```powershell
   & "C:\Qt\6.11.2\mingw_64\bin\windeployqt.exe" "build\trip-log.exe"
   ```

### How to build going forward

```powershell
cmake -B build -S . `
  -G "MinGW Makefiles" `
  -DCMAKE_PREFIX_PATH="C:/Qt/6.11.2/mingw_64" `
  -DCMAKE_TOOLCHAIN_FILE="C:/vcpkg/scripts/buildsystems/vcpkg.cmake" `
  -DVCPKG_TARGET_TRIPLET=x64-mingw-dynamic
cmake --build build
& "C:\Qt\6.11.2\mingw_64\bin\windeployqt.exe" "build\trip-log.exe"
.\build\trip-log.exe
```

Re-run `windeployqt` after each fresh build whenever new Qt modules get linked
in (e.g. once SQL or network modules are added) — it only copies what the exe
currently needs, so a new dependency means the deployed DLL set is stale until
you rerun it.

Next up per `CLAUDE.md`'s status list: SQLite `trips` table with a hardcoded
insert/read via console, before wiring it to the Qt form.
