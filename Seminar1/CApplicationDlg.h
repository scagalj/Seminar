#pragma once


// CApplicationDlg dialog

class CApplicationDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CApplicationDlg)

public:
	CApplicationDlg(CWnd* pParent = nullptr); // standard constructor
	explicit CApplicationDlg(const CString &name, CWnd* pParent);
	virtual ~CApplicationDlg();
	BOOL OnInitDialog();
	CString user;
	int poredak;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_App };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl c_rezervacije_danas;
	void IspisRezervacija();
	afx_msg void OnBnClickedButtonLogout();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButtonHotel();
	afx_msg void OnBnClickedButtonZaposlenik();
	afx_msg void OnBnClickedButtonGost();
	afx_msg void OnBnClickedButtonSlobodneSobe();
	afx_msg void OnBnClickedButtonRezervacije();
	afx_msg void OnBnClickedButtonOsvjezi();
	afx_msg void OnLvnColumnclickListDRezervacije(NMHDR *pNMHDR, LRESULT *pResult);
	bool SortColumn(int columnIndex, bool ascending);
};
