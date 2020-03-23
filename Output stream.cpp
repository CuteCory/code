
#include <iostream>
#include <thread>
#include <fstream>
#include <string>
#include <Windows.h>

using namespace std;


int ispeed;
void ctrl()
{
	ispeed = 10;
}

// Clipboard
int clip(string strT)
{
	cout << strT << endl;

	if (OpenClipboard(NULL))
	{
		HGLOBAL hClip;
		char* chBuffer;
		int iBuff_size;

		EmptyClipboard();

		iBuff_size = strlen(strT.c_str());
		hClip = GlobalAlloc(GMEM_DDESHARE, iBuff_size + 1);
		chBuffer = (char*)GlobalLock(hClip);

		lstrcpy(chBuffer, LPCSTR(strT.c_str()));
		GlobalUnlock(hClip);

		SetClipboardData(CF_TEXT, hClip);
		CloseClipboard();
	}

	return 0;
}

int main()
{
	thread tCtrl(ctrl);

	string strPath;
	cout << " TextFile path:  ";
	cin >> strPath;

	Sleep(5000);

	ifstream iText(strPath);
	string strLineText;
	POINT CurPoint;
	HWND hCurrent;
	while (getline(iText, strLineText))
	{
		GetCursorPos(&CurPoint);
		hCurrent = WindowFromPoint(CurPoint);

		if (!clip(strLineText))
		{
			SendMessage(hCurrent, WM_PASTE, NULL, NULL);
			SendMessage(hCurrent, WM_KEYDOWN, VK_RETURN, NULL);
		}

		Sleep(ispeed);
	}

	iText.close();

	tCtrl.join();

}

