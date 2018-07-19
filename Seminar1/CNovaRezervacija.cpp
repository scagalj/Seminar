// CNovaRezervacija.cpp : implementation file
//

#include "stdafx.h"
#include "Seminar1.h"
#include "CNovaRezervacija.h"
#include "afxdialogex.h"


// CNovaRezervacija dialog

IMPLEMENT_DYNAMIC(CNovaRezervacija, CDialogEx)

CNovaRezervacija::CNovaRezervacija(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_NOVA_REZERVACIJA, pParent)
	, m_Ime(_T(""))
	, m_Prezime(_T(""))
	, m_Adresa(_T(""))
	, m_Grad(_T(""))
	, m_Drzava(_T(""))
	, m_OIB(_T(""))
	, m_Kontakt(_T(""))
	, m_pretraziOIB(_T(""))
	, m_Brojgostiju(_T(""))
	, m_IDSobe(_T(""))
{

}
CNovaRezervacija::CNovaRezervacija(int *sobeID, CString datumD, CString datumO, CWnd* pParent)
	: CDialogEx(IDD_DIALOG_NOVA_REZERVACIJA, pParent)
	,datumIN(datumD)
	,datumOUT(datumO)
{
	int i = 0;
	while (*sobeID != '\0') {
		slobodnesobeID[i] = *sobeID;
		sobeID++;
		i++;
	}

}

CNovaRezervacija::~CNovaRezervacija()
{
}

void CNovaRezervacija::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_R_IME, m_Ime);
	DDX_Text(pDX, IDC_EDIT_R_PREZIME, m_Prezime);
	DDX_Text(pDX, IDC_EDIT_R_ADRESA, m_Adresa);
	DDX_Text(pDX, IDC_EDIT_R_GRAD, m_Grad);
	DDX_Text(pDX, IDC_EDIT_R_DRZAVA, m_Drzava);
	DDX_Text(pDX, IDC_EDIT_R_OIB, m_OIB);
	DDX_Text(pDX, IDC_EDIT_R_KONTAKT, m_Kontakt);
	DDX_Text(pDX, IDC_EDIT_R_OIB_P, m_pretraziOIB);
	DDX_Text(pDX, IDC_EDIT_R_BROJGOSTIJU, m_Brojgostiju);
	DDX_Text(pDX, IDC_EDIT_R_IDSOBE, m_IDSobe);
	DDX_Control(pDX, IDC_LIST_R_ODABRANESOBE, c_OdabraneSobe);
}


BEGIN_MESSAGE_MAP(CNovaRezervacija, CDialogEx)
END_MESSAGE_MAP()


// CNovaRezervacija message handlers
