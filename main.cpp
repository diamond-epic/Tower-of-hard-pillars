#include <iostream> // used for printing (cout) and input (cin)
#include <windows.h> // for window management i think
#include <string> // pretty self explanatory i hope
#include <cmath> // did you know that cmath actually stands for complex math? actually idk if this is true don't quote me on this lmao
#include <vector> // resizable arrays
#include <fstream> // file reading

// this'll be defined later don't worry nvm it has to be defined now
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            // All painting occurs here, between BeginPaint and EndPaint.

            FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));

            EndPaint(hwnd, &ps);
        }
        return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// stuff that runs when the program starts no i totally didn't just copy and paste this from a windows tutorial
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow) {
    // Register the window class. prob used for like easy identification and grouping or smth
    const char CLASS_NAME[]  = "Tower of hard pillars";

    WNDCLASS wc = { };

    wc.lpfnWndProc   = WindowProc; // pointer to the window procedure that basically handles everything after initialization
    wc.hInstance     = hInstance; // handle to the application instance... whatever that means
    wc.lpszClassName = CLASS_NAME; // i mean... it says it ight there
    wc.hCursor       = NULL; // i'll deal with this later...
    wc.hIcon         = NULL; // same with this...

    RegisterClass(&wc); // make it go like "yo windows this guy tryna play Tohp" and then windows is like "ok sounds good i'll write that down mkay"

    // ok now we actually create the window
    HWND hwnd = CreateWindowEx(
        WS_EX_CONTEXTHELP,              // Optional window styles. (this one has question mark)
        CLASS_NAME,                     // Window class
        "Tower of hard pillars",       // Window text
        (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME), // Window style (basically like any window except without minimize or maximize buttons)

        // Size and position (x, y, nwidth, nheight)
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
        );

    if (hwnd == NULL) // no window = die
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow); // actually makes the window visible

    // hot damn i use the word "actually" a lot anyways now message system

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}