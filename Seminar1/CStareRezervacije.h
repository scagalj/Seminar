#pragma once


// CStareRezervacije dialog

class CStareRezervacije : public CDialogEx
{
	DECLARE_DYNAMIC(CStareRezervacije)

public:
	CStareRezervacije(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CStareRezervacije();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_STARE_REZERVACIJE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl c_stare_rezervacije;
	virtual BOOL OnInitDialog();
	void IspisRezervacija();
};
