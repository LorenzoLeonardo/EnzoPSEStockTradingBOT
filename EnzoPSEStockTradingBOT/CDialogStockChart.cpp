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
	m_hGraphChart = NULL;
}

CDialogStockChart::~CDialogStockChart()
{
	CloseHandle(m_hGraphChart);
}

void CDialogStockChart::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CUSTOM_CHART, m_ChartCtrl);
}


BEGIN_MESSAGE_MAP(CDialogStockChart, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDialogStockChart message handlers


unsigned __stdcall  CDialogStockChart::UpdateGraphThread(void* parg)
{
	CDialogStockChart* pDLG = (CDialogStockChart*)parg;

	while (!pDLG->UpdateGraph())
	{
		Sleep(60000);
	}
	return 0;
}

BOOL CDialogStockChart::UpdateGraph()
{


	double XVal[20];
	double YVal[20];

	memset(XVal, 0, sizeof(XVal));
	memset(YVal, 0, sizeof(YVal));
	YVal[0] = m_pCStock->GetPricePerShare();
	XVal[0] = (((double)GetTickCount64()/ (double)1000)/(double)60) - (((double)m_ulTimeStart/ (double)1000) / (double)60);

	pSeries->AddPoints(XVal, YVal, 1);

	return m_bIsClosed;
}

BOOL CDialogStockChart::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CChartCtrl ref;
	ref.RemoveAllSeries();
	m_ChartCtrl.EnableRefresh(true);
	pBottomAxis = m_ChartCtrl.CreateStandardAxis(CChartCtrl::BottomAxis);
	pLeftAxis = m_ChartCtrl.CreateStandardAxis(CChartCtrl::LeftAxis);
	pBottomAxis->SetMinMax(0, 360);
	pLeftAxis->SetMinMax(0, m_pCStock->GetPricePerShare()*2);
	pBottomAxis->SetTickIncrement(false, 20.0);
	pBottomAxis->SetDiscrete(false);
	pBottomAxis->EnableScrollBar(true);

	
	pSeries = m_ChartCtrl.CreateLineSerie();
	pSeries->SetWidth(5);
	pSeries->SetColor(RGB(255, 0, 255));
	// TODO:  Add extra initialization here
	m_ulTimeStart = GetTickCount64();
	m_bIsClosed = false;
	m_hGraphChart = (HANDLE)_beginthreadex(NULL, 0, UpdateGraphThread, this, 0, NULL);
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


void CDialogStockChart::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	m_bIsClosed = true;
//	WaitForSingleObject(m_hGraphChart, INFINITE);
//	CDialogEx::OnClose();
}
