// CGosti.cpp : implementation file
//

#include "stdafx.h"
#include "Seminar1.h"
#include "CGosti.h"
#include "afxdialogex.h"
#include "Gost.h"
#include "CDodajGosta.h"


// CGosti dialog

IMPLEMENT_DYNAMIC(CGosti, CDialogEx)

CGosti::CGosti(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_GOST, pParent)
{

}

CGosti::~CGosti()
{
}

void CGosti::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_GOSTI, gosti);
}


BEGIN_MESSAGE_MAP(CGosti, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_DODAJ_GOSTA, &CGosti::OnBnClickedButtonDodajGosta)
END_MESSAGE_MAP()


// CGosti message handlers


BOOL CGosti::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	gosti.InsertColumn(0, _T("ID"), LVCFMT_LEFT, 50);
	gosti.InsertColumn(1, _T("Ime"), LVCFMT_LEFT, 80);
	gosti.InsertColumn(2, _T("Prezime"), LVCFMT_LEFT, 80);
	gosti.InsertColumn(3, _T("OIB"), LVCFMT_LEFT, 100);
	gosti.InsertColumn(4, _T("Adresa"), LVCFMT_LEFT, 100);
	gosti.InsertColumn(5, _T("Grad"), LVCFMT_LEFT, 100);
	gosti.InsertColumn(6, _T("Drzava"), LVCFMT_LEFT, 100);
	gosti.InsertColumn(7, _T("Kontakt"), LVCFMT_LEFT, 100);
	gosti.SetExtendedStyle(gosti.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	IspisiGoste();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
void CGosti::IspisiGoste() {
	gosti.DeleteAllItems();
	CGost gost;
	gost.Open();
	while (!gost.IsEOF()) {
		CString id;
		id.Format(_T("%ld"), gost.m_GostID);
		int nIndex = gosti.InsertItem(0, id);
		gosti.SetItemText(nIndex, 1, gost.m_Ime);
		gosti.SetItemText(nIndex, 2, gost.m_Prezime);
		gosti.SetItemText(nIndex, 3, gost.m_OIB);
		gosti.SetItemText(nIndex, 4, gost.m_Adresa);
		gosti.SetItemText(nIndex, 5, gost.m_Grad);
		gosti.SetItemText(nIndex, 6, gost.m_Drzava);
		gosti.SetItemText(nIndex, 7, gost.m_Kontakt);
		gost.MoveNext();
	}
	gost.Close();

}



void CGosti::OnBnClickedButtonDodajGosta()
{
	CDodajGosta gost;
	int x = gost.DoModal();
	if (x == IDOK) {
		IspisiGoste();
		AfxMessageBox(_T("Gost uspiješno dodan"));
	}

	// TODO: Add your control notification handler code here
}
