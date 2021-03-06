#pragma once


// CDodajHotel dialog

class CDodajHotel : public CDialogEx
{
	DECLARE_DYNAMIC(CDodajHotel)

public:
	CDodajHotel(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDodajHotel();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Add_Hotel };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString h_Naziv;
	CString h_Adresa;
	CString h_Grad;
	CString h_Kontakt;
	afx_msg void OnBnClickedButtonHotelAdd();
};
