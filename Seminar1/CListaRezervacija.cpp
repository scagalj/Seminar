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
	CString s;
	s.LoadString(715);
	c_lista_rezervacija.InsertColumn(0, s, LVCFMT_LEFT, 30);
	s.LoadString(700);
	c_lista_rezervacija.InsertColumn(1, s, LVCFMT_LEFT, 90);
	s.LoadString(701);
	c_lista_rezervacija.InsertColumn(2, s, LVCFMT_LEFT, 50);
	s.LoadString(702);
	c_lista_rezervacija.InsertColumn(3, s, LVCFMT_LEFT, 50);
	s.LoadString(703);
	c_lista_rezervacija.InsertColumn(4, s, LVCFMT_LEFT, 90);
	s.LoadString(704);
	c_lista_rezervacija.InsertColumn(5, s, LVCFMT_LEFT, 90);
	s.LoadString(705);
	c_lista_rezervacija.InsertColumn(6, s, LVCFMT_LEFT, 100);
	s.LoadString(706);
	c_lista_rezervacija.InsertColumn(7, s, LVCFMT_LEFT, 100);
	s.LoadString(707);
	c_lista_rezervacija.InsertColumn(8, s, LVCFMT_LEFT, 100);
	c_lista_rezervacija.SetExtendedStyle(c_lista_rezervacija.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	s.LoadString(715);
	c_list_rez_sobe.InsertColumn(0, s, LVCFMT_LEFT, 50);
	s.LoadString(728);
	c_list_rez_sobe.InsertColumn(1, s, LVCFMT_LEFT, 150);
	c_list_rez_sobe.SetExtendedStyle(c_list_rez_sobe.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	IspisRezervacija();
	GetDlgItem(IDC_BUTTON_R_IZBRISI)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_R_PRINT)->EnableWindow(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CListaRezervacija::IspisRezervacija() {
	CString s,s1;
	CRezervacija rez;
	rez.Open();
	while (!rez.IsEOF()) {
		if (rez.m_Check_OUT < CTime::GetCurrentTime())
			rez.MoveNext();
		else {
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
			s1.LoadString(524);
			s.Format(_T("%.2f %s"), rez.m_Ukupna_cijena,s1);
			c_lista_rezervacija.SetItemText(nIndex, 8, s);

			rez.MoveNext();
		}
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
	id = _tstoi(t);
	CString s,s1;
	s.Format(_T("SELECT * FROM Rezervacija Where RezervacijaID = %d"), id);
	rez.Open(CRecordset::dynaset, s);

	int sirina_p = pDC->GetDeviceCaps(HORZRES);
	int visina_p = pDC->GetDeviceCaps(VERTRES);
	CSize font = pDC->GetTextExtent(_T("A"));
	int x1 = sirina_p / 12;
	int y1 = font.cy * 4;

	s.Format(_T("SELECT * FROM Gost Where GostID = %d"), rez.m_GostID);
	gost.Open(CRecordset::dynaset, s);
	s.Format(_T("%s %s"), gost.m_Ime, gost.m_Prezime);
	pDC->TextOut(x1*9, y1*=3, s);
	pDC->TextOut(x1 * 9, y1 += font.cy, gost.m_OIB);
	pDC->TextOut(x1*9, y1+=font.cy, gost.m_Adresa);
	s.Format(_T("%s, %s"), gost.m_Grad, gost.m_Drzava);
	pDC->TextOut(x1 * 9, y1 += font.cy, s);
	pDC->TextOut(x1 * 9, y1 += font.cy, gost.m_Kontakt);
	gost.Close();
	s1.LoadString(510);
	pDC->TextOut(x1*5,y1+=(font.cy*3),s1);
	pDC->MoveTo(x1, y1 +100);
	pDC->LineTo(x1 * 11, y1+100);
	s.Format(_T("SELECT * FROM Zaposlenik Where ZaposlenikID = %d"), rez.m_ZaposlenikID);
	zap.Open(CRecordset::dynaset, s);
	s1.LoadString(511);
	s.Format(_T("%s: %s"),s1, zap.m_Kor_Oznaka);
	pDC->TextOut(x1, y1+=(font.cy*3), s);
	s1.LoadString(512);
	s.Format(_T("%s: %s"),s1, rez.m_Datum_rezervacije.Format("%d.%m.%Y"));
	pDC->TextOut(x1, y1 +=(font.cy+=30), s);
	s1.LoadString(513);
	s.Format(_T("%s: %d"),s1, rez.m_Broj_nocenja);
	pDC->TextOut(x1, y1 += font.cy, s);
	s1.LoadString(514);
	s.Format(_T("%s: %d"),s1, rez.m_Broj_gostiju);
	pDC->TextOut(x1, y1 += font.cy, s);
	s1.LoadString(515);
	s.Format(_T("%s: %s"),s1, rez.m_Check_IN.Format("%d.%m.%Y"));
	pDC->TextOut(x1, y1 += font.cy, s);
	s1.LoadString(516);
	s.Format(_T("%s: %s"),s1, rez.m_Check_OUT.Format("%d.%m.%Y"));
	pDC->TextOut(x1, y1 += font.cy, s);
	s1.LoadString(517);
	pDC->TextOut(x1, y1 += (font.cy * 3), s1);
	s1.LoadString(715);
	pDC->TextOut(x1*2, y1 += (font.cy * 2), s1);
	s1.LoadString(717);
	pDC->TextOut(x1 * 3, y1, s1);
	s1.LoadString(718);
	pDC->TextOut(x1 * 7, y1, s1);
	s1.LoadString(719);
	pDC->TextOut(x1 * 9, y1, s1);
	pDC->MoveTo(x1 * 2, y1 + 100);
	pDC->LineTo(x1 * 10, y1 + 100);

	CDetaljiRezervacije det;
	s.Format(_T("SELECT * FROM DetaljiRezervacije Where RezervacijaID = %d"), rez.m_RezervacijaID);
	det.Open(CRecordset::dynaset, s);
	while (!det.IsEOF()) {
		CSoba soba;
		s.Format(_T("SELECT * FROM Soba Where SobaID = %d"), det.m_SobaID);
		soba.Open(CRecordset::dynaset, s);
		id = soba.m_HotelID;
		s.Format(_T("%d"), soba.m_SobaID);
		pDC->TextOut(x1 * 2, y1 += font.cy, s);
		CVrstaSobe vrsta;
		s.Format(_T("SELECT * FROM VrstaSobe Where VrstaSobeID = %d"), soba.m_VrstaSobeID);
		vrsta.Open(CRecordset::dynaset, s);
		pDC->TextOut(x1 * 3, y1, vrsta.m_Opis);
		s.LoadString(720);
		s1.LoadString(721);
		soba.m_Konzumiranje_duhana == TRUE ? pDC->TextOut(x1 * 7, y1, s) : pDC->TextOut(x1 * 7, y1, s1);
		soba.m_Ljubimci == TRUE ? pDC->TextOut(x1 * 9, y1, s) : pDC->TextOut(x1 * 9, y1, s1);
		vrsta.Close();
		soba.Close();
		det.MoveNext();
	}
	
	s.Format(_T("SELECT * FROM Hotel Where HotelID = %d"), id);
	hotel.Open(CRecordset::dynaset, s);
	font.cy -= 30;
	y1 = font.cy * 4;
	pDC->TextOut(x1, y1, hotel.m_Naziv);
	pDC->TextOut(x1, y1 += font.cy, hotel.m_Adresa);
	pDC->TextOut(x1, y1 += font.cy, hotel.m_Grad);
	pDC->TextOut(x1, y1 += font.cy, hotel.m_Kontakt);
	hotel.Close();

	y1 = visina_p - visina_p/4;
	s1.LoadString(524);
	s.Format(_T("%.2f %s"), rez.m_Ukupna_cijena,s1);
	s1.LoadString(518);
	pDC->TextOut(x1 * 9, y1, s1);
	pDC->TextOut(x1 * 9, y1 += (font.cy + 50), s);
	s1.LoadString(705);
	pDC->TextOut(x1, y1 += (font.cy * 4), s1);
	s1.LoadString(706);
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