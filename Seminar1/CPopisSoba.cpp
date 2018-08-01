// CPopisSoba.cpp : implementation file
//

#include "stdafx.h"
#include "Seminar1.h"
#include "CPopisSoba.h"
#include "afxdialogex.h"
#include "Soba.h"
#include "VrstaSobe.h"


// CPopisSoba dialog

IMPLEMENT_DYNAMIC(CPopisSoba, CDialogEx)

CPopisSoba::CPopisSoba(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_POPIS_SOBA, pParent)
{

}

CPopisSoba::CPopisSoba(const int &HotelID, const CString &Naziv_Hotela, CWnd* pParent)
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

void CPopisSoba::PopisSoba(CString x) {
	CSoba p_soba;
	CString s,s1;
	CString id=x;
	CVrstaSobe vrsta;
	s.Format(_T("[HotelID] = %d"), id);
	p_soba.m_strFilter = s;
	p_soba.Open();
	popis_soba.DeleteAllItems();
	while (!p_soba.IsEOF()) {
		id.Format(_T("%ld"), p_soba.m_SobaID);
		int nIndex = popis_soba.InsertItem(0, id);
		s.LoadString(720);
		s1.LoadString(721);
		p_soba.m_Konzumiranje_duhana == TRUE ? popis_soba.SetItemText(nIndex, 1, s) : popis_soba.SetItemText(nIndex, 1, s1);
		p_soba.m_Ljubimci == TRUE ? popis_soba.SetItemText(nIndex, 2, s) : popis_soba.SetItemText(nIndex, 2, s1);
		id.Format(_T("%ld"), p_soba.m_VrstaSobeID);
		popis_soba.SetItemText(nIndex, 3, id);
		s.Format(_T("[VrstaSobeID] = %s"), id);
		vrsta.m_strFilter = s;
		vrsta.Open();
		popis_soba.SetItemText(nIndex, 4, vrsta.m_Opis);
		s1.LoadString(524);
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
		s.LoadString(715);
		popis_soba.InsertColumn(0, s, LVCFMT_LEFT, 90);
		s.LoadString(718);
		popis_soba.InsertColumn(1, s, LVCFMT_LEFT, 130);
		s.LoadString(719);
		popis_soba.InsertColumn(2, s, LVCFMT_LEFT, 130);
		s.LoadString(724);
		popis_soba.InsertColumn(3, s, LVCFMT_LEFT, 90);
		s.LoadString(725);
		popis_soba.InsertColumn(4, s, LVCFMT_LEFT, 170);
		s.LoadString(722);
		popis_soba.InsertColumn(5, s, LVCFMT_LEFT, 90);
		popis_soba.SetExtendedStyle(popis_soba.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

		PopisSoba(id);

		GetDlgItem(IDC_BUTTON_POPIS_IZBRISI_SOBU)->EnableWindow(FALSE);
	return TRUE;
}


BEGIN_MESSAGE_MAP(CPopisSoba, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_POPIS_IZBRISI_SOBU, &CPopisSoba::OnBnClickedButtonPopisIzbrisiSobu)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_POPIS_SOBA, &CPopisSoba::OnLvnItemchangedListPopisSoba)
END_MESSAGE_MAP()


// CPopisSoba message handlers


void CPopisSoba::OnBnClickedButtonPopisIzbrisiSobu()
{

	int x = popis_soba.GetNextItem(-1, LVNI_SELECTED);
	CString t = popis_soba.GetItemText(x, 0);
	CSoba soba;
	int y = _tstoi(t);
	CString s;
	s.Format(_T("[SobaID] = %d"), y);
	soba.m_strFilter = s;
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
