// Soba.h : Implementation of the CSoba class



// CSoba implementation

// code generated on 13. srpnja 2018., 19:13

#include "stdafx.h"
#include "Soba.h"
IMPLEMENT_DYNAMIC(CSoba, CRecordset)

CSoba::CSoba(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_SobaID = 0;
	m_Konzumiranje_duhana = FALSE;
	m_Ljubimci = FALSE;
	m_HotelID = 0;
	m_VrstaSobeID = 0;
	m_nFields = 5;
	m_nDefaultType = dynaset;
}
//#error Security Issue: The connection string may contain a password
// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString CSoba::GetDefaultConnect()
{
	return _T("ODBC;DSN=seminar_baza");
}

CString CSoba::GetDefaultSQL()
{
	return _T("[Soba]");
}

void CSoba::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[SobaID]"), m_SobaID);
	RFX_Bool(pFX, _T("[Konzumiranje_duhana]"), m_Konzumiranje_duhana);
	RFX_Bool(pFX, _T("[Ljubimci]"), m_Ljubimci);
	RFX_Long(pFX, _T("[HotelID]"), m_HotelID);
	RFX_Long(pFX, _T("[VrstaSobeID]"), m_VrstaSobeID);

}
/////////////////////////////////////////////////////////////////////////////
// CSoba diagnostics

#ifdef _DEBUG
void CSoba::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSoba::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


