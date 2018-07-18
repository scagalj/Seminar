// Rezervacija.h : Declaration of the CRezervacija

#pragma once

// code generated on 17. srpnja 2018., 11:48

class CRezervacija : public CRecordset
{
public:
	CRezervacija(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRezervacija)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	long	m_RezervacijaID;
	CTime	m_Datum_rezervacije;
	long	m_Broj_nocenja;
	long	m_Broj_gostiju;
	CTime	m_Check_IN;
	CTime	m_Check_OUT;
	double	m_Ukupna_cijena;
	long	m_GostID;
	long	m_ZaposlenikID;

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


