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

CSlobodneSobe::CSlobodneSobe(const CString & name, CWnd * pParent) 
	: CDialogEx(IDD_DIALOG_SLOBODNE_SOBE, pParent)
	, korisnik(name)
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
	GetDlgItemText(IDC_DATETIMEPICKER_SOBE, datumin);
	UpdateData(FALSE);
	*pResult = 0;
}
//datum odlaska
void CSlobodneSobe::OnDtnDatetimechangeDatetimepickerCout(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	GetDlgItemText(IDC_DATETIMEPICKER_COUT, datumout);
	UpdateData(FALSE);
	*pResult = 0;
}

BOOL CSlobodneSobe::OnInitDialog()
{
	CString s;
	CDialogEx::OnInitDialog();
	CHotel hotel;
	hotel.Open();
	while(!hotel.IsEOF()) {
		c_hoteli.AddString(hotel.m_Naziv);
		hotel.MoveNext();
	}
	hotel.Close();

	s.LoadString(715);
	c_list_sobe.InsertColumn(0, s, LVCFMT_LEFT, 90);
	s.LoadString(718);
	c_list_sobe.InsertColumn(1, s, LVCFMT_LEFT, 90);
	s.LoadString(719);
	c_list_sobe.InsertColumn(2, s, LVCFMT_LEFT, 90);
	s.LoadString(724);
	c_list_sobe.InsertColumn(3, s, LVCFMT_LEFT, 90);
	s.LoadString(725);
	c_list_sobe.InsertColumn(4, s, LVCFMT_LEFT, 130);
	s.LoadString(722);
	c_list_sobe.InsertColumn(5, s, LVCFMT_LEFT, 130);
	s.LoadString(726);
	c_list_sobe.InsertColumn(6, s, LVCFMT_LEFT, 130);
	c_list_sobe.SetExtendedStyle(c_list_sobe.GetExtendedStyle() | LVS_EX_FULLROWSELECT);


	GetDlgItem(IDC_BUTTON_NOVA_REZERVACIJA)->EnableWindow(FALSE);

	return TRUE;
}

void CSlobodneSobe::OnCbnSelchangeComboSlobodneNazivhotela()
{
	c_hoteli.GetLBText(c_hoteli.GetCurSel(), c_hoteli_naziv);
	UpdateData(FALSE);

}

void CSlobodneSobe::OnBnClickedButtonSlobodneSobePrikaz()
{
	CString s, id;
	int i = 0;
	CHotel hotel;
	CSoba soba;
	BOOL slobodna = TRUE;
	GetDlgItem(IDC_BUTTON_NOVA_REZERVACIJA)->EnableWindow(TRUE);
	c_list_sobe.DeleteAllItems();
	if (c_hoteli_naziv == "" || datumin == "" || datumout== "") {
		s.LoadString(503);
		AfxMessageBox(s);
		return;
	}
	s.Format(_T("[Naziv] = %s"), c_hoteli_naziv);
	hotel.m_strFilter = s;
	hotel.Open();
	hotelid = hotel.m_HotelID;
	hotel.Close();
	//Dohvaæanje soba s ID odabranog hotela
	s.Format(_T("[HotelID] = %d"), hotelid);
	soba.m_strFilter = s;
	soba.Open();
	while (!soba.IsEOF()) {
		slobodna = TRUE;
		//Dohvaæanje detalja rezervacija za pojedinu sobu
		CDetaljiRezervacije detalji;
		s.Format(_T("[SobaID] = %d"), soba.m_SobaID);
		detalji.m_strFilter = s;
		detalji.Open();
		while (!detalji.IsEOF()) {
			//Dohvaæanje rezervacije na osnovi Detalja rezervacije
			CRezervacija rez;
			s.Format(_T("[RezervacijaID] = %d"), detalji.m_RezervacijaID);
			rez.m_strFilter = s;
			rez.Open();
			COleDateTime t1, t2;
			t1.ParseDateTime(datumin); //odabrani datumi
			t2.ParseDateTime(datumout); //odabrani datum
			CTime t3, t4;
			SYSTEMTIME st;
			if (t1.GetAsSystemTime(st))
				t3 = CTime(st);
			if (t2.GetAsSystemTime(st))
				t4 = CTime(st);

			if (!(t3 < rez.m_Check_IN && t4 < rez.m_Check_IN || t3 > rez.m_Check_OUT && t4 > rez.m_Check_OUT)) {
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
	CString id,s,s1;
	id.Format(_T("%ld"), sobaid);
	int nIndex = c_list_sobe.InsertItem(0, id);
	s.LoadString(720);
	s1.LoadString(721);
	duhan == TRUE ? c_list_sobe.SetItemText(nIndex, 1, s) : c_list_sobe.SetItemText(nIndex, 1, s1);
	ljubimac == TRUE ? c_list_sobe.SetItemText(nIndex, 2, s) : c_list_sobe.SetItemText(nIndex, 2, s1);
	id.Format(_T("%ld"), vrstasobeid);
	c_list_sobe.SetItemText(nIndex, 3, id);
	CVrstaSobe vrsta;
	s.Format(_T("[VrstaSobeID] = %s"), id);
	vrsta.m_strFilter = s;
	vrsta.Open();
	c_list_sobe.SetItemText(nIndex, 4, vrsta.m_Opis);
	s1.LoadString(524);
	s.Format(_T("%.2f %s"), vrsta.m_Cijena,s1);
	c_list_sobe.SetItemText(nIndex, 5, s);
	s.Format(_T("%ld"), vrsta.m_Maks_broj_gostiju);
	c_list_sobe.SetItemText(nIndex, 6, s);
	vrsta.Close();
}





void CSlobodneSobe::OnBnClickedButtonNovaRezervaciju()
{
	CNovaRezervacija nova(slobodnesobeID1, datumin,datumout,korisnik,this);
	nova.DoModal();
}
