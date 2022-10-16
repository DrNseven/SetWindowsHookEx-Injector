#include <Windows.h>
#include <iostream>

using namespace std;

int wmain(int argc, wchar_t* argv[], wchar_t* envp[]) {
	wchar_t* dllPath;
	dllPath = argv[1];

	if (GetFileAttributes(dllPath) == INVALID_FILE_ATTRIBUTES) {
		cout << "[ FAILED ] DLL file does not exist." << endl;
		system("pause");
		return EXIT_FAILURE;
	}

	HWND hwnd = FindWindowW(L"UnrealWindow", NULL); //Game window classname
	if (hwnd == NULL) {
		cout << "[ FAILED ] Could not find target window." << endl;
		system("pause");
		return EXIT_FAILURE;
	}

	// Getting the thread of the window and the PID
	DWORD pid = NULL;
	DWORD tid = GetWindowThreadProcessId(hwnd, &pid);
	if (tid == NULL) {
		cout << "[ FAILED ] Could not get thread ID of the target window." << endl;
		system("pause");
		return EXIT_FAILURE;
	}

	// Loading DLL
	HMODULE dll = LoadLibraryEx(dllPath, NULL, DONT_RESOLVE_DLL_REFERENCES); //Loading dll from params
	if (dll == NULL) {
		cout << "[ FAILED ] The DLL could not be found." << endl;
		system("pause");
		return EXIT_FAILURE;
	}

	// Getting exported function address
	HOOKPROC addr = (HOOKPROC)GetProcAddress(dll, "NextHook"); //export see dllmain.cpp "C" __declspec(dllexport) int NextHook(int code, WPARAM wParam, LPARAM lParam)
	if (addr == NULL) {
		cout << "[ FAILED ] The function was not found." << endl;
		system("pause");
		return EXIT_FAILURE;
	}

	// Setting the hook in the hook chain
	HHOOK handle = SetWindowsHookEx(WH_GETMESSAGE, addr, dll, tid); // Or WH_KEYBOARD if you prefer to trigger the hook manually
	if (handle == NULL) {
		cout << "[ FAILED ] Couldn't set the hook with SetWindowsHookEx." << endl;
		system("pause");
		return EXIT_FAILURE;
	}

	// Triggering the hook
	PostThreadMessage(tid, WM_NULL, NULL, NULL);

	// Waiting for user input to remove the hook
	cout << "[ OK ] Hook set and triggered." << endl;
	cout << "[ >> ] Press any key to unhook (This will unload the DLL)." << endl;
	system("pause > nul");

	// Unhooking
	BOOL unhook = UnhookWindowsHookEx(handle);
	if (unhook == FALSE) {
		cout << "[ FAILED ] Could not remove the hook." << endl;
		system("pause");
		return EXIT_FAILURE;
	}

	cout << "[ OK ] Done. Press any key to exit." << endl;
	system("pause > nul");
	return EXIT_SUCCESS;
}
