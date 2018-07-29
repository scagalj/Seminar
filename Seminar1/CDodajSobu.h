#pragma once


// CDodajSobu dialog

class CDodajSobu : public CDialogEx
{
	DECLARE_DYNAMIC(CDodajSobu)

public:
	CDodajSobu(CWnd* pParent = nullptr);   // standard constructor
	explicit CDodajSobu(const int &HotelID,const CString &Naziv_Hotela, CWnd* pParent);
	virtual ~CDodajSobu();
	BOOL OnInitDialog();
	int s_HotelID;
	CString s_NazivHotela;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DODAJ_SOBU };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CComboBox vrsta_soba;
	CString s_vrsta_soba;
	afx_msg void OnCbnSelchangeComboSobaVrsta();
	BOOL s_duhan;
	BOOL s_ljubimci;
	afx_msg void OnBnClickedButtonDodajSobu();
};
