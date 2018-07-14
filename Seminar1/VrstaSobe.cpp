// VrstaSobe.h : Implementation of the CVrstaSobe class



// CVrstaSobe implementation

// code generated on 13. srpnja 2018., 19:01

#include "stdafx.h"
#include "VrstaSobe.h"
IMPLEMENT_DYNAMIC(CVrstaSobe, CRecordset)

CVrstaSobe::CVrstaSobe(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_VrstaSobeID = 0;
	m_Opis = L"";
	m_Cijena = 0.0;
	m_Maks_broj_gostiju = 0;
	m_nFields = 4;
	m_nDefaultType = dynaset;
}
//#error Security Issue: The connection string may contain a password
// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString CVrstaSobe::GetDefaultConnect()
{
	return _T("ODBC;DSN=seminar_baza");
}

CString CVrstaSobe::GetDefaultSQL()
{
	return _T("[VrstaSobe]");
}

void CVrstaSobe::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[VrstaSobeID]"), m_VrstaSobeID);
	RFX_Text(pFX, _T("[Opis]"), m_Opis);
	RFX_Double(pFX, _T("[Cijena]"), m_Cijena);
	RFX_Long(pFX, _T("[Maks_broj_gostiju]"), m_Maks_broj_gostiju);

}
/////////////////////////////////////////////////////////////////////////////
// CVrstaSobe diagnostics

#ifdef _DEBUG
void CVrstaSobe::AssertValid() const
{
	CRecordset::AssertValid();
}

void CVrstaSobe::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


