// CGosti.cpp : implementation file
//

#include "stdafx.h"
#include "Seminar1.h"
#include "CGosti.h"
#include "afxdialogex.h"


// CGosti dialog

IMPLEMENT_DYNAMIC(CGosti, CDialogEx)

CGosti::CGosti(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_GOST, pParent)
{

}

CGosti::~CGosti()
{
}

void CGosti::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGosti, CDialogEx)
END_MESSAGE_MAP()


// CGosti message handlers
