@ECHO OFF

cl.exe /nologo /W0 detraces_hooking.cpp hooks.cpp /MT /link /DLL detours\lib.X64\detours.lib /export:DetourFinishHelperProcess,@1,NONAME /OUT:build\detraces.dll 
cl.exe /nologo /Ox /MT /W0 /GS- /DNDEBUG /Tp detraces_launcher.cpp /link detours\lib.X64\detours.lib /OUT:build\detraces_launcher.exe /SUBSYSTEM:CONSOLE
cl.exe /nologo /Ox /MT /W0 /GS- /DNDEBUG /Tp detraces_injector.cpp /link detours\lib.X64\detours.lib /OUT:build\detraces_injector.exe /SUBSYSTEM:CONSOLE


cl.exe /nologo /Ox /MT /W0 /GS- /DNDEBUG /Tp target.cpp /link secur32.lib /OUT:build\target.exe /SUBSYSTEM:CONSOLE 


del *.obj build\*.lib build\*.exp