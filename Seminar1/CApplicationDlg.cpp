// CApplicationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Seminar1.h"
#include "CApplicationDlg.h"
#include "afxdialogex.h"
#include "CHoteli.h"
#include "Seminar1Dlg.h"
#include "CZaposlenici.h"
#include "CGosti.h"

// CApplicationDlg dialog

IMPLEMENT_DYNAMIC(CApplicationDlg, CDialogEx)

CApplicationDlg::CApplicationDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_App, pParent)
{

}

CApplicationDlg::CApplicationDlg(const CString &name, CWnd* pParent)
	: CDialogEx(IDD_DIALOG_App, pParent)
	, user(name)
{

}

CApplicationDlg::~CApplicationDlg()
{
}

BOOL CApplicationDlg::OnInitDialog() {
	CWnd *label = GetDlgItem(IDC_STATIC_User);
	label->SetWindowText(user);
	
	return TRUE;
}

void CApplicationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

}


BEGIN_MESSAGE_MAP(CApplicationDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_Logout, &CApplicationDlg::OnBnClickedButtonLogout)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_HOTEL, &CApplicationDlg::OnBnClickedButtonHotel)
	ON_BN_CLICKED(IDC_BUTTON_ZAPOSLENIK, &CApplicationDlg::OnBnClickedButtonZaposlenik)
	ON_BN_CLICKED(IDC_BUTTON_GOST, &CApplicationDlg::OnBnClickedButtonGost)
END_MESSAGE_MAP()


// CApplicationDlg message handlers


void CApplicationDlg::OnBnClickedButtonLogout()
{
	CSeminar1Dlg Logout;
	CDialogEx::OnOK();
	Logout.DoModal();
	// TODO: Add your control notification handler code here
}


void CApplicationDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CDialogEx::OnPaint() for painting messages
	RECT rc;
	GetClientRect(&rc);
	dc.MoveTo(rc.right / 3, 0);
	dc.LineTo(rc.right / 3, 200);
	dc.MoveTo((rc.right / 3) * 2, 0);
	dc.LineTo((rc.right / 3) * 2, 200);
}


void CApplicationDlg::OnBnClickedButtonHotel()
{
	CHoteli hotel;
	hotel.DoModal();
	// TODO: Add your control notification handler code here
}


void CApplicationDlg::OnBnClickedButtonZaposlenik()
{
	CZaposlenici zaposlenici;
	zaposlenici.DoModal();

	// TODO: Add your control notification handler code here
}


void CApplicationDlg::OnBnClickedButtonGost()
{
	CGosti gosti;
	gosti.DoModal();
	

	// TODO: Add your control notification handler code here
}
