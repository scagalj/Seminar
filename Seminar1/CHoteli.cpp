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
	return TRUE;
}


void CHoteli::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHoteli, CDialogEx)
END_MESSAGE_MAP()


// CHoteli message handlers
