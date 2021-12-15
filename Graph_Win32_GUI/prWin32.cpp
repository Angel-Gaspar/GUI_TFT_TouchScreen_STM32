// prWin32.cpp: define el punto de entrada de la aplicación.
//

#include "stdafx.h"
#include "prWin32.h"
// -------------------------------------COPY FROM HERE -----------------------------------

#include "includes.h"
#include "gui_definplayer.h"
#include "gui_break.h"
#include "gui_score.h"
#include "gui_popupsets.h"
#include "gui_popupspecial.h"
#include "gui_match_conf.h"

volatile _Bool key_pressed;
volatile point16 pt_touched;
HWND hWnd_actual;
extern u32 time_last_asynchr_press;

// -------------------------------------TO HERE -----------------------------------

#define MAX_LOADSTRING 100

// Variables globales:
HINSTANCE hInst;                                // Instancia actual
TCHAR szTitle[MAX_LOADSTRING];                    // text de la barra de título
TCHAR szWindowClass[MAX_LOADSTRING];            // nombre de clase de la ventana principal

// Declaraciones de funciones adelantadas incluidas en este módulo de código:
ATOM                MyRegisterClass(HINSTANCE hInstance);
_Bool                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
        

     // TODO: colocar código aquí.
    MSG msg;
    HACCEL hAccelTable;

    // Inicializar cadenas globales
    LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadString(hInstance, IDC_PRWIN32, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Realizar la inicialización de la aplicación:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PRWIN32));

    // Bucle principal de messages:
    while (GetMessage(&msg, NULL, 0, 0))
    {
        // -------------------------------------COPY FROM HERE -----------------------------------

        if (msg.message == WM_LBUTTONDOWN)
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd_actual, &ps);
			set_hDC (hdc);  
        
			EndPaint(hWnd_actual, &ps);
        }
        // -------------------------------------TO HERE -----------------------------------

        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCIÓN: MyRegisterClass()
//
//  PROPÓSITO: registrar la clase de ventana.
//
//  COMENTARIOS:
//
//    Esta función y su uso son sólo necesarios si desea que el código
//    sea compatible con sistemas Win32 anteriores a la función
//    'RegisterClassEx' que se agregó a Windows 95. Es importante llamar a esta función
//    para que la aplicación obtenga iconos pequeños bien formados
//    asociados a ella.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style            = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra        = 0;
    wcex.cbWndExtra        = 0;
    wcex.hInstance        = hInstance;
    wcex.hIcon            = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PRWIN32));
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground    = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName    = MAKEINTRESOURCE(IDC_PRWIN32);
    wcex.lpszClassName    = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassEx(&wcex);
}

//
//   FUNCIÓN: InitInstance(HINSTANCE, int)
//
//   PROPÓSITO: guardar el identificador de instancia y crear la ventana principal
//
//   COMENTARIOS:
//
//        En esta función, se guarda el identificador de instancia en una variable común y
//        se crea y muestra la ventana principal del programa.
//
_Bool InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Almacenar identificador de instancia en una variable global

   // -------------------------------------COPY FROM HERE -----------------------------------
  
   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
          X_ORG, Y_ORG, LCD_W+19, LCD_H+60, NULL, NULL, hInstance, NULL);

   //   CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }
   ShowWindow(hWnd, SW_SHOW);
   hWnd_actual = hWnd;

   PAINTSTRUCT ps;

   HDC hdc = BeginPaint(hWnd, &ps);
    set_hDC (hdc);

	Initialize_Global_Variables(); 
	
	set_window_match_configuration();
	
    EndPaint(hWnd, &ps);
// ------------------------------------- TO HERE -----------------------------------

   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCIÓN: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PROPÓSITO: procesar messages de la ventana principal.
//
//  WM_COMMAND    : procesar el menú de aplicación
//  WM_PAINT    : pintar la ventana principal
//  WM_DESTROY    : enviar un message de finalización y volver
//
//

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wmId, wmEvent; 	 
	static u32 prev_ms = 0;  // ----------------------------- COPY THIS LINE --------------
    HDC hdc;

    switch (message)
    {
    case WM_COMMAND:
        wmId    = LOWORD(wParam);
        wmEvent = HIWORD(wParam);
        // Analizar las selecciones de menú:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
        break;
    case WM_PAINT:

        break;
    // -------------------------------------COPY FROM HERE -----------------------------------
    case WM_LBUTTONDOWN:
    	   static RECT rcClient;  
		 u32 get_milliseconds(void);
         
         u32 this_ms;
		 this_ms = get_milliseconds() ;
		 if (this_ms - time_last_asynchr_press < 1000)
			 return DefWindowProc(hWnd, message, wParam, lParam);;
		 prev_ms = this_ms;
         GetClientRect(hWnd, &rcClient); 

        // ClipCursor(&rcClient); 
        POINT pt;
        // Save the coordinates of the mouse cursor.  
 
        pt.x = (LONG) LOWORD(lParam); 
        pt.y = (LONG) HIWORD(lParam); 
 
        // If the user has clicked the bitmap rectangle, redraw  
        // it using the dotted pen. Set the fDragRect flag to  
        // indicate that the user is about to drag the rectangle.  
 
        if (PtInRect(&rcClient, pt)) 
        { 
            hdc = GetDC(hWnd); 
            key_pressed = 1;
            point16 pt16;
            pt16.x = (s16)pt.x;
            pt16.y = (s16)pt.y;

			//if (gui.active_window != KEYBOARD){
				manage_touch(pt16);
			//}
            pt_touched.x = pt16.x;
            pt_touched.y = pt16.y;
            ReleaseDC(hWnd, hdc); 
        } 
         break;
         // -------------------------------------TO HERE -----------------------------------
       
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);

    }
    return 0;
}

// Controlador de messages del cuadro Acerca de.
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
