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
#include "Hotel.h"
#include "Funkcije.h"
#include "CUrediRezervaciju.h"

// CListaRezervacija dialog

IMPLEMENT_DYNAMIC(CListaRezervacija, CDialogEx)

CListaRezervacija::CListaRezervacija(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_LISTA_REZEVACIJA, pParent)
	, ispis(0)
	, poredak(true)
	, stupac(-1)
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
	DDX_Radio(pDX, IDC_RADIO1, ispis);
}


BEGIN_MESSAGE_MAP(CListaRezervacija, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_REZERVACIJE, &CListaRezervacija::OnLvnItemchangedListRezervacije)
	ON_BN_CLICKED(IDC_BUTTON_R_IZBRISI, &CListaRezervacija::OnBnClickedButtonRIzbrisi)
	ON_BN_CLICKED(IDC_BUTTON_R_PRINT, &CListaRezervacija::OnBnClickedButtonRPrint)
	ON_BN_CLICKED(IDC_RADIO3, &CListaRezervacija::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO2, &CListaRezervacija::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO1, &CListaRezervacija::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_BUTTON_UREDI, &CListaRezervacija::OnBnClickedButtonUredi)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_REZERVACIJE, &CListaRezervacija::OnLvnColumnclickListRezervacije)
END_MESSAGE_MAP()


// CListaRezervacija message handlers


BOOL CListaRezervacija::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString s;
	s.LoadString(IDS_STRING_ID);
	c_lista_rezervacija.InsertColumn(0, s, LVCFMT_LEFT, 30);
	s.LoadString(IDS_STRING_DATUM);
	c_lista_rezervacija.InsertColumn(1, s, LVCFMT_LEFT, 90);
	s.LoadString(IDS_STRING_NOCI);
	c_lista_rezervacija.InsertColumn(2, s, LVCFMT_LEFT, 50);
	s.LoadString(IDS_STRING_BROJ_GOSTIJU);
	c_lista_rezervacija.InsertColumn(3, s, LVCFMT_LEFT, 50);
	s.LoadString(IDS_STRING_CHECK_IN);
	c_lista_rezervacija.InsertColumn(4, s, LVCFMT_LEFT, 90);
	s.LoadString(IDS_STRING_CHECK_OUT);
	c_lista_rezervacija.InsertColumn(5, s, LVCFMT_LEFT, 90);
	s.LoadString(IDS_STRING_GOST);
	c_lista_rezervacija.InsertColumn(6, s, LVCFMT_LEFT, 100);
	s.LoadString(IDS_STRING_ZAPOSLENIK);
	c_lista_rezervacija.InsertColumn(7, s, LVCFMT_LEFT, 100);
	s.LoadString(IDS_STRING_UKUPNO);
	c_lista_rezervacija.InsertColumn(8, s, LVCFMT_LEFT, 100);
	c_lista_rezervacija.SetExtendedStyle(c_lista_rezervacija.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	s.LoadString(IDS_STRING_ID);
	c_list_rez_sobe.InsertColumn(0, s, LVCFMT_LEFT, 50);
	s.LoadString(IDS_STRING_VRSTA);
	c_list_rez_sobe.InsertColumn(1, s, LVCFMT_LEFT, 150);
	c_list_rez_sobe.SetExtendedStyle(c_list_rez_sobe.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	IspisRezervacija();
	GetDlgItem(IDC_BUTTON_R_IZBRISI)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_R_PRINT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_UREDI)->EnableWindow(FALSE);
	return TRUE;
}

