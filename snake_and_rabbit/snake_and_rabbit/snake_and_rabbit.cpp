// snake_and_rabbit.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "snake_and_rabbit.h"
#include <cmath>
#include "worm.h"
#include "rabbit.h"

#define MAX_LOADSTRING 100


// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
int setSpeedWorm = 10; //заданная скорость
int prevSpeedWorm = 10; // скорость на предыдущем цикле
int speedRabbit = 10;
int prevSpeedRabbit = 10;
bool snakeDie = 0;
bool reset = 0;


// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    setting(HWND, UINT, WPARAM, LPARAM);
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SNAKEANDRABBIT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SNAKEANDRABBIT));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SNAKEANDRABBIT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SNAKEANDRABBIT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
const unsigned int TIMER_SEC = 1; // идентификатор таймера.
worm* Snake = new worm(500, 500, &snakeDie);
rabbit* LittleWizard = new rabbit();


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static RECT Rect;
	static LOGBRUSH br;
	static HBRUSH brush;


	switch (message)
	{
	case WM_CREATE: // событие "создание окна"
	{
		br.lbStyle = BS_SOLID; //сплошная заливка
		br.lbColor = 0x555500;
		brush = CreateBrushIndirect(&br); // создание кисти
		SetTimer(hWnd, TIMER_SEC, 100, NULL);
		GetClientRect(hWnd, &Rect); // считывание характеристик окна

	}
	break;
	case WM_LBUTTONDOWN: { // событие "нажата левая кнопка мыши" 

		// определение координат клика мыши:
		/*xPos = LOWORD(lParam);
		yPos = HIWORD(lParam);*/

	}
					   break;
	case WM_KEYDOWN: { // событие "нажата кнопка клавиатуры"

		switch (wParam) { // определяет, по какой кнопке что делать

		case VK_LEFT: { // нажата кнопка влево

			Snake->SetStep(-1, 0);

		}
					break;
		case VK_RIGHT: { // нажата кнопка вправо

			Snake->SetStep(1, 0);

		}
					 break;
		case VK_UP: { // нажата кнопка вверх


			Snake->SetStep(-1, 1);

		}
				  break;
		case VK_DOWN: { // нажата кнопка вниз

			Snake->SetStep(1, 1);

		}
					break;
		case VK_SPACE: {

		}
		}

	}
				   break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		
		case ID_32772:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, setting);
				break;
				
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;

	case WM_TIMER: // событие таймера
	{
		//DeathEater->stepSelf();


		InvalidateRect(hWnd, NULL, TRUE); // вызывает событие WM_PAINT 
	}
	break;
	case WM_PAINT: // событие отрисовки окна
	{
		GetClientRect(hWnd, &Rect); // получение характеристик окна, в том числе размеров по х и у

		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps); // получение дескриптора окна
		FillRect(hdc, &Rect, brush); // закрашивание окна цветом фона
		// задание цвета обводки (DC_PEN) и заливки (DC_BRUSH) фигур, которые мы будем рисовать
		SelectObject(hdc, GetStockObject(DC_PEN));
		SetDCPenColor(hdc, RGB(0, 0, 255));
		SelectObject(hdc, GetStockObject(DC_BRUSH));
		SetDCBrushColor(hdc, RGB(0, 255, 255));
		if (setSpeedWorm != prevSpeedWorm) // если новая скорость не равна старой 
		{
			Snake->SetSpeed(setSpeedWorm);
			prevSpeedWorm = setSpeedWorm;
		}
		if (speedRabbit != prevSpeedRabbit) // если новая скорость не равна старой 
		{
			LittleWizard->SpeedRabbit(speedRabbit);
			prevSpeedRabbit = speedRabbit;
		}

		LittleWizard->drawSelf(hdc, Rect.right, Rect.bottom, Snake);
		if (Snake -> IsWormDie())  {
			KillTimer(hWnd, TIMER_SEC);
		}

		//MyDrawt(hdc, wormStartX, wormStartY, Rect.right, Rect.bottom); // Пользовательская функция

		EndPaint(hWnd, &ps); // окончание рисования
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;

    }
    return (INT_PTR)FALSE;
}
INT_PTR CALLBACK setting(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	TCHAR buf[64]; //буфер для приема значений текстовых полей
	wsprintf(buf, _T("%d"), setSpeedWorm);
	UNREFERENCED_PARAMETER(lParam);
	
	switch (message)
	{
	case WM_INITDIALOG:
	  	SetDlgItemText(hDlg, IDC_EDIT1, buf);
		wsprintf(buf, _T("%d"), speedRabbit);
		SetDlgItemText(hDlg, IDC_EDIT2, buf); 
	    CheckDlgButton(hDlg, IDC_CHECK1, snakeDie);
		return (INT_PTR)TRUE;
		
	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_BUTTON1) {
			SetTimer(hDlg, TIMER_SEC, 100, NULL);
		}
		else if (LOWORD(wParam) == IDOK)
			{

				GetDlgItemText(hDlg, IDC_EDIT1, buf, sizeof(buf));
				setSpeedWorm = _ttoi(buf); // измененние скорости змеи
				SetDlgItemText(hDlg, IDC_EDIT1, buf);
				GetDlgItemText(hDlg, IDC_EDIT2, buf, sizeof(buf));
				speedRabbit = _ttoi(buf);
				SetDlgItemText(hDlg, IDC_EDIT2, buf);
				snakeDie = IsDlgButtonChecked(hDlg, IDC_CHECK1);

				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
			else if (LOWORD(wParam) == IDCANCEL) {

				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
			else;
		break;

		
	}
	return (INT_PTR)FALSE;
}IDD_DIALOG1