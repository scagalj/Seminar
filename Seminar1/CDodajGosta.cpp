// CDodajGosta.cpp : implementation file
//

#include "stdafx.h"
#include "Seminar1.h"
#include "CDodajGosta.h"
#include "afxdialogex.h"
#include "Gost.h"


// CDodajGosta dialog

IMPLEMENT_DYNAMIC(CDodajGosta, CDialogEx)

CDodajGosta::CDodajGosta(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DODAJ_GOSTA, pParent)
	, m_Ime(_T(""))
	, m_Prezime(_T(""))
	, m_OIB(_T(""))
	, m_Adresa(_T(""))
	, m_Grad(_T(""))
	, m_Drzava(_T(""))
	, m_Kontakt(_T(""))
{

}

CDodajGosta::~CDodajGosta()
{
}

void CDodajGosta::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_GOST_IME, m_Ime);
	DDX_Text(pDX, IDC_EDIT_GOST_PREZIME, m_Prezime);
	DDX_Text(pDX, IDC_EDIT_GOST_OIB, m_OIB);
	DDX_Text(pDX, IDC_EDIT_GOST_ADRESA, m_Adresa);
	DDX_Text(pDX, IDC_EDIT_GOST_GRAD, m_Grad);
	DDX_Text(pDX, IDC_EDIT_GOST_DRZAVA, m_Drzava);
	DDX_Text(pDX, IDC_EDIT_GOST_KONTAKT, m_Kontakt);
}


BEGIN_MESSAGE_MAP(CDodajGosta, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDodajGosta::OnBnClickedOk)
END_MESSAGE_MAP()


// CDodajGosta message handlers


void CDodajGosta::OnBnClickedOk()
{
	CString s;
	GetDlgItemText(IDC_EDIT_GOST_IME, m_Ime);
	GetDlgItemText(IDC_EDIT_GOST_PREZIME, m_Prezime);
	GetDlgItemText(IDC_EDIT_GOST_OIB, m_OIB);
	GetDlgItemText(IDC_EDIT_GOST_ADRESA, m_Adresa);
	GetDlgItemText(IDC_EDIT_GOST_GRAD, m_Grad);
	GetDlgItemText(IDC_EDIT_GOST_DRZAVA, m_Drzava);
	GetDlgItemText(IDC_EDIT_GOST_KONTAKT, m_Kontakt);
	if (m_Ime == "" || m_Prezime == "" || m_OIB == "" || m_Adresa == "" || m_Grad  == "" || m_Drzava=="" || m_Kontakt == "") {
		s.LoadString(IDS_STRING_PAZNA_POLJA);
		AfxMessageBox(s);
		return;
	}
	CGost gost;
	gost.Open();
	gost.AddNew();
	gost.m_Ime = m_Ime;
	gost.m_Prezime = m_Prezime;
	gost.m_OIB = m_OIB;
	gost.m_Adresa = m_Adresa;
	gost.m_Grad = m_Grad;
	gost.m_Drzava = m_Drzava;
	gost.m_Kontakt = m_Kontakt;
	if (!gost.Update()) {
		s.LoadString(IDS_STRING_GOST2);
		AfxMessageBox(s);
	}
	gost.Close();
	CDialogEx::OnOK();
}
