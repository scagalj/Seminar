// CHoteli.cpp : implementation file
//

#include "stdafx.h"
#include "Seminar1.h"
#include "CHoteli.h"
#include "afxdialogex.h"
#include "Hotel.h"
#include "CDodajHotel.h"
#include "CDodajSobu.h"
#include "CPopisSoba.h"
#include "Funkcije.h"

// CHoteli dialog

IMPLEMENT_DYNAMIC(CHoteli, CDialogEx)

CHoteli::CHoteli(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_HOTEL, pParent)
	, h_trazi(_T(""))
{

}

CHoteli::~CHoteli()
{
}

BOOL CHoteli::OnInitDialog() {
	CDialog::OnInitDialog();
	CString s;
	s.LoadString(IDS_STRING_ID);
	hoteli.InsertColumn(0, s, LVCFMT_LEFT, 90);
	s.LoadString(IDS_STRING_NAZIV);
	hoteli.InsertColumn(1, s, LVCFMT_LEFT, 150);
	s.LoadString(IDS_STRING_ADRESA);
	hoteli.InsertColumn(2, s, LVCFMT_LEFT, 150);
	s.LoadString(IDS_STRING_GRAD);
	hoteli.InsertColumn(3, s, LVCFMT_LEFT, 130);
	s.LoadString(IDS_STRING_KONTAKT);
	hoteli.InsertColumn(4, s, LVCFMT_LEFT, 130);
	hoteli.SetExtendedStyle(hoteli.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	IspisiHotele();
	Ugasibotune(false);
	return TRUE;
}


void CHoteli::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_HOTELI, hoteli);
	DDX_Text(pDX, IDC_EDIT_Hotel_Trazi, h_trazi);
}


BEGIN_MESSAGE_MAP(CHoteli, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_DODAJ_HOTEL, &CHoteli::OnBnClickedButtonAddHotel)
	ON_BN_CLICKED(IDC_BUTTON_HOTEL_IZBRISI, &CHoteli::OnBnClickedButtonDeleteHotel)
	ON_BN_CLICKED(IDC_BUTTON_Hotel_Trazi, &CHoteli::OnBnClickedButtonHotelTrazi)
	ON_BN_CLICKED(IDC_BUTTON_DODAJ_SOBU, &CHoteli::OnBnClickedButtonDodajSobu)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_HOTELI, &CHoteli::OnLvnItemchangedListHoteli)
	ON_BN_CLICKED(IDC_BUTTON_POPIS_SOBA, &CHoteli::OnBnClickedButtonPopisSoba)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_HOTELI, &CHoteli::OnLvnColumnclickListHoteli)
END_MESSAGE_MAP()


// CHoteli message handlers


void CHoteli::IspisiHotele()
{
	hoteli.DeleteAllItems();
	CHotel hotel;
	hotel.Open();
	while (!hotel.IsEOF()) {
		CString id;
		id.Format(_T("%ld"), hotel.m_HotelID);
		int nIndex = hoteli.InsertItem(0, id);
		hoteli.SetItemText(nIndex, 1, hotel.m_Naziv);
		hoteli.SetItemText(nIndex, 2, hotel.m_Adresa);
		hoteli.SetItemText(nIndex, 3, hotel.m_Grad);
		hoteli.SetItemText(nIndex, 4, hotel.m_Kontakt);
		hotel.MoveNext();
	}
	hotel.Close();
}


void CHoteli::OnBnClickedButtonAddHotel()
{
	CString s;
	CDodajHotel addHotel;
	if (addHotel.DoModal() == IDOK) {
		IspisiHotele();
		s.LoadString(IDS_STRING_HOTEL2);
		AfxMessageBox(s);
	}
}


void CHoteli::OnBnClickedButtonDeleteHotel()
{
	int x = hoteli.GetNextItem(-1, LVNI_SELECTED);
	CString t = hoteli.GetItemText(x,0);
	CHotel hotel;
	hotel.m_strFilter = HotelID(_tstoi(t));
	hotel.Open();
	hotel.Delete();
	hoteli.DeleteItem(x);
	hotel.Close();
}


void CHoteli::OnBnClickedButtonHotelTrazi()
{
	GetDlgItemText(IDC_EDIT_Hotel_Trazi, h_trazi);
	GetDlgItem(IDC_EDIT_Hotel_Trazi)->SetWindowText(_T(""));
	Ugasibotune(false);
	if (h_trazi == "*") {
		IspisiHotele();
		return;
	}
	CHotel hotel;
	hotel.Open();
	hoteli.DeleteAllItems();
	while (!hotel.IsEOF()) {
		CString name = hotel.m_Naziv;
		if (name.MakeLower().Find(h_trazi.MakeLower()) != -1) {
			CString id("");
			id.Format(_T("%ld"), hotel.m_HotelID);
			int nIndex = hoteli.InsertItem(0, id);
			hoteli.SetItemText(nIndex, 1, hotel.m_Naziv);
			hoteli.SetItemText(nIndex, 2, hotel.m_Adresa);
			hoteli.SetItemText(nIndex, 3, hotel.m_Grad);
			hoteli.SetItemText(nIndex, 4, hotel.m_Kontakt);	
		}
		hotel.MoveNext();
	}
	hotel.Close();
}


void CHoteli::OnBnClickedButtonDodajSobu()
{
	CHotel hotel;
	CString s;
	int x = hoteli.GetNextItem(-1, LVNI_SELECTED);
	CString t = hoteli.GetItemText(x, 0);
	hotel.m_strFilter = HotelID(_tstoi(t));
	hotel.Open();
	CDodajSobu soba(hotel.m_HotelID,hotel.m_Naziv,this);
	if (soba.DoModal() == IDOK) {
		s.LoadString(IDS_STRING_SOBA3);
		AfxMessageBox(s);
	}
	hotel.Close();
}


void CHoteli::OnLvnItemchangedListHoteli(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	bool ispit = pNMLV->uNewState & LVIS_SELECTED ? TRUE : FALSE;
	Ugasibotune(ispit);
	*pResult = 0;
}


void CHoteli::OnBnClickedButtonPopisSoba()
{
	CHotel hotel;
	int x = hoteli.GetNextItem(-1, LVNI_SELECTED);
	CString t = hoteli.GetItemText(x, 0);
	hotel.m_strFilter = HotelID(_tstoi(t));
	hotel.Open();
	CPopisSoba popis(hotel.m_HotelID, hotel.m_Naziv, this);
	popis.DoModal();
	hotel.Close();
}

void CHoteli::Ugasibotune(bool ispit) {
	GetDlgItem(IDC_BUTTON_DODAJ_SOBU)->EnableWindow(ispit);
	GetDlgItem(IDC_BUTTON_HOTEL_IZBRISI)->EnableWindow(ispit);
	GetDlgItem(IDC_BUTTON_POPIS_SOBA)->EnableWindow(ispit);
}

CString CHoteli::HotelID(int x) {
	CString s;
	s.Format(_T("[HotelID] = %d"), x);
	return s;

}

void CHoteli::OnLvnColumnclickListHoteli(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	SortColumn(pNMLV->iSubItem, poredak);
	poredak == 0 ? poredak = 1 : poredak = 0;
	*pResult = 0;
}

bool CHoteli::SortColumn(int columnIndex, bool ascending)
{
	sort::PARAMSORT paramsort(hoteli, columnIndex, ascending, false);
	ListView_SortItemsEx(hoteli, sort::SortFunc, &paramsort);
	return true;
}