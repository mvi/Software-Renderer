/*	
 *	Reference material:
 *		Yves Maurer's GDIRotate
 *		Wolfgang F. Engel's Beginning Direct3D Game Programming
 *		Eric Lengyel's Mathematics for 3D Games Programming & Computer Graphics
 *		Allen Sherrod's Game Graphics Programming
 *
 */

// GDIRotate.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <math.h>
#include "resource.h"
#include <stdlib.h>
#include <stdio.h>
#include "comdef.h"
#include <vector>
#include <iostream>
#include <fstream>
#include "model.h"
#include "Structs.h"
#include "Vector2.h"
#include "Matrix.h"
#include "MathHelper.h"
#include "Camera.h"

#include <windows.h>

#define MAX_LOADSTRING 100

using namespace std;
#include "guicon.h"


// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// The title bar text
float g_angle = 0.2f;							// The current Rotation angle

int framesDrawn=0;

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
void OnKeyDown(WPARAM key);

void InitialiseGeometry();
void Draw3DTriangle(HDC hdc,Vector2 point1, Vector2 point2, Vector2 point3);
Vector3 Project(Vector3 camera, Vector3 target);

//Camera
Matrix world,projection;
Camera camera;

Model model;

bool initialised = false;
void Initialise()
{
	world = Matrix::CreateRotationY(0);
	camera = Camera(Vector3(1200,100,-200),Vector3(0,0,0),Vector3(0,1,0));
	projection = Matrix::CreatePerspectiveFieldOfView(MathHelper::degreeToRadian(45),800/600,0.1,1000 );

	InitialiseGeometry();
}
void InitialiseGeometry()
{
	model = Model("Debug\\Tank.obj");
}


int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	MSG msg;
	HACCEL hAccelTable;

	#ifdef _DEBUG

	RedirectIOToConsole();

	#endif

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_GDIROTATE, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_GDIROTATE);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_GDIROTATE);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCSTR)IDC_GDIROTATE;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   // Initialize the Timer to 100 ms delay between screen updates
   SetTimer(hWnd, 10, 100, 0);
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


// Handler for drawing
void Draw(HWND hWnd)
{
	framesDrawn++;

	if(!initialised)
	{
		Initialise();
		initialised = true;
	}

	PAINTSTRUCT ps;
	HDC hdc;

	hdc = BeginPaint(hWnd, &ps);
	
	HPEN hPen = CreatePen(PS_NULL,0,RGB(0,0,255));
	HGDIOBJ defaultSelectObject = SelectObject(hdc, hPen);
	
	Rectangle(hdc, 0, 0, 1000, 600);
	DeleteObject(hPen);
	hPen = CreatePen(PS_SOLID,5,16711680);
	SelectObject(hdc, hPen);
	DeleteObject(hPen);
	hPen = CreatePen(PS_SOLID,1,RGB(0,0,0));
	SelectObject(hdc,hPen);

	//Project 3d co-ordinates into 2d screen space
	world = Matrix::CreateRotationY(0);
	Matrix view = Matrix::CreateLookAt(camera.eye,camera.target,camera.up);
	projection = Matrix::CreatePerspectiveFieldOfView(MathHelper::degreeToRadian(45),1.25,0.1,1000 );

	Matrix vp = Matrix::Multiply(view,projection);
	Matrix wvp = Matrix::Multiply(world,vp);

	vector<Vector2> points;

	for(int meshIndex=0; meshIndex< model.meshes.size(); meshIndex++)
	{
		for(int i=0;i<model.meshes[meshIndex].vertexBuffer.size();i++)
		{
			Vector3 currentVertex = model.meshes[meshIndex].vertexBuffer.at(i);
			
			//Multiply 3d position by World*View*Projection
			Vector4 a2 = Matrix::MultiplyB(wvp,currentVertex);

			//Homegenous divide
			a2.x /= a2.w;
            a2.y /= a2.w;
            a2.z /= a2.w;

			//NDC to ScreenSpace
            a2.x = ((a2.x + 1) / 2) * 800;
            a2.y = ((1 - a2.y ) / 2) * 600;

			Vector2 screenpoint = Vector2(a2.x,a2.y);

			points.push_back(screenpoint);
		}

		for(int j=0;j<model.meshes[meshIndex].indexBuffer.size();j++)
		{
			Draw3DTriangle(hdc, points.at(model.meshes[meshIndex].indexBuffer.at(j).x-1),points.at(model.meshes[meshIndex].indexBuffer.at(j).y-1),points.at(model.meshes[meshIndex].indexBuffer.at(j).z-1));
		}

	}
	
	DeleteObject(hPen);
	SelectObject(hdc,defaultSelectObject);
	EndPaint(hWnd, &ps);		
}


void Draw3DTriangle(HDC hdc, Vector2 point1, Vector2 point2, Vector2 point3)
{
	MoveToEx(hdc, point1.x, point1.y, NULL);
	LineTo(hdc, point2.x, point2.y);
	LineTo(hdc, point3.x, point3.y);
	LineTo(hdc, point1.x, point1.y);	
}

void OnKeyDown(WPARAM key)
{
	if(key == VK_LEFT)	
		camera.eye = Vector3(camera.eye.x, camera.eye.y, camera.eye.z - 100);	
	if(key == VK_RIGHT)	
		camera.eye = Vector3(camera.eye.x, camera.eye.y, camera.eye.z + 100);	
	if(key == VK_UP)	
		camera.eye = Vector3(camera.eye.x - 100, camera.eye.y, camera.eye.z);	
	if(key == VK_DOWN)	
		camera.eye = Vector3(camera.eye.x + 100, camera.eye.y, camera.eye.z);	
}

  //FUNCTION: WndProc(HWND, unsigned, WORD, LONG)

  //PURPOSE:  Processes messages for the main window.

  //WM_COMMAND	- process the application menu
  //WM_PAINT	- Paint the main window
  //WM_DESTROY	- post a quit message and return

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;

	switch (message) 
	{
		case WM_TIMER:
			// Handle the redraw with the timer
			g_angle = g_angle + .15f;
			RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			break;
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
				case IDM_EXIT:
				   DestroyWindow(hWnd);
				   break;
				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_KEYDOWN:
			OnKeyDown(wParam);
			break;
		case WM_PAINT:
			Draw(hWnd);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}