#pragma once

namespace f {
	CString DohvatiGosta(int id);
	CString DohvatiZaposlenika(int id);

}

namespace sobe {

	bool Dostupnostsobe(int id, CString datumin, CString datumout);
	CTime Datum(CString in);
}

namespace sort {
	struct PARAMSORT
	{
		PARAMSORT(HWND hWnd, int stupac, bool poredak, bool datum);
		HWND m_hWnd;
		int  m_stupac;
		bool m_poredak;
		bool m_datum;
	};
	int CALLBACK SortFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	
}