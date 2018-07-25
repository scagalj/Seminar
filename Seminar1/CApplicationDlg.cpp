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
#include "CStareRezervacije.h"

// CApplicationDlg dialog

IMPLEMENT_DYNAMIC(CApplicationDlg, CDialogEx)

CApplicationDlg::CApplicationDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_App, pParent)
{

}

CApplicationDlg::CApplicationDlg(const CString &name, CWnd* pParent)
	: CDialogEx(IDD_DIALOG_App, pParent)
	, user(name)
{

}

CApplicationDlg::~CApplicationDlg()
{
}

BOOL CApplicationDlg::OnInitDialog() {

	CDialogEx::OnInitDialog();
	CWnd *label = GetDlgItem(IDC_STATIC_User);
	label->SetWindowText(user);

	c_rezervacije_danas.InsertColumn(0, _T("ID"), LVCFMT_LEFT, 30);
	c_rezervacije_danas.InsertColumn(1, _T("Datum"), LVCFMT_LEFT, 90);
	c_rezervacije_danas.InsertColumn(2, _T("Noci"), LVCFMT_LEFT, 50);
	c_rezervacije_danas.InsertColumn(3, _T("Gosti"), LVCFMT_LEFT, 50);
	c_rezervacije_danas.InsertColumn(4, _T("Check IN"), LVCFMT_LEFT, 90);
	c_rezervacije_danas.InsertColumn(5, _T("Check OUT"), LVCFMT_LEFT, 90);
	c_rezervacije_danas.InsertColumn(6, _T("Gost"), LVCFMT_LEFT, 100);
	c_rezervacije_danas.InsertColumn(7, _T("Kreirao"), LVCFMT_LEFT, 100);
	c_rezervacije_danas.InsertColumn(8, _T("Ukupna cijena"), LVCFMT_LEFT, 100);
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
	ON_BN_CLICKED(IDC_BUTTON_Logout, &CApplicationDlg::OnBnClickedButtonLogout)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_HOTEL, &CApplicationDlg::OnBnClickedButtonHotel)
	ON_BN_CLICKED(IDC_BUTTON_ZAPOSLENIK, &CApplicationDlg::OnBnClickedButtonZaposlenik)
	ON_BN_CLICKED(IDC_BUTTON_GOST, &CApplicationDlg::OnBnClickedButtonGost)
	ON_BN_CLICKED(IDC_BUTTON_SLOBODNE_SOBE, &CApplicationDlg::OnBnClickedButtonSlobodneSobe)
	ON_BN_CLICKED(IDC_BUTTON_REZERVACIJE, &CApplicationDlg::OnBnClickedButtonRezervacije)
	ON_BN_CLICKED(IDC_BUTTON_STARE_REZERVACIJE, &CApplicationDlg::OnBnClickedButtonStareRezervacije)
END_MESSAGE_MAP()


// CApplicationDlg message handlers


void CApplicationDlg::OnBnClickedButtonLogout()
{
	CSeminar1Dlg Logout;
	CDialogEx::OnOK();
	Logout.DoModal();
	// TODO: Add your control notification handler code here
}


void CApplicationDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CDialogEx::OnPaint() for painting messages
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
	// TODO: Add your control notification handler code here
}


void CApplicationDlg::OnBnClickedButtonZaposlenik()
{
	CZaposlenici zaposlenici;
	zaposlenici.DoModal();

	// TODO: Add your control notification handler code here
}


void CApplicationDlg::OnBnClickedButtonGost()
{
	CGosti gosti;
	gosti.DoModal();
	

	// TODO: Add your control notification handler code here
}


void CApplicationDlg::OnBnClickedButtonSlobodneSobe()
{
	CSlobodneSobe slobodnesobe(user,this);
	slobodnesobe.DoModal();

	// TODO: Add your control notification handler code here
}


void CApplicationDlg::OnBnClickedButtonRezervacije()
{
	CListaRezervacija rezervacije;
	rezervacije.DoModal();

	// TODO: Add your control notification handler code here
}

void CApplicationDlg::IspisRezervacija() {
	CString s;
	CRezervacija rez;
	rez.Open();
	CTime today = CTime::GetCurrentTime();
	int year = today.GetYear();
	int mon = today.GetMonth();
	int day = today.GetDay();
	while (!rez.IsEOF()) {
		if (rez.m_Check_OUT.GetYear() == year  && rez.m_Check_OUT.GetMonth() == mon && rez.m_Check_OUT.GetDay() == day) {
			s.Format(_T("%ld"), rez.m_RezervacijaID);
			int nIndex = c_rezervacije_danas.InsertItem(0, s);
			s = rez.m_Datum_rezervacije.Format(_T("%d.%m.%Y"));
			c_rezervacije_danas.SetItemText(nIndex, 1, s);
			s.Format(_T("%d"), rez.m_Broj_nocenja);
			c_rezervacije_danas.SetItemText(nIndex, 2, s);
			s.Format(_T("%d"), rez.m_Broj_gostiju);
			c_rezervacije_danas.SetItemText(nIndex, 3, s);
			s = rez.m_Check_IN.Format(_T("%d.%m.%Y"));
			c_rezervacije_danas.SetItemText(nIndex, 4, s);
			s = rez.m_Check_OUT.Format(_T("%d.%m.%Y"));
			c_rezervacije_danas.SetItemText(nIndex, 5, s);
			c_rezervacije_danas.SetItemText(nIndex, 6, IspisGosta(rez.m_GostID));
			c_rezervacije_danas.SetItemText(nIndex, 7, IspisZaposlenika(rez.m_ZaposlenikID));
			s.Format(_T("%.2f HRK"), rez.m_Ukupna_cijena);
			c_rezervacije_danas.SetItemText(nIndex, 8, s);
			rez.MoveNext();
		}
		else {
			rez.MoveNext();
		}
	}
	rez.Close();

}
CString CApplicationDlg::IspisGosta(int id) {
	CString s;
	CGost gost;
	s.Format(_T("SELECT * FROM Gost Where GostID = %d"), id);
	gost.Open(CRecordset::dynaset, s);
	s.Format(_T("%s %s"), gost.m_Ime, gost.m_Prezime);
	gost.Close();
	return s;
}
CString CApplicationDlg::IspisZaposlenika(int id) {
	CString s;
	CZaposlenik zaposlenik;
	s.Format(_T("SELECT * FROM Zaposlenik Where ZaposlenikID = %d"), id);
	zaposlenik.Open(CRecordset::dynaset, s);
	s.Format(_T("%s"), zaposlenik.m_Kor_Oznaka);
	zaposlenik.Close();
	return s;

}

void CApplicationDlg::OnBnClickedButtonStareRezervacije()
{
	CStareRezervacije sr;
	sr.DoModal();

	// TODO: Add your control notification handler code here
}
