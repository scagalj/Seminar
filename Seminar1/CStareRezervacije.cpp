// CStareRezervacije.cpp : implementation file
//

#include "stdafx.h"
#include "Seminar1.h"
#include "CStareRezervacije.h"
#include "afxdialogex.h"
#include "Zaposlenik.h"
#include "Gost.h"
#include "Rezervacija.h"
#include "Funkcije.h"


// CStareRezervacije dialog

IMPLEMENT_DYNAMIC(CStareRezervacije, CDialogEx)

CStareRezervacije::CStareRezervacije(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_STARE_REZERVACIJE, pParent)
{

}

CStareRezervacije::~CStareRezervacije()
{
}

void CStareRezervacije::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_STARE_REZERVACIJE, c_stare_rezervacije);
}


BEGIN_MESSAGE_MAP(CStareRezervacije, CDialogEx)
END_MESSAGE_MAP()


// CStareRezervacije message handlers


BOOL CStareRezervacije::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString s;
	s.LoadString(IDS_STRING_ID);
	c_stare_rezervacije.InsertColumn(0, s, LVCFMT_LEFT, 30);
	s.LoadString(IDS_STRING_DATUM);
	c_stare_rezervacije.InsertColumn(1, s, LVCFMT_LEFT, 90);
	s.LoadString(IDS_STRING_NOCI);
	c_stare_rezervacije.InsertColumn(2, s, LVCFMT_LEFT, 50);
	s.LoadString(IDS_STRING_BROJ_GOSTIJU);
	c_stare_rezervacije.InsertColumn(3, s, LVCFMT_LEFT, 50);
	s.LoadString(IDS_STRING_CHECK_IN);
	c_stare_rezervacije.InsertColumn(4, s, LVCFMT_LEFT, 90);
	s.LoadString(IDS_STRING_CHECK_OUT);
	c_stare_rezervacije.InsertColumn(5,s, LVCFMT_LEFT, 90);
	s.LoadString(IDS_STRING_GOST);
	c_stare_rezervacije.InsertColumn(6, s, LVCFMT_LEFT, 100);
	s.LoadString(IDS_STRING_ZAPOSLENIK);
	c_stare_rezervacije.InsertColumn(7, s, LVCFMT_LEFT, 100);
	s.LoadString(IDS_STRING_UKUPNO);
	c_stare_rezervacije.InsertColumn(8, s, LVCFMT_LEFT, 100);
	c_stare_rezervacije.SetExtendedStyle(c_stare_rezervacije.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	IspisRezervacija();

	return TRUE;
}

void CStareRezervacije::IspisRezervacija() {
	CString s,s1;
	CRezervacija rez;
	rez.Open();
	while (!rez.IsEOF()) {
		if (rez.m_Check_OUT < CTime::GetCurrentTime()) {
			s.Format(_T("%ld"), rez.m_RezervacijaID);
			int nIndex = c_stare_rezervacije.InsertItem(0, s);
			c_stare_rezervacije.SetItemText(nIndex, 1, rez.m_Datum_rezervacije.Format(_T("%d.%m.%Y")));
			s.Format(_T("%d"), rez.m_Broj_nocenja);
			c_stare_rezervacije.SetItemText(nIndex, 2, s);
			s.Format(_T("%d"), rez.m_Broj_gostiju);
			c_stare_rezervacije.SetItemText(nIndex, 3, s);
			c_stare_rezervacije.SetItemText(nIndex, 4, rez.m_Check_IN.Format(_T("%d.%m.%Y")));
			c_stare_rezervacije.SetItemText(nIndex, 5, rez.m_Check_OUT.Format(_T("%d.%m.%Y")));
			c_stare_rezervacije.SetItemText(nIndex, 6, f::DohvatiGosta(rez.m_GostID));
			c_stare_rezervacije.SetItemText(nIndex, 7, f::DohvatiZaposlenika(rez.m_ZaposlenikID));
			s1.LoadString(IDS_STRING_VALUTA);
			s.Format(_T("%.2f %s"), rez.m_Ukupna_cijena,s1);
			c_stare_rezervacije.SetItemText(nIndex, 8, s);
			rez.MoveNext();
		}
		else {
			rez.MoveNext();
		}
	}
	rez.Close();

}