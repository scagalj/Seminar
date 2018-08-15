#pragma once


// CDodajGosta dialog

class CDodajGosta : public CDialogEx
{
	DECLARE_DYNAMIC(CDodajGosta)

public:
	CDodajGosta(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDodajGosta();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DODAJ_GOSTA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	int id;
	CString m_Ime;
	CString m_Prezime;
	CString m_OIB;
	CString m_Adresa;
	CString m_Grad;
	CString m_Drzava;
	CString m_Kontakt;
	int GetValue() const { return id; }
};
