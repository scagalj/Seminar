// CApplicationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Seminar1.h"
#include "CApplicationDlg.h"
#include "afxdialogex.h"

#include "Seminar1Dlg.h"

// CApplicationDlg dialog

IMPLEMENT_DYNAMIC(CApplicationDlg, CDialogEx)

CApplicationDlg::CApplicationDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_App, pParent)
{

}

CApplicationDlg::~CApplicationDlg()
{
}

void CApplicationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CApplicationDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_Logout, &CApplicationDlg::OnBnClickedButtonLogout)
END_MESSAGE_MAP()


// CApplicationDlg message handlers


void CApplicationDlg::OnBnClickedButtonLogout()
{
	CSeminar1Dlg Logout;
	CDialogEx::OnOK();
	Logout.DoModal();
	// TODO: Add your control notification handler code here
}
