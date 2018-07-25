// CNovaRezervacija.cpp : implementation file
//

#include "stdafx.h"
#include "Seminar1.h"
#include "CNovaRezervacija.h"
#include "afxdialogex.h"
#include "Gost.h"
#include "Rezervacija.h"
#include "Zaposlenik.h"
#include "Soba.h"
#include "VrstaSobe.h"
#include "DetaljiRezervacije.h"

// CNovaRezervacija dialog

IMPLEMENT_DYNAMIC(CNovaRezervacija, CDialogEx)

CNovaRezervacija::CNovaRezervacija(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_NOVA_REZERVACIJA, pParent)
	, m_Ime(_T(""))
	, m_Prezime(_T(""))
	, m_Adresa(_T(""))
	, m_Grad(_T(""))
	, m_Drzava(_T(""))
	, m_OIB(_T(""))
	, m_Kontakt(_T(""))
	, m_pretraziOIB(_T(""))
	, m_Brojgostiju(0)
	, m_IDSobe(_T(""))
{

}
CNovaRezervacija::CNovaRezervacija(int *sobeID, CString datumD, CString datumO,CString name, CWnd* pParent)
	: CDialogEx(IDD_DIALOG_NOVA_REZERVACIJA, pParent)
	,datumIN(datumD)
	,datumOUT(datumO)
	,korisnik(name)
{
	int i = 0;
	while (*sobeID != '\0') {
		slobodnesobeID[i] = *sobeID;
		sobeID++;
		i++;
	}
	CZaposlenik zaposlenik;
	CString s;
	s.Format(_T("SELECT * FROM Zaposlenik Where Kor_Oznaka = '%s'"), korisnik);
	zaposlenik.Open(CRecordset::dynaset, s);
	zapID = zaposlenik.m_ZaposlenikID;
	zaposlenik.Close();
}

CNovaRezervacija::~CNovaRezervacija()
{
}

void CNovaRezervacija::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_R_IME, m_Ime);
	DDX_Text(pDX, IDC_EDIT_R_PREZIME, m_Prezime);
	DDX_Text(pDX, IDC_EDIT_R_ADRESA, m_Adresa);
	DDX_Text(pDX, IDC_EDIT_R_GRAD, m_Grad);
	DDX_Text(pDX, IDC_EDIT_R_DRZAVA, m_Drzava);
	DDX_Text(pDX, IDC_EDIT_R_OIB, m_OIB);
	DDX_Text(pDX, IDC_EDIT_R_KONTAKT, m_Kontakt);
	DDX_Text(pDX, IDC_EDIT_R_OIB_P, m_pretraziOIB);
	DDX_Text(pDX, IDC_EDIT_R_BROJGOSTIJU, m_Brojgostiju);
	DDX_Text(pDX, IDC_EDIT_R_IDSOBE, m_IDSobe);
	DDX_Control(pDX, IDC_LIST_R_ODABRANESOBE, c_OdabraneSobe);
}


BEGIN_MESSAGE_MAP(CNovaRezervacija, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_R_TRAZI, &CNovaRezervacija::OnBnClickedButtonRTrazi)
	ON_BN_CLICKED(IDOK, &CNovaRezervacija::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_R_DODAJ, &CNovaRezervacija::OnBnClickedButtonRDodaj)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_R_ODABRANESOBE, &CNovaRezervacija::OnLvnItemchangedListROdabranesobe)
	ON_BN_CLICKED(IDC_BUTTON_R_IZBRISI, &CNovaRezervacija::OnBnClickedButtonRIzbrisi)
END_MESSAGE_MAP()


// CNovaRezervacija message handlers


