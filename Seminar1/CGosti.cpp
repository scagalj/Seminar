// CGosti.cpp : implementation file
//

#include "stdafx.h"
#include "Seminar1.h"
#include "CGosti.h"
#include "afxdialogex.h"
#include "Gost.h"
#include "CDodajGosta.h"
#include "Funkcije.h"


// CGosti dialog

IMPLEMENT_DYNAMIC(CGosti, CDialogEx)

CGosti::CGosti(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_GOST, pParent)
	,poredak(true)
	,stupac(-1)
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
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_GOSTI, &CGosti::OnLvnColumnclickListGosti)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_GOSTI, &CGosti::OnLvnItemchangedListGosti)
	ON_BN_CLICKED(IDC_BUTTON_GOST_IZBRISI, &CGosti::OnBnClickedButtonGostIzbrisi)
END_MESSAGE_MAP()


// CGosti message handlers


BOOL CGosti::OnInitDialog()
{
	CString s;
	CDialogEx::OnInitDialog();
	s.LoadString(IDS_STRING_ID);
	gosti.InsertColumn(0,s, LVCFMT_LEFT, 50);
	s.LoadString(IDS_STRING_IME);
	gosti.InsertColumn(1, s, LVCFMT_LEFT, 80);
	s.LoadString(IDS_STRING_PREZIME);
	gosti.InsertColumn(2, s, LVCFMT_LEFT, 80);
	s.LoadString(IDS_STRING_OIB);
	gosti.InsertColumn(3, s, LVCFMT_LEFT, 100);
	s.LoadString(IDS_STRING_ADRESA);
	gosti.InsertColumn(4, s, LVCFMT_LEFT, 100);
	s.LoadString(IDS_STRING_GRAD);
	gosti.InsertColumn(5, s, LVCFMT_LEFT, 100);
	s.LoadString(IDS_STRING_DRZAVA);
	gosti.InsertColumn(6, s, LVCFMT_LEFT, 100);
	s.LoadString(IDS_STRING_KONTAKT);
	gosti.InsertColumn(7, s, LVCFMT_LEFT, 100);
	gosti.SetExtendedStyle(gosti.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	GetDlgItem(IDC_BUTTON_GOST_IZBRISI)->EnableWindow(FALSE);
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
		s.LoadString(IDS_STRING_GOST1);
		AfxMessageBox(s);
	}
}


void CGosti::OnLvnColumnclickListGosti(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	poredak = pNMLV->iSubItem == stupac ? !poredak : false;
	stupac = pNMLV->iSubItem;
	SortColumn(stupac, poredak);
	*pResult = 0;
}

bool CGosti::SortColumn(int columnIndex, bool ascending)
{
	sort::PARAMSORT paramsort(gosti, columnIndex, ascending, false);
	ListView_SortItemsEx(gosti, sort::SortFunc, &paramsort);
	return true;
}

void CGosti::OnLvnItemchangedListGosti(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	bool ispit = pNMLV->uNewState & LVIS_SELECTED ? TRUE : FALSE;
	GetDlgItem(IDC_BUTTON_GOST_IZBRISI)->EnableWindow(ispit);
	*pResult = 0;
}


void CGosti::OnBnClickedButtonGostIzbrisi()
{

	int x = gosti.GetNextItem(-1, LVNI_SELECTED);
	CString t = gosti.GetItemText(x, 0);
	CGost gost;
	gost.m_strFilter.Format(_T("[GostID] = %d"), _tstoi(t));
	gost.Open();
	gost.Delete();
	gosti.DeleteItem(x);
	gost.Close();
}
