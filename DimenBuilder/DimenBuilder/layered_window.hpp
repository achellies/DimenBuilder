#ifndef LAYERED_WINDOW_HPP
#define LAYERED_WINDOW_HPP

#include <gdiplus.h>
#pragma comment( lib, "gdiplus.lib" ) 
using namespace Gdiplus;

class WindowImplBase;
class ContainerWindowImpl;
class LayeredWindow : public WindowImplBase
{
public:

	LayeredWindow();
	~LayeredWindow();

public:

	LPCTSTR GetWindowClassName() const;	

	virtual void OnFinalMessage(HWND hWnd);

	virtual LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual LRESULT OnWindowPosChanged(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual void Init();

	void SetShadowInfo(Bitmap* pShadowImage, int nShadow, BOOL bAutoDelete, const RECT& rcPadding, BOOL bUpdate = TRUE);

	void SetContainerWindow(ContainerWindowImpl* pContainerWindow);

	void LayoutWindow(RECT rect);

	void RepaintLayeredWnd(HDC hDC = NULL);

protected:
	void Notify(TNotifyUI& msg);

	virtual tString GetSkinFolder();
	virtual tString GetSkinFile();


private:
	// ¿Ø¼þµÄÈÝÆ÷
	ContainerWindowImpl* container_window_;

	Bitmap*	shadow_image_;

	int		m_nShadow;
	BOOL	m_bAutoDelete;
	RECT	m_rcPadding;
};

#endif // LAYERED_WINDOW_HPP