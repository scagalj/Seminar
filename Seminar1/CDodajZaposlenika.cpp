// CDodajZaposlenika.cpp : implementation file
//

#include "stdafx.h"
#include "Seminar1.h"
#include "CDodajZaposlenika.h"
#include "afxdialogex.h"
#include "Zaposlenik.h"


// CDodajZaposlenika dialog

IMPLEMENT_DYNAMIC(CDodajZaposlenika, CDialogEx)

CDodajZaposlenika::CDodajZaposlenika(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DODAJ_ZAPOSLENIK, pParent)
	, m_Kor_Oznaka(_T(""))
	, m_Ime(_T(""))
	, m_Lozinka(_T(""))
	, m_Prezime(_T(""))
	, m_Adresa(_T(""))
	, m_Grad(_T(""))
	, m_Drzava(_T(""))
	, m_Kontakt(_T(""))
{

}

CDodajZaposlenika::~CDodajZaposlenika()
{
}

void CDodajZaposlenika::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_Z_KOznaka, m_Kor_Oznaka);
	DDX_Text(pDX, IDC_EDIT_Z_Ime, m_Ime);
	DDX_Text(pDX, IDC_EDIT_Z_Lozinka, m_Lozinka);
	DDX_Text(pDX, IDC_EDIT_Z_Prezime, m_Prezime);
	DDX_Text(pDX, IDC_EDIT_Z_Adresa, m_Adresa);
	DDX_Text(pDX, IDC_EDIT_Z_Grad, m_Grad);
	DDX_Text(pDX, IDC_EDIT_Z_Drzava, m_Drzava);
	DDX_Text(pDX, IDC_EDIT_Z_Kontakt, m_Kontakt);
}


BEGIN_MESSAGE_MAP(CDodajZaposlenika, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDodajZaposlenika::OnBnClickedOk)
END_MESSAGE_MAP()


// CDodajZaposlenika message handlers


void CDodajZaposlenika::OnBnClickedOk()
{
	CString s;
	CWnd *label = GetDlgItem(IDC_STATIC_Z_STATUS);
	GetDlgItemText(IDC_EDIT_Z_KOznaka, m_Kor_Oznaka);
	GetDlgItemText(IDC_EDIT_Z_Lozinka, m_Lozinka);
	GetDlgItemText(IDC_EDIT_Z_Ime, m_Ime);
	GetDlgItemText(IDC_EDIT_Z_Prezime, m_Prezime);
	GetDlgItemText(IDC_EDIT_Z_Adresa, m_Adresa);
	GetDlgItemText(IDC_EDIT_Z_Grad, m_Grad);
	GetDlgItemText(IDC_EDIT_Z_Drzava, m_Drzava);
	GetDlgItemText(IDC_EDIT_Z_Kontakt, m_Kontakt);
	if (m_Kor_Oznaka == "" || m_Lozinka == "") {
		s.LoadString(IDS_STRING_PAZNA_POLJA);
		label->SetWindowText(s);
		return;
	}
	CZaposlenik zaposlenik;
	zaposlenik.Open();
	zaposlenik.AddNew();
	zaposlenik.m_Kor_Oznaka = m_Kor_Oznaka;
	zaposlenik.m_Lozinka = m_Lozinka;
	zaposlenik.m_Ime = m_Ime;
	zaposlenik.m_Prezime = m_Prezime;
	zaposlenik.m_Adresa = m_Adresa;
	zaposlenik.m_Grad = m_Grad;
	zaposlenik.m_Drzava = m_Drzava;
	zaposlenik.m_Kontakt = m_Kontakt;
	if (!zaposlenik.Update()) {
		s.LoadString(IDS_STRING_ZAPOSLENIK1);
		label->SetWindowText(s);
	}
	else {
		s.LoadString(IDS_STRING_ZAPOSLENIK2);
		label->SetWindowText(s);
	}
	zaposlenik.Close();
	CDialogEx::OnOK();
}
