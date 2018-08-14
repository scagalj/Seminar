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
	CListCtrl c_list_rez_sobe;
	int ispis,rezID;
	void Print();
	virtual BOOL OnInitDialog();
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);	
	afx_msg void OnLvnItemchangedListRezervacije(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonRIzbrisi();
	afx_msg void OnBnClickedButtonRPrint();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio1();
	void IspisRezervacija();
	void IspisiSobe(int id);
	afx_msg void OnBnClickedButtonUredi();
};
