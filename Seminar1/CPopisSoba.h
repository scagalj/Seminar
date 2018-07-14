#pragma once


// CPopisSoba dialog

class CPopisSoba : public CDialogEx
{
	DECLARE_DYNAMIC(CPopisSoba)

public:
	CPopisSoba(CWnd* pParent = nullptr);   // standard constructor
	explicit CPopisSoba(const int &HotelID, const CString &Naziv_Hotela, CWnd* pParent);
	virtual ~CPopisSoba();
	BOOL OnInitDialog();
	int p_HotelID;
	CString p_NazivHotela;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_POPIS_SOBA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl popis_soba;
};
