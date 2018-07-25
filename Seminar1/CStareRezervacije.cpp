// CStareRezervacije.cpp : implementation file
//

#include "stdafx.h"
#include "Seminar1.h"
#include "CStareRezervacije.h"
#include "afxdialogex.h"
#include "Zaposlenik.h"
#include "Gost.h"
#include "Rezervacija.h"


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

	c_stare_rezervacije.InsertColumn(0, _T("ID"), LVCFMT_LEFT, 30);
	c_stare_rezervacije.InsertColumn(1, _T("Datum"), LVCFMT_LEFT, 90);
	c_stare_rezervacije.InsertColumn(2, _T("Noci"), LVCFMT_LEFT, 50);
	c_stare_rezervacije.InsertColumn(3, _T("Gosti"), LVCFMT_LEFT, 50);
	c_stare_rezervacije.InsertColumn(4, _T("Check IN"), LVCFMT_LEFT, 90);
	c_stare_rezervacije.InsertColumn(5, _T("Check OUT"), LVCFMT_LEFT, 90);
	c_stare_rezervacije.InsertColumn(6, _T("Gost"), LVCFMT_LEFT, 100);
	c_stare_rezervacije.InsertColumn(7, _T("Kreirao"), LVCFMT_LEFT, 100);
	c_stare_rezervacije.InsertColumn(8, _T("Ukupna cijena"), LVCFMT_LEFT, 100);
	c_stare_rezervacije.SetExtendedStyle(c_stare_rezervacije.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	IspisRezervacija();
	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CStareRezervacije::IspisRezervacija() {
	CString s;
	CRezervacija rez;
	rez.Open();
	while (!rez.IsEOF()) {
		if (rez.m_Check_OUT < CTime::GetCurrentTime()) {
			s.Format(_T("%ld"), rez.m_RezervacijaID);
			int nIndex = c_stare_rezervacije.InsertItem(0, s);
			s = rez.m_Datum_rezervacije.Format(_T("%d.%m.%Y"));
			c_stare_rezervacije.SetItemText(nIndex, 1, s);
			s.Format(_T("%d"), rez.m_Broj_nocenja);
			c_stare_rezervacije.SetItemText(nIndex, 2, s);
			s.Format(_T("%d"), rez.m_Broj_gostiju);
			c_stare_rezervacije.SetItemText(nIndex, 3, s);
			s = rez.m_Check_IN.Format(_T("%d.%m.%Y"));
			c_stare_rezervacije.SetItemText(nIndex, 4, s);
			s = rez.m_Check_OUT.Format(_T("%d.%m.%Y"));
			c_stare_rezervacije.SetItemText(nIndex, 5, s);
			c_stare_rezervacije.SetItemText(nIndex, 6, IspisGosta(rez.m_GostID));
			c_stare_rezervacije.SetItemText(nIndex, 7, IspisZaposlenika(rez.m_ZaposlenikID));
			s.Format(_T("%.2f HRK"), rez.m_Ukupna_cijena);
			c_stare_rezervacije.SetItemText(nIndex, 8, s);
			rez.MoveNext();
		}
		else {
			rez.MoveNext();
		}
	}
	rez.Close();

}
CString CStareRezervacije::IspisGosta(int id) {
	CString s;
	CGost gost;
	s.Format(_T("SELECT * FROM Gost Where GostID = %d"), id);
	gost.Open(CRecordset::dynaset, s);
	s.Format(_T("%s %s"), gost.m_Ime, gost.m_Prezime);
	gost.Close();
	return s;
}
CString CStareRezervacije::IspisZaposlenika(int id) {
	CString s;
	CZaposlenik zaposlenik;
	s.Format(_T("SELECT * FROM Zaposlenik Where ZaposlenikID = %d"), id);
	zaposlenik.Open(CRecordset::dynaset, s);
	s.Format(_T("%s"), zaposlenik.m_Kor_Oznaka);
	zaposlenik.Close();
	return s;

}