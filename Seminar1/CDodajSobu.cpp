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
	, s_vrsta_soba(_T(""))
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
	DDX_CBString(pDX, IDC_COMBO_SOBA_VRSTA, s_vrsta_soba);
	DDX_Check(pDX, IDC_CHECK_DUHAN, s_duhan);
	DDX_Check(pDX, IDC_CHECK_LJUBIMCI, s_ljubimci);
}

BOOL CDodajSobu::OnInitDialog() {
	CDialogEx::OnInitDialog();
	CString id;
	CWnd *label = GetDlgItem(IDC_STATIC_HotelID);
	id.Format(_T("%ld"), s_HotelID);
	label->SetWindowText(id);
	label = GetDlgItem(IDC_STATIC_NazivHotela);
	label->SetWindowTextW(s_NazivHotela);
	CVrstaSobe vrstasobe;
	vrstasobe.Open();
	while (!vrstasobe.IsEOF()) {
		vrsta_soba.AddString(vrstasobe.m_Opis);
		vrstasobe.MoveNext();
	}
	vrstasobe.Close();
	return TRUE;
}

BEGIN_MESSAGE_MAP(CDodajSobu, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_SOBA_VRSTA, &CDodajSobu::OnCbnSelchangeComboSobaVrsta)
	ON_BN_CLICKED(IDC_BUTTON_DODAJ_SOBU, &CDodajSobu::OnBnClickedButtonDodajSobu)
END_MESSAGE_MAP()


// CDodajSobu message handlers


void CDodajSobu::OnCbnSelchangeComboSobaVrsta()
{
	vrsta_soba.GetLBText(vrsta_soba.GetCurSel(), s_vrsta_soba);
	UpdateData(FALSE);
}


void CDodajSobu::OnBnClickedButtonDodajSobu()
{
	//LoadString(hInstance, IDS_STRING1, s, sizeof s);
	CString s;
	CWnd *label = GetDlgItem(IDC_STATIC_SOBA_STATUS);
	if (vrsta_soba.GetCurSel() < 0) {
		s.LoadString(500);
		label->SetWindowText(s);
		return;
	}
	bool duhan,ljubimci;
	CButton *m_ctlCheck1 = (CButton*)GetDlgItem(IDC_CHECK_DUHAN);
	duhan = (m_ctlCheck1->GetCheck() == 1) ? true : false;
	m_ctlCheck1 = (CButton*)GetDlgItem(IDC_CHECK_LJUBIMCI);
	ljubimci = (m_ctlCheck1->GetCheck() == 1) ? true : false;
	s.Format(_T("SELECT * FROM VrstaSobe Where Opis = '%s'"), s_vrsta_soba);
	CVrstaSobe sobe;
	sobe.Open(CRecordset::dynaset, s);
	int id = sobe.m_VrstaSobeID;
	CSoba soba;
	soba.Open();
	soba.AddNew();
	soba.m_Konzumiranje_duhana = duhan;
	soba.m_Ljubimci = ljubimci;
	soba.m_HotelID = s_HotelID;
	soba.m_VrstaSobeID = id;
	if (!soba.Update()) {
		s.LoadString(501);
		label->SetWindowText(s);
	}else{
		s.LoadString(502);
		label->SetWindowText(s);
	}
	sobe.Close();
	soba.Close();
	vrsta_soba.SetCurSel(-1);
}
