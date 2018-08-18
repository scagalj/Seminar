#pragma once


// CZaposlenici dialog

class CZaposlenici : public CDialogEx
{
	DECLARE_DYNAMIC(CZaposlenici)

public:
	CZaposlenici(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CZaposlenici();
	void IspisiZaposlenike();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ZAPOSLENIK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int poredak;
	CListCtrl zaposlenici;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonZaposlenikDodaj();
	afx_msg void OnBnClickedButtonZaposlenikIzbrisi();
	afx_msg void OnLvnItemchangedListPopisZaposlenika(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnColumnclickListPopisZaposlenika(NMHDR *pNMHDR, LRESULT *pResult);
	bool SortColumn(int columnIndex, bool ascending);
};
