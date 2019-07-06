
#include <Windows.h>
#include <memory>

#include "scene.h"

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")

static HDC   hdc   = NULL;
static HGLRC hglrc = NULL;
static Scene* p_scene = NULL;

void release_glrc() {
    if (hglrc != NULL) {
        wglMakeCurrent(NULL, NULL);
        wglDeleteContext(hglrc);
        hglrc = NULL;
    }
}

void init_glrc(HWND hwnd) {
    release_glrc();

    PIXELFORMATDESCRIPTOR pfd = { 
        sizeof(PIXELFORMATDESCRIPTOR),   // size of this pfd  
        1,                     // version number  
        PFD_DRAW_TO_WINDOW |   // support window  
        PFD_SUPPORT_OPENGL |   // support OpenGL  
        PFD_DOUBLEBUFFER,      // double buffered  
        PFD_TYPE_RGBA,         // RGBA type  
        24,                    // 24-bit color depth  
        0, 0, 0, 0, 0, 0,      // color bits ignored  
        8,                     // no alpha buffer  
        0,                     // shift bit ignored  
        0,                     // no accumulation buffer  
        0, 0, 0, 0,            // accum bits ignored  
        32,                    // 32-bit z-buffer  
        0,                     // no stencil buffer  
        0,                     // no auxiliary buffer  
        0,                      // main layer  
        0,                     // reserved  
        0, 0, 0                // layer masks ignored  
    }; 

    hdc = GetDC(hwnd);
    int  iPixelFormat = ChoosePixelFormat(hdc, &pfd);
    SetPixelFormat(hdc, iPixelFormat, &pfd);
    hglrc = wglCreateContext(hdc);
    wglMakeCurrent(hdc, hglrc);
	gl_load_proc();
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {

    switch (message) {
    case WM_CREATE:
        //init_glrc(hwnd);
        return 0;

    case WM_MOVE:
        //init_glrc(hwnd);
        return 0;

    case WM_SIZE:
        init_glrc(hwnd);
		p_scene = new HelloWorldScene();
        return 0;

    case WM_PAINT:
        if (hglrc != NULL) {

            GLboolean bool_value;
            GLboolean bool_values[4];
            GLint int_value;
            GLint int_values[4];
            GLfloat float_value;
            GLfloat float_values[4];

            glGetIntegerv(GL_MAJOR_VERSION, &int_value);
            glGetIntegerv(GL_MINOR_VERSION, &int_value);
            glGetBooleanv(GL_BLEND, &bool_value);
            glGetIntegerv(GL_COLOR_CLEAR_VALUE, int_values);
            glGetBooleanv(GL_COLOR_LOGIC_OP, &bool_value);
            glGetIntegerv(GL_LOGIC_OP_MODE, &int_value);
            glGetBooleanv(GL_COLOR_WRITEMASK, bool_values);
            glGetBooleanv(GL_CULL_FACE, &bool_value);
            glGetIntegerv(GL_CULL_FACE_MODE, &int_value);
            glGetIntegerv(GL_CURRENT_PROGRAM, &int_value);
            glGetBooleanv(GL_DEPTH_TEST, &bool_value);
            glGetBooleanv(GL_DEPTH_WRITEMASK, &bool_value);
            glGetIntegerv(GL_DEPTH_CLEAR_VALUE, &int_value);
            glGetBooleanv(GL_DOUBLEBUFFER, &bool_value);
            glGetBooleanv(GL_DRAW_BUFFER, &bool_value);



			GLuint query[2];
			GLuint num[2];
			glGenQueries(2, query);
			glBeginQuery(GL_SAMPLES_PASSED, query[0]);
			glBeginQuery(GL_PRIMITIVES_GENERATED, query[1]);

            p_scene->Draw();

			glEndQuery(GL_SAMPLES_PASSED);
			glEndQuery(GL_PRIMITIVES_GENERATED);
			glGetQueryObjectuiv(query[0], GL_QUERY_RESULT, &num[0]);
			glGetQueryObjectuiv(query[1], GL_QUERY_RESULT, &num[1]);

            SwapBuffers(hdc);
        }

        PAINTSTRUCT ps;
        BeginPaint(hwnd, &ps);
        EndPaint(hwnd, &ps);
        return 0;

    case WM_DESTROY:
        release_glrc();
		delete p_scene;
        ReleaseDC(hwnd, hdc);
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
    static TCHAR szAppName[] = TEXT("HelloWin");
    HWND        hwnd;
    MSG         msg;
    WNDCLASS    wndclass;

    wndclass.style              = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wndclass.lpfnWndProc        = WndProc;
    wndclass.cbClsExtra         = 0;
    wndclass.cbWndExtra         = 0;
    wndclass.hInstance          = hInstance;
    wndclass.hIcon              = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor            = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground      = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName       = NULL;
    wndclass.lpszClassName      = szAppName;

    if (!RegisterClass(&wndclass)) {
        MessageBox(NULL, TEXT("This program requires Windows NT!"), szAppName, MB_ICONERROR);
        return 0;
    }

    hwnd = CreateWindow(szAppName,
                        TEXT("The Hello Program"),
                        WS_OVERLAPPEDWINDOW,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        NULL,
                        NULL,
                        hInstance,
                        NULL);

    ShowWindow(hwnd, iCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}