void CListaRezervacija::IspisRezervacija() {
	CString s,s1;
	CRezervacija rez;
	c_lista_rezervacija.DeleteAllItems();
	if (ispis == 0)
		rez.m_strFilter.Format(_T("[Check_OUT] >= #%s#"), CTime::GetCurrentTime().Format("%m-%d-%Y"));
	else if(ispis == 1)
		rez.m_strFilter.Format(_T("[Check_OUT] < #%s#"), CTime::GetCurrentTime().Format("%m-%d-%Y"));
	rez.Open();
	while (!rez.IsEOF()) {
			s.Format(_T("%ld"), rez.m_RezervacijaID);
			int nIndex = c_lista_rezervacija.InsertItem(0, s);
			c_lista_rezervacija.SetItemText(nIndex, 1, rez.m_Datum_rezervacije.Format(_T("%d.%m.%Y")));
			s.Format(_T("%d"), rez.m_Broj_nocenja);
			c_lista_rezervacija.SetItemText(nIndex, 2, s);
			s.Format(_T("%d"), rez.m_Broj_gostiju);
			c_lista_rezervacija.SetItemText(nIndex, 3, s);
			c_lista_rezervacija.SetItemText(nIndex, 4, rez.m_Check_IN.Format(_T("%d.%m.%Y"))); 
			c_lista_rezervacija.SetItemText(nIndex, 5, rez.m_Check_OUT.Format(_T("%d.%m.%Y")));
			c_lista_rezervacija.SetItemText(nIndex, 6, f::DohvatiGosta(rez.m_GostID));
			c_lista_rezervacija.SetItemText(nIndex, 7, f::DohvatiZaposlenika(rez.m_ZaposlenikID));
			s1.LoadString(IDS_STRING_VALUTA);
			s.Format(_T("%.2f %s"), rez.m_Ukupna_cijena,s1);
			c_lista_rezervacija.SetItemText(nIndex, 8, s);

			rez.MoveNext();
	}
	rez.Close();
}


void CListaRezervacija::IspisiSobe(int id) {
	CString s;
	CDetaljiRezervacije det;
	int nIndex;
	det.m_strFilter.Format(_T("[RezervacijaID] = %d"), id);
	det.Open();
	while (!det.IsEOF()) {
		CSoba soba;
		soba.m_strFilter.Format(_T("[SobaID] = %d"), det.m_SobaID);
		soba.Open();
		s.Format(_T("%d"), soba.m_SobaID);
		nIndex = c_list_rez_sobe.InsertItem(0, s);
		CVrstaSobe vrsta;
		vrsta.m_strFilter.Format(_T("[VrstaSobeID] = %d"), soba.m_VrstaSobeID);
		vrsta.Open();
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
		rezID = _tstoi(t);
		IspisiSobe(rezID);
	}
	bool ispit = pNMLV->uNewState & LVIS_SELECTED ? TRUE : FALSE;
	GetDlgItem(IDC_BUTTON_R_IZBRISI)->EnableWindow(ispit);
	GetDlgItem(IDC_BUTTON_R_PRINT)->EnableWindow(ispit);
	GetDlgItem(IDC_BUTTON_UREDI)->EnableWindow(ispit);

	*pResult = 0;
}


