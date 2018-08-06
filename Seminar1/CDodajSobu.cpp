// CDodajSobu.cpp : implementation file
//
#include "stdafx.h"
#include "Seminar1.h"
#include "CDodajSobu.h"
#include "afxdialogex.h"
#include "VrstaSobe.h"
#include "Soba.h"

// CDodajSobu dialog

IMPLEMENT_DYNAMIC(CDodajSobu, CDialogEx)

CDodajSobu::CDodajSobu(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DODAJ_SOBU, pParent)
	, s_duhan(FALSE)
	, s_ljubimci(FALSE)
{

}
CDodajSobu::CDodajSobu(const int &HotelID, const CString &Naziv_Hotela, CWnd* pParent)
	: CDialogEx(IDD_DIALOG_DODAJ_SOBU, pParent)
	, s_HotelID(HotelID)
	, s_NazivHotela(Naziv_Hotela)
{

}


CDodajSobu::~CDodajSobu()
{
}




void CDodajSobu::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SOBA_VRSTA, vrsta_soba);
	DDX_Check(pDX, IDC_CHECK_DUHAN, s_duhan);
	DDX_Check(pDX, IDC_CHECK_LJUBIMCI, s_ljubimci);
}

BOOL CDodajSobu::OnInitDialog() {
	CDialogEx::OnInitDialog();
	CString id;
	int i = 0,soba_id;
	CVrstaSobe vrstasobe;
	CWnd *label = GetDlgItem(IDC_STATIC_HotelID);
	id.Format(_T("%ld"), s_HotelID);
	label->SetWindowText(id);
	label = GetDlgItem(IDC_STATIC_NazivHotela);
	label->SetWindowTextW(s_NazivHotela);
	vrstasobe.Open();
	while (!vrstasobe.IsEOF()) {
		soba_id = vrstasobe.m_VrstaSobeID;
		vrsta_soba.AddString(vrstasobe.m_Opis);
		vrsta_soba.SetItemData(i, soba_id);
		i++;
		vrstasobe.MoveNext();
	}
	vrstasobe.Close();

	return TRUE;
}

BEGIN_MESSAGE_MAP(CDodajSobu, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_DODAJ_SOBU, &CDodajSobu::OnBnClickedButtonDodajSobu)
END_MESSAGE_MAP()


// CDodajSobu message handlers




void CDodajSobu::OnBnClickedButtonDodajSobu()
{
	CString s;
	CSoba soba;
	bool duhan, ljubimci;
	CWnd *label = GetDlgItem(IDC_STATIC_SOBA_STATUS);
	if (vrsta_soba.GetCurSel() < 0) {
		s.LoadString(IDS_STRING_SOBA1);
		label->SetWindowText(s);
		return;
	}
	CButton *m_ctlCheck1 = (CButton*)GetDlgItem(IDC_CHECK_DUHAN);
	duhan = (m_ctlCheck1->GetCheck() == 1) ? true : false;
	m_ctlCheck1 = (CButton*)GetDlgItem(IDC_CHECK_LJUBIMCI);
	ljubimci = (m_ctlCheck1->GetCheck() == 1) ? true : false;
	soba.Open();
	soba.AddNew();
	soba.m_Konzumiranje_duhana = duhan;
	soba.m_Ljubimci = ljubimci;
	soba.m_HotelID = s_HotelID;
	soba.m_VrstaSobeID = vrsta_soba.GetItemData(vrsta_soba.GetCurSel());
	if (!soba.Update()) {
		s.LoadString(IDS_STRING_SOBA2);
		label->SetWindowText(s);
	}else{
		s.LoadString(IDS_STRING_SOBA3);
		label->SetWindowText(s);
	}
	soba.Close();
	vrsta_soba.SetCurSel(-1);
}
