// Zaposlenik.h : Implementation of the CZaposlenik class



// CZaposlenik implementation

// code generated on 9. srpnja 2018., 17:51

#include "stdafx.h"
#include "Zaposlenik.h"
IMPLEMENT_DYNAMIC(CZaposlenik, CRecordset)

CZaposlenik::CZaposlenik(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ZaposlenikID = 0;
	m_Kor_Oznaka = L"";
	m_Lozinka = L"";
	m_Ime = L"";
	m_Prezime = L"";
	m_Adresa = L"";
	m_Grad = L"";
	m_Drzava = L"";
	m_Kontakt = L"";
	m_nFields = 9;
	m_nDefaultType = dynaset;
}
//#error Security Issue: The connection string may contain a password
// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString CZaposlenik::GetDefaultConnect()
{
	return _T("ODBC;DSN=seminar_baza");
}

CString CZaposlenik::GetDefaultSQL()
{
	return _T("[Zaposlenik]");
}

void CZaposlenik::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[ZaposlenikID]"), m_ZaposlenikID);
	RFX_Text(pFX, _T("[Kor_Oznaka]"), m_Kor_Oznaka);
	RFX_Text(pFX, _T("[Lozinka]"), m_Lozinka);
	RFX_Text(pFX, _T("[Ime]"), m_Ime);
	RFX_Text(pFX, _T("[Prezime]"), m_Prezime);
	RFX_Text(pFX, _T("[Adresa]"), m_Adresa);
	RFX_Text(pFX, _T("[Grad]"), m_Grad);
	RFX_Text(pFX, _T("[Drzava]"), m_Drzava);
	RFX_Text(pFX, _T("[Kontakt]"), m_Kontakt);

}
/////////////////////////////////////////////////////////////////////////////
// CZaposlenik diagnostics

#ifdef _DEBUG
void CZaposlenik::AssertValid() const
{
	CRecordset::AssertValid();
}

void CZaposlenik::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


