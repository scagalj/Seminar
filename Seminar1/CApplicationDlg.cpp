// CApplicationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Seminar1.h"
#include "CApplicationDlg.h"
#include "afxdialogex.h"
#include "CHoteli.h"
#include "Seminar1Dlg.h"
#include "CZaposlenici.h"
#include "CGosti.h"
#include "CSlobodneSobe.h"
#include "CListaRezervacija.h"
#include "Zaposlenik.h"
#include "Gost.h"
#include "Rezervacija.h"
#include "Funkcije.h"

// CApplicationDlg dialog

IMPLEMENT_DYNAMIC(CApplicationDlg, CDialogEx)

CApplicationDlg::CApplicationDlg(const CString name, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_APLIKACIJA, pParent)
	,user(name)
	, poredak(true)
	,stupac(-1)
{

}

CApplicationDlg::~CApplicationDlg()
{
}

BOOL CApplicationDlg::OnInitDialog() {
	CString s;
	CDialogEx::OnInitDialog();
	CWnd *label = GetDlgItem(IDC_STATIC_KORISNIK);
	label->SetWindowText(user);
	s.LoadString(IDS_STRING_ID);
	c_rezervacije_danas.InsertColumn(0, s, LVCFMT_LEFT, 30);
	s.LoadString(IDS_STRING_DATUM);
	c_rezervacije_danas.InsertColumn(1, s, LVCFMT_LEFT, 90);
	s.LoadString(IDS_STRING_NOCI);
	c_rezervacije_danas.InsertColumn(2, s, LVCFMT_LEFT, 50);
	s.LoadString(IDS_STRING_BROJ_GOSTIJU);
	c_rezervacije_danas.InsertColumn(3, s, LVCFMT_LEFT, 50);
	s.LoadString(IDS_STRING_CHECK_IN);
	c_rezervacije_danas.InsertColumn(4, s, LVCFMT_LEFT, 90);
	s.LoadString(IDS_STRING_CHECK_OUT);
	c_rezervacije_danas.InsertColumn(5, s, LVCFMT_LEFT, 90);
	s.LoadString(IDS_STRING_GOST);
	c_rezervacije_danas.InsertColumn(6, s, LVCFMT_LEFT, 100);
	s.LoadString(IDS_STRING_ZAPOSLENIK);
	c_rezervacije_danas.InsertColumn(7, s, LVCFMT_LEFT, 100);
	s.LoadString(IDS_STRING_UKUPNO);
	c_rezervacije_danas.InsertColumn(8, s, LVCFMT_LEFT, 100);
	c_rezervacije_danas.SetExtendedStyle(c_rezervacije_danas.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	IspisRezervacija();

	return TRUE;
}

void CApplicationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_D_REZERVACIJE, c_rezervacije_danas);
}


BEGIN_MESSAGE_MAP(CApplicationDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ODJAVA, &CApplicationDlg::OnBnClickedButtonLogout)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_HOTEL, &CApplicationDlg::OnBnClickedButtonHotel)
	ON_BN_CLICKED(IDC_BUTTON_ZAPOSLENIK, &CApplicationDlg::OnBnClickedButtonZaposlenik)
	ON_BN_CLICKED(IDC_BUTTON_GOST, &CApplicationDlg::OnBnClickedButtonGost)
	ON_BN_CLICKED(IDC_BUTTON_SLOBODNE_SOBE, &CApplicationDlg::OnBnClickedButtonSlobodneSobe)
	ON_BN_CLICKED(IDC_BUTTON_REZERVACIJE, &CApplicationDlg::OnBnClickedButtonRezervacije)
	ON_BN_CLICKED(IDC_BUTTON_OSVJEZI, &CApplicationDlg::OnBnClickedButtonOsvjezi)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_D_REZERVACIJE, &CApplicationDlg::OnLvnColumnclickListDRezervacije)
END_MESSAGE_MAP()


