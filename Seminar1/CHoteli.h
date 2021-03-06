#pragma once


// CHoteli dialog

class CHoteli : public CDialogEx
{
	DECLARE_DYNAMIC(CHoteli)

public:
	CHoteli(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CHoteli();
	BOOL OnInitDialog();
	void IspisiHotele();
	void Ugasibotune(bool ispit);
	CString HotelID(int x);


// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_HOTEL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl hoteli;
	CString h_trazi;
	bool poredak;
	int stupac;
	afx_msg void OnBnClickedButtonAddHotel();
	afx_msg void OnBnClickedButtonDeleteHotel();
	afx_msg void OnBnClickedButtonHotelTrazi();
	afx_msg void OnBnClickedButtonDodajSobu();
	afx_msg void OnLvnItemchangedListHoteli(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonPopisSoba();
	afx_msg void OnLvnColumnclickListHoteli(NMHDR *pNMHDR, LRESULT *pResult);
	bool SortColumn(int columnIndex, bool ascending);
};
