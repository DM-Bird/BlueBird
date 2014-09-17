#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <stdio.h>
#include <stdlib.h>


enum
{
  _NET_WM_STATE_REMOVE =0,
  _NET_WM_STATE_ADD = 1,
  _NET_WM_STATE_TOGGLE =2
};

class MainWindow
{
public:
	static MainWindow* GetInstance();
	static MainWindow* g_pInstance;
	Display* GetDisplay();
protected:

private:
	MainWindow();
	~MainWindow();

private:
	Display *g_Display;
	Window *g_MainWindow, *g_RootWindow;
	int m_Screen, Screen_width, Screen_height;
};
