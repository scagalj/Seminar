#pragma once


// CUrediRezervaciju dialog

class CUrediRezervaciju : public CDialogEx
{
	DECLARE_DYNAMIC(CUrediRezervaciju)

public:
	CUrediRezervaciju(int rezID, CString check_in, CString check_out,  CWnd* pParent = nullptr);   // standard constructor
	virtual ~CUrediRezervaciju();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_UREDI_REZERVACIJU };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CDateTimeCtrl datum_in;
	CDateTimeCtrl datum_out;
	CString datumin, datumout;
	int rezID;
	afx_msg void OnDtnDatetimechangeDatetimeUrediDatumdolaska(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDtnDatetimechangeDatetimeUrediDatumodlaska(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonDatumProvjera();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
