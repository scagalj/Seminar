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
		CDetaljiRezervacije detalji;
		detalji.m_strFilter.Format(_T("[SobaID] = %d"), id);
		detalji.Open();
		while (!detalji.IsEOF()) {
			//Dohvaæanje rezervacije na osnovi Detalja rezervacije
			CRezervacija rez;
			rez.m_strFilter.Format(_T("[RezervacijaID] = %d"), detalji.m_RezervacijaID);
			rez.Open();
			COleDateTime t1, t2;
			t1.ParseDateTime(datumin); //odabrani datumi
			t2.ParseDateTime(datumout); //odabrani datum
			CTime t3, t4;
			SYSTEMTIME st;
			if (t1.GetAsSystemTime(st))
				t3 = CTime(st);

			if (t2.GetAsSystemTime(st))
				t4 = CTime(st);

			if (!(t3 < rez.m_Check_IN && t4 < rez.m_Check_IN || t3 > rez.m_Check_OUT && t4 > rez.m_Check_OUT)) {
				//Soba je zauzeta
				slobodna = FALSE;
				break;
			}
			rez.Close();
			detalji.MoveNext();
		}

		detalji.Close();
		return slobodna == TRUE ? TRUE : FALSE;	
	
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