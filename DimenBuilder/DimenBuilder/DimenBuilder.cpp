//
// main.cpp
// ~~~~~~~~
//
// Copyright (c) 2012 achellies (achellies at 163 dot com)
//
// This code may be used in compiled form in any way you desire. This
// source file may be redistributed by any means PROVIDING it is 
// not sold for profit without the authors written consent, and 
// providing that this notice and the authors name is included. 
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability if it causes any damage to you or your
// computer whatsoever. It's free, so don't hassle me about it.
//
// Beware of bugs.
//

#include "stdafx.h"
#include "win_impl_base.hpp"
#include "layered_window.hpp"
#include "container_window_impl.hpp"
#include "main_frame.hpp"

#include <gdiplus.h>
#pragma comment( lib, "gdiplus.lib" ) 
using namespace Gdiplus;

#if defined(WIN32) && !defined(UNDER_CE)
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
#else
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpCmdLine, int nCmdShow)
#endif
{
	GdiplusStartupInput g_gdiplusStartupInput;
	ULONG_PTR g_gdiplusToken;

	CPaintManagerUI::SetInstance(hInstance);

#if defined(WIN32) && !defined(UNDER_CE)
	HRESULT Hr = ::CoInitialize(NULL);
#else
	HRESULT Hr = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
#endif
	if( FAILED(Hr) ) return 0;

	::GdiplusStartup(&g_gdiplusToken, &g_gdiplusStartupInput, NULL);

//	MainFrame* pFrame = new MainFrame();
//	if( pFrame == NULL ) return 0;
//#if defined(WIN32) && !defined(UNDER_CE)
//	pFrame->Create(NULL, _T("DimenBuilder"), UI_WNDSTYLE_FRAME, WS_EX_STATICEDGE | WS_EX_APPWINDOW, CRect());
//#else
//	pFrame->Create(NULL, _T("DimenBuilder"), UI_WNDSTYLE_FRAME, WS_EX_TOPMOST, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
//#endif
//	pFrame->CenterWindow();
//	::ShowWindow(*pFrame, SW_SHOW);
	MainFrame frame;
	frame.InitLayeredWindow();

	CPaintManagerUI::MessageLoop();

	::GdiplusShutdown(g_gdiplusToken);

	return 0;
}