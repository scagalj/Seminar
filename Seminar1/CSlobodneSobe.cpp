// CSlobodneSobe.cpp : implementation file
//

#include "stdafx.h"
#include "Seminar1.h"
#include "CSlobodneSobe.h"
#include "afxdialogex.h"
#include "Hotel.h"
#include "Soba.h"
#include "Rezervacija.h"
#include "DetaljiRezervacije.h"
#include "VrstaSobe.h"
#include "CNovaRezervacija.h"

// CSlobodneSobe dialog

IMPLEMENT_DYNAMIC(CSlobodneSobe, CDialogEx)

CSlobodneSobe::CSlobodneSobe(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SLOBODNE_SOBE, pParent)
	, c_hoteli_naziv(_T(""))
{

}

CSlobodneSobe::~CSlobodneSobe()
{
}

void CSlobodneSobe::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER_SOBE, t_SlobodneSobe);
	DDX_Control(pDX, IDC_COMBO_SLOBODNE_NAZIVHOTELA, c_hoteli);
	DDX_CBString(pDX, IDC_COMBO_SLOBODNE_NAZIVHOTELA, c_hoteli_naziv);
	DDX_Control(pDX, IDC_LIST_SLOBODNE_SOBE_POPIS, c_list_sobe);
	DDX_Control(pDX, IDC_DATETIMEPICKER_COUT, t_slobodnesobe_out);
}


BEGIN_MESSAGE_MAP(CSlobodneSobe, CDialogEx)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_SOBE, &CSlobodneSobe::OnDtnDatetimechangeDatetimepickerSobe)
	ON_CBN_SELCHANGE(IDC_COMBO_SLOBODNE_NAZIVHOTELA, &CSlobodneSobe::OnCbnSelchangeComboSlobodneNazivhotela)
	ON_BN_CLICKED(IDC_BUTTON_SLOBODNE_SOBE_PRIKAZ, &CSlobodneSobe::OnBnClickedButtonSlobodneSobePrikaz)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_COUT, &CSlobodneSobe::OnDtnDatetimechangeDatetimepickerCout)
	ON_BN_CLICKED(IDC_BUTTON_NOVA_REZERVACIJA, &CSlobodneSobe::OnBnClickedButtonNovaRezervaciju)
END_MESSAGE_MAP()


// CSlobodneSobe message handlers

//datum dolaska
void CSlobodneSobe::OnDtnDatetimechangeDatetimepickerSobe(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: Add your control notification handler code here
	GetDlgItemText(IDC_DATETIMEPICKER_SOBE, datumin);
	UpdateData(FALSE);
	*pResult = 0;
}
//datum odlaska
void CSlobodneSobe::OnDtnDatetimechangeDatetimepickerCout(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: Add your control notification handler code here
	GetDlgItemText(IDC_DATETIMEPICKER_COUT, datumout);
	UpdateData(FALSE);
	*pResult = 0;
}

BOOL CSlobodneSobe::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CHotel hotel;
	hotel.Open();
	while(!hotel.IsEOF()) {
		c_hoteli.AddString(hotel.m_Naziv);
		hotel.MoveNext();
	}
	hotel.Close();

	
	c_list_sobe.InsertColumn(0, _T("SobaID"), LVCFMT_LEFT, 90);
	c_list_sobe.InsertColumn(1, _T("Duhan"), LVCFMT_LEFT, 90);
	c_list_sobe.InsertColumn(2, _T("Ljubimac"), LVCFMT_LEFT, 90);
	c_list_sobe.InsertColumn(3, _T("Vrsta ID"), LVCFMT_LEFT, 90);
	c_list_sobe.InsertColumn(4, _T("Opic"), LVCFMT_LEFT, 130);
	c_list_sobe.InsertColumn(5, _T("Cijena"), LVCFMT_LEFT, 130);
	c_list_sobe.InsertColumn(6, _T("Max broj osoba"), LVCFMT_LEFT, 130);
	c_list_sobe.SetExtendedStyle(c_list_sobe.GetExtendedStyle() | LVS_EX_FULLROWSELECT);


	GetDlgItem(IDC_BUTTON_NOVA_REZERVACIJA)->EnableWindow(FALSE);
	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CSlobodneSobe::OnCbnSelchangeComboSlobodneNazivhotela()
{
	c_hoteli.GetLBText(c_hoteli.GetCurSel(), c_hoteli_naziv);
	UpdateData(FALSE);

}

