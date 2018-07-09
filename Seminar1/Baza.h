// Baza.h : Declaration of the CBaza

#pragma once

// code generated on 9. srpnja 2018., 14:48

class CBaza : public CRecordset
{
public:
	CBaza(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CBaza)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).
	//GOST
	long	m_GostGostID;
	CStringW	m_GostIme;
	CStringW	m_GostPrezime;
	CStringW	m_GostAdresa;
	CStringW	m_GostGrad;
	CStringW	m_GostDrava;
	CStringW	m_GostKontakt;
	//HOTEL
	long	m_HotelHotelID;
	CStringW	m_HotelNaziv;
	CStringW	m_HotelAdresa;
	CStringW	m_HotelGrad;
	CStringW	m_HotelKontakt;
	//REZERVACIJA
	long	m_RezervacijaRezID;
	CTime	m_RezervacijaDatum_rezervacije;
	long	m_RezervacijaBroj_nocenja;
	long	m_RezervacijaBroj_gostiju;
	CTime	m_RezervacijaCheck_IN;
	CTime	m_RezervacijaCheck_OUT;
	double	m_RezervacijaUkupna_cijena;
	long	m_RezervacijaGostID;
	long	m_RezervacijaZaposlenikID;
	long	m_RezervacijaSobaID;
	//SOBA
	long	m_SobaSobaID;
	BOOL	m_SobaKonzumiranje_duhana;
	BOOL	m_SobaLjubimci;
	long	m_SobaHotelID;
	long	m_SobaVrstaSobeID;
	//VRSTA SOBE
	long	m_VrstaSobeVrstaSobeID;
	CStringW	m_VrstaSobeOpis;
	double	m_VrstaSobeCijena;
	long	m_VrstaSobeMaks_broj_gostiju;
	//ZAPOSLENIK
	long	m_ZaposlenikZaposlenikID;
	CStringW	m_ZaposlenikKor_Oznaka;
	CStringW	m_ZaposlenikLozinka;
	CStringW	m_ZaposlenikIme;
	CStringW	m_ZaposlenikPrezime;
	CStringW	m_ZaposlenikAdresa;
	CStringW	m_ZaposlenikGrad;
	CStringW	m_ZaposlenikDrava;
	CStringW	m_ZaposlenikKontakt;

// Overrides
	// Wizard generated virtual function overrides
	public:
	virtual CString GetDefaultConnect();	// Default connection string

	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


