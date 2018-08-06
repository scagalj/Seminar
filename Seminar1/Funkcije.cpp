#include "stdafx.h"
#include "Seminar1.h"
#include "afxdialogex.h"
#include "Funkcije.h"
#include "Gost.h"
#include "Zaposlenik.h"

namespace f {
	CString DohvatiGosta(int id) {
		CGost rs;
		rs.m_strFilter.Format(_T("[GostID] = %d"), id);
		return rs.Open() ? rs.m_Ime + _T(" ") + rs.m_Prezime : _T("");
	}
	CString DohvatiZaposlenika(int id) {
		CZaposlenik rs;
		rs.m_strFilter.Format(_T("[ZaposlenikID] = %d"), id);
		return rs.Open() ? rs.m_Kor_Oznaka : _T("");
	}

}