void CListaRezervacija::OnBnClickedButtonRIzbrisi()
{
	int x = c_lista_rezervacija.GetNextItem(-1, LVNI_SELECTED);
	CString t = c_lista_rezervacija.GetItemText(x, 0);
	CRezervacija rez;
	rez.m_strFilter.Format(_T("[RezervacijaID] = %d"), _tstoi(t));
	rez.Open();
	rez.Delete();
	c_lista_rezervacija.DeleteItem(x);
	rez.Close();
	c_list_rez_sobe.DeleteAllItems();
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
	int id = c_lista_rezervacija.GetNextItem(-1, LVNI_SELECTED);
	CString t = c_lista_rezervacija.GetItemText(id, 0);
	CRezervacija rez;
	CHotel hotel;
	CGost gost;
	CZaposlenik zap;
	CSoba soba;
	CString s,s1;
	rez.m_strFilter.Format(_T("[RezervacijaID] = %d"), _tstoi(t));
	rez.Open();

	int sirina_p = pDC->GetDeviceCaps(HORZRES);
	int visina_p = pDC->GetDeviceCaps(VERTRES);
	CSize font = pDC->GetTextExtent(_T("A"));
	int x1 = sirina_p / 12;
	int y1 = font.cy * 4;

	gost.m_strFilter.Format(_T("[GostID] = %d"), rez.m_GostID);
	gost.Open();
	s.Format(_T("%s %s"), gost.m_Ime, gost.m_Prezime);
	pDC->TextOut(x1*9, y1*=3, s);
	pDC->TextOut(x1 * 9, y1 += font.cy, gost.m_OIB);
	pDC->TextOut(x1*9, y1+=font.cy, gost.m_Adresa);
	s.Format(_T("%s, %s"), gost.m_Grad, gost.m_Drzava);
	pDC->TextOut(x1 * 9, y1 += font.cy, s);
	pDC->TextOut(x1 * 9, y1 += font.cy, gost.m_Kontakt);
	gost.Close();
	s1.LoadString(IDS_STRING_PRINT1);
	pDC->TextOut(x1*5,y1+=(font.cy*3),s1);
	pDC->MoveTo(x1, y1 +100);
	pDC->LineTo(x1 * 11, y1+100);
	zap.m_strFilter.Format(_T("[ZaposlenikID] = %d"), rez.m_ZaposlenikID);
	zap.Open();
	s1.LoadString(IDS_STRING_PRINT2);
	s.Format(_T("%s: %s"),s1, zap.m_Kor_Oznaka);
	pDC->TextOut(x1, y1+=(font.cy*3), s);
	s1.LoadString(IDS_STRING_PRINT3);
	s.Format(_T("%s: %s"),s1, rez.m_Datum_rezervacije.Format("%d.%m.%Y"));
	pDC->TextOut(x1, y1 +=(font.cy+=30), s);
	s1.LoadString(IDS_STRING_PRINT4);
	s.Format(_T("%s: %d"),s1, rez.m_Broj_nocenja);
	pDC->TextOut(x1, y1 += font.cy, s);
	s1.LoadString(IDS_STRING_PRINT5);
	s.Format(_T("%s: %d"),s1, rez.m_Broj_gostiju);
	pDC->TextOut(x1, y1 += font.cy, s);
	s1.LoadString(IDS_STRING_PRINT6);
	s.Format(_T("%s: %s"),s1, rez.m_Check_IN.Format("%d.%m.%Y"));
	pDC->TextOut(x1, y1 += font.cy, s);
	s1.LoadString(IDS_STRING_PRINT7);
	s.Format(_T("%s: %s"),s1, rez.m_Check_OUT.Format("%d.%m.%Y"));
	pDC->TextOut(x1, y1 += font.cy, s);
	s1.LoadString(IDS_STRING_PRINT8);
	pDC->TextOut(x1, y1 += (font.cy * 3), s1);
	s1.LoadString(IDS_STRING_ID);
	pDC->TextOut(x1*2, y1 += (font.cy * 2), s1);
	s1.LoadString(IDS_STRING_OPIS);
	pDC->TextOut(x1 * 3, y1, s1);
	s1.LoadString(IDS_STRING_DUHAN);
	pDC->TextOut(x1 * 7, y1, s1);
	s1.LoadString(IDS_STRING_LJUBIMAC);
	pDC->TextOut(x1 * 9, y1, s1);
	pDC->MoveTo(x1 * 2, y1 + 100);
	pDC->LineTo(x1 * 10, y1 + 100);

	CDetaljiRezervacije det;
	det.m_strFilter.Format(_T("[RezervacijaID] = %d"), rez.m_RezervacijaID);
	det.Open();
	while (!det.IsEOF()) {
		CSoba soba;
		soba.m_strFilter.Format(_T("[SobaID] = %d"), det.m_SobaID);
		soba.Open();
		id = soba.m_HotelID;
		s.Format(_T("%d"), soba.m_SobaID);
		pDC->TextOut(x1 * 2, y1 += font.cy, s);
		CVrstaSobe vrsta;
		vrsta.m_strFilter.Format(_T("[VrstaSobeID] = %d"), soba.m_VrstaSobeID);
		vrsta.Open();
		pDC->TextOut(x1 * 3, y1, vrsta.m_Opis);
		s.LoadString(IDS_STRING_DA);
		s1.LoadString(IDS_STRING_NE);
		soba.m_Konzumiranje_duhana == TRUE ? pDC->TextOut(x1 * 7, y1, s) : pDC->TextOut(x1 * 7, y1, s1);
		soba.m_Ljubimci == TRUE ? pDC->TextOut(x1 * 9, y1, s) : pDC->TextOut(x1 * 9, y1, s1);
		vrsta.Close();
		soba.Close();
		det.MoveNext();
	}
	
	hotel.m_strFilter.Format(_T("[HotelID] = %d"), id);
	hotel.Open();
	font.cy -= 30;
	y1 = font.cy * 4;
	pDC->TextOut(x1, y1, hotel.m_Naziv);
	pDC->TextOut(x1, y1 += font.cy, hotel.m_Adresa);
	pDC->TextOut(x1, y1 += font.cy, hotel.m_Grad);
	pDC->TextOut(x1, y1 += font.cy, hotel.m_Kontakt);
	hotel.Close();

	y1 = visina_p - visina_p/4;
	s1.LoadString(IDS_STRING_VALUTA);
	s.Format(_T("%.2f %s"), rez.m_Ukupna_cijena,s1);
	s1.LoadString(IDS_STRING_PRINT9);
	pDC->TextOut(x1 * 9, y1, s1);
	pDC->TextOut(x1 * 9, y1 += (font.cy + 50), s);
	s1.LoadString(IDS_STRING_GOST);
	pDC->TextOut(x1, y1 += (font.cy * 4), s1);
	s1.LoadString(IDS_STRING_ZAPOSLENIK);
	pDC->TextOut(x1 * 8, y1, s1);
	pDC->MoveTo(x1, y1 += 300);
	pDC->LineTo(x1 * 3, y1);
	pDC->MoveTo(x1*8, y1);
	pDC->LineTo(x1 * 10, y1);
	det.Close();


	rez.Close();
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


void CListaRezervacija::OnBnClickedRadio1()
{
	ispis = 0;
	IspisRezervacija();
}

void CListaRezervacija::OnBnClickedRadio2()
{
	ispis = 1;
	IspisRezervacija();
}

void CListaRezervacija::OnBnClickedRadio3()
{
	ispis = 2;
	IspisRezervacija();
}




void CListaRezervacija::OnBnClickedButtonUredi()
{
	CRezervacija rez;
	rez.m_strFilter.Format(_T("[RezervacijaID] = %d"), rezID);
	rez.Open();
	CUrediRezervaciju uredi(rezID, rez.m_Check_IN.Format(_T("%d.%m.%Y")), rez.m_Check_OUT.Format(_T("%d.%m.%Y")),this);
	if (uredi.DoModal() == IDOK)
		IspisRezervacija();
}


bool CListaRezervacija::SortColumn(int columnIndex, bool ascending)
{
	bool datum = columnIndex == 1 || columnIndex == 4 || columnIndex == 5 ? true : false;
	sort::PARAMSORT paramsort(c_lista_rezervacija, columnIndex, ascending, datum);
	ListView_SortItemsEx(c_lista_rezervacija, sort::SortFunc, &paramsort);
	return true;
}

void CListaRezervacija::OnLvnColumnclickListRezervacije(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	poredak = pNMLV->iSubItem == stupac ? !poredak : false;
	stupac = pNMLV->iSubItem;
	SortColumn(stupac, poredak);
	*pResult = 0;
}
