#include "MainWindow.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

MainWindow* MainWindow::GetInstance()
{
	if(NULL == g_pInstance)
		g_pInstance = new MainWindow();
	return g_pInstance;
}

MainWindow::MainWindow()
{
	//std::cout << "hello~!" << std::endl;
	
	g_Display = XOpenDisplay(NULL);
	if(NULL == g_Display)
	{
		fprintf(stderr, "Cannot open Display\n");
		exit(1);
	}

	m_Screen = DefaultScreen(g_Display);
	Screen_width = DisplayWidth(g_Display, m_Screen);
	Screen_height = DisplayHeight(g_Display, m_Screen);

	XSetWindowAttributes attr;
	attr.border_pixel = BlackPixel(g_Display, m_Screen);
	attr.background_pixel = WhitePixel(g_Display, m_Screen);
	attr.override_redirect = True;
	attr.event_mask = ExposureMask | KeyPressMask;

	unsigned long theWindowMask;
	theWindowMask = CWBackPixel|CWBorderPixel;

	g_RootWindow = &(RootWindow(g_Display, m_Screen));

	Window tmp_MainWindow = XCreateWindow(g_Display, *g_RootWindow, 0, 0, Screen_width, Screen_height, 0, CopyFromParent, InputOutput, CopyFromParent, theWindowMask, &attr);
	g_MainWindow = &tmp_MainWindow;

	XSelectInput(g_Display, *(g_MainWindow), ExposureMask | KeyPressMask);
	XMapWindow(g_Display, *(g_MainWindow));

	XEvent xev;
	while(1)
	{
		XNextEvent(g_Display, &xev);
		if(xev.type == Expose)
		{
			XFillRectangle(g_Display, *(g_MainWindow), DefaultGC(g_Display, m_Screen), 0, 0, Screen_width, Screen_height);
			Atom wmState =  XInternAtom(g_Display, "_NET_WM_STATE", False);
			Atom fullScreen = XInternAtom(g_Display, "_NET_WM_STATEFULLSCREEN", False);
		
			xev.xclient.type = ClientMessage;
			xev.xclient.serial = 0;
			xev.xclient.window = *g_MainWindow;
			xev.xclient.message_type = wmState;
			xev.xclient.format = 32;
			xev.xclient.data.l[0] = _NET_WM_STATE_ADD;
			xev.xclient.data.l[1] = fullScreen;
			xev.xclient.data.l[2] = 0;
		
			XSendEvent(g_Display, *g_RootWindow, False, SubstructureRedirectMask | SubstructureNotifyMask | ResizeRedirectMask, &xev);
		}
		else if(xev.type == KeyPress)
		{
			if(xev.xkey.keycode == XKeysymToKeycode(g_Display,XK_F1))
			{
				XDestroyWindow(g_Display, m_Screen);
				XCloseDisplay(g_Display);
				break;
			}
		}
	}
}

MainWindow::~MainWindow()
{
	//std::cout << "bye~!" << std::endl;
}

Display* MainWindow::GetDisplay()
{
	return g_Display;
}
