#include "stdafx.h"
#include <windows.h>
#if !defined(UNDER_CE)
#include <shellapi.h>
#endif

#include "resource.h"
#include "win_impl_base.hpp"
#include "layered_window.hpp"
#include "container_window_impl.hpp"

// http://hi.baidu.com/mygmh/blog/item/dfff43094813f3d63ac7636d.html
// http://hi.baidu.com/mygmh/blog/item/81fe9c0ed6eb4cff36d12285.html
// http://hi.baidu.com/mygmh/blog/item/d6c86f36094239c5a2cc2ba3.html
// http://www.codeproject.com/KB/dialog/PerfectTranlucentDlg.aspx

LayeredWindow::LayeredWindow()
: container_window_(NULL)
, shadow_image_(NULL)
, m_nShadow(0)
, m_bAutoDelete(FALSE)
{}

LayeredWindow::~LayeredWindow()
{
	memset(&m_rcPadding, 0, sizeof(RECT));
}

LPCTSTR LayeredWindow::GetWindowClassName() const
{
	return _T("LayeredWindow");
}

void LayeredWindow::OnFinalMessage(HWND hWnd)
{
	if (m_bAutoDelete && shadow_image_)
		delete shadow_image_;
	shadow_image_ = NULL;

	delete this;
}

tString LayeredWindow::GetSkinFolder()
{
	return tString();
}

tString LayeredWindow::GetSkinFile()
{
	return tString();
}

LRESULT LayeredWindow::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LONG styleValue = ::GetWindowLong(m_hWnd, GWL_STYLE);
	styleValue &= ~( WS_CAPTION | WS_MAXIMIZEBOX | WS_SIZEBOX );
	::SetWindowLong(m_hWnd, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

	RECT rcClient = {0};
	::GetClientRect(m_hWnd, &rcClient);
	::SetWindowPos(m_hWnd, NULL, rcClient.left, rcClient.top, rcClient.right - rcClient.left, \
		rcClient.bottom - rcClient.top, SWP_FRAMECHANGED);

	//HDWP hDWP = BeginDeferWindowPos(1);
	//hDWP = DeferWindowPos(hDWP,m_hWnd, NULL, rcClient.left, rcClient.top, rcClient.right - rcClient.left, \
	//	rcClient.bottom - rcClient.top, SWP_FRAMECHANGED);
	//hDWP = DeferWindowPos(hDWP,container_window_->GetHWND(), NULL, rcClient.left, rcClient.top, rcClient.right - rcClient.left, \
	//	rcClient.bottom - rcClient.top, SWP_FRAMECHANGED);
	//EndDeferWindowPos(hDWP);

	Init();
	return 0;
}

void LayeredWindow::Notify(TNotifyUI& msg)
{
}

LRESULT LayeredWindow::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	return 0L;
}

LRESULT LayeredWindow::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return HTCAPTION;

	LRESULT ret = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
	if (ret == HTCLIENT)
		return HTCAPTION;
	return ret;
}

LRESULT LayeredWindow::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CWindowWnd::HandleMessage(uMsg, wParam, lParam);

	RepaintLayeredWnd();
	InvalidateRect(m_hWnd, NULL, TRUE);

	return 0L;
}

LRESULT LayeredWindow::OnWindowPosChanged(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LRESULT ret = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
	WINDOWPOS* lpwndpos = reinterpret_cast<WINDOWPOS*>(lParam);
	if (lpwndpos != NULL)
	{
		if (container_window_ && container_window_->GetHWND() && (!(lpwndpos->flags & SWP_NOMOVE) || !(lpwndpos->flags & SWP_NOSIZE)) )
		{
			RECT rcWindow = {0};
			::GetWindowRect(container_window_->GetHWND(), &rcWindow);
			RECT rect;
			::GetWindowRect(m_hWnd, &rect);
			if ((rcWindow.left != (rect.left + m_nShadow + m_rcPadding.left))
				|| ((rcWindow.top != (rect.top + m_nShadow + m_rcPadding.top))))
			{
				//SetWindowPos(container_window_->GetHWND(), NULL, 
				//rect.left + m_nShadow + m_rcPadding.left, 
				//rect.top + m_nShadow + m_rcPadding.top, 
				//0/*rect.right - rect.left + (2 * m_nShadow + m_rcPadding.right + m_rcPadding.left)*/, 
				//0/*rect.bottom - rect.top + (2 * m_nShadow + m_rcPadding.bottom + m_rcPadding.top)*/,
				//SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOSENDCHANGING);

				HDWP hDWP = BeginDeferWindowPos(1);
				//hDWP = DeferWindowPos(hDWP,m_hWnd, NULL, 
				//	rect.left + m_nShadow + m_rcPadding.left, 
				//	rect.top + m_nShadow + m_rcPadding.top, 
				//	0/*rect.right - rect.left + (2 * m_nShadow + m_rcPadding.right + m_rcPadding.left)*/, 
				//	0/*rect.bottom - rect.top + (2 * m_nShadow + m_rcPadding.bottom + m_rcPadding.top)*/,
				//	SWP_NOZORDER | 
				//	SWP_NOACTIVATE | 
				//	SWP_NOSIZE //| SWP_NOSENDCHANGING
				//	);
				hDWP = DeferWindowPos(hDWP,container_window_->GetHWND(), NULL, 
					rect.left + m_nShadow + m_rcPadding.left, 
					rect.top + m_nShadow + m_rcPadding.top, 
					0/*rect.right - rect.left + (2 * m_nShadow + m_rcPadding.right + m_rcPadding.left)*/, 
					0/*rect.bottom - rect.top + (2 * m_nShadow + m_rcPadding.bottom + m_rcPadding.top)*/,
					SWP_NOZORDER | 
					SWP_NOACTIVATE | 
					SWP_NOSIZE //| SWP_NOSENDCHANGING
					
					//SWP_NOACTIVATE | SWP_NOZORDER 
					//|SWP_NOMOVE
					);
				EndDeferWindowPos(hDWP);
			}

		}
	}

	return ret;
}


