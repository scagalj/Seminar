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
	CString s;
	CDialogEx::OnInitDialog();
	s.LoadString(715);
	gosti.InsertColumn(0,s, LVCFMT_LEFT, 50);
	s.LoadString(708);
	gosti.InsertColumn(1, s, LVCFMT_LEFT, 80);
	s.LoadString(709);
	gosti.InsertColumn(2, s, LVCFMT_LEFT, 80);
	s.LoadString(710);
	gosti.InsertColumn(3, s, LVCFMT_LEFT, 100);
	s.LoadString(711);
	gosti.InsertColumn(4, s, LVCFMT_LEFT, 100);
	s.LoadString(712);
	gosti.InsertColumn(5, s, LVCFMT_LEFT, 100);
	s.LoadString(713);
	gosti.InsertColumn(6, s, LVCFMT_LEFT, 100);
	s.LoadString(714);
	gosti.InsertColumn(7, s, LVCFMT_LEFT, 100);
	gosti.SetExtendedStyle(gosti.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	IspisiGoste();

	return TRUE;
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
	CString s;
	int x = gost.DoModal();
	if (x == IDOK) {
		IspisiGoste();
		s.LoadString(504);
		AfxMessageBox(s);
	}
}
