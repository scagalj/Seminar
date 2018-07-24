// CListaRezervacija.cpp : implementation file
//

#include "stdafx.h"
#include "Seminar1.h"
#include "CListaRezervacija.h"
#include "afxdialogex.h"
#include "Rezervacija.h"
#include "DetaljiRezervacije.h"
#include "Zaposlenik.h"
#include "Gost.h"
#include "Soba.h"
#include "VrstaSobe.h"


// CListaRezervacija dialog

IMPLEMENT_DYNAMIC(CListaRezervacija, CDialogEx)

CListaRezervacija::CListaRezervacija(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_LISTA_REZEVACIJA, pParent)
{

}

CListaRezervacija::~CListaRezervacija()
{
}

void CListaRezervacija::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_REZERVACIJE, c_lista_rezervacija);
	DDX_Control(pDX, IDC_LIST_REZERVACIJA_SOBE, c_list_rez_sobe);
}


BEGIN_MESSAGE_MAP(CListaRezervacija, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_REZERVACIJE, &CListaRezervacija::OnLvnItemchangedListRezervacije)
	ON_BN_CLICKED(IDC_BUTTON_R_IZBRISI, &CListaRezervacija::OnBnClickedButtonRIzbrisi)
	ON_BN_CLICKED(IDC_BUTTON_R_PRINT, &CListaRezervacija::OnBnClickedButtonRPrint)
END_MESSAGE_MAP()


// CListaRezervacija message handlers


