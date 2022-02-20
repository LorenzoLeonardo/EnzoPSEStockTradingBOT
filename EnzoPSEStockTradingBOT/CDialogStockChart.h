#pragma once
#include "afxdialogex.h"
#include "ChartCtrl/ChartCtrl.h"
#include "ChartCtrl/ChartLineSerie.h"
#include "ChartCtrl/Chartlabel.h"

// CDialogStockChart dialog

class CDialogStockChart : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogStockChart)

public:
	CDialogStockChart(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDialogStockChart();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHART_DIALOG };
#endif

protected:
	
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()

	CChartCtrl m_ChartCtrl;
	CChartStandardAxis *pBottomAxis;
	CChartStandardAxis *pLeftAxis;
	CChartLineSerie *pSeries;

};
