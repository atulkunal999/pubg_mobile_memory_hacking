#include "Main.h"
#include "pch.h"


int Width = GetSystemMetrics(SM_CXSCREEN);
int Height = GetSystemMetrics(SM_CYSCREEN);

const MARGINS Margin = { -1 };

char lWindowName[256] = "Its Random";
HWND hWnd;

char tWindowName[256] = "Gameloop【Turbo AOW Engine】";
HWND tWnd;

RECT tSize;
MSG Message;

FILE* f;
void AConsole()
{
	AllocConsole();
	freopen_s(&f, "CONOUT$", "w", stdout);
}
void gen_random(char* s, const int len) {
	srand(time(NULL));
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

	for (int i = 0; i < len; ++i) {
		s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
	}

	s[len] = 0;
}
void initall()
{
	//g_pEsp->viewWordBase = base;
	int ProcessId = ProcManager::getAowProcID();
	if (!ProcessId)
	{
		MessageBox(0, "Game Loop Not Found Exiting...","Error",MB_OK);
		exit(1);
	}
	g_pMemoryManager->init(ProcessId, false);
	if (!g_pMemoryManager->DriverLoaded) {
		MessageBox(0, "Error Loading Driver", "Error", MB_OK);
		exit(1);
	}
	g_pEsp->viewWordBase = g_pEsp->getViewWorld();
	g_pEsp->GetModuleBaseAddress(ProcessId, "aow_exe.exe");
	g_pEsp->GetMagic();
	g_pEsp->initMagic();
	g_pEsp->init();
}
LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{	
	case WM_PAINT:
		Render();
		break;

	case WM_CREATE:
		DwmExtendFrameIntoClientArea(hWnd, &Margin);
		break;

	case WM_DESTROY:
		PostQuitMessage(1);
		return 0;

	default:
		return DefWindowProc(hWnd, Message, wParam, lParam);
		break;
	}
	return 0;
}

std::vector<std::string> SplitString(char str[])
{
	std::vector<std::string> retstr;

	char* token = strtok(str, " ");
 
	while (token != NULL)
	{
		retstr.push_back(token);
		token = strtok(NULL, " ");
	}
	return retstr;
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hSecInstance, LPSTR nCmdLine, INT nCmdShow)
{
	std::string argv = GetCommandLineA();
	std::vector<std::string> splited = SplitString(GetCommandLineA());
	int vtadds = 0;
	//MessageBoxA(0, argv.c_str(), std::to_string(splited.size()).c_str(), MB_OK);
	
	char* logkey = new char[32];
	std::string enterdkey = "";
	//AConsole();
	if (false)
	{
		std::cout << termcolor::blue << "COPY THE KEY AND PRESS OK " << termcolor::reset;
		gen_random(logkey, 32);
		std::string linkChar = "https://shrinkearn.com/st?api=9e7699d679c6140314c6f4cd195fe708a26f4df6&url=http://urlecho.appspot.com/echo?body=";
		linkChar.append(logkey);
		ShellExecute(NULL, NULL, linkChar.c_str(), NULL, NULL, SW_SHOWNORMAL);
		MessageBoxA(0, "Copy Key and Press Ok", "", MB_OK);

		HANDLE h;
		if (!OpenClipboard(NULL))
			std::cout << "Can't open clipboard";
		h = GetClipboardData(CF_TEXT);
		enterdkey = (char*)h;
		CloseClipboard();

		if (strcmp(logkey, enterdkey.c_str()) != 0)
		{
			std::cout << termcolor::red << "Error : Wrong Key" << termcolor::reset;
			MessageBoxA(0, "WRONG KEY", "", 0);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		AConsole();
	}

	initall();
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)SetWindowToTarget, 0, 0, 0);
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)aimbotload, 0, 0, 0);

	ZeroMemory(lWindowName, sizeof(lWindowName));
	srand(time(NULL));
	gen_random(lWindowName, (rand() % 30) + 2);

	WNDCLASSEX wClass;
	wClass.cbClsExtra = NULL;
	wClass.cbSize = sizeof(WNDCLASSEX);
	wClass.cbWndExtra = NULL;
	wClass.hbrBackground = (HBRUSH)CreateSolidBrush(D3DCOLOR_ARGB(0, 0, 0, 0));
	wClass.hCursor = LoadCursor(0, IDC_ARROW);
	wClass.hIcon = LoadIcon(0, IDI_APPLICATION);
	wClass.hIconSm = LoadIcon(0, IDI_APPLICATION);
	wClass.hInstance = hInstance;
	wClass.lpfnWndProc = WinProc;
	wClass.lpszClassName = lWindowName;
	wClass.lpszMenuName = lWindowName;
	wClass.style = CS_VREDRAW | CS_HREDRAW;

	if(!RegisterClassEx(&wClass))
		exit(1);

	tWnd = FindWindow(0, tWindowName);
	if (!IsWindow(tWnd))
	{
		char tWindowName2[256] = "Gameloop【Turbo AOW Engine-4.4】";
		ZeroMemory(tWindowName, 256);
		memcpy(tWindowName, tWindowName2, sizeof(tWindowName2));
		tWnd = FindWindow(0, tWindowName);
	}
	if (IsWindow(tWnd))
		tWnd = FindWindowEx(tWnd, NULL, "AEngineRenderWindowClass", NULL);
	if (tWnd)
	{
		GetWindowRect(tWnd, &tSize);
		Width = tSize.right - tSize.left;
		Height = tSize.bottom - tSize.top;
		hWnd = CreateWindowEx(WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED, lWindowName, lWindowName,  WS_POPUP, tSize.left, tSize.top, Width, Height, 0, 0, 0, 0);
		SetLayeredWindowAttributes(hWnd, 0, 255, LWA_ALPHA);
		//SetLayeredWindowAttributes(hWnd, 0, RGB(0, 0, 0), LWA_COLORKEY);
		ShowWindow( hWnd, SW_NORMAL);
	}

	DirectXInit(hWnd);
	LoadFont();
	UpdateWindow(hWnd);
	for (;;)
	{
		if(PeekMessage(&Message, hWnd, 0, 0, PM_REMOVE))
		{
			DispatchMessage(&Message);
			TranslateMessage(&Message);
		}
	}
	return Message.wParam;
}


void SetWindowToTarget()
{
	while(true)
	{
		tWnd = FindWindow(0, tWindowName);
		if (!IsWindow(tWnd))
		{
			char tWindowName2[256] = "Gameloop【Turbo AOW Engine-4.4】";
			ZeroMemory(tWindowName, 256);
			memcpy(tWindowName, tWindowName2, sizeof(tWindowName2));
			tWnd = FindWindow(0, tWindowName);
		}
		if (IsWindow(tWnd))
			tWnd = FindWindowEx(tWnd, NULL, "AEngineRenderWindowClass", NULL);
		if (tWnd)
		{
			GetWindowRect(tWnd, &tSize);
			Width = tSize.right - tSize.left;
			Height = tSize.bottom - tSize.top;
			DWORD dwStyle = GetWindowLong(tWnd, GWL_EXSTYLE);
			if(dwStyle & WS_BORDER)
			{
				tSize.top += 23;
				Height -= 23;
			}
			MoveWindow(hWnd, tSize.left, tSize.top, Width, Height, true);
		}
		else
		{
			char ErrorMsg[125];
			sprintf(ErrorMsg, "Make sure %s is running!", tWindowName);
			MessageBox(0, ErrorMsg, "Error - Cannot find the game!", MB_OK | MB_ICONERROR);
			exit(1);
		}
		g_pEsp->update();
		GetKey();
		Sleep(5);
	}
}
