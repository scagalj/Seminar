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
	zaposlenici.InsertColumn(0, _T("ID"), LVCFMT_LEFT, 50);
	zaposlenici.InsertColumn(1, _T("Kor oznaka"), LVCFMT_LEFT, 90);
	zaposlenici.InsertColumn(2, _T("Ime"), LVCFMT_LEFT, 90);
	zaposlenici.InsertColumn(3, _T("Prezime"), LVCFMT_LEFT, 90);
	zaposlenici.InsertColumn(4, _T("Adresa"), LVCFMT_LEFT, 120);
	zaposlenici.InsertColumn(5, _T("Grad"), LVCFMT_LEFT, 90);
	zaposlenici.InsertColumn(6, _T("Drzava"), LVCFMT_LEFT, 90);
	zaposlenici.InsertColumn(7, _T("Kontakt"), LVCFMT_LEFT, 120);
	zaposlenici.SetExtendedStyle(zaposlenici.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	
	IspisiZaposlenike();
	
	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CZaposlenici::OnBnClickedButtonZaposlenikDodaj()
{
	CDodajZaposlenika zaposlenik;
	zaposlenik.DoModal();
	IspisiZaposlenike();
	// TODO: Add your control notification handler code here
}


void CZaposlenici::OnBnClickedButtonZaposlenikIzbrisi()
{


	int x = zaposlenici.GetNextItem(-1, LVNI_SELECTED);
	CString t = zaposlenici.GetItemText(x, 0);
	CZaposlenik zaposlenik;
	int y = _tstoi(t);
	CString s;
	s.Format(_T("SELECT * FROM Zaposlenik Where ZaposlenikID = %d"), y);
	zaposlenik.Open(CRecordset::dynaset, s);
	zaposlenik.Delete();
	zaposlenici.DeleteItem(x);
	zaposlenik.Close();
	// TODO: Add your control notification handler code here
}
