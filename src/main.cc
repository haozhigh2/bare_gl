
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")

static HDC   hdc   = NULL;
static HGLRC hglrc = NULL;

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
        0,                     // no alpha buffer  
        0,                     // shift bit ignored  
        0,                     // no accumulation buffer  
        0, 0, 0, 0,            // accum bits ignored  
        32,                    // 32-bit z-buffer  
        0,                     // no stencil buffer  
        0,                     // no auxiliary buffer  
        PFD_MAIN_PLANE,        // main layer  
        0,                     // reserved  
        0, 0, 0                // layer masks ignored  
    }; 

    hdc = GetDC(hwnd);
    int  iPixelFormat = ChoosePixelFormat(hdc, &pfd);
    SetPixelFormat(hdc, iPixelFormat, &pfd);
    hglrc = wglCreateContext(hdc);
    wglMakeCurrent(hdc, hglrc);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_CREATE:
        init_glrc(hwnd);
        return 0;

    case WM_MOVE:
        init_glrc(hwnd);
        return 0;

    case WM_SIZE:
        init_glrc(hwnd);
        return 0;

    case WM_PAINT:
        if (hglrc != NULL) {
            GLfloat light_diffuse[] ={ 1.0, 0.0, 0.0, 1.0 };  /* Red diffuse light. */
            GLfloat light_position[] ={ 1.0, 1.0, 1.0, 0.0 };  /* Infinite light location. */
            GLfloat n[6][3] ={  /* Normals for the 6 faces of a cube. */
              {-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0},
              {0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0} };
            GLint faces[6][4] ={  /* Vertex indices for the 6 faces of a cube. */
              {0, 1, 2, 3}, {3, 2, 6, 7}, {7, 6, 5, 4},
              {4, 5, 1, 0}, {5, 6, 2, 1}, {7, 4, 0, 3} };
            GLfloat v[8][3];  /* Will be filled in with X,Y,Z vertexes. */

             /* Setup cube vertex data. */
              v[0][0] = v[1][0] = v[2][0] = v[3][0] = -1;
              v[4][0] = v[5][0] = v[6][0] = v[7][0] = 1;
              v[0][1] = v[1][1] = v[4][1] = v[5][1] = -1;
              v[2][1] = v[3][1] = v[6][1] = v[7][1] = 1;
              v[0][2] = v[3][2] = v[4][2] = v[7][2] = 1;
              v[1][2] = v[2][2] = v[5][2] = v[6][2] = -1;
            
              /* Enable a single OpenGL light. */
              glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
              glLightfv(GL_LIGHT0, GL_POSITION, light_position);
              glEnable(GL_LIGHT0);
              glEnable(GL_LIGHTING);
            
              /* Use depth buffering for hidden surface elimination. */
              glEnable(GL_DEPTH_TEST);
            
              /* Setup the view of the cube. */
              glMatrixMode(GL_PROJECTION);
              gluPerspective( /* field of view in degree */ 40.0,
                /* aspect ratio */ 1.0,
                /* Z near */ 1.0, /* Z far */ 10.0);
              glMatrixMode(GL_MODELVIEW);
              gluLookAt(0.0, 0.0, 5.0,  /* eye is at (0,0,5) */
                0.0, 0.0, 0.0,      /* center is at (0,0,0) */
                0.0, 1.0, 0.);      /* up is in positive Y direction */
            
              /* Adjust cube position to be asthetic angle. */
              glTranslatef(0.0, 0.0, -1.0);
              glRotatef(60, 1.0, 0.0, 0.0);
              glRotatef(-20, 0.0, 0.0, 1.0);

              glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

              for (int i = 0; i < 6; i++) {
                  glBegin(GL_QUADS);
                  glNormal3fv(&n[i][0]);
                  glVertex3fv(&v[faces[i][0]][0]);
                  glVertex3fv(&v[faces[i][1]][0]);
                  glVertex3fv(&v[faces[i][2]][0]);
                  glVertex3fv(&v[faces[i][3]][0]);
                  glEnd();
              }

            SwapBuffers(hdc);
        }

        PAINTSTRUCT ps;
        BeginPaint(hwnd, &ps);
        EndPaint(hwnd, &ps);
        return 0;

    case WM_DESTROY:
        release_glrc();
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