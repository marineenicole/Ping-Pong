#include <windows.h>

bool running = true; // Flag to keep the window open

LRESULT CALLBACK WindowCallback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

    // Handles messages for the window
    switch(uMsg) {
        // close or destroy window messages
        case WM_CLOSE:
        case WM_DESTROY: {
            running = false; // Set flag to false for exiting the loop
            PostQuitMessage(0); // Signal the message loop to exit
        } break;

        // Paint message, fills window to white when resizing
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            // redraw the entire client area here
            FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW + 1));
            EndPaint(hwnd, &ps);
        }break;

        default: {
            //  Use default window procedure for unhandled messages
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    }

    return 0;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
        PSTR lpCmdLine, int nCmdShow)
{
    // Create Window Class
    WNDCLASS window_class = {};
    window_class.style = CS_HREDRAW | CS_VREDRAW; // redrawing the window horizontally and vertically
    window_class.lpszClassName = "Ping-Pong Game"; // Names the window
    window_class.lpfnWndProc = WindowCallback;

    // Register Class
    RegisterClass(&window_class); // registers the window class

    // Create Window
    HWND window = CreateWindow(window_class.lpszClassName, "My first Game!!",
              WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT,
              1080, 720, nullptr, nullptr, hInstance, nullptr);

    // Main message loop runs while the game is running
    MSG message;
    while(running && GetMessage(&message, nullptr, 0,0)) {
        // Process messages
        TranslateMessage(&message);
        DispatchMessage(&message);
    }

return 0;
}