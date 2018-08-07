// CZaposlenici.cpp : implementation file
//

#include "stdafx.h"
#include "Seminar1.h"
#include "CZaposlenici.h"
#include "afxdialogex.h"
#include "Zaposlenik.h"
#include "CDodajZaposlenika.h"


// CZaposlenici dialog

IMPLEMENT_DYNAMIC(CZaposlenici, CDialogEx)

CZaposlenici::CZaposlenici(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ZAPOSLENIK, pParent)
{

}

CZaposlenici::~CZaposlenici()
{
}

void CZaposlenici::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_POPIS_ZAPOSLENIKA, zaposlenici);
}


BEGIN_MESSAGE_MAP(CZaposlenici, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ZAPOSLENIK_DODAJ, &CZaposlenici::OnBnClickedButtonZaposlenikDodaj)
	ON_BN_CLICKED(IDC_BUTTON_ZAPOSLENIK_IZBRISI, &CZaposlenici::OnBnClickedButtonZaposlenikIzbrisi)
END_MESSAGE_MAP()


// CZaposlenici message handlers
void CZaposlenici::IspisiZaposlenike() {
	zaposlenici.DeleteAllItems();
	CZaposlenik zaposlenik;
	zaposlenik.Open();
	while (!zaposlenik.IsEOF()) {
		CString id;
		id.Format(_T("%ld"), zaposlenik.m_ZaposlenikID);
		int nIndex = zaposlenici.InsertItem(0, id);
		zaposlenici.SetItemText(nIndex, 1, zaposlenik.m_Kor_Oznaka);
		zaposlenici.SetItemText(nIndex, 2, zaposlenik.m_Ime);
		zaposlenici.SetItemText(nIndex, 3, zaposlenik.m_Prezime);
		zaposlenici.SetItemText(nIndex, 4, zaposlenik.m_Adresa);
		zaposlenici.SetItemText(nIndex, 5, zaposlenik.m_Grad);
		zaposlenici.SetItemText(nIndex, 6, zaposlenik.m_Drzava);
		zaposlenici.SetItemText(nIndex, 7, zaposlenik.m_Kontakt);
		zaposlenik.MoveNext();
	}
	zaposlenik.Close();

}


BOOL CZaposlenici::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString s;
	s.LoadString(IDS_STRING_ID);
	zaposlenici.InsertColumn(0,s, LVCFMT_LEFT, 50);
	s.LoadString(IDS_STRING_OZNAKA);
	zaposlenici.InsertColumn(1, s, LVCFMT_LEFT, 90);
	s.LoadString(IDS_STRING_IME);
	zaposlenici.InsertColumn(2, s, LVCFMT_LEFT, 90);
	s.LoadString(IDS_STRING_PREZIME);
	zaposlenici.InsertColumn(3, s, LVCFMT_LEFT, 90);
	s.LoadString(IDS_STRING_ADRESA);
	zaposlenici.InsertColumn(4, s, LVCFMT_LEFT, 120);
	s.LoadString(IDS_STRING_GRAD);
	zaposlenici.InsertColumn(5, s, LVCFMT_LEFT, 90);
	s.LoadString(IDS_STRING_DRZAVA);
	zaposlenici.InsertColumn(6, s, LVCFMT_LEFT, 90);
	s.LoadString(IDS_STRING_KONTAKT);
	zaposlenici.InsertColumn(7, s, LVCFMT_LEFT, 120);
	zaposlenici.SetExtendedStyle(zaposlenici.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	
	IspisiZaposlenike();

	return TRUE;
}


void CZaposlenici::OnBnClickedButtonZaposlenikDodaj()
{
	CDodajZaposlenika zaposlenik;
	zaposlenik.DoModal();
	IspisiZaposlenike();
}


void CZaposlenici::OnBnClickedButtonZaposlenikIzbrisi()
{


	int x = zaposlenici.GetNextItem(-1, LVNI_SELECTED);
	CString t = zaposlenici.GetItemText(x, 0);
	CZaposlenik zaposlenik;
	zaposlenik.m_strFilter.Format(_T("[ZaposlenikID] = %d"), _tstoi(t));
	zaposlenik.Open();
	zaposlenik.Delete();
	zaposlenici.DeleteItem(x);
	zaposlenik.Close();
}
