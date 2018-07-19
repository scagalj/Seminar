#pragma once


// CNovaRezervacija dialog

class CNovaRezervacija : public CDialogEx
{
	DECLARE_DYNAMIC(CNovaRezervacija)

public:
	CNovaRezervacija(CWnd* pParent = nullptr);   // standard constructor
	explicit CNovaRezervacija(int *sobeID,CString datimD,CString datumO,CString name, CWnd* pParent);
	virtual ~CNovaRezervacija();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_NOVA_REZERVACIJA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int slobodnesobeID[100];
	CString korisnik;
	CString datumIN, datumOUT;
	CString m_Ime;
	CString m_Prezime;
	CString m_Adresa;
	CString m_Grad;
	CString m_Drzava;
	CString m_OIB;
	CString m_Kontakt;
	CString m_pretraziOIB;
	CString m_Brojgostiju;
	CString m_IDSobe;
	CListCtrl c_OdabraneSobe;
};
