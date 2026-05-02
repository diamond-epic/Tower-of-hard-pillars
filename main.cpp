#include <iostream> // used for printing (cout) and input (cin)
#include <windows.h> // for window management i think
#include <string> // pretty self explanatory i hope
#include <cmath> // did you know that cmath actually stands for complex math? actually idk if this is true don't quote me on this lmao
#include <vector> // resizable arrays
#include <fstream> // file reading

// this'll be defined later don't worry
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// stuff that runs when the program starts
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    // Register the window class.
    const wchar_t CLASS_NAME[]  = L"Tower of hard pillars";

    WNDCLASS wc = { };

    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;
    return 0;
}