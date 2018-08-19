#include "stdafx.h"
#include "Seminar1.h"
#include "afxdialogex.h"
#include "Funkcije.h"
#include "Gost.h"
#include "Zaposlenik.h"
#include "Rezervacija.h"
#include "DetaljiRezervacije.h"
#include "VrstaSobe.h"
#include "Soba.h"

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

namespace sobe {

	BOOL Dostupnostsobe(int id, CString datumin, CString datumout) {
		BOOL slobodna=TRUE;
		CTime t3, t4;
		CDetaljiRezervacije detalji;
		detalji.m_strFilter.Format(_T("[SobaID] = %d"), id);
		detalji.Open();
		while (!detalji.IsEOF()) {
			//Dohvaæanje rezervacije na osnovi Detalja rezervacije
			CRezervacija rez;
			rez.m_strFilter.Format(_T("[RezervacijaID] = %d"), detalji.m_RezervacijaID);
			rez.Open();
			t3 = Datum(datumin);
			t4 = Datum(datumout);
			if (!(t3 < rez.m_Check_IN && t4 < rez.m_Check_IN || t3 > rez.m_Check_OUT && t4 > rez.m_Check_OUT)) {
				//Soba je zauzeta
				slobodna = FALSE;
				break;
			}
			rez.Close();
			detalji.MoveNext();
		}

		detalji.Close();
		return slobodna ? TRUE : FALSE;	
	
	}

	CTime Datum(CString datum) {
		COleDateTime t1;
		CTime d1;
		SYSTEMTIME st;
		t1.ParseDateTime(datum);
		if (t1.GetAsSystemTime(st))
			d1 = CTime(st);
		return d1;
	}
}

namespace sort {
	

	PARAMSORT::PARAMSORT(HWND hWnd, int stupac, bool poredak, bool datum)
		:m_hWnd(hWnd)
		, m_stupac(stupac)
		, m_poredak(poredak)
		,m_datum(datum)
	{}
	int CALLBACK SortFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
	{
		PARAMSORT& ps = *(PARAMSORT*)lParamSort;

		TCHAR prvi[256] = _T(""), drugi[256] = _T("");
		ListView_GetItemText(ps.m_hWnd, lParam1,
			ps.m_stupac, prvi, sizeof(prvi));
		ListView_GetItemText(ps.m_hWnd, lParam2,
			ps.m_stupac, drugi, sizeof(drugi));
		double x = _wtoi(prvi);
		double y = _wtoi(drugi);
		if (x != 0 && ps.m_datum == false) {	
			return ps.m_poredak ? x - y : -(x - y);
		}
		if (ps.m_datum == true) {
			CTime t1, t2;
			t1 = sobe::Datum(prvi);
			t2 = sobe::Datum(drugi);
			return ps.m_poredak ? t1 < t2 : t1>t2;
		}
		return ps.m_poredak ? _tcscmp(prvi, drugi) : _tcscmp(drugi, prvi);

	}
}