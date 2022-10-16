# SetWindowsHookEx-Injector
SetWindowsHookEx Injector with example

- hookloader.exe = injector
- test.dll = example dll


1. Just add this to your dll:
extern "C" __declspec(dllexport) int NextHook(int code, WPARAM wParam, LPARAM lParam) {
	return CallNextHookEx(NULL, code, wParam, lParam);
}

2. Edit your game window in hookloader/main.cpp:
HWND hwnd = FindWindow(L"UnrealWindow", NULL); //<-- game window class example for valorant here

3. Compile & done

Usage: hookloader.exe (dllname).dll or drag (dllname).dll into hookloader.exe

UC Thread: https://www.unknowncheats.me/forum/valorant/518015-p100-dll-injector.html
