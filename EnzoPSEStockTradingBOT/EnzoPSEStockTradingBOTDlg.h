
// EnzoPSEStockTradingBOTDlg.h : header file
//

#pragma once
#include "CStock.h"
#include "CListCtrlCustom.h"
#include "CDialogStockChart.h"
#include <map>

using namespace std;
#define STOCK_BDO     _T("https://phisix-api4.appspot.com/stocks/BDO.json")
#define STOCK_BPI     _T("https://phisix-api4.appspot.com/stocks/BPI.json")
#define STOCK_CHIB    _T("https://phisix-api4.appspot.com/stocks/CHIB.json")
#define STOCK_COL     _T("https://phisix-api4.appspot.com/stocks/COL.json")
#define STOCK_EW      _T("https://phisix-api4.appspot.com/stocks/EW.json")
#define STOCK_BDO     _T("https://phisix-api4.appspot.com/stocks/BDO.json")
#define STOCK_BDO     _T("https://phisix-api4.appspot.com/stocks/BDO.json")
#define STOCK_BDO     _T("https://phisix-api4.appspot.com/stocks/BDO.json")
#define STOCK_BDO     _T("https://phisix-api4.appspot.com/stocks/BDO.json")
#define STOCK_BDO     _T("https://phisix-api4.appspot.com/stocks/BDO.json")
#define STOCK_BDO     _T("https://phisix-api4.appspot.com/stocks/BDO.json")
#define STOCK_BDO     _T("https://phisix-api4.appspot.com/stocks/BDO.json")
#define STOCK_ALL      _T("https://phisix-api4.appspot.com/stocks.json")

// CEnzoPSEStockTradingBOTDlg dialog
class CEnzoPSEStockTradingBOTDlg : public CDialogEx
{
// Construction
public:
	CEnzoPSEStockTradingBOTDlg(CWnd* pParent = nullptr);	// standard constructor
	~CEnzoPSEStockTradingBOTDlg();
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ENZOPSESTOCKTRADINGBOT_DIALOG };
#endif
	static unsigned __stdcall  CEnzoPSEStockTradingBOTDlg::ListenForJSON(void* parg);
	bool IsAppClosed()
	{
		return m_bIsPressedStop;
	}
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	inline map<string_t, CStock> JSONToStock(string_t sJSON);
	void DisplayStockInfo(map<string_t, CStock>& mapStocks);
	void InitializeStockInfo(map<string_t, CStock>& mapStocks);
	void CopyNewDataToStockList(map<string_t, CStock>& mapStocks);
	HANDLE GetEventHandle()
	{
		return m_hEvent;
	}
// Implementation
protected:
	enum
	{
		COL_NUMBERING = 0,
		COL_COMPANYNAME,
		COL_STOCKSYMBOL,
		COL_CURRENCY,
		COL_PRICE,
		COL_VOLUME,
		COL_CHANGE,
		COL_DATE,
	};
	HICON m_hIcon;
	HANDLE m_hListenJSON;
	HANDLE m_hEvent;
	bool m_bIsPressedStop;
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnUserDefinedCloseDialog(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
	CListCtrlCustom m_ctrlListStocks;
	map<string_t, CStock> m_mapCStock;
	HBRUSH m_hBrushBackGround;

public:
	afx_msg void OnClose();
//	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedStartStop();
	afx_msg void OnNMDblclkListStocks(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButtonCheckgraph();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
