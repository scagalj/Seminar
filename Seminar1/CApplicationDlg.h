#pragma once


// CApplicationDlg dialog

class CApplicationDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CApplicationDlg)

public:
	CApplicationDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CApplicationDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_App };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonLogout();
};
