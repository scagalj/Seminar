// Baza.h : Implementation of the CBaza class



// CBaza implementation

// code generated on 9. srpnja 2018., 14:48

#include "stdafx.h"
#include "Baza.h"
IMPLEMENT_DYNAMIC(CBaza, CRecordset)

CBaza::CBaza(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_GostGostID = 0;
	m_GostIme = L"";
	m_GostPrezime = L"";
	m_GostAdresa = L"";
	m_GostGrad = L"";
	m_GostDrava = L"";
	m_GostKontakt = L"";
	m_HotelHotelID = 0;
	m_HotelNaziv = L"";
	m_HotelAdresa = L"";
	m_HotelGrad = L"";
	m_HotelKontakt = L"";
	m_RezervacijaRezID = 0;
	m_RezervacijaDatum_rezervacije;
	m_RezervacijaBroj_nocenja = 0;
	m_RezervacijaBroj_gostiju = 0;
	m_RezervacijaCheck_IN;
	m_RezervacijaCheck_OUT;
	m_RezervacijaUkupna_cijena = 0.0;
	m_RezervacijaGostID = 0;
	m_RezervacijaZaposlenikID = 0;
	m_RezervacijaSobaID = 0;
	m_SobaSobaID = 0;
	m_SobaKonzumiranje_duhana = FALSE;
	m_SobaLjubimci = FALSE;
	m_SobaHotelID = 0;
	m_SobaVrstaSobeID = 0;
	m_VrstaSobeVrstaSobeID = 0;
	m_VrstaSobeOpis = L"";
	m_VrstaSobeCijena = 0.0;
	m_VrstaSobeMaks_broj_gostiju = 0;
	m_ZaposlenikZaposlenikID = 0;
	m_ZaposlenikKor_Oznaka = L"";
	m_ZaposlenikLozinka = L"";
	m_ZaposlenikIme = L"";
	m_ZaposlenikPrezime = L"";
	m_ZaposlenikAdresa = L"";
	m_ZaposlenikGrad = L"";
	m_ZaposlenikDrava = L"";
	m_ZaposlenikKontakt = L"";
	m_nFields = 40;
	m_nDefaultType = dynaset;
}
#error Security Issue: The connection string may contain a password
// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString CBaza::GetDefaultConnect()
{
	return _T("DSN=seminar_baza;DBQ=C:\\Users\\Student\\Documents\\SeminarDataBase.accdb;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;UID=admin;");
}

CString CBaza::GetDefaultSQL()
{
	return _T("[Gost],[Hotel],[Rezervacija],[Soba],[VrstaSobe],[Zaposlenik]");
}

void CBaza::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[Gost].[GostID]"), m_GostGostID);
	RFX_Text(pFX, _T("[Gost].[Ime]"), m_GostIme);
	RFX_Text(pFX, _T("[Gost].[Prezime]"), m_GostPrezime);
	RFX_Text(pFX, _T("[Gost].[Adresa]"), m_GostAdresa);
	RFX_Text(pFX, _T("[Gost].[Grad]"), m_GostGrad);
	RFX_Text(pFX, _T("[Gost].[Država]"), m_GostDrava);
	RFX_Text(pFX, _T("[Gost].[Kontakt]"), m_GostKontakt);
	RFX_Long(pFX, _T("[Hotel].[HotelID]"), m_HotelHotelID);
	RFX_Text(pFX, _T("[Hotel].[Naziv]"), m_HotelNaziv);
	RFX_Text(pFX, _T("[Hotel].[Adresa]"), m_HotelAdresa);
	RFX_Text(pFX, _T("[Hotel].[Grad]"), m_HotelGrad);
	RFX_Text(pFX, _T("[Hotel].[Kontakt]"), m_HotelKontakt);
	RFX_Long(pFX, _T("[Rezervacija].[RezID]"), m_RezervacijaRezID);
	RFX_Date(pFX, _T("[Rezervacija].[Datum_rezervacije]"), m_RezervacijaDatum_rezervacije);
	RFX_Long(pFX, _T("[Rezervacija].[Broj_nocenja]"), m_RezervacijaBroj_nocenja);
	RFX_Long(pFX, _T("[Rezervacija].[Broj_gostiju]"), m_RezervacijaBroj_gostiju);
	RFX_Date(pFX, _T("[Rezervacija].[Check_IN]"), m_RezervacijaCheck_IN);
	RFX_Date(pFX, _T("[Rezervacija].[Check_OUT]"), m_RezervacijaCheck_OUT);
	RFX_Double(pFX, _T("[Rezervacija].[Ukupna_cijena]"), m_RezervacijaUkupna_cijena);
	RFX_Long(pFX, _T("[Rezervacija].[GostID]"), m_RezervacijaGostID);
	RFX_Long(pFX, _T("[Rezervacija].[ZaposlenikID]"), m_RezervacijaZaposlenikID);
	RFX_Long(pFX, _T("[Rezervacija].[SobaID]"), m_RezervacijaSobaID);
	RFX_Long(pFX, _T("[Soba].[SobaID]"), m_SobaSobaID);
	RFX_Bool(pFX, _T("[Soba].[Konzumiranje_duhana]"), m_SobaKonzumiranje_duhana);
	RFX_Bool(pFX, _T("[Soba].[Ljubimci]"), m_SobaLjubimci);
	RFX_Long(pFX, _T("[Soba].[HotelID]"), m_SobaHotelID);
	RFX_Long(pFX, _T("[Soba].[VrstaSobeID]"), m_SobaVrstaSobeID);
	RFX_Long(pFX, _T("[VrstaSobe].[VrstaSobeID]"), m_VrstaSobeVrstaSobeID);
	RFX_Text(pFX, _T("[VrstaSobe].[Opis]"), m_VrstaSobeOpis);
	RFX_Double(pFX, _T("[VrstaSobe].[Cijena]"), m_VrstaSobeCijena);
	RFX_Long(pFX, _T("[VrstaSobe].[Maks_broj_gostiju]"), m_VrstaSobeMaks_broj_gostiju);
	RFX_Long(pFX, _T("[Zaposlenik].[ZaposlenikID]"), m_ZaposlenikZaposlenikID);
	RFX_Text(pFX, _T("[Zaposlenik].[Kor_Oznaka]"), m_ZaposlenikKor_Oznaka);
	RFX_Text(pFX, _T("[Zaposlenik].[Lozinka]"), m_ZaposlenikLozinka);
	RFX_Text(pFX, _T("[Zaposlenik].[Ime]"), m_ZaposlenikIme);
	RFX_Text(pFX, _T("[Zaposlenik].[Prezime]"), m_ZaposlenikPrezime);
	RFX_Text(pFX, _T("[Zaposlenik].[Adresa]"), m_ZaposlenikAdresa);
	RFX_Text(pFX, _T("[Zaposlenik].[Grad]"), m_ZaposlenikGrad);
	RFX_Text(pFX, _T("[Zaposlenik].[Država]"), m_ZaposlenikDrava);
	RFX_Text(pFX, _T("[Zaposlenik].[Kontakt]"), m_ZaposlenikKontakt);

}
/////////////////////////////////////////////////////////////////////////////
// CBaza diagnostics

#ifdef _DEBUG
void CBaza::AssertValid() const
{
	CRecordset::AssertValid();
}

void CBaza::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


