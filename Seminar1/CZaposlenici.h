#pragma once


// CZaposlenici dialog

class CZaposlenici : public CDialogEx
{
	DECLARE_DYNAMIC(CZaposlenici)

public:
	CZaposlenici(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CZaposlenici();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ZAPOSLENIK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl zaposlenici;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonZaposlenikDodaj();
	afx_msg void OnBnClickedButtonZaposlenikIzbrisi();
};