LRESULT LayeredWindow::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	switch (wParam)
	{
	case SC_CLOSE:
		break;
	case SC_MAXIMIZE:
		break;
	case SC_MINIMIZE:
		::ShowWindow(m_hWnd, SW_HIDE);
		break;
	default:
		break;
	}

	return CWindowWnd::HandleMessage(uMsg, wParam, lParam);;
}

LRESULT LayeredWindow::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	PAINTSTRUCT ps;
	HDC hDC = ::BeginPaint(m_hWnd, &ps);
	RepaintLayeredWnd(hDC);
	::EndPaint(m_hWnd, &ps);
	return 0L;
}

void LayeredWindow::Init()
{
	RepaintLayeredWnd();
}

void LayeredWindow::SetShadowInfo(Bitmap* pShadowImage, int nShadow, BOOL bAutoDelete, const RECT& rcPadding, BOOL bUpdate)
{
	if ( m_bAutoDelete && shadow_image_ )
		delete shadow_image_;
	shadow_image_ = NULL;
	if (pShadowImage)
		shadow_image_ = pShadowImage;
	m_nShadow = nShadow;
	m_bAutoDelete = bAutoDelete;
	m_rcPadding = rcPadding;
	if (bUpdate && m_hWnd )
	{
		RepaintLayeredWnd();
	}
}

void LayeredWindow::SetContainerWindow(ContainerWindowImpl* pContainerWindow)
{
	container_window_ = pContainerWindow;
	if (container_window_ && container_window_->GetHWND())
		container_window_->SetLayeredWindow(this);
}

void LayeredWindow::LayoutWindow(RECT rect)
{
	RECT rcWindow = {0};
	::GetWindowRect(m_hWnd, &rcWindow);
	if ((rcWindow.left != (rect.left - (m_nShadow + m_rcPadding.left)))
		|| ((rcWindow.top != (rect.top - (m_nShadow + m_rcPadding.top)))))
	{
		//SetWindowPos(m_hWnd, NULL, 
		//rect.left - (m_nShadow + m_rcPadding.left), 
		//rect.top - (m_nShadow + m_rcPadding.top), 
		//0/*rect.right - rect.left + (2 * m_nShadow + m_rcPadding.right + m_rcPadding.left)*/, 
		//0/*rect.bottom - rect.top + (2 * m_nShadow + m_rcPadding.bottom + m_rcPadding.top)*/,
		//SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOSENDCHANGING);

		HDWP hDWP = BeginDeferWindowPos(1);
		hDWP = DeferWindowPos(hDWP,m_hWnd, NULL, 
			rect.left - (m_nShadow + m_rcPadding.left), 
			rect.top - (m_nShadow + m_rcPadding.top), 
			0/*rect.right - rect.left + (2 * m_nShadow + m_rcPadding.right + m_rcPadding.left)*/, 
			0/*rect.bottom - rect.top + (2 * m_nShadow + m_rcPadding.bottom + m_rcPadding.top)*/,
			SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOSIZE //| SWP_NOSENDCHANGING
			);
		//hDWP = DeferWindowPos(hDWP,container_window_->GetHWND(), NULL, 
		//	rect.left - (m_nShadow + m_rcPadding.left), 
		//	rect.top - (m_nShadow + m_rcPadding.top), 
		//	0/*rect.right - rect.left + (2 * m_nShadow + m_rcPadding.right + m_rcPadding.left)*/, 
		//	0/*rect.bottom - rect.top + (2 * m_nShadow + m_rcPadding.bottom + m_rcPadding.top)*/,
		//	SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOSENDCHANGING);
		EndDeferWindowPos(hDWP);
	}

}

void LayeredWindow::RepaintLayeredWnd(HDC hDC)
{
	BOOL bRelease = FALSE;
	if (!hDC)
	{
		hDC = ::GetWindowDC(m_hWnd);
		bRelease = TRUE;
	}

	if (shadow_image_)
	{
		RECT rect;
		GetWindowRect(m_hWnd, &rect);
		int cx = rect.right - rect.left;
		int cy = rect.bottom - rect.top;
		int w = shadow_image_->GetWidth();
		int h = shadow_image_->GetHeight();
		if( h > 0 && w > 0  && cx > 0 && cy > 0 )
		{
			HBITMAP hBitmap = ::CreateCompatibleBitmap(hDC, cx, cy);
			HDC hMemDC = ::CreateCompatibleDC(hDC);
			HBITMAP hOldBitmap = (HBITMAP)::SelectObject(hMemDC, hBitmap);

			Graphics g(hMemDC);
			g.DrawImage(shadow_image_, Rect(0, 0, cx, cy));

			POINT ptWinPos = { rect.left, rect.top }, ptSrc = { 0, 0 };
			SIZE sizeWindow = { cx, cy };
			BLENDFUNCTION blendFunc= { AC_SRC_OVER, 0, 254, AC_SRC_ALPHA };
			::UpdateLayeredWindow(m_hWnd, hDC, &ptWinPos, &sizeWindow, hMemDC, &ptSrc, 0, &blendFunc, ULW_ALPHA);

			::SelectObject(hMemDC, hOldBitmap);
			::DeleteObject(hBitmap);
			::DeleteDC(hMemDC);
		}
	}
	if ( bRelease )
		::ReleaseDC(m_hWnd, hDC);
}