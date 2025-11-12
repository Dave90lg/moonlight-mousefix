#define WIN32_LEAN_AND_MEAN
#define UNICODE
#define _UNICODE
#include <windows.h>
#include <stdio.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (msg == WM_DESTROY) PostQuitMessage(0);
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

void CloseMouseProperties(void) {
    // Try English title first
    HWND hwnd = FindWindow(L"#32770", L"Mouse Properties");
    if (!hwnd) {
        // Some Windows builds/locales use this variation
        hwnd = FindWindow(L"#32770", L"Properties for Mouse");
    } else {
        PostMessage(hwnd, WM_CLOSE, 0, 0);
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrev, LPSTR lpCmdLine, int nShowCmd) {
    const wchar_t CLASS_NAME[] = L"Moonlight MouseFix";

    WNDCLASS wc = {0};
    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0, CLASS_NAME, L"Moonlight MouseFix",
        WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 200,
        NULL, NULL, hInstance, NULL);

    if (!hwnd) return 1;
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    // Display waiting text
    HDC hdc = GetDC(hwnd);
    RECT r; GetClientRect(hwnd, &r);
    DrawText(hdc, L"Waiting 10 seconds before disabling mouse acceleration...",
             -1, &r, DT_CENTER | DT_VCENTER | DT_WORDBREAK);
    ReleaseDC(hwnd, hdc);

    Sleep(10000);   // Wait 1 second

    // --- Close Mouse Properties FIRST ---
    CloseMouseProperties();
    Sleep(500);     // brief delay to let it close cleanly

    // --- Now disable "Enhance pointer precision" ---
    int mouseParams[3] = {0,0,0};
    SystemParametersInfo(SPI_SETMOUSE, 0, mouseParams,
                         SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);
    SystemParametersInfo(SPI_SETMOUSESPEED, 0, (PVOID)10,
                         SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);

    // Optional "done" message for 1 second
    hdc = GetDC(hwnd);
    GetClientRect(hwnd, &r);
    FillRect(hdc, &r, (HBRUSH)(COLOR_WINDOW+1));
    DrawText(hdc, L"Mouse Properties closed.\nAcceleration disabled.\nExiting...",
             -1, &r, DT_CENTER | DT_VCENTER | DT_WORDBREAK);
    ReleaseDC(hwnd, hdc);
    Sleep(1000);

    DestroyWindow(hwnd);
    return 0;
}
