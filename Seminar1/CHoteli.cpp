// CHoteli.cpp : implementation file
//

#include "stdafx.h"
#include "Seminar1.h"
#include "CHoteli.h"
#include "afxdialogex.h"
#include "Hotel.h"


// CHoteli dialog

IMPLEMENT_DYNAMIC(CHoteli, CDialogEx)

CHoteli::CHoteli(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_HOTEL, pParent)
{

}

CHoteli::~CHoteli()
{
}

BOOL CHoteli::OnInitDialog() {
	CDialog::OnInitDialog();
	hoteli.InsertColumn(0, _T("HotelID"), LVCFMT_LEFT, 90);
	hoteli.InsertColumn(1, _T("Naziv"), LVCFMT_LEFT, 150);
	hoteli.InsertColumn(2, _T("Adresa"), LVCFMT_LEFT, 150);
	hoteli.InsertColumn(3, _T("Grad"), LVCFMT_LEFT, 130);
	hoteli.InsertColumn(4, _T("Kontakt"), LVCFMT_LEFT, 130);
	hoteli.SetExtendedStyle(hoteli.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	OnBnClickedButtonOhotel();
	return TRUE;
}


void CHoteli::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_HOTELI, hoteli);
}


BEGIN_MESSAGE_MAP(CHoteli, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_OHotel, &CHoteli::OnBnClickedButtonOhotel)
END_MESSAGE_MAP()


// CHoteli message handlers


void CHoteli::OnBnClickedButtonOhotel()
{
	hoteli.DeleteAllItems();
	CHotel hotel;
	hotel.Open();
	while (!hotel.IsEOF()) {
		CString id("");
		id.Format(_T("%ld"), hotel.m_HotelID);
		int nIndex = hoteli.InsertItem(0, id);
		hoteli.SetItemText(nIndex, 1, hotel.m_Naziv);
		hoteli.SetItemText(nIndex, 2, hotel.m_Adresa);
		hoteli.SetItemText(nIndex, 3, hotel.m_Grad);
		hoteli.SetItemText(nIndex, 4, hotel.m_Kontakt);
		hotel.MoveNext();
	}
	hotel.Close();
	// TODO: Add your control notification handler code here
}
