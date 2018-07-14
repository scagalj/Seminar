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
	CString s;
	CString id=x;
	s.Format(_T("SELECT * FROM Soba Where HotelID = %s"), id);
	p_soba.Open(CRecordset::dynaset, s);
	popis_soba.DeleteAllItems();
	while (!p_soba.IsEOF()) {
		CString id;
		id.Format(_T("%ld"), p_soba.m_SobaID);
		int nIndex = popis_soba.InsertItem(0, id);
		if (p_soba.m_Konzumiranje_duhana == TRUE)
			popis_soba.SetItemText(nIndex, 1, _T("Da"));
		else {
			popis_soba.SetItemText(nIndex, 1, _T("Ne"));
		}
		if (p_soba.m_Ljubimci == TRUE)
			popis_soba.SetItemText(nIndex, 2, _T("Da"));
		else {
			popis_soba.SetItemText(nIndex, 2, _T("Ne"));
		}
		id.Format(_T("%ld"), p_soba.m_VrstaSobeID);
		popis_soba.SetItemText(nIndex, 3, id);
		CVrstaSobe vrsta;
		CString s;
		s.Format(_T("SELECT * FROM VrstaSobe Where VrstaSobeID = %s"), id);
		vrsta.Open(CRecordset::dynaset, s);
		popis_soba.SetItemText(nIndex, 4, vrsta.m_Opis);
		CString c;
		c.Format(_T("%.2f HRK"), vrsta.m_Cijena);
		popis_soba.SetItemText(nIndex, 5, c);
		vrsta.Close();
		p_soba.MoveNext();
	}
	p_soba.Close();

}

BOOL CPopisSoba::OnInitDialog() {
		CDialogEx::OnInitDialog();
		CString id;
		CWnd *label = GetDlgItem(IDC_STATIC_POPIS_HID);
		id.Format(_T("%ld"), p_HotelID);
		label->SetWindowText(id);
		label = GetDlgItem(IDC_STATIC_POPIS_HNAZIV);
		label->SetWindowTextW(p_NazivHotela);

		popis_soba.InsertColumn(0, _T("Soba ID"), LVCFMT_LEFT, 90);
		popis_soba.InsertColumn(1, _T("Duhan"), LVCFMT_LEFT, 130);
		popis_soba.InsertColumn(2, _T("LJubimci"), LVCFMT_LEFT, 130);
		popis_soba.InsertColumn(3, _T("Vrsta Sobe ID"), LVCFMT_LEFT, 90);
		popis_soba.InsertColumn(4, _T("Opis Sobe"), LVCFMT_LEFT, 170);
		popis_soba.InsertColumn(5, _T("Cijena Sobe"), LVCFMT_LEFT, 90);
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
	s.Format(_T("SELECT * FROM Soba Where SobaID = %d"), y);
	soba.Open(CRecordset::dynaset, s);
	soba.Delete();
	popis_soba.DeleteItem(x);
	soba.Close();

	// TODO: Add your control notification handler code here
}


void CPopisSoba::OnLvnItemchangedListPopisSoba(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	bool ispit = pNMLV->uNewState & LVIS_SELECTED ? TRUE : FALSE;
	GetDlgItem(IDC_BUTTON_POPIS_IZBRISI_SOBU)->EnableWindow(ispit);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}
