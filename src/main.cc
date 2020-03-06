#include <Windows.h>
#include <memory>

#include "scene/scene.h"

#define IDM_SCENE_HELLOWORLD 40001
#define IDM_SCENE_BOARD      40002
#define IDM_SCENE_RAY        40003

HMENU create_menu() {
    HMENU h_menu_scenes_basic = CreateMenu();
    AppendMenu(h_menu_scenes_basic, MF_STRING, IDM_SCENE_HELLOWORLD, L"&HelloWorld");
    AppendMenu(h_menu_scenes_basic, MF_STRING, IDM_SCENE_BOARD, L"&Board");

    HMENU h_menu_scenes_ray = CreateMenu();
    AppendMenu(h_menu_scenes_ray, MF_STRING, IDM_SCENE_RAY, L"&Ray");

    HMENU h_menu_scenes = CreateMenu();
    AppendMenu(h_menu_scenes, MF_POPUP, (UINT_PTR)h_menu_scenes_basic, L"&Basic");
    AppendMenu(h_menu_scenes, MF_POPUP, (UINT_PTR)h_menu_scenes_ray, L"&Ray Tracing");

    HMENU h_menu = CreateMenu();
    AppendMenu(h_menu, MF_POPUP, (UINT_PTR)h_menu_scenes, L"&Scenes");

    return h_menu;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    static unique_ptr<Scene> p_scene{ nullptr };

    switch (message) {
    case WM_CREATE: {
        PIXELFORMATDESCRIPTOR pfd ={
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

        HDC hdc = GetDC(hwnd);
        int  iPixelFormat = ChoosePixelFormat(hdc, &pfd);
        SetPixelFormat(hdc, iPixelFormat, &pfd);
        HGLRC hglrc = wglCreateContext(hdc);
        wglMakeCurrent(hdc, hglrc);

        gl_load_proc();

        p_scene = unique_ptr<Scene>(make_unique<SceneBoard>());
        return 0;
    }

    case WM_MOVE:
        return 0;

    case WM_ERASEBKGND:
        return 0;

    case WM_SIZE: {
        RECT rect;
        GetClientRect(hwnd, &rect);
        p_scene->SetViewport(0, 0, rect.right, rect.bottom);
        return 0;
    }

    case WM_KEYDOWN:
        p_scene->KeyDown((int)wParam);
        PostMessage(hwnd, WM_PAINT, 0, 0);
        return 0;

    case WM_COMMAND: {
        switch (LOWORD(wParam)) {
        case IDM_SCENE_HELLOWORLD:
            if (p_scene->Name() != "HelloWorld") {
                p_scene = unique_ptr<Scene>(make_unique<SceneHelloWorld>());
                PostMessage(hwnd, WM_PAINT, 0, 0);
            }
            return 0;
        case IDM_SCENE_BOARD:
            if (p_scene->Name() != "Board") {
                p_scene = unique_ptr<Scene>(make_unique<SceneBoard>());
                PostMessage(hwnd, WM_PAINT, 0, 0);
            }
            return 0;
        case IDM_SCENE_RAY:
            //if (p_scene->Name() != "Ray") {
            //    p_scene = unique_ptr<Scene>(make_unique<SceneRay>());
            //    PostMessage(hwnd, WM_PAINT, 0, 0);
            //}
            return 0;
        default:
            break;
        }
    }

    case WM_PAINT:
#ifdef DEBUG_SHADER
            GLboolean bool_value;
            GLboolean bool_values[4];
            GLint int_value;
            GLint int_values[4];
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
#endif


#ifdef DEBUG_SHADER
			glEndQuery(GL_SAMPLES_PASSED);
			glEndQuery(GL_PRIMITIVES_GENERATED);
			glGetQueryObjectuiv(query[0], GL_QUERY_RESULT, &num[0]);
			glGetQueryObjectuiv(query[1], GL_QUERY_RESULT, &num[1]);
#endif

        PAINTSTRUCT ps;
        BeginPaint(hwnd, &ps);
        p_scene->Draw();
        SwapBuffers(GetDC(hwnd));
        EndPaint(hwnd, &ps);
        return 0;

    case WM_DESTROY:
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
                        create_menu(),
                        hInstance,
                        NULL);

    ShowWindow(hwnd, iCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return static_cast<int>(msg.wParam);
}