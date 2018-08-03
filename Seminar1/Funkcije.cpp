#include "stdafx.h"
#include "Seminar1.h"
#include "afxdialogex.h"
#include "Funkcije.h"
#include "Gost.h"
#include "Zaposlenik.h"

CString Funkcije::DohvatiGosta(int id) {
	CGost gost;
	s.Format(_T("[GostID] = %d"), id);
	gost.m_strFilter = s;
	gost.Open();
	s.Format(_T("%s %s"), gost.m_Ime, gost.m_Prezime);
	gost.Close();
	return s;
}

CString Funkcije::DohvatiZaposlenika(int id) {
	CZaposlenik zaposlenik;
	s.Format(_T("[ZaposlenikID] = %d"), id);
	zaposlenik.m_strFilter = s;
	zaposlenik.Open();
	s.Format(_T("%s"), zaposlenik.m_Kor_Oznaka);
	zaposlenik.Close();
	return s;

}