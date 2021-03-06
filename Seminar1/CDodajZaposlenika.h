#pragma once


// CDodajZaposlenika dialog

class CDodajZaposlenika : public CDialogEx
{
	DECLARE_DYNAMIC(CDodajZaposlenika)

public:
	CDodajZaposlenika(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDodajZaposlenika();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DODAJ_ZAPOSLENIK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString m_Kor_Oznaka;
	CString m_Ime;
	CString m_Lozinka;
	CString m_Prezime;
	CString m_Adresa;
	CString m_Grad;
	CString m_Drzava;
	CString m_Kontakt;
};
