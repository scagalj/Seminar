// Hotel.h : Implementation of the CHotel class



// CHotel implementation

// code generated on 11. srpnja 2018., 18:20

#include "stdafx.h"
#include "Hotel.h"
IMPLEMENT_DYNAMIC(CHotel, CRecordset)

CHotel::CHotel(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_HotelID = 0;
	m_Naziv = L"";
	m_Adresa = L"";
	m_Grad = L"";
	m_Kontakt = L"";
	m_nFields = 5;
	m_nDefaultType = dynaset;
}
//#error Security Issue: The connection string may contain a password
// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString CHotel::GetDefaultConnect()
{
	return _T("ODBC;DSN=seminar_baza");
}

CString CHotel::GetDefaultSQL()
{
	return _T("[Hotel]");
}

void CHotel::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[HotelID]"), m_HotelID);
	RFX_Text(pFX, _T("[Naziv]"), m_Naziv);
	RFX_Text(pFX, _T("[Adresa]"), m_Adresa);
	RFX_Text(pFX, _T("[Grad]"), m_Grad);
	RFX_Text(pFX, _T("[Kontakt]"), m_Kontakt);

}
/////////////////////////////////////////////////////////////////////////////
// CHotel diagnostics

#ifdef _DEBUG
void CHotel::AssertValid() const
{
	CRecordset::AssertValid();
}

void CHotel::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


