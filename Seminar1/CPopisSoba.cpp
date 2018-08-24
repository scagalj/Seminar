// CPopisSoba.cpp : implementation file
//

#include "stdafx.h"
#include "Seminar1.h"
#include "CPopisSoba.h"
#include "afxdialogex.h"
#include "Soba.h"
#include "VrstaSobe.h"
#include "Funkcije.h"


// CPopisSoba dialog

IMPLEMENT_DYNAMIC(CPopisSoba, CDialogEx)

CPopisSoba::CPopisSoba(const int HotelID, const CString Naziv_Hotela, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_POPIS_SOBA, pParent)
	, p_HotelID(HotelID)
	, p_NazivHotela(Naziv_Hotela)
{

}


CPopisSoba::~CPopisSoba()
{
}

void CPopisSoba::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_POPIS_SOBA, popis_soba);
}

void CPopisSoba::PopisSoba(int x) {
	CSoba p_soba;
	CString s,s1;
	CVrstaSobe vrsta;
	p_soba.m_strFilter.Format(_T("[HotelID] = %d"), x);
	p_soba.Open();
	popis_soba.DeleteAllItems();
	while (!p_soba.IsEOF()) {
		s.Format(_T("%ld"), p_soba.m_SobaID);
		int nIndex = popis_soba.InsertItem(0, s);
		s.LoadString(IDS_STRING_DA);
		s1.LoadString(IDS_STRING_NE);
		p_soba.m_Konzumiranje_duhana == TRUE ? popis_soba.SetItemText(nIndex, 1, s) : popis_soba.SetItemText(nIndex, 1, s1);
		p_soba.m_Ljubimci == TRUE ? popis_soba.SetItemText(nIndex, 2, s) : popis_soba.SetItemText(nIndex, 2, s1);
		s.Format(_T("%ld"), p_soba.m_VrstaSobeID);
		popis_soba.SetItemText(nIndex, 3, s);
		vrsta.m_strFilter.Format(_T("[VrstaSobeID] = %ld"), p_soba.m_VrstaSobeID);
		vrsta.Open();
		popis_soba.SetItemText(nIndex, 4, vrsta.m_Opis);
		s1.LoadString(IDS_STRING_VALUTA);
		s.Format(_T("%.2f %s"), vrsta.m_Cijena,s1);
		popis_soba.SetItemText(nIndex, 5, s);
		vrsta.Close();
		p_soba.MoveNext();
	}
	p_soba.Close();

}

BOOL CPopisSoba::OnInitDialog() {
		CDialogEx::OnInitDialog();
		CString id,s;
		CWnd *label = GetDlgItem(IDC_STATIC_POPIS_HID);
		id.Format(_T("%ld"), p_HotelID);
		label->SetWindowText(id);
		label = GetDlgItem(IDC_STATIC_POPIS_HNAZIV);
		label->SetWindowTextW(p_NazivHotela);
		s.LoadString(IDS_STRING_ID);
		popis_soba.InsertColumn(0, s, LVCFMT_LEFT, 90);
		s.LoadString(IDS_STRING_DUHAN);
		popis_soba.InsertColumn(1, s, LVCFMT_LEFT, 130);
		s.LoadString(IDS_STRING_LJUBIMAC);
		popis_soba.InsertColumn(2, s, LVCFMT_LEFT, 130);
		s.LoadString(IDS_STRING_VRSTA_SOBE);
		popis_soba.InsertColumn(3, s, LVCFMT_LEFT, 90);
		s.LoadString(IDS_STRING_OPIS_SOBE);
		popis_soba.InsertColumn(4, s, LVCFMT_LEFT, 170);
		s.LoadString(IDS_STRING_CIJENA);
		popis_soba.InsertColumn(5, s, LVCFMT_LEFT, 90);
		popis_soba.SetExtendedStyle(popis_soba.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

		PopisSoba(p_HotelID);

		GetDlgItem(IDC_BUTTON_POPIS_IZBRISI_SOBU)->EnableWindow(FALSE);
	return TRUE;
}


BEGIN_MESSAGE_MAP(CPopisSoba, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_POPIS_IZBRISI_SOBU, &CPopisSoba::OnBnClickedButtonPopisIzbrisiSobu)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_POPIS_SOBA, &CPopisSoba::OnLvnItemchangedListPopisSoba)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_POPIS_SOBA, &CPopisSoba::OnLvnColumnclickListPopisSoba)
END_MESSAGE_MAP()


// CPopisSoba message handlers


void CPopisSoba::OnBnClickedButtonPopisIzbrisiSobu()
{

	int x = popis_soba.GetNextItem(-1, LVNI_SELECTED);
	CString t = popis_soba.GetItemText(x, 0);
	CSoba soba;
	CString s;
	soba.m_strFilter.Format(_T("[SobaID] = %d"), _tstoi(t));
	soba.Open();
	soba.Delete();
	popis_soba.DeleteItem(x);
	soba.Close();
}


void CPopisSoba::OnLvnItemchangedListPopisSoba(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	bool ispit = pNMLV->uNewState & LVIS_SELECTED ? TRUE : FALSE;
	GetDlgItem(IDC_BUTTON_POPIS_IZBRISI_SOBU)->EnableWindow(ispit);
	*pResult = 0;
}


void CPopisSoba::OnLvnColumnclickListPopisSoba(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	SortColumn(pNMLV->iSubItem, poredak);
	poredak == 0 ? poredak = 1 : poredak = 0;
	*pResult = 0;
}


bool CPopisSoba::SortColumn(int columnIndex, bool ascending)
{
	sort::PARAMSORT paramsort(popis_soba, columnIndex, ascending, false);
	ListView_SortItemsEx(popis_soba, sort::SortFunc, &paramsort);
	return true;
}