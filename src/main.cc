#include <Windows.h>
#include <memory>
#include <set>

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
    static unique_ptr<SceneBase> p_scene{ nullptr };

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

        GLint context_flags[7]{
             WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
             WGL_CONTEXT_MINOR_VERSION_ARB, 3,
             WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
             0
             };
        HGLRC hglrc2 = wglCreateContextAttribsARB(hdc, hglrc, context_flags);
        wglMakeCurrent(hdc, hglrc2);
        gl_load_proc();

        //GLint num_extensions{0};
        //set<string> extensions;
        //glGetIntegerv(GL_NUM_EXTENSIONS, &num_extensions);
        //for (int i = 0; i < num_extensions; i++)
        //    extensions.emplace((char*)glGetStringi(GL_EXTENSIONS, i));

        p_scene = unique_ptr<SceneBase>(make_unique<SceneBoard>());
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
                p_scene = unique_ptr<SceneBase>(make_unique<SceneHelloWorld>());
                PostMessage(hwnd, WM_PAINT, 0, 0);
            }
            return 0;
        case IDM_SCENE_BOARD:
            if (p_scene->Name() != "Board") {
                p_scene = unique_ptr<SceneBase>(make_unique<SceneBoard>());
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