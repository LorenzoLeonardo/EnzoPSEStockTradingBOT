#pragma once
#include "afxdialogex.h"


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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
