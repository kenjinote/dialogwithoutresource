#include <windows.h>

INT_PTR CALLBACK DlgWndProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			PostQuitMessage(0);
			return TRUE;
		}
		break;
	}
	return FALSE;
}

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
	static BYTE test[] =
	{
		/* Dialog header */
		0x01,0x00, /* Version */
			0xff,0xff, /* Extended template marker */
			0x00,0x00,0x00,0x00, /* Context Help ID */
			0x00,0x00,0x00,0x00, /* Extended style */
			0xc0,0x00,0xc8,0x80, /* Style (WS_SYSMENU|WS_CAPTION|WS_POPUP|DS_SETFONT|DS_MODALFRAME) */
			0x01,0x00, /* Control count */
			0x00,0x00, /* X */
			0x00,0x00, /* Y */
			0xF0,0x00, /* Width */
			0x80,0x00, /* Height */
			0x00,0x00, /* Menu name */
			0x00,0x00, /* Class name */
			'T',0x00,'e',0x00, /* Caption (unicode) */
			's',0x00,'t',0x00,
			0x00,0x00,
			0xff,0x7f, /* Font height (0x7fff = message box font) */

			/* Control #1 */
			0x00,0x00, /* Align to DWORD (header is 42 bytes) */
			0x00,0x00,0x00,0x00, /* Context Help ID */
			0x00,0x00,0x00,0x00, /* Extended style */
			0x00,0x00,0x00,0x50, /* Style (WS_CHILD|WS_VISIBLE) */
			0x00,0x00, /* X */
			0x00,0x00, /* Y */
			0xF0,0x00, /* Width */
			0x80,0x00, /* Height */
			0xff,0xff,0xff,0xff, /* Control ID */
			0xff,0xff,0x82,0x00, /* Class (Static) */
			'H',0x00,'e',0x00, /* Caption (unicode) */
			'l',0x00,'l',0x00,
			'o',0x00,',',0x00,
			' ',0x00,'W',0x00,
			'o',0x00,'r',0x00,
			'l',0x00,'d',0x00,
			'!',0x00,'!',0x00,
			'!',0x00,'!',0x00,
			'!',0x00,0x00,0x00,
			0x00,0x00, /* Size of extended data */

			0x00,0x00 /* Align to DWORD */
	};
	// メインダイアログ生成

	HWND hDlg = CreateDialogIndirect(GetModuleHandle(0), (LPCDLGTEMPLATE)&test, 0, DlgWndProc);

	HMONITOR hMonitor;
	MONITORINFO mi;
	RECT rcWnd;
	RECT rcMon;
	POINT posMouse;
	GetWindowRect(hDlg, &rcWnd);
	GetCursorPos(&posMouse);
	hMonitor = MonitorFromPoint(posMouse, MONITOR_DEFAULTTONEAREST);
	mi.cbSize = sizeof(mi);
	GetMonitorInfo(hMonitor, &mi);
	rcMon = mi.rcMonitor;
	rcWnd.left = rcMon.left + ((rcMon.right - rcMon.left) - (rcWnd.right - rcWnd.left)) / 2;
	rcWnd.top = rcMon.top + ((rcMon.bottom - rcMon.top) - (rcWnd.bottom - rcWnd.top)) / 2;
	SetWindowPos(hDlg, 0, rcWnd.left, rcWnd.top, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);

	MSG msg;
	STARTUPINFO si;
	si.dwFlags = 0;
	GetStartupInfo(&si);
	ShowWindow(hDlg, si.dwFlags & STARTF_USESHOWWINDOW ? si.wShowWindow : SW_SHOWDEFAULT);
	UpdateWindow(hDlg);
	while (GetMessage(&msg, 0, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}
