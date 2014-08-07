#ifndef CONTAINER_WINDOW_IMPL_HPP
#define CONTAINER_WINDOW_IMPL_HPP

class WindowImplBase;
class LayeredWindow;
class ContainerWindowImpl : public WindowImplBase
{
public:

	ContainerWindowImpl();

public:

	LPCTSTR GetWindowClassName() const;	

	virtual void OnFinalMessage(HWND hWnd);

	virtual LRESULT OnWindowPosChanged(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	void SetLayeredWindow(LayeredWindow* pContainerWindow);

protected:	

protected:
	LayeredWindow*	layered_window_;
	HGLOBAL m_global;
	IStream* m_stream;
};

#endif // CONTAINER_WINDOW_IMPL_HPP