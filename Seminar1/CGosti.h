#pragma once


// CGosti dialog

class CGosti : public CDialogEx
{
	DECLARE_DYNAMIC(CGosti)

public:
	CGosti(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CGosti();
	void IspisiGoste();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_GOST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	bool poredak;
	int stupac;
	CListCtrl gosti;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonDodajGosta();
	afx_msg void OnLvnColumnclickListGosti(NMHDR *pNMHDR, LRESULT *pResult);
	bool SortColumn(int columnIndex, bool ascending);
	afx_msg void OnLvnItemchangedListGosti(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonGostIzbrisi();
};