BOOL CListaRezervacija::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	c_lista_rezervacija.InsertColumn(0, _T("ID"), LVCFMT_LEFT, 30);
	c_lista_rezervacija.InsertColumn(1, _T("Datum"), LVCFMT_LEFT, 90);
	c_lista_rezervacija.InsertColumn(2, _T("Noci"), LVCFMT_LEFT, 50);
	c_lista_rezervacija.InsertColumn(3, _T("Gosti"), LVCFMT_LEFT, 50);
	c_lista_rezervacija.InsertColumn(4, _T("Check IN"), LVCFMT_LEFT, 90);
	c_lista_rezervacija.InsertColumn(5, _T("Check OUT"), LVCFMT_LEFT, 90);
	c_lista_rezervacija.InsertColumn(6, _T("Gost"), LVCFMT_LEFT, 100);
	c_lista_rezervacija.InsertColumn(7, _T("Kreirao"), LVCFMT_LEFT, 100);
	c_lista_rezervacija.InsertColumn(8, _T("Ukupna cijena"), LVCFMT_LEFT, 100);
	c_lista_rezervacija.SetExtendedStyle(c_lista_rezervacija.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	c_list_rez_sobe.InsertColumn(0, _T("ID"), LVCFMT_LEFT, 50);
	c_list_rez_sobe.InsertColumn(1, _T("Vrsta"), LVCFMT_LEFT, 150);
	c_list_rez_sobe.SetExtendedStyle(c_list_rez_sobe.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	IspisRezervacija();
	GetDlgItem(IDC_BUTTON_R_IZBRISI)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_R_PRINT)->EnableWindow(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CListaRezervacija::IspisRezervacija() {
	CString s;
	CRezervacija rez;
	rez.Open();
	while (!rez.IsEOF()) {

		s.Format(_T("%ld"), rez.m_RezervacijaID);
		int nIndex = c_lista_rezervacija.InsertItem(0, s);
		s = rez.m_Datum_rezervacije.Format(_T("%d.%m.%Y"));
		c_lista_rezervacija.SetItemText(nIndex, 1, s);
		s.Format(_T("%d"), rez.m_Broj_nocenja);
		c_lista_rezervacija.SetItemText(nIndex, 2, s);
		s.Format(_T("%d"), rez.m_Broj_gostiju);
		c_lista_rezervacija.SetItemText(nIndex, 3, s);
		s = rez.m_Check_IN.Format(_T("%d.%m.%Y"));
		c_lista_rezervacija.SetItemText(nIndex, 4, s);
		s = rez.m_Check_OUT.Format(_T("%d.%m.%Y"));
		c_lista_rezervacija.SetItemText(nIndex, 5, s);		
		c_lista_rezervacija.SetItemText(nIndex, 6, IspisGosta(rez.m_GostID));
		c_lista_rezervacija.SetItemText(nIndex, 7, IspisZaposlenika(rez.m_ZaposlenikID));
		s.Format(_T("%.2f HRK"), rez.m_Ukupna_cijena);
		c_lista_rezervacija.SetItemText(nIndex, 8, s);

		rez.MoveNext();
	}
	rez.Close();

}
CString CListaRezervacija::IspisGosta(int id) {
	CString s;
	CGost gost;
	s.Format(_T("SELECT * FROM Gost Where GostID = %d"), id);
	gost.Open(CRecordset::dynaset, s);
	s.Format(_T("%s %s"), gost.m_Ime , gost.m_Prezime);
	gost.Close();
	return s;
}
CString CListaRezervacija::IspisZaposlenika(int id) {
	CString s;
	CZaposlenik zaposlenik;
	s.Format(_T("SELECT * FROM Zaposlenik Where ZaposlenikID = %d"), id);
	zaposlenik.Open(CRecordset::dynaset, s);
	s.Format(_T("%s"), zaposlenik.m_Kor_Oznaka);
	zaposlenik.Close();
	return s;

}
void CListaRezervacija::IspisiSobe(int id) {
	CString s;
	int nIndex;
	CDetaljiRezervacije det;
	s.Format(_T("SELECT * FROM DetaljiRezervacije Where RezervacijaID = %d"), id);
	det.Open(CRecordset::dynaset, s);
	while (!det.IsEOF()) {
		CSoba soba;
		s.Format(_T("SELECT * FROM Soba Where SobaID = %d"), det.m_SobaID);
		soba.Open(CRecordset::dynaset, s);
		s.Format(_T("%d"), soba.m_SobaID);
		nIndex = c_list_rez_sobe.InsertItem(0, s);
		CVrstaSobe vrsta;
		s.Format(_T("SELECT * FROM VrstaSobe Where VrstaSobeID = %d"), soba.m_VrstaSobeID);
		vrsta.Open(CRecordset::dynaset, s);
		c_list_rez_sobe.SetItemText(nIndex, 1, vrsta.m_Opis);
		vrsta.Close();
		soba.Close();
		det.MoveNext();
	}
	det.Close();

}

void CListaRezervacija::OnLvnItemchangedListRezervacije(NMHDR *pNMHDR, LRESULT *pResult)
{
	
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	c_list_rez_sobe.DeleteAllItems();
	int n = c_lista_rezervacija.GetNextItem(-1, LVNI_SELECTED);
	if (n != -1) {
		CString t = c_lista_rezervacija.GetItemText(n, 0);
		int x = _tstoi(t);
		IspisiSobe(x);
	}
	bool ispit = pNMLV->uNewState & LVIS_SELECTED ? TRUE : FALSE;
	GetDlgItem(IDC_BUTTON_R_IZBRISI)->EnableWindow(ispit);
	GetDlgItem(IDC_BUTTON_R_PRINT)->EnableWindow(ispit);

	// TODO: Add your control notification handler code here
	*pResult = 0;
}


void CListaRezervacija::OnBnClickedButtonRIzbrisi()
{
	int x = c_lista_rezervacija.GetNextItem(-1, LVNI_SELECTED);
	CString t = c_lista_rezervacija.GetItemText(x, 0);
	CRezervacija rez;
	int y = _tstoi(t);
	CString s;
	s.Format(_T("SELECT * FROM Rezervacija Where RezervacijaID = %d"), y);
	rez.Open(CRecordset::dynaset, s);
	rez.Delete();
	c_lista_rezervacija.DeleteItem(x);
	rez.Close();
	c_list_rez_sobe.DeleteAllItems();
	// TODO: Add your control notification handler code here
}


void CListaRezervacija::OnBnClickedButtonRPrint()
{
	Print();

}

void CListaRezervacija::OnBeginPrinting(CDC *pDC, CPrintInfo* pInfo)
{

	pInfo->SetMaxPage(1);
}


void CListaRezervacija::OnPrint(CDC *pDC, CPrintInfo* pInfo)
{
	
}


void CListaRezervacija::OnEndPrinting(CDC *pDC, CPrintInfo* pInfo)
{

}

void CListaRezervacija::Print()
{
	CDC dc;
	CPrintDialog printDlg(FALSE);

	if (printDlg.DoModal() == IDCANCEL)     // Get printer settings from user
		return;

	dc.Attach(printDlg.GetPrinterDC());     // Get and attach a printer DC

	dc.m_bPrinting = TRUE;

	CString strTitle;                       // Get the application title

	strTitle.LoadString(AFX_IDS_APP_TITLE);

	DOCINFO di;                             // Initialize print document details

	::ZeroMemory(&di, sizeof(DOCINFO));
	di.cbSize = sizeof(DOCINFO);
	di.lpszDocName = strTitle;

	BOOL bPrintingOK = dc.StartDoc(&di);    // Begin a new print job


											// Get the printing extents and store in the m_rectDraw field of a 

											// CPrintInfo object
	CPrintInfo Info;
	Info.m_rectDraw.SetRect(0, 0,
		dc.GetDeviceCaps(HORZRES),
		dc.GetDeviceCaps(VERTRES));

	OnBeginPrinting(&dc, &Info);            // Call your "Init printing" function

	for (UINT page = Info.GetMinPage();
		page <= Info.GetMaxPage() && bPrintingOK;
		page++)
	{
		dc.StartPage();                     // begin new page

		Info.m_nCurPage = page;
		OnPrint(&dc, &Info);                // Call your "Print page" function

		bPrintingOK = (dc.EndPage() > 0);   // end page

	}
	OnEndPrinting(&dc, &Info);              // Call your "Clean up" function


	if (bPrintingOK)
		dc.EndDoc();                        // end a print job

	else
		dc.AbortDoc();                      // abort job.


	dc.DeleteDC();                          // delete the printer DC

}