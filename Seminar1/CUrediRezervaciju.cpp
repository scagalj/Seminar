// CUrediRezervaciju.cpp : implementation file
//

#include "stdafx.h"
#include "Seminar1.h"
#include "CUrediRezervaciju.h"
#include "afxdialogex.h"
#include "Funkcije.h"
#include "Rezervacija.h"
#include "DetaljiRezervacije.h"


// CUrediRezervaciju dialog

IMPLEMENT_DYNAMIC(CUrediRezervaciju, CDialogEx)

CUrediRezervaciju::CUrediRezervaciju(int rezID, CString check_in, CString check_out, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_UREDI_REZERVACIJU, pParent)
	, rezID(rezID)
	, datumin(check_in)
	, datumout(check_out)
{

}

CUrediRezervaciju::~CUrediRezervaciju()
{
}

BOOL CUrediRezervaciju::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	VERIFY(datum_in.SetTime(&sobe::Datum(datumin)));
	VERIFY(datum_out.SetTime(&sobe::Datum(datumout)));
	GetDlgItem(IDOK)->EnableWindow(FALSE);

	return TRUE;
}

void CUrediRezervaciju::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIME_UREDI_DATUMDOLASKA, datum_in);
	DDX_Control(pDX, IDC_DATETIME_UREDI_DATUMODLASKA, datum_out);
}


BEGIN_MESSAGE_MAP(CUrediRezervaciju, CDialogEx)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIME_UREDI_DATUMDOLASKA, &CUrediRezervaciju::OnDtnDatetimechangeDatetimeUrediDatumdolaska)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIME_UREDI_DATUMODLASKA, &CUrediRezervaciju::OnDtnDatetimechangeDatetimeUrediDatumodlaska)
	ON_BN_CLICKED(IDC_BUTTON_DATUM_PROVJERA, &CUrediRezervaciju::OnBnClickedButtonDatumProvjera)
	ON_BN_CLICKED(IDOK, &CUrediRezervaciju::OnBnClickedOk)
END_MESSAGE_MAP()


// CUrediRezervaciju message handlers


void CUrediRezervaciju::OnDtnDatetimechangeDatetimeUrediDatumdolaska(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	GetDlgItemText(IDC_DATETIME_UREDI_DATUMDOLASKA, datumin);
	UpdateData(TRUE);
	*pResult = 0;
}


void CUrediRezervaciju::OnDtnDatetimechangeDatetimeUrediDatumodlaska(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	GetDlgItemText(IDC_DATETIME_UREDI_DATUMODLASKA, datumout);
	UpdateData(TRUE);
	*pResult = 0;
}


void CUrediRezervaciju::OnBnClickedButtonDatumProvjera()
{
	CString s;
	CDetaljiRezervacije detalji;
	detalji.m_strFilter.Format(_T("[RezervacijaID] = %d"), rezID);
	detalji.Open();
	while (!detalji.IsEOF()) {
		detalji.MoveNext();
		if (sobe::Dostupnostsobe(detalji.m_SobaID, datumin, datumout) == FALSE) {
			s.LoadString(IDS_STRING_DATUM_NE);
			AfxMessageBox(s);
			GetDlgItem(IDOK)->EnableWindow(FALSE);
			return;
		}
		
	}
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	s.LoadString(IDS_STRING_DATUM_DA);
	AfxMessageBox(s);
	detalji.Close();
}





void CUrediRezervaciju::OnBnClickedOk()
{
	CTime t3, t4;
	t3 = sobe::Datum(datumin);
	t4 = sobe::Datum(datumout);
	CRezervacija rezervacija;
	rezervacija.m_strFilter.Format(_T("[RezervacijaID] = %d"), rezID);
	rezervacija.Open();
	rezervacija.Edit();
	rezervacija.m_Check_IN = t3;
	rezervacija.m_Check_OUT = t4;
	rezervacija.m_Datum_rezervacije = CTime::GetCurrentTime();
	rezervacija.Update();
	rezervacija.Close();

	CDialogEx::OnOK();
}
