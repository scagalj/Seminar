#pragma once


// CNovaRezervacija dialog

class CNovaRezervacija : public CDialogEx
{
	DECLARE_DYNAMIC(CNovaRezervacija)

public:
	CNovaRezervacija(CWnd* pParent = nullptr);   // standard constructor
	explicit CNovaRezervacija(CString datimD,CString datumO,CString name,int hotelid, CWnd* pParent);
	virtual ~CNovaRezervacija();
	bool DodajGosta();
	void IspisiCijenu();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_NOVA_REZERVACIJA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	double ukupna_cijena;
	int zapID;
	int gostID=-1;
	int m_Brojnocenja;
	int hotelID;
	CString datumIN, datumOUT;
	CTime datumD, datumO;
	CString m_Ime;
	CString m_Prezime;
	CString m_Adresa;
	CString m_Grad;
	CString m_Drzava;
	CString m_OIB;
	CString m_Kontakt;
	CString m_pretraziOIB;
	int m_Brojgostiju,m_BrojGostijuizracun;
	CString m_IDSobe;
	CListCtrl c_OdabraneSobe;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonRTrazi();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonRDodaj();
	afx_msg void OnLvnItemchangedListROdabranesobe(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonRIzbrisi();
	afx_msg void OnBnClickedButtonNoviGost();
};
