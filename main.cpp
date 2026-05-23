#include <windows.h> // for window management i think also Sleep(ms) is useful
#include <string> // pretty self explanatory i hope
#include <cmath> // did you know that cmath actually stands for complex math? actually idk if this is true don't quote me on this lmao
#include <vector> // resizable arrays
#include <thread> // for multithreading - basically doing more than one thing at a time
#include <iostream> // for console debugging


// for keeping track of windows
std::vector<HWND> windows;

enum Window {
    MAIN,
    HEALTH,
    BEWARE
};

void ShowAllWindows() {
    for (HWND window : windows) {
        BringWindowToTop(window);
    }
    BringWindowToTop(windows[0]);
}

// for menu items
enum Menu {
    HMENU_GAME_HELP,
    HMENU_GAME_QUIT,
    
    HMENU_CHEATS_NOCLIP,
    HMENU_CHEATS_GODMODE,
    HMENU_CHEATS_ALLJUMP,
    
    HMENU_WINDOWS_SHOWALLWINDOWS
};
namespace Diamond {
    HWND GetWindow(Window mustvebeenthewind) {return windows[mustvebeenthewind];}

    class Bitmap {
    
    };
}

// this'll be defined later don't worry nvm it has to be defined now
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    std::cout << "message " << uMsg << " " << hwnd << "\n";
    if (!windows.empty()) std::cout << windows[0] << "\n";
    switch (uMsg)
    {
        case WM_CREATE:
            windows.push_back(hwnd);
            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_PAINT:
            {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hwnd, &ps);
                
                // All painting occurs here, between BeginPaint and EndPaint.
                if (hwnd == Diamond::GetWindow(BEWARE)) {
                    FillRect(hdc, &ps.rcPaint, CreateSolidBrush(RGB(0,0,0)));
                    HBRUSH red = CreateSolidBrush(RGB(255,0,0));
                    FillRect(hdc, RECT(), red)
                }
                else {
                    FillRect(hdc, &ps.rcPaint, CreateSolidBrush(RGB(0,255,255)));
                }

                EndPaint(hwnd, &ps);
            }
            return 0;
        // all functions of menu items
        case WM_COMMAND:
            switch ((int)LOWORD(wParam))
            {
                case HMENU_GAME_HELP:
                    ShellExecute(hwnd, "Open", "https://diamondepic.neocities.org", NULL, NULL, SW_SHOWNORMAL);
                    break;
                
                case HMENU_GAME_QUIT:
                    PostQuitMessage(0);

                case HMENU_WINDOWS_SHOWALLWINDOWS:
                    ShowAllWindows();
                
            }
            return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// stuff that runs when the program starts no i totally didn't just copy and paste this from a windows tutorial
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow) {
    // Register the window class. prob used for like easy identification and grouping or smth
    const char CLASS_NAME[]  = "Tohp";
    
    WNDCLASS wc = { };

    wc.lpfnWndProc   = WindowProc; // pointer to the window procedure that basically handles everything after initialization
    wc.hInstance     = hInstance; // handle to the application instance... whatever that means
    wc.lpszClassName = CLASS_NAME; // ignore the errors they are stoopid
    wc.hCursor       = NULL; // i'll deal with this later...
    wc.hIcon         = LoadIcon(hInstance, "MAINICON"); // icon that shows up in the menu. refer to the resource.rc file for the name

    RegisterClass(&wc); // make it go like "yo windows this guy tryna play Tohp" and then windows is like "ok sounds good i'll write that down mkay"

    HMENU hMenu = CreateMenu(); // create the menu for the main window

    // CreateMenu() is also used to make the dropdown menus that go on the menu bar
    HMENU hMenu_Game = CreateMenu();
    HMENU hMenu_Cheats = CreateMenu();
    HMENU hMenu_Windows = CreateMenu();

    // AppendMenu() attaches dropdown menus to the menu bar
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hMenu_Game, "Game");
    // AppendMenu() can also add items to dropdown menus
    AppendMenu(hMenu_Game, MF_STRING, HMENU_GAME_HELP, "Help");
    AppendMenu(hMenu_Game, MF_STRING, HMENU_GAME_QUIT, "Quit");

    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hMenu_Cheats, "Cheats");
    
    AppendMenu(hMenu_Cheats, MF_STRING, HMENU_CHEATS_NOCLIP, "Noclip");
    AppendMenu(hMenu_Cheats, MF_STRING, HMENU_CHEATS_GODMODE, "God Mode");
    AppendMenu(hMenu_Cheats, MF_STRING, HMENU_CHEATS_ALLJUMP, "All Jump");

    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hMenu_Windows, "Windows");

    AppendMenu(hMenu_Windows, MF_STRING, HMENU_WINDOWS_SHOWALLWINDOWS, "Show All Windows");

    int screenwidth = GetSystemMetrics(SM_CXSCREEN);
    int screenheight = GetSystemMetrics(SM_CYSCREEN);

    // ok now we actually create the window
    HWND hwnd = CreateWindowEx(
        WS_EX_CONTEXTHELP,              // Optional window styles. (this one has question mark)
        CLASS_NAME,                     // Window class
        "Tower of hard pillars",        // Window text
        (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU), // Window style (basically like any window except without minimize or maximize buttons)

        // Size and position (x, y, nwidth, nheight)
        (screenwidth - 1024) / 2, (screenheight - 764) / 2, 1024, 764,

        NULL,       // Parent window    
        hMenu,      // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
        );

    HWND hwnd2 = CreateWindowEx(
        0,                           // Optional window styles.
        CLASS_NAME,                     // Window class
        "Health",                       // Window text
        WS_CAPTION,                     // Window style

        // Size and position (x, y, nwidth, nheight)
        (screenwidth + 1124) / 2, (screenheight - 764) / 2, 200, 100,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
        );

    // warning popup that says "YOUR NOT READY..."
    HWND beware = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        "Your not ready...",            // Window text
        WS_POPUP,                       // Window style

        // Size and position (x, y, nwidth, nheight)
        (screenwidth - 400) / 2, (screenheight - 200) / 2, 400, 200,

        NULL,       // Parent window    
        NULL,      // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
        );

    // no window = die
    for (HWND window : windows) {
        if (window == NULL) return 0;
    }

    // now we get to window showing shenanigans
    // create a thread so that you don't just see nothing for 4 seconds
    std::thread opening([beware, hwnd, hwnd2, nCmdShow]() {
        // FreeConsole(); // hide the console that appears for some reason when you open the game
    
        ShowWindow(beware, nCmdShow);
    
        Sleep(4000);
    
        ShowWindow(beware, SW_HIDE);
    
        ShowWindow(hwnd2, nCmdShow); // order matters btw so this shows up behind all
        ShowWindow(hwnd, nCmdShow); // actually makes the window visible

        SetFocus(hwnd);
        return;
    });

    if (opening.joinable()) opening.detach();

    // hot damn i use the word "actually" a lot anyways now message system

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}