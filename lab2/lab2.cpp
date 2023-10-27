#include <windows.h>//заголовочный файл, в котором находится описание основных функций Windows API
#include<windowsx.h>//заголовочный файл, в котором находится подключение дополнительных библиотек для работы с графикой.
#include "CBall.h" //пределения класса CBall
#include "CHLimiter.h"
#include "CVLimiter.h"

HINSTANCE g_hInstance; //это дескриптор экземпляра или дескриптор модуля. Операционная система использует это значение для идентификации исполняемого файла или EXE - файла при загрузке в память
int g_nCmdShow;//это флаг, указывающий, является ли основное окно приложения свернуто, развернуто или отображается в обычном режиме.

HWND g_mainWnd;//для определения дескриптора главного кода
CBall b1(10, 10, 150, 150, 50);//создание объекта типа CBall с именем b1 и передача конструктору координат, размеров и скорости
CHLimiter h1(250, 350, 300);//горизонтальное препятствие
CVLimiter v1(250, 350, 500);//верт. препятствие

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); //Объявление прототипа функции WndProc, которая является обработчиком сообщений для главного окна
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_DESTROY://Если окно уничтожается
	{
		PostQuitMessage(0);
		return 0;
	}
	case WM_PAINT: {
		HDC hDC;
		PAINTSTRUCT ps;
		hDC = BeginPaint(hWnd, &ps);
		b1.Draw(hDC);
		h1.Draw(hDC);
		v1.Draw(hDC);
		EndPaint(hWnd, &ps);
		return 0;
	}
	case WM_SIZE://При изменении размеров окна
	{
		RECT rect;
		rect.top = 0;
		rect.left = 0;
		rect.bottom = HIWORD(lParam);
		rect.right = LOWORD(lParam);
		b1.SetBounds(rect);
		return 0;
	}
	case WM_KEYDOWN://обработка и генерация реакции на нажатие клавиш для препятствия
	{
		switch (wParam) {
		case VK_DOWN:
			v1.MoveY(5);
			return 0;
		case VK_UP:
			v1.MoveY(-5);
			return 0;
		case VK_LEFT:
			v1.MoveX(5);
			return 0;
		case VK_RIGHT:
			v1.MoveX(-5);
			return 0;
		}
		break;
	}
	default:
		break;

	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

BOOL InitAppClass() {// Определение функции, которая инициализирует класс приложения. Она создает и регистрирует класс окна с помощью структуры WNDCLASS и функций LoadIcon(), LoadCursor(), GetStockObject() и RegisterClass()
	ATOM class_id;
	WNDCLASS wc;
	memset(&wc, 0, sizeof(wc));
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = g_hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszClassName = L"lab2";
	class_id = RegisterClass(&wc);

	if (class_id != 0)
		return TRUE;
	return FALSE;
}

BOOL InitWindow() { // Определение функции InitWindow(), которая инициализирует главное окно, используя функцию CreateWindow().Она устанавливает различные параметры окна, такие как заголовок, стиль, расположение и размеры.Затем окно отображается с помощью ShowWindow() и обновляется с помощью UpdateWindow()
	g_mainWnd = CreateWindow(L"lab2", L"Лабораторная работа №2",
		WS_OVERLAPPEDWINDOW, //стиль окна: перекрывающееся окно
		CW_USEDEFAULT, CW_USEDEFAULT,
		400, 400,
		0, 0, //родительское окно и дескриптор меню
		g_hInstance, //дескриптор экземпляра
		0);
	if (!g_mainWnd) return FALSE;
	ShowWindow(g_mainWnd, g_nCmdShow);
	UpdateWindow(g_mainWnd);

	return TRUE;
}

void OnIdle() { //вызываться тогда, когда сообщений в очереди нет
	DWORD ticks = GetTickCount();

	b1.Move(ticks);
	InvalidateRect(g_mainWnd, NULL, TRUE);
}

WPARAM StartMessageLoop() { // цикл обработки сообщений
	MSG msg;
	while (1) {
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT)
				break;
			DispatchMessage(&msg);
		}
		else {
			Sleep(20);
			OnIdle();
		}
	}
	return msg.wParam;
}

//BOOL Ellipse//Объявление прототипа функции Ellipse, которая рисует эллипс на указанном контексте рисования (hdc) внутри описывающего прямоугольника, определенного четырьмя координатами
//	HDC hdc,
//	int nLeftrect,
//	int nTopRect,
//	int nRightRect,
//	int nBottomRect
//);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) { //Точка входа приложения
	g_hInstance = hInstance;
	g_nCmdShow = nCmdShow;

	if (!InitAppClass())
		return 0;

	if (!InitWindow())
		return 0;

	RECT cr;
	GetClientRect(g_mainWnd, &cr);
	b1.SetBounds(cr);
	b1.SetHLimiter(&h1);
	b1.SetVLimiter(&v1);
	return StartMessageLoop();
}

