# Detraces
Detraces is a proof of concept that demostrates the use of Microsoft Research's [Detours](https://github.com/microsoft/Detours) package to replicate, to some extent, the behavior of Linux tools like `strace` or `ltrace` on Windows.

This project is purely educational, it's just a way to get my hands dirty on Windows internals, API hooking and native, low level-ish development.

## Components
- `detraces_hooking.cpp`: The actual API hooking code
- `detraces_launcher.cpp`: Detours' [withdll.cpp](https://github.com/microsoft/Detours/blob/main/samples/withdll/withdll.cpp) with minimal modifications. Used to start the target process and inject the `detraces_hooking` dll at launch
- `detraces_injector.cpp`: Inject the `detraces_hooking.dll` into an already executing process
- `target.cpp`: Just a sample target executable, used to test everything

## Actual Capabilities
Detraces can now intercept and show calls to the following functions:
- Winuser
    - GetForegroundWindow
    - GetWindowTextA
    - MessageBoxA
- File API
    - CreateFileA
    - WriteFile
    - ReadFile

After the initial PoC stage, the goal will be to implement function call tracing in a scalable and dynamic way.

## The Past and the Future of this project
After watching [this video by antirez](https://www.youtube.com/watch?v=1FW8uzTQGxs), I have changed my mind a bit about this "side project". 

What's the point of developing something to learn, as I previously wrote, "Windows internals, API hooking and native, low level development", using a 25 years old library that does the very thing I'm trying to learn? 

Hell no, being the best in using a library is something I can accomplish with 2 queries to ChatGPT. I want to be better than this. Following this commit, I'll try to implement detours myself. It will be orders of magnitude more difficult, and changces are that this project will go out of the window, but if I don't do this now, when?