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
	DDX_Control(pDX, IDC_CUSTOM_CHART, m_ChartCtrl);
}


BEGIN_MESSAGE_MAP(CDialogStockChart, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDialogStockChart message handlers


BOOL CDialogStockChart::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	CChartCtrl ref;
	ref.RemoveAllSeries();
	m_ChartCtrl.EnableRefresh(true);
	pBottomAxis = m_ChartCtrl.CreateStandardAxis(CChartCtrl::BottomAxis);
	pLeftAxis = m_ChartCtrl.CreateStandardAxis(CChartCtrl::LeftAxis);
	pBottomAxis->SetMinMax(100, 300);
	pLeftAxis->SetMinMax(-1, 1.5);
	pBottomAxis->SetTickIncrement(false, 20.0);
	pBottomAxis->SetDiscrete(false);
	pBottomAxis->EnableScrollBar(true);

	pSeries = m_ChartCtrl.CreateLineSerie();
	pSeries->SetWidth(5);
	pSeries->SetColor(RGB(255, 0, 255));

	double XVal[20] = {103.5,145.856};
	double YVal[20] = { 0.812003,0.295188 };

	pSeries->SetPoints(XVal, YVal, 20);
	m_ChartCtrl.EnableRefresh(true);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


HBRUSH CDialogStockChart::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}


void CDialogStockChart::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CDialogEx::OnPaint() for painting messages

	CDialogEx::OnPaint();
}
