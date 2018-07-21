#pragma once


// CListaRezervacija dialog

class CListaRezervacija : public CDialogEx
{
	DECLARE_DYNAMIC(CListaRezervacija)

public:
	CListaRezervacija(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CListaRezervacija();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LISTA_REZEVACIJA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl c_lista_rezervacija;
	virtual BOOL OnInitDialog();
	void IspisRezervacija();
	CString IspisGosta(int id);
	CString IspisZaposlenika(int id);
	void IspisiSobe(int id);
	CListCtrl c_list_rez_sobe;
	afx_msg void OnLvnItemchangedListRezervacije(NMHDR *pNMHDR, LRESULT *pResult);
};
