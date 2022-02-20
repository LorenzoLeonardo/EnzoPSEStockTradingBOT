// CDialogStockChart.cpp : implementation file
//

#include "pch.h"
#include "EnzoPSEStockTradingBOT.h"
#include "afxdialogex.h"
#include "CDialogStockChart.h"
#include "ChartCtrl/ChartLineSerie.h"
#include "ChartCtrl/ChartPointsSerie.h"
#include "ChartCtrl/ChartSurfaceSerie.h"
#include "ChartCtrl/ChartGrid.h"
#include "ChartCtrl/ChartBarSerie.h"
#include "ChartCtrl/ChartLabel.h"
#include "ChartCtrl/ChartAxisLabel.h"
#include "ChartCtrl/ChartStandardAxis.h"
#include "ChartCtrl/ChartDateTimeAxis.h"
#include "ChartCtrl/ChartCrossHairCursor.h"
#include "ChartCtrl/ChartDragLineCursor.h"


// CDialogStockChart dialog

IMPLEMENT_DYNAMIC(CDialogStockChart, CDialogEx)

CDialogStockChart::CDialogStockChart(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHART_DIALOG, pParent)
{

}

CDialogStockChart::~CDialogStockChart()
{
}

void CDialogStockChart::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogStockChart, CDialogEx)
END_MESSAGE_MAP()


// CDialogStockChart message handlers
