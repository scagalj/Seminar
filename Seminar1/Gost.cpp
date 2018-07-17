// Gost.h : Implementation of the CGost class



// CGost implementation

// code generated on 15. srpnja 2018., 15:42

#include "stdafx.h"
#include "Gost.h"
IMPLEMENT_DYNAMIC(CGost, CRecordset)

CGost::CGost(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_GostID = 0;
	m_Ime = L"";
	m_Prezime = L"";
	m_Adresa = L"";
	m_Grad = L"";
	m_Drzava = L"";
	m_Kontakt = L"";
	m_OIB = L"";
	m_nFields = 8;
	m_nDefaultType = dynaset;
}
//#error Security Issue: The connection string may contain a password
// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString CGost::GetDefaultConnect()
{
	return _T("ODBC;DSN=seminar_baza");
}

CString CGost::GetDefaultSQL()
{
	return _T("[Gost]");
}

void CGost::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[GostID]"), m_GostID);
	RFX_Text(pFX, _T("[Ime]"), m_Ime);
	RFX_Text(pFX, _T("[Prezime]"), m_Prezime);
	RFX_Text(pFX, _T("[Adresa]"), m_Adresa);
	RFX_Text(pFX, _T("[Grad]"), m_Grad);
	RFX_Text(pFX, _T("[Drzava]"), m_Drzava);
	RFX_Text(pFX, _T("[Kontakt]"), m_Kontakt);
	RFX_Text(pFX, _T("[OIB]"), m_OIB);

}
/////////////////////////////////////////////////////////////////////////////
// CGost diagnostics

#ifdef _DEBUG
void CGost::AssertValid() const
{
	CRecordset::AssertValid();
}

void CGost::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