BOOL CNovaRezervacija::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	c_OdabraneSobe.InsertColumn(0, _T("ID"), LVCFMT_LEFT, 40);
	c_OdabraneSobe.InsertColumn(1, _T("Opis"), LVCFMT_LEFT, 140);
	c_OdabraneSobe.InsertColumn(2, _T("Cijena"), LVCFMT_LEFT, 60);
	c_OdabraneSobe.InsertColumn(3, _T("Broj osoba"), LVCFMT_LEFT, 70);
	c_OdabraneSobe.SetExtendedStyle(c_OdabraneSobe.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	CWnd *label = GetDlgItem(IDC_STATIC_R_DATUMDOLASKA);
	label->SetWindowText(datumIN);
	label = GetDlgItem(IDC_STATIC_R_DATUMODLASKA);
	label->SetWindowText(datumOUT);
	COleDateTime t1, t2;
	t1.ParseDateTime(datumIN);
	t2.ParseDateTime(datumOUT);
	CTime t3, t4;
	SYSTEMTIME st;
	if (t1.GetAsSystemTime(st))
		t3 = CTime(st);
	if (t2.GetAsSystemTime(st))
		t4 = CTime(st);
	datumD = t3;
	datumO = t4;
	CTimeSpan t5 = t4 - t3;
	m_Brojnocenja = t5.GetDays();
	CString s;
	s.Format(_T("%ld"), m_Brojnocenja);
	label = GetDlgItem(IDC_STATIC_R_BROJNOCENJA);
	label->SetWindowText(s);
	label = GetDlgItem(IDC_STATIC_R_DATUM);
	s = CTime::GetCurrentTime().Format("%d.%m.%Y");
	label->SetWindowText(s);
	GetDlgItem(IDC_BUTTON_R_IZBRISI)->EnableWindow(FALSE);
	
	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
bool CNovaRezervacija::DodajGosta() {
	GetDlgItemText(IDC_EDIT_R_IME, m_Ime);
	GetDlgItemText(IDC_EDIT_R_PREZIME, m_Prezime);
	GetDlgItemText(IDC_EDIT_R_ADRESA, m_Adresa);
	GetDlgItemText(IDC_EDIT_R_GRAD, m_Grad);
	GetDlgItemText(IDC_EDIT_R_DRZAVA, m_Drzava);
	GetDlgItemText(IDC_EDIT_R_OIB, m_OIB);
	GetDlgItemText(IDC_EDIT_R_KONTAKT, m_Kontakt);
	if (m_Ime == "" || m_Prezime == "" || m_OIB == "" || m_Kontakt == "") {
		return false;
	}
	CGost gost;
	gost.Open();
	gost.AddNew();
	gost.m_Ime = m_Ime;
	gost.m_Prezime = m_Prezime;
	gost.m_Adresa = m_Adresa;
	gost.m_Grad = m_Grad;
	gost.m_Drzava = m_Drzava;
	gost.m_OIB = m_OIB;
	gost.m_Kontakt = m_Kontakt;
	gost.Update();
	gost.MoveLast();
	gostID = gost.m_GostID;
	gost.Close();
	return true;
}

void CNovaRezervacija::IspisiCijenu() {
	CString s;
	if (!(datumD.GetMonth() < 7 && datumO.GetMonth() < 7 || datumD.GetMonth() >= 9 && datumO.GetMonth() >= 9))
		s.Format(_T("%.2f HRK"), ukupna_cijena*1.2);
	CWnd *label = GetDlgItem(IDC_STATIC_R_UKUPNACIJENA);
	s.Format(_T("%.2f HRK"), ukupna_cijena*1.2);
	label->SetWindowText(s);
}

void CNovaRezervacija::OnBnClickedButtonRTrazi()
{
	CString s;
	CWnd *label = GetDlgItem(IDC_STATIC_R_IMEGOSTA);
	GetDlgItemText(IDC_EDIT_R_OIB_P, m_pretraziOIB);
	CGost gost;
	s.Format(_T("SELECT * FROM Gost Where OIB = '%s'"), m_pretraziOIB);
	gost.Open(CRecordset::dynaset, s);
	if (gost.m_Ime != "") {	
		gostID = gost.m_GostID;
		s.Format(_T("%s %s"), gost.m_Ime, gost.m_Prezime);
		label->SetWindowText(s);
	}
	else {
		label->SetWindowText(_T("Korisnik ne postoji"));
	}
	// TODO: Add your control notification handler code here
}


void CNovaRezervacija::OnBnClickedOk()
{
	if (gostID < 0) {
		if (DodajGosta() == false) {
			AfxMessageBox(_T("Korisnik nije pravilno unesen"));
			return;
		}
	}
	CString s;
	GetDlgItemText(IDC_EDIT_R_BROJGOSTIJU, s);
	m_Brojgostiju = _tstoi(s);
	if (m_Brojgostiju > m_BrojGostijuizracun || m_Brojgostiju == 0) {
		AfxMessageBox(_T("Pre mali broj ležajeva"));
		return;
	}
	CRezervacija rezervacija;
	rezervacija.Open();
	rezervacija.AddNew();
	rezervacija.m_Datum_rezervacije = CTime::GetCurrentTime();
	rezervacija.m_Broj_nocenja = m_Brojnocenja;
	rezervacija.m_Broj_gostiju = m_Brojgostiju;
	rezervacija.m_Check_IN = datumD;
	rezervacija.m_Check_OUT = datumO;
	rezervacija.m_Ukupna_cijena = ukupna_cijena*1.2;
	rezervacija.m_GostID = gostID;
	rezervacija.m_ZaposlenikID = zapID;
	rezervacija.Update();
	rezervacija.MoveLast();
	CDetaljiRezervacije detalji;
	detalji.Open();
	int x = c_OdabraneSobe.GetItemCount();
	int i = 0;
	while (i < x) {
		CString t = c_OdabraneSobe.GetItemText(i, 0);
		int id = _tstoi(t);
		detalji.AddNew();
		detalji.m_SobaID = id;
		detalji.m_RezervacijaID = rezervacija.m_RezervacijaID;
		detalji.Update();
		i++;

	}
	detalji.Close();
	rezervacija.Close();
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


void CNovaRezervacija::OnBnClickedButtonRDodaj()
{
	GetDlgItemText(IDC_EDIT_R_IDSOBE, m_IDSobe);
	int id = _tstoi(m_IDSobe);
	if (id < 0) {
		AfxMessageBox(_T("Nepavilan unos!"));
		return;
	}
	int i = 0;
	bool t=FALSE;
	while (slobodnesobeID[i] != '\0') {
		if (slobodnesobeID[i] == id) {
			slobodnesobeID[i] = -1;
			t = TRUE;
			break;
		}
		i++;
	}
	if (t == FALSE) {
		AfxMessageBox(_T("Soba nije slobodna u odabranom razdoblju"));
		GetDlgItem(IDC_EDIT_R_IDSOBE)->SetWindowText(_T(""));
		return;
	}
	CString s;
	s.Format(_T("SELECT * FROM Soba Where SobaID = %d"), id);
	CSoba soba;
	CVrstaSobe vrsta;
	soba.Open(CRecordset::dynaset, s);
	int nIndex = c_OdabraneSobe.InsertItem(0, m_IDSobe);
	s.Format(_T("SELECT * FROM VrstaSobe Where VrstaSobeID = %d"), soba.m_VrstaSobeID);
	vrsta.Open(CRecordset::dynaset, s);
	c_OdabraneSobe.SetItemText(nIndex, 1, vrsta.m_Opis);
	//cijena i broj osoba
	s.Format(_T("%.2f HRK"), vrsta.m_Cijena);
	c_OdabraneSobe.SetItemText(nIndex, 2, s);
	s.Format(_T("%ld"), vrsta.m_Maks_broj_gostiju);
	c_OdabraneSobe.SetItemText(nIndex, 3, s);
	//Dodat izracun za cijenu soba
	ukupna_cijena += (vrsta.m_Cijena * m_Brojnocenja);
	m_BrojGostijuizracun += vrsta.m_Maks_broj_gostiju;
	vrsta.Close();
	soba.Close();
	GetDlgItem(IDC_EDIT_R_IDSOBE)->SetWindowText(_T(""));
	IspisiCijenu();

	// TODO: Add your control notification handler code here
}


void CNovaRezervacija::OnLvnItemchangedListROdabranesobe(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	bool ispit = pNMLV->uNewState & LVIS_SELECTED ? TRUE : FALSE;
	GetDlgItem(IDC_BUTTON_R_IZBRISI)->EnableWindow(ispit);
	*pResult = 0;
}


void CNovaRezervacija::OnBnClickedButtonRIzbrisi()
{
	int n = c_OdabraneSobe.GetNextItem(-1, LVNI_SELECTED);
	if (n != -1) {
		CString t = c_OdabraneSobe.GetItemText(n, 2);
		double y = _tstoi(t);
		ukupna_cijena -= (y * m_Brojnocenja);
		t = c_OdabraneSobe.GetItemText(n, 3);
		int brosoba = _tstoi(t);
		m_BrojGostijuizracun -= brosoba;
		t = c_OdabraneSobe.GetItemText(n, 0);
		int id = _tstoi(t);
		int i = 0;
		while (slobodnesobeID[i] != '\0') {
			if (slobodnesobeID[i] < 0) {
				slobodnesobeID[i] = id;
				break;
			}i++;
		}
		c_OdabraneSobe.DeleteItem(n);
		IspisiCijenu();
	}
	// TODO: Add your control notification handler code here
}
