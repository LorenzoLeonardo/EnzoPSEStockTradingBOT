#pragma once
#include "afxdialogex.h"
#include "ChartCtrl/ChartCtrl.h"
#include "ChartCtrl/ChartLineSerie.h"
#include "ChartCtrl/Chartlabel.h"
#include "CStock.h"
// CDialogStockChart dialog

class CDialogStockChart : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogStockChart)

public:
	CDialogStockChart(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDialogStockChart();

	void SetPointerToStock(CStock* pStock)
	{
		m_pCStock = pStock;
	}
	BOOL UpdateGraph();
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHART_DIALOG };
#endif
	static unsigned __stdcall  UpdateGraphThread(void* parg);
protected:
	HANDLE m_hGraphChart;
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
	BOOL m_bIsClosed;
	ULONG m_ulTimeStart;
	double m_startPrice;
	CChartCtrl m_ChartCtrl;
	CChartStandardAxis *pBottomAxis;
	CChartStandardAxis *pLeftAxis;
	CChartLineSerie *pSeries;
	CStock* m_pCStock;

public:
	afx_msg void OnClose();
};
