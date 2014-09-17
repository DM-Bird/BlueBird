#include <X11/X.h>
#include <X11/Xlib.h>
#include<X11/Xutil.h>
#include <stdio.h>
#include <stdlib.h>

enum
{
  _NET_WM_STATE_REMOVE =0,
  _NET_WM_STATE_ADD = 1,
  _NET_WM_STATE_TOGGLE =2
};

int main(int argc, char* argv[])
{
 Display *m_display;
 int m_screen,window_width, window_height;
 Window m_window, m_rootWindow;

 unsigned long theWindowMask;
 theWindowMask = CWBackPixel|CWBorderPixel;

 m_display = XOpenDisplay(NULL);
 if( NULL == m_display)
 {
        fprintf(stderr, "Cannot open display\n");
        exit(1);
 }

 m_screen = DefaultScreen(m_display);
 window_width = DisplayWidth(m_display, m_screen);
 window_height = DisplayHeight(m_display, m_screen);

 XSetWindowAttributes attr;
 attr.border_pixel = BlackPixel(m_display,m_screen);
 attr.background_pixel= WhitePixel(m_display,m_screen);
 attr.override_redirect = True;
 attr.event_mask = ExposureMask | KeyPressMask;

 m_rootWindow = RootWindow(m_display, m_screen);

 //m_window = XCreateSimpleWindow(m_display, RootWindow(m_display, m_screen),0,0, 640,480,1,BlackPixel(m_display,m_screen),WhitePixel(m_display, m_screen));
 //m_window = XCreateWindow(m_display, RootWindow(m_display, m_screen), 0, 0, window_width, window_height, 2, CopyFromParent, InputOutput, CopyFromParent, theWindowMask, &attr);
 m_window = XCreateWindow(m_display, m_rootWindow, 0, 0, window_width, window_height, 0, CopyFromParent, InputOutput, CopyFromParent, theWindowMask, &attr);
 XSelectInput(m_display, m_window, ExposureMask | KeyPressMask);
 XMapWindow(m_display, m_window);

 XEvent xev;
 while(1)
 {
  XNextEvent(m_display, &xev);
  if(xev.type == Expose)
  {
   XFillRectangle(m_display, m_window, DefaultGC(m_display, m_screen), 0, 0, window_width, window_height);

   Atom wmState = XInternAtom(m_display, "_NET_WM_STATE", False);
   Atom fullScreen = XInternAtom(m_display, "_NET_WM_STATE_FULLSCREEN", False);
   xev.xclient.type = ClientMessage;
   xev.xclient.serial = 0;
   xev.xclient.window = m_window;
   xev.xclient.message_type = wmState;
   xev.xclient.format = 32;
   xev.xclient.data.l[0] = _NET_WM_STATE_ADD;
   xev.xclient.data.l[1] = fullScreen;
   xev.xclient.data.l[2] = 0;
   XSendEvent(m_display, RootWindow(m_display,m_screen),False,SubstructureRedirectMask | SubstructureNotifyMask | ResizeRedirectMask,&xev);
  }
  else if(xev.type == KeyPress)
  {
	  if(xev.xkey.keycode == XKeysymToKeycode(m_display,XK_F1))
	  {
		XDestroyWindow(m_display, m_screen);
		XCloseDisplay(m_display);
		//exit(0);
		break;
	  }
  }
 }

 return 0;
}

