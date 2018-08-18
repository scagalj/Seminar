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
#include "Funkcije.h"

// CSlobodneSobe dialog

IMPLEMENT_DYNAMIC(CSlobodneSobe, CDialogEx)

CSlobodneSobe::CSlobodneSobe(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SLOBODNE_SOBE, pParent)
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
	DDX_Control(pDX, IDC_LIST_SLOBODNE_SOBE_POPIS, c_list_sobe);
	DDX_Control(pDX, IDC_DATETIMEPICKER_COUT, t_slobodnesobe_out);
}


BEGIN_MESSAGE_MAP(CSlobodneSobe, CDialogEx)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_SOBE, &CSlobodneSobe::OnDtnDatetimechangeDatetimepickerSobe)
	ON_BN_CLICKED(IDC_BUTTON_SLOBODNE_SOBE_PRIKAZ, &CSlobodneSobe::OnBnClickedButtonSlobodneSobePrikaz)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_COUT, &CSlobodneSobe::OnDtnDatetimechangeDatetimepickerCout)
	ON_BN_CLICKED(IDC_BUTTON_NOVA_REZERVACIJA, &CSlobodneSobe::OnBnClickedButtonNovaRezervaciju)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_SLOBODNE_SOBE_POPIS, &CSlobodneSobe::OnLvnColumnclickListSlobodneSobePopis)
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
		c_hoteli.AddString(hotel.m_Naziv);
		c_hoteli.SetItemData(i, hotel.m_HotelID);
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

	return TRUE;
}

void CSlobodneSobe::OnBnClickedButtonSlobodneSobePrikaz()
{
	CString s;
	int i = 0;
	CSoba soba;
	GetDlgItem(IDC_BUTTON_NOVA_REZERVACIJA)->EnableWindow(TRUE);
	c_list_sobe.DeleteAllItems();
	if (c_hoteli.GetItemData(c_hoteli.GetCurSel()) < 0 || datumin == "" || datumout== "") {
		s.LoadString(IDS_STRING_PAZNA_POLJA);
		AfxMessageBox(s);
		return;
	}
	//Dohvaæanje soba s ID odabranog hotela
	soba.m_strFilter.Format(_T("[HotelID] = %d"), c_hoteli.GetItemData(c_hoteli.GetCurSel()));
	soba.Open();
	while (!soba.IsEOF()) {
		//Dohvaæanje detalja rezervacija za pojedinu sobu
		if (sobe::Dostupnostsobe(soba.m_SobaID, datumin, datumout) == TRUE)
			IspisSobe(soba.m_SobaID);
		soba.MoveNext();	
	}
	soba.Close();
	
}

void CSlobodneSobe::IspisSobe(long sobaid){
	CString id,s,s1;
	CSoba soba;
	soba.m_strFilter.Format(_T("[SobaID] = %d"), sobaid);
	soba.Open();
	id.Format(_T("%ld"), sobaid);
	int nIndex = c_list_sobe.InsertItem(0, id);
	s.LoadString(IDS_STRING_DA);
	s1.LoadString(IDS_STRING_NE);
	soba.m_Konzumiranje_duhana == TRUE ? c_list_sobe.SetItemText(nIndex, 1, s) : c_list_sobe.SetItemText(nIndex, 1, s1);
	soba.m_Ljubimci == TRUE ? c_list_sobe.SetItemText(nIndex, 2, s) : c_list_sobe.SetItemText(nIndex, 2, s1);
	id.Format(_T("%ld"), soba.m_VrstaSobeID);
	c_list_sobe.SetItemText(nIndex, 3, id);
	CVrstaSobe vrsta;
	vrsta.m_strFilter.Format(_T("[VrstaSobeID] = %s"), id);
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
	CNovaRezervacija nova(datumin,datumout,korisnik, c_hoteli.GetItemData(c_hoteli.GetCurSel()),this);
	if (nova.DoModal() == IDOK){
		CString s;
		OnBnClickedButtonSlobodneSobePrikaz();
		s.LoadString(IDS_STRING_REZ_KREIRANA);
		AfxMessageBox(s);
	}
}


void CSlobodneSobe::OnLvnColumnclickListSlobodneSobePopis(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	SortColumn(pNMLV->iSubItem, poredak);
	poredak == 0 ? poredak = 1 : poredak = 0;
	*pResult = 0;
}

bool CSlobodneSobe::SortColumn(int columnIndex, bool ascending)
{
	sort::PARAMSORT paramsort(c_list_sobe, columnIndex, ascending, false);
	ListView_SortItemsEx(c_list_sobe, sort::SortFunc, &paramsort);
	return true;
}