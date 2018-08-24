#pragma once


// CPopisSoba dialog

class CPopisSoba : public CDialogEx
{
	DECLARE_DYNAMIC(CPopisSoba)

public:
	CPopisSoba(const int HotelID, const CString Naziv_Hotela,  CWnd* pParent = nullptr);   // standard constructor
	virtual ~CPopisSoba();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_POPIS_SOBA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl popis_soba;
	BOOL OnInitDialog();
	bool poredak;
	int stupac;
	int p_HotelID;
	CString p_NazivHotela;
	void PopisSoba(int x);
	afx_msg void OnBnClickedButtonPopisIzbrisiSobu();
	afx_msg void OnLvnItemchangedListPopisSoba(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnColumnclickListPopisSoba(NMHDR *pNMHDR, LRESULT *pResult);
	bool SortColumn(int columnIndex, bool ascending);
};