void CSlobodneSobe::OnBnClickedButtonSlobodneSobePrikaz()
{
	int i = 0;
	GetDlgItem(IDC_BUTTON_NOVA_REZERVACIJA)->EnableWindow(TRUE);
	c_list_sobe.DeleteAllItems();
	BOOL slobodna = TRUE;
	if (c_hoteli_naziv == "" || datumin == "" || datumout== "") {
		AfxMessageBox(_T("Polja ne smiju biti prazna"));
		return;
	}
	CHotel hotel;
	CString s,id;
	s.Format(_T("SELECT * FROM Hotel Where Naziv = '%s'"), c_hoteli_naziv);
	hotel.Open(CRecordset::dynaset, s);
	hotelid = hotel.m_HotelID;
	hotel.Close();
	//Dohvaćanje soba s ID odabranog hotela
	CSoba soba;
	s.Format(_T("SELECT * FROM Soba Where HotelID = %d"), hotelid); 
	soba.Open(CRecordset::dynaset, s);
	while (!soba.IsEOF()) {
		slobodna = TRUE;
		//Dohvaćanje detalja rezervacija za pojedinu sobu
		CDetaljiRezervacije detalji;
		s.Format(_T("SELECT * FROM DetaljiRezervacije Where SobaID = %d"), soba.m_SobaID);
		detalji.Open(CRecordset::dynaset, s);
		while (!detalji.IsEOF()) {
			//Dohvaćanje rezervacije na osnovi Detalja rezervacije
			CRezervacija rez;
			s.Format(_T("SELECT * FROM Rezervacija Where RezervacijaID = %d"), detalji.m_RezervacijaID);
			rez.Open(CRecordset::dynaset, s);
			COleDateTime t1, t2;
			CTime odabraniDatumIN, odabraniDatumOUT;
			t1.ParseDateTime(datumin); //odabrani datumi
			t2.ParseDateTime(datumout); //odabrani datum
			CTime t3, t4;
			SYSTEMTIME st;
			if (t1.GetAsSystemTime(st))
				t3 = CTime(st);
			if (t2.GetAsSystemTime(st))
				t4 = CTime(st);

			if (t3 < rez.m_Check_IN && t4 < rez.m_Check_IN || t3 > rez.m_Check_OUT && t4 > rez.m_Check_OUT) {
				//Soba je slobodna
			}
			else {
				//Soba je zauzeta
				slobodna = FALSE;
				break;
			}
			rez.Close();
			detalji.MoveNext();
		}

		detalji.Close();
		if (slobodna == TRUE) {
			IspisSobe(soba.m_SobaID, soba.m_Konzumiranje_duhana, soba.m_Ljubimci, soba.m_VrstaSobeID);
			slobodnesobeID1[i] = soba.m_SobaID;
			i++;
		}
		soba.MoveNext();
	}
	soba.Close();
	
}

void CSlobodneSobe::IspisSobe(long sobaid, bool duhan, bool ljubimac, long vrstasobeid){
	CString id;
	id.Format(_T("%ld"), sobaid);
	int nIndex = c_list_sobe.InsertItem(0, id);
	if (duhan == TRUE)
		c_list_sobe.SetItemText(nIndex, 1, _T("Da"));
	else {
		c_list_sobe.SetItemText(nIndex, 1, _T("Ne"));
	}
	if (ljubimac == TRUE)
		c_list_sobe.SetItemText(nIndex, 2, _T("Da"));
	else {
		c_list_sobe.SetItemText(nIndex, 2, _T("Ne"));
	}
	id.Format(_T("%ld"), vrstasobeid);
	c_list_sobe.SetItemText(nIndex, 3, id);
	CVrstaSobe vrsta;
	CString s;
	s.Format(_T("SELECT * FROM VrstaSobe Where VrstaSobeID = %s"), id);
	vrsta.Open(CRecordset::dynaset, s);
	c_list_sobe.SetItemText(nIndex, 4, vrsta.m_Opis);
	CString c;
	c.Format(_T("%.2f HRK"), vrsta.m_Cijena);
	c_list_sobe.SetItemText(nIndex, 5, c);
	c.Format(_T("%ld"), vrsta.m_Maks_broj_gostiju);
	c_list_sobe.SetItemText(nIndex, 6, c);
	vrsta.Close();
}





void CSlobodneSobe::OnBnClickedButtonNovaRezervaciju()
{
	CNovaRezervacija nova(slobodnesobeID1, datumin,datumout,this);
	nova.DoModal();
	// TODO: Add your control notification handler code here
}
