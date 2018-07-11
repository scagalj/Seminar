// CHoteli.cpp : implementation file
//

#include "stdafx.h"
#include "Seminar1.h"
#include "CHoteli.h"
#include "afxdialogex.h"


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
	return TRUE;
}


void CHoteli::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_HOTELI, hoteli);
}


BEGIN_MESSAGE_MAP(CHoteli, CDialogEx)
END_MESSAGE_MAP()


// CHoteli message handlers
