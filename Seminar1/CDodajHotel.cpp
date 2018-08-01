// CDodajHotel.cpp : implementation file
//

#include "stdafx.h"
#include "Seminar1.h"
#include "CDodajHotel.h"
#include "afxdialogex.h"
#include "Hotel.h"


// CDodajHotel dialog

IMPLEMENT_DYNAMIC(CDodajHotel, CDialogEx)

CDodajHotel::CDodajHotel(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DODAJ_HOTEL, pParent)
	, h_Naziv(_T(""))
	, h_Adresa(_T(""))
	, h_Grad(_T(""))
	, h_Kontakt(_T(""))
{

}

CDodajHotel::~CDodajHotel()
{
}

void CDodajHotel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_Hotel_Naziv, h_Naziv);
	DDX_Text(pDX, IDC_EDIT_Hotel_Adresa, h_Adresa);
	DDX_Text(pDX, IDC_EDIT_Hotel_Grad, h_Grad);
	DDX_Text(pDX, IDC_EDIT_Hotel_Kontakt, h_Kontakt);
}


BEGIN_MESSAGE_MAP(CDodajHotel, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_DODAJ_HOTEL, &CDodajHotel::OnBnClickedButtonHotelAdd)
END_MESSAGE_MAP()


// CDodajHotel message handlers


void CDodajHotel::OnBnClickedButtonHotelAdd()
{
	CString s;
	GetDlgItemText(IDC_EDIT_Hotel_Naziv, h_Naziv);
	GetDlgItemText(IDC_EDIT_Hotel_Adresa, h_Adresa);
	GetDlgItemText(IDC_EDIT_Hotel_Grad, h_Grad);
	GetDlgItemText(IDC_EDIT_Hotel_Kontakt, h_Kontakt);
	CWnd *label = GetDlgItem(IDC_STATIC_Hotel_Stanje);
	if (h_Naziv == "" || h_Adresa == "" || h_Grad == "") {
		s.LoadString(IDS_STRING_PAZNA_POLJA);
		label->SetWindowText(s);	
		return;
	}
	
	CHotel hotel;
	hotel.Open();
	hotel.AddNew();
	hotel.m_Naziv = h_Naziv;
	hotel.m_Adresa = h_Adresa;
	hotel.m_Grad = h_Grad;
	hotel.m_Kontakt = h_Kontakt;
	if (!hotel.Update()) {
		s.LoadString(IDS_STRING_HOTEL1);
		label->SetWindowText(s);
		return;
	}
	s.LoadString(IDS_STRING_HOTEL2);
	label->SetWindowText(s);
	hotel.Close();
	CDialogEx::OnOK();
}
