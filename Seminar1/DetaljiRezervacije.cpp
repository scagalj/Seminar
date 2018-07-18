// DetaljiRezervacije.h : Implementation of the CDetaljiRezervacije class



// CDetaljiRezervacije implementation

// code generated on 17. srpnja 2018., 11:49

#include "stdafx.h"
#include "DetaljiRezervacije.h"
IMPLEMENT_DYNAMIC(CDetaljiRezervacije, CRecordset)

CDetaljiRezervacije::CDetaljiRezervacije(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_SobaID = 0;
	m_RezervacijaID = 0;
	m_nFields = 3;
	m_nDefaultType = dynaset;
}
//#error Security Issue: The connection string may contain a password
// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString CDetaljiRezervacije::GetDefaultConnect()
{
	return _T("ODBC;DSN=seminar_baza");
}

CString CDetaljiRezervacije::GetDefaultSQL()
{
	return _T("[DetaljiRezervacije]");
}

void CDetaljiRezervacije::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Long(pFX, _T("[SobaID]"), m_SobaID);
	RFX_Long(pFX, _T("[RezervacijaID]"), m_RezervacijaID);

}
/////////////////////////////////////////////////////////////////////////////
// CDetaljiRezervacije diagnostics

#ifdef _DEBUG
void CDetaljiRezervacije::AssertValid() const
{
	CRecordset::AssertValid();
}

void CDetaljiRezervacije::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


