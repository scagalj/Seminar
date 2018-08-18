#pragma once


// CPopisSoba dialog

class CPopisSoba : public CDialogEx
{
	DECLARE_DYNAMIC(CPopisSoba)

public:
	CPopisSoba(CWnd* pParent = nullptr);   // standard constructor
	explicit CPopisSoba(const int &HotelID, const CString &Naziv_Hotela, CWnd* pParent);
	virtual ~CPopisSoba();
	BOOL OnInitDialog();
	int p_HotelID,poredak;
	CString p_NazivHotela;
	void PopisSoba(int x);

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_POPIS_SOBA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl popis_soba;
	afx_msg void OnBnClickedButtonPopisIzbrisiSobu();
	afx_msg void OnLvnItemchangedListPopisSoba(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnColumnclickListPopisSoba(NMHDR *pNMHDR, LRESULT *pResult);
	bool SortColumn(int columnIndex, bool ascending);
};
