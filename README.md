# Detraces
Detraces is a proof of concept that demostrates the use of Microsoft Research's [Detours](https://github.com/microsoft/Detours) package to replicate, to some extent, the behavior of Linux tools like `strace` or `ltrace` on Windows.

This project is purely educational, it's just a way to get my hands dirty on Windows internals, API hooking and native, low level-ish development.

## Components
- `detraces_hooking.cpp`: The actual API hooking code
- `detraces_launcher.cpp`: Detours' [withdll.cpp](https://github.com/microsoft/Detours/blob/main/samples/withdll/withdll.cpp) with minimal modifications. Used to inject the `detraces_hooking` dll into the target process 
- `target.cpp`: Just a sample target executable, used to test everything

## Actual Capabilities
Detraces can now intercept and show calls to the following functions:
- Winuser
    - GetForegroundWindow
    - GetWindowTextA
    - MessageBoxA
- File API
    - CreateFileA

After the initial PoC stage, the goal will be to implement function call tracing in a scalable and dynamic way.