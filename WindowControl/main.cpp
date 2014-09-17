/************************************************
* File Name:main.cpp
* Author: Easymoon
* mail:
* Create Time:2014-09-18
************************************************/

#include "MainWindow.h"

MainWindow* MainWindow::g_pInstance = NULL;

int main(int argc, char* argv[])
{
	MainWindow* mainWindow = MainWindow::GetInstance();
	return 0;
}
