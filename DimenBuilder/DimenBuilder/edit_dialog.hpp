#ifndef EDIT_DIALOG_HPP
#define EDIT_DIALOG_HPP


class WindowImplBase;
class CEditDialog : public WindowImplBase
{
public:

	CEditDialog(HWND hParent, const tString& name, const tString& adjust);
	~CEditDialog();

	tString GetExceptionName() { return name_; }
	tString GetAdjustRadio() { return adjust_; }
protected:

	LPCTSTR GetWindowClassName() const;	

	virtual void OnFinalMessage(HWND hWnd);

	virtual void Init();

	virtual LRESULT ResponseDefaultKeyEvent(WPARAM wParam);

	virtual tString GetSkinFile();

	virtual tString GetSkinFolder();

	virtual LONG GetStyle();

	virtual CControlUI* CreateControl(LPCTSTR pstrClass);

	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	virtual LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

protected:
	void Notify(TNotifyUI& msg);

	void OnPrepare(TNotifyUI& msg);

private:
	HWND parent_;
	tString name_;
	tString adjust_;
};

#endif EDIT_DIALOG_HPP