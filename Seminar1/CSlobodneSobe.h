#pragma once


// CSlobodneSobe dialog

class CSlobodneSobe : public CDialogEx
{
	DECLARE_DYNAMIC(CSlobodneSobe)

public:
	CSlobodneSobe(const CString name, CWnd* pParent = nullptr);   // standard constructor
	virtual ~CSlobodneSobe();


// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SLOBODNE_SOBE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDtnDatetimechangeDatetimepickerSobe(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonSlobodneSobePrikaz();
	afx_msg void OnDtnDatetimechangeDatetimepickerCout(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	void IspisSobe(long sobaid);
	CListCtrl c_list_sobe;
	CComboBox c_hoteli;
	CDateTimeCtrl t_SlobodneSobe;
	CDateTimeCtrl t_slobodnesobe_out;
	CString datumin;
	CString datumout;
	CString korisnik;
	int poredak;
	afx_msg void OnBnClickedButtonNovaRezervaciju();
	afx_msg void OnLvnColumnclickListSlobodneSobePopis(NMHDR *pNMHDR, LRESULT *pResult);
	bool SortColumn(int columnIndex, bool ascending);
};
