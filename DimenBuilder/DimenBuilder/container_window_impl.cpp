#include "stdafx.h"
#include <windows.h>
#if !defined(UNDER_CE)
#include <shellapi.h>
#endif

#include "resource.h"
#include "win_impl_base.hpp"
#include "layered_window.hpp"
#include "container_window_impl.hpp"

ContainerWindowImpl::ContainerWindowImpl()
: layered_window_(NULL)
, m_global(NULL)
, m_stream(NULL)
{}

LPCTSTR ContainerWindowImpl::GetWindowClassName() const
{
	return _T("ContainerWindowImpl");
}

void ContainerWindowImpl::OnFinalMessage(HWND hWnd)
{
	if (layered_window_ != NULL)
	{
		layered_window_->Close();
		layered_window_ = NULL;
	}

	WindowImplBase::OnFinalMessage(hWnd);

	if (layered_window_ != NULL)
	{
		layered_window_->Close();
		layered_window_ = NULL;
	}

	if (m_global != NULL)
	{
		::GlobalUnlock(m_global);
		::GlobalFree(m_global);
	}

	delete this;
}

LRESULT ContainerWindowImpl::OnWindowPosChanged(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LRESULT ret = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
	WINDOWPOS* lpwndpos = reinterpret_cast<WINDOWPOS*>(lParam);
	if (lpwndpos != NULL)
	{
		if (layered_window_ && layered_window_->GetHWND() && (!(lpwndpos->flags & SWP_NOMOVE) || !(lpwndpos->flags & SWP_NOSIZE)) )
		{
			RECT rect;
			::GetWindowRect(m_hWnd, &rect);
			layered_window_->LayoutWindow(rect);
		}
	}

	return ret;
}

void ContainerWindowImpl::SetLayeredWindow(LayeredWindow* pLayeredWindow)
{
	layered_window_ = pLayeredWindow;
}