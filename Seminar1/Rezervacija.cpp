// Rezervacija.h : Implementation of the CRezervacija class



// CRezervacija implementation

// code generated on 17. srpnja 2018., 11:48

#include "stdafx.h"
#include "Rezervacija.h"
IMPLEMENT_DYNAMIC(CRezervacija, CRecordset)

CRezervacija::CRezervacija(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_RezervacijaID = 0;
	m_Datum_rezervacije;
	m_Broj_nocenja = 0;
	m_Broj_gostiju = 0;
	m_Check_IN;
	m_Check_OUT;
	m_Ukupna_cijena = 0.0;
	m_GostID = 0;
	m_ZaposlenikID = 0;
	m_nFields = 9;
	m_nDefaultType = dynaset;
}
//#error Security Issue: The connection string may contain a password
// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString CRezervacija::GetDefaultConnect()
{
	return _T("ODBC;DSN=seminar_baza");
}

CString CRezervacija::GetDefaultSQL()
{
	return _T("[Rezervacija]");
}

void CRezervacija::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[RezervacijaID]"), m_RezervacijaID);
	RFX_Date(pFX, _T("[Datum_rezervacije]"), m_Datum_rezervacije);
	RFX_Long(pFX, _T("[Broj_nocenja]"), m_Broj_nocenja);
	RFX_Long(pFX, _T("[Broj_gostiju]"), m_Broj_gostiju);
	RFX_Date(pFX, _T("[Check_IN]"), m_Check_IN);
	RFX_Date(pFX, _T("[Check_OUT]"), m_Check_OUT);
	RFX_Double(pFX, _T("[Ukupna_cijena]"), m_Ukupna_cijena);
	RFX_Long(pFX, _T("[GostID]"), m_GostID);
	RFX_Long(pFX, _T("[ZaposlenikID]"), m_ZaposlenikID);

}
/////////////////////////////////////////////////////////////////////////////
// CRezervacija diagnostics

#ifdef _DEBUG
void CRezervacija::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRezervacija::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


