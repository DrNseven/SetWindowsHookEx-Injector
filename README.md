# SetWindowsHookEx-Injector
SetWindowsHookEx Injector with d3d11 hook example

- hookloader.exe = injector
- test.dll = dll

hookloader/main.cpp edit:
HWND hwnd = FindWindow(NULL, L"UnrealTournament "); //<-- game window

HMODULE dll = LoadLibraryEx(L"test.dll", NULL, DONT_RESOLVE_DLL_REFERENCES); //<-- DLL

test/dllmain.cpp edit:
what you want, contains hooked D3D11DrawIndexed


