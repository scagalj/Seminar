#pragma once


// CHoteli dialog

class CHoteli : public CDialogEx
{
	DECLARE_DYNAMIC(CHoteli)

public:
	CHoteli(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CHoteli();
	BOOL OnInitDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_HOTEL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
