// Seminar1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Seminar1.h"
#include "Seminar1Dlg.h"
#include "afxdialogex.h"

#include "CApplicationDlg.h"
#include "Zaposlenik.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSeminar1Dlg dialog



CSeminar1Dlg::CSeminar1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SEMINAR1_DIALOG, pParent)
	, m_Korisnik(_T(""))
	, m_Lozinka(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSeminar1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Korisnik, m_Korisnik);
	DDX_Text(pDX, IDC_Lozinka, m_Lozinka);
}

BEGIN_MESSAGE_MAP(CSeminar1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_LOGIRAN, &CSeminar1Dlg::OnBnClickedLogin)
END_MESSAGE_MAP()


// CSeminar1Dlg message handlers

BOOL CSeminar1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon


	return TRUE;
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSeminar1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSeminar1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSeminar1Dlg::OnBnClickedLogin()
{

	UpdateData(TRUE);
	CZaposlenik login;
	CString korisnik, lozinka, s;
	bool t = FALSE;
	login.Open();
	while (!login.IsEOF()) {
		if (m_Korisnik == login.m_Kor_Oznaka && m_Lozinka == login.m_Lozinka)
		{
			korisnik = login.m_Kor_Oznaka;
			lozinka = login.m_Lozinka;
			t = TRUE;
			break;
		}login.MoveNext();
	
	}
	
	if (t) {
		CApplicationDlg App(korisnik,this);
		CDialogEx::OnOK();
		App.DoModal();

	}
	else {
		s.LoadString(519);
		AfxMessageBox(s);
	}
	login.Close();
	
	UpdateData(FALSE);
}
