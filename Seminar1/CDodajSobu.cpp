// CDodajSobu.cpp : implementation file
//
#include "stdafx.h"
#include "Seminar1.h"
#include "CDodajSobu.h"
#include "afxdialogex.h"


// CDodajSobu dialog

IMPLEMENT_DYNAMIC(CDodajSobu, CDialogEx)

CDodajSobu::CDodajSobu(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DODAJ_SOBU, pParent)
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

BOOL CDodajSobu::OnInitDialog() {
	CString id;
	CWnd *label = GetDlgItem(IDC_STATIC_HotelID);
	id.Format(_T("%ld"), s_HotelID);
	label->SetWindowText(id);
	label = GetDlgItem(IDC_STATIC_NazivHotela);
	label->SetWindowTextW(s_NazivHotela);

	return TRUE;
}


void CDodajSobu::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDodajSobu, CDialogEx)
END_MESSAGE_MAP()


// CDodajSobu message handlers