// CApplicationDlg message handlers


void CApplicationDlg::OnBnClickedButtonLogout()
{
	CSeminar1Dlg Logout;
	CDialogEx::OnOK();
	Logout.DoModal();
	
}


void CApplicationDlg::OnPaint()
{
	CPaintDC dc(this); 

	RECT rc;
	GetClientRect(&rc);
	dc.MoveTo(rc.right / 3, 0);
	dc.LineTo(rc.right / 3, 200);
	dc.MoveTo((rc.right / 3) * 2, 0);
	dc.LineTo((rc.right / 3) * 2, 200);
}


void CApplicationDlg::OnBnClickedButtonHotel()
{
	CHoteli hotel;
	hotel.DoModal();
}


void CApplicationDlg::OnBnClickedButtonZaposlenik()
{
	CZaposlenici zaposlenici;
	zaposlenici.DoModal();
}


void CApplicationDlg::OnBnClickedButtonGost()
{
	CGosti gosti;
	gosti.DoModal();
	

}


void CApplicationDlg::OnBnClickedButtonSlobodneSobe()
{
	CSlobodneSobe slobodnesobe(user,this);
	slobodnesobe.DoModal();
}


void CApplicationDlg::OnBnClickedButtonRezervacije()
{
	CListaRezervacija rezervacije;
	rezervacije.DoModal();
}

void CApplicationDlg::IspisRezervacija() {
	c_rezervacije_danas.DeleteAllItems();
	CString s,s1;
	CRezervacija rez;
	rez.m_strFilter.Format(_T("[Check_OUT] = #%s#"), CTime::GetCurrentTime().Format("%m-%d-%Y"));
	rez.Open();
	while (!rez.IsEOF()) {
			s.Format(_T("%ld"), rez.m_RezervacijaID);
			int nIndex = c_rezervacije_danas.InsertItem(0, s);
			c_rezervacije_danas.SetItemText(nIndex, 1, rez.m_Datum_rezervacije.Format(_T("%d.%m.%Y")));
			s.Format(_T("%d"), rez.m_Broj_nocenja);
			c_rezervacije_danas.SetItemText(nIndex, 2, s);
			s.Format(_T("%d"), rez.m_Broj_gostiju);
			c_rezervacije_danas.SetItemText(nIndex, 3, s);
			c_rezervacije_danas.SetItemText(nIndex, 4, rez.m_Check_IN.Format(_T("%d.%m.%Y")));
			c_rezervacije_danas.SetItemText(nIndex, 5, rez.m_Check_OUT.Format(_T("%d.%m.%Y")));
			c_rezervacije_danas.SetItemText(nIndex, 6, f::DohvatiGosta(rez.m_GostID));
			c_rezervacije_danas.SetItemText(nIndex, 7, f::DohvatiZaposlenika(rez.m_ZaposlenikID));
			s1.LoadString(IDS_STRING_VALUTA);
			s.Format(_T("%.2f %s"), rez.m_Ukupna_cijena,s1);
			c_rezervacije_danas.SetItemText(nIndex, 8, s);
			rez.MoveNext();
	}
	rez.Close();

}

void CApplicationDlg::OnBnClickedButtonOsvjezi()
{
	IspisRezervacija();
}


void CApplicationDlg::OnLvnColumnclickListDRezervacije(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	poredak = pNMLV->iSubItem == stupac ? !poredak : false;
	stupac = pNMLV->iSubItem;
	SortColumn(stupac, poredak);
	*pResult = 0;
}

bool CApplicationDlg::SortColumn(int columnIndex, bool ascending)
{
	bool datum = columnIndex == 1 || columnIndex == 4 || columnIndex == 5 ?  true : false;
	sort::PARAMSORT paramsort(c_rezervacije_danas, columnIndex, ascending, datum);
	ListView_SortItemsEx(c_rezervacije_danas, sort::SortFunc, &paramsort);
	return true;
}
