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
	UpdateData(TRUE);
	*pResult = 0;
}
//datum odlaska
void CSlobodneSobe::OnDtnDatetimechangeDatetimepickerCout(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	GetDlgItemText(IDC_DATETIMEPICKER_COUT, datumout);
	UpdateData(TRUE);
	*pResult = 0;
}

BOOL CSlobodneSobe::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString s;
	int i = 0;
	CHotel hotel;
	hotel.Open();
	while(!hotel.IsEOF()) {
		 hotel_id = hotel.m_HotelID;
		c_hoteli.AddString(hotel.m_Naziv);
		c_hoteli.SetItemData(i, hotel_id);
		hotel.MoveNext();
		i++;
	}
	hotel.Close();

	s.LoadString(IDS_STRING_ID);
	c_list_sobe.InsertColumn(0, s, LVCFMT_LEFT, 90);
	s.LoadString(IDS_STRING_DUHAN);
	c_list_sobe.InsertColumn(1, s, LVCFMT_LEFT, 90);
	s.LoadString(IDS_STRING_LJUBIMAC);
	c_list_sobe.InsertColumn(2, s, LVCFMT_LEFT, 90);
	s.LoadString(IDS_STRING_VRSTA_SOBE);
	c_list_sobe.InsertColumn(3, s, LVCFMT_LEFT, 90);
	s.LoadString(IDS_STRING_OPIS_SOBE);
	c_list_sobe.InsertColumn(4, s, LVCFMT_LEFT, 130);
	s.LoadString(IDS_STRING_CIJENA);
	c_list_sobe.InsertColumn(5, s, LVCFMT_LEFT, 130);
	s.LoadString(IDS_STRING_MAX_OSOBA);
	c_list_sobe.InsertColumn(6, s, LVCFMT_LEFT, 130);
	c_list_sobe.SetExtendedStyle(c_list_sobe.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	GetDlgItem(IDC_BUTTON_NOVA_REZERVACIJA)->EnableWindow(FALSE);
	
	CEdit* pEdit = (CEdit*)c_hoteli.GetWindow(GW_CHILD);
	pEdit->EnableWindow();
	pEdit->SetReadOnly();

	return TRUE;
}

void CSlobodneSobe::OnCbnSelchangeComboSlobodneNazivhotela()
{
	hotel_id = c_hoteli.GetItemData(c_hoteli.GetCurSel());

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
		s.LoadString(IDS_STRING_PAZNA_POLJA);
		AfxMessageBox(s);
		return;
	}
	//Dohvaæanje soba s ID odabranog hotela
	s.Format(_T("[HotelID] = %d"), hotel_id);
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
	s.LoadString(IDS_STRING_DA);
	s1.LoadString(IDS_STRING_NE);
	duhan == TRUE ? c_list_sobe.SetItemText(nIndex, 1, s) : c_list_sobe.SetItemText(nIndex, 1, s1);
	ljubimac == TRUE ? c_list_sobe.SetItemText(nIndex, 2, s) : c_list_sobe.SetItemText(nIndex, 2, s1);
	id.Format(_T("%ld"), vrstasobeid);
	c_list_sobe.SetItemText(nIndex, 3, id);
	CVrstaSobe vrsta;
	s.Format(_T("[VrstaSobeID] = %s"), id);
	vrsta.m_strFilter = s;
	vrsta.Open();
	c_list_sobe.SetItemText(nIndex, 4, vrsta.m_Opis);
	s1.LoadString(IDS_STRING_VALUTA);
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
