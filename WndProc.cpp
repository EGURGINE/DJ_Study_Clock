#include "pch.h"
#include "WndProc.h"

#define TIME01 1001
#define _1_SEC_ 1000

HFONT hFont[2];
TCHAR g_strTime[128] = L"";

int hour = 0;
int min = 0;
int sec = 0;

int OnPaint(HWND hWnd, WPARAM wParam, LPARAM lParam);
int OnTimer(HWND hWnd, WPARAM wParam, LPARAM lParam);

int OnCreate(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    SetTimer(hWnd, TIME01, _1_SEC_, NULL);
    SendMessage(hWnd, WM_TIMER, TIME01, 0);

    hFont[0] = CreateFont(20, 0, 0, 0, 0, 0, 0, 0,
        HANGEUL_CHARSET, 3, 2, 1,
        VARIABLE_PITCH | FF_ROMAN, L"굴림체");
    hFont[1] = CreateFont(20, 0, 0, 0, 0, 0, 0, 0,
        HANGEUL_CHARSET, 3, 2, 1,
        VARIABLE_PITCH | FF_ROMAN, L"궁서체");
    return 0;
}

int OnTimer(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    SYSTEMTIME st;
    GetLocalTime(&st);
    hour = st.wHour;
    min = st.wMinute;
    sec = st.wSecond;


    SetWindowTextW(hWnd, g_strTime);
    InvalidateRect(hWnd, NULL, false);
    return 0;
}

int OnPaint(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);
    // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
//*

//*/
    TextOut(hdc, 100, 100, g_strTime, wcslen(g_strTime));
    //NumOutput(hdc, 0, 0, 9, 20);
    SelectObject(hdc, (HFONT)hFont[0]);
   /* SelectObject(hdc, (HFONT)hFont[1]);
    DrawNumber(hdc, 40, 0, 0, 9875443);*/
    SetTextColor(hdc, RGB(rand() % 236, rand() % 236, rand() % 236));

    if (hour>=10) DrawNumber(hdc, 40, 80, 60, hour);
    else
    {
        DrawNumber(hdc, 40, 80, 60, 0);
        DrawNumber(hdc, 40, 210, 60, hour);

    }    
    SetTextColor(hdc, RGB(rand() % 236, rand() % 236, rand() % 236));

    if (min>=10) DrawNumber(hdc, 40, 350, 60, min);
    else
    {
        DrawNumber(hdc, 40, 350, 60, 0); 
        DrawNumber(hdc, 40, 480, 60, min);
    }
    SetTextColor(hdc, RGB(rand() % 236, rand() % 236, rand() % 236));

    if (sec>=10) DrawNumber(hdc, 40, 650, 60, sec);
    else
    {
        DrawNumber(hdc, 40, 650, 60, 0);
        DrawNumber(hdc, 40, 780, 60, sec);
    }

    EndPaint(hWnd, &ps);
    return 0;
}

int OnDestroy(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    DeleteObject(hFont[0]);
    DeleteObject(hFont[1]);

    KillTimer(hWnd, TIME01);
    PostQuitMessage(0);
    return 0;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE: return OnCreate(hWnd, wParam, lParam);
    case WM_TIMER:  return OnTimer(hWnd, wParam, lParam);
    case WM_PAINT:  return OnPaint(hWnd, wParam, lParam);
    case WM_DESTROY:return OnDestroy(hWnd, wParam, lParam);
    default:        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
