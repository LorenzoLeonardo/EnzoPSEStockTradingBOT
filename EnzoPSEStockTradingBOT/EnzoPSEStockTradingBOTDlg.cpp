
// EnzoPSEStockTradingBOTDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "EnzoPSEStockTradingBOT.h"
#include "EnzoPSEStockTradingBOTDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CEnzoPSEStockTradingBOTDlg dialog


CEnzoPSEStockTradingBOTDlg::CEnzoPSEStockTradingBOTDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ENZOPSESTOCKTRADINGBOT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEnzoPSEStockTradingBOTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_STOCKS, m_ctrlListStocks);
}

BEGIN_MESSAGE_MAP(CEnzoPSEStockTradingBOTDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
//	ON_BN_CLICKED(IDOK, &CEnzoPSEStockTradingBOTDlg::OnBnClickedOk)
ON_BN_CLICKED(IDC_START_STOP, &CEnzoPSEStockTradingBOTDlg::OnBnClickedStartStop)
ON_NOTIFY(NM_DBLCLK, IDC_LIST_STOCKS, &CEnzoPSEStockTradingBOTDlg::OnNMDblclkListStocks)
ON_BN_CLICKED(IDC_BUTTON_CHECKGRAPH, &CEnzoPSEStockTradingBOTDlg::OnBnClickedButtonCheckgraph)
ON_MESSAGE(WM_ENZO_CLOSE, OnUserDefinedCloseDialog)
END_MESSAGE_MAP()


// CEnzoPSEStockTradingBOTDlg message handlers

BOOL CEnzoPSEStockTradingBOTDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	LPCTSTR lpcRecHeader[] = { _T("No."), _T("Company Name"), _T("Stock Symbol"), _T("Currency"), _T("Price Per Share"), _T("Volume"),  _T("Change"), _T("Date") };
	int nCol = 0;
	//::SetWindowTheme(m_ctrlListStocks.GetSafeHwnd(), _T(""), _T(""));//To change text Color of Group Box
	m_ctrlListStocks.SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_HEADERDRAGDROP | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	// TODO: Add extra initialization here
	m_ctrlListStocks.InsertColumn(nCol, lpcRecHeader[nCol++], LVCFMT_FIXED_WIDTH| LVCFMT_RIGHT, 30);
	m_ctrlListStocks.InsertColumn(nCol, lpcRecHeader[nCol++], LVCFMT_LEFT, 130);
	m_ctrlListStocks.InsertColumn(nCol, lpcRecHeader[nCol++], LVCFMT_LEFT, 60);
	m_ctrlListStocks.InsertColumn(nCol, lpcRecHeader[nCol++], LVCFMT_LEFT, 60);
	m_ctrlListStocks.InsertColumn(nCol, lpcRecHeader[nCol++], LVCFMT_LEFT, 90);
	m_ctrlListStocks.InsertColumn(nCol, lpcRecHeader[nCol++], LVCFMT_LEFT, 110);
	m_ctrlListStocks.InsertColumn(nCol, lpcRecHeader[nCol++], LVCFMT_LEFT, 60);
	m_ctrlListStocks.InsertColumn(nCol, lpcRecHeader[nCol++], LVCFMT_LEFT, 180);
	m_bIsPressedStop = true;

	m_hEvent = NULL;
	m_hListenJSON = NULL;
	OnBnClickedStartStop();
	return TRUE;  // return TRUE  unless you set the focus to a control
}
LRESULT CEnzoPSEStockTradingBOTDlg::OnUserDefinedCloseDialog(WPARAM wParam, LPARAM lParam)
{
	OnOK();
	return 0;
}
unsigned __stdcall  CEnzoPSEStockTradingBOTDlg::ListenForJSON(void* parg)
{
	CEnzoPSEStockTradingBOTDlg* pDLG = (CEnzoPSEStockTradingBOTDlg * )parg;
	string_t sJSON;
	http_client client(STOCK_ALL);//(STOCK_BDO);

	auto resp = client.request(_T("GET")).get();
	sJSON = resp.extract_string(true).get();
	map<string_t, CStock> cstock = pDLG->JSONToStock(sJSON);
	pDLG->InitializeStockInfo(cstock);
	
	while (WaitForSingleObject(pDLG->GetEventHandle(), 0) != WAIT_OBJECT_0)
	{
		resp = client.request(_T("GET")).get();
		sJSON = resp.extract_string(true).get();
		cstock = pDLG->JSONToStock(sJSON);
		pDLG->DisplayStockInfo(cstock);
		Sleep(1000);
	}
	::PostMessage(pDLG->GetSafeHwnd(), WM_ENZO_CLOSE, 0, 0);
	return 0;
}

void CEnzoPSEStockTradingBOTDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CEnzoPSEStockTradingBOTDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CEnzoPSEStockTradingBOTDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CEnzoPSEStockTradingBOTDlg::CopyNewDataToStockList(map<string_t, CStock>& mapStocks)
{
	map<string_t, CStock>::iterator it = mapStocks.begin();

	while (it != mapStocks.end())
	{
		m_mapCStock[it->first] = it->second;
		it++;
	}
}
void CEnzoPSEStockTradingBOTDlg::DisplayStockInfo(map<string_t, CStock>& mapStocks)
{
	map<string_t, CStock>::iterator it = mapStocks.begin();
	LVFINDINFO lvFindInfo;
	lvFindInfo.flags = LVFI_PARTIAL | LVFI_STRING;
	


	LVITEM lvItem;
	lvItem.mask = LVIF_TEXT;
	int findResult = -1;

	//LPCTSTR lpcRecHeader[] = { _T("No."), 
	//	_T("Company Name"), 
	//	_T("Stock Symbol"),
	//	_T("Currency"),
	//	_T("Price Per Share"),
	//	_T("Volume"), 
	//	_T("Change"), 
	//	_T("Date") };
	string_t sTemp;
	CString csFormat;
	//m_mapCStock = mapStocks;
	CopyNewDataToStockList(mapStocks);
	for (int i = 0; it!= mapStocks.end(); ++i, it++)
	{
		csFormat.Format(_T("%.2f"), it->second.GetPricePerShare());
		lvItem.iItem = i;
		lvItem.iSubItem = 4;
		lvItem.pszText = (LPTSTR)csFormat.GetBuffer();
		m_ctrlListStocks.SetItem(&lvItem);

		sTemp = to_wstring(it->second.GetVolume());
		lvItem.iItem = i;
		lvItem.iSubItem = 5;
		lvItem.pszText = (LPTSTR)sTemp.c_str();
		m_ctrlListStocks.SetItem(&lvItem);

		csFormat.Format(_T("%.2f"), it->second.GetPercentChange());
		lvItem.iItem = i;
		lvItem.iSubItem = 6;
		lvItem.pszText = (LPTSTR)csFormat.GetBuffer();
		m_ctrlListStocks.SetItem(&lvItem);

		sTemp = it->second.GetDate();
		lvItem.iItem = i;
		lvItem.iSubItem = 7;
		lvItem.pszText = (LPTSTR)sTemp.c_str();
		m_ctrlListStocks.SetItem(&lvItem);
	}
}

void CEnzoPSEStockTradingBOTDlg::InitializeStockInfo(map<string_t, CStock>& mapStocks)
{
	map<string_t, CStock>::iterator it = mapStocks.begin();
	int nRow = 0, col = 0;

	CopyNewDataToStockList(mapStocks);
	m_ctrlListStocks.DeleteAllItems();
	CString csFormat;
	while (it != mapStocks.end())
	{
		m_ctrlListStocks.InsertItem(LVIF_TEXT | LVIF_STATE, nRow,
			to_wstring(nRow + 1).c_str(), 0, 0, 0, 0);


		m_ctrlListStocks.SetItemText(nRow, col + 1, it->second.GetCompanyName().c_str());
		m_ctrlListStocks.SetItemText(nRow, col + 2, it->second.GetStockSymbol().c_str());
		m_ctrlListStocks.SetItemText(nRow, col + 3, it->second.GetCurrency().c_str());
		csFormat.Format(_T("%.2f"), it->second.GetPricePerShare());
		m_ctrlListStocks.SetItemText(nRow, col + 4, csFormat);
		m_ctrlListStocks.SetItemText(nRow, col + 5, to_wstring(it->second.GetVolume()).c_str());
		csFormat.Format(_T("%.2f"), it->second.GetPercentChange());
		m_ctrlListStocks.SetItemText(nRow, col + 6, csFormat);
		m_ctrlListStocks.SetItemText(nRow, col + 7, it->second.GetDate().c_str());
		it++;
		nRow++;
	}
}
map<string_t, CStock> CEnzoPSEStockTradingBOTDlg::JSONToStock(string_t sJSON)
{
	CJSONParser parse;
	CStock cstock;
	string_t sTemp;
	float fTemp;
	unsigned long ulTemp;
	map<string_t, string_t> m_mapLst;
	map<string_t, CStock> m_stockList;
	map<string_t, string_t>::iterator it;
	parse.SetJSONString(sJSON);

	m_mapLst = parse.GetParsedStrings();
	it = m_mapLst.begin();
	while (it != m_mapLst.end())
	{
		parse.GetValue(it->second, _T("\"name\""), sTemp);
		cstock.SetCompanyName(sTemp);

		parse.GetValue(it->second, _T("\"currency\""), sTemp);
		cstock.SetCurrency(sTemp);

		parse.GetValue(it->second, _T("\"symbol\""), sTemp);
		cstock.SetStockSymbol(sTemp);

		parse.GetValue(it->second, _T("\"amount\""), fTemp);
		cstock.SetPricePerShare(fTemp);

		parse.GetValue(it->second, _T("\"percent_change\""), fTemp);
		cstock.SetPercentChange(fTemp);

		parse.GetValue(it->second, _T("\"volume\""), ulTemp);
		cstock.SetVolume(ulTemp);

		parse.GetValue(_T("\"as_of\""), sTemp);
		cstock.SetDate(sTemp);

		m_stockList[cstock.GetStockSymbol()] = cstock;
		it++;
	}

	return m_stockList;
}

void CEnzoPSEStockTradingBOTDlg::OnClose()
{
	if (m_bIsPressedStop)
	{
		if (m_hEvent != NULL)
		{
			CloseHandle(m_hEvent);
			m_hEvent = NULL;

		}
		if (m_hListenJSON != NULL)
		{
			CloseHandle(m_hListenJSON);
			m_hListenJSON = NULL;
		}
		CDialog::OnClose();
	}
	else
	{
		SetEvent(m_hEvent);
		m_bIsPressedStop = true;
		this->GetDlgItem(IDC_START_STOP)->SetWindowText(_T("Start Monitoring"));

	}
}


//void CEnzoPSEStockTradingBOTDlg::OnBnClickedOk()
//{
//	// TODO: Add your control notification handler code here
//	CDialogEx::OnOK();
//}


void CEnzoPSEStockTradingBOTDlg::OnBnClickedStartStop()
{
	if (m_bIsPressedStop)
	{
		if (m_hEvent != NULL)
		{
			CloseHandle(m_hEvent);
			m_hEvent = NULL;

		}
		if (m_hListenJSON != NULL)
		{
			CloseHandle(m_hListenJSON);
			m_hListenJSON = NULL;
		}
		m_hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
		m_hListenJSON = (HANDLE)_beginthreadex(NULL, 0, ListenForJSON, this, 0, NULL);
		m_bIsPressedStop = false;
		this->GetDlgItem(IDC_START_STOP)->SetWindowText(_T("Stop Monitoring"));

	}
	else
	{

		SetEvent(m_hEvent);
		m_bIsPressedStop = true;
		this->GetDlgItem(IDC_START_STOP)->SetWindowText(_T("Start Monitoring"));

	}
}


void CEnzoPSEStockTradingBOTDlg::OnNMDblclkListStocks(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	LVITEM itemToGet;
	ZeroMemory(&itemToGet, sizeof(LVITEM));

	//specifies the index of the item in the CListCtrl that should be retrieved
	itemToGet.iItem = pNMItemActivate->iItem;
	itemToGet.iSubItem = 2;

	TCHAR szBuffer[32];
	memset(szBuffer, 0,sizeof(szBuffer));

	itemToGet.mask = LVIF_TEXT;
	itemToGet.pszText = szBuffer;
	CString cs = m_ctrlListStocks.GetItemText(pNMItemActivate->iItem, 2);
	int ret = m_ctrlListStocks.GetItem(&itemToGet);
	//m_mapCStock

	CStock *ptr = &m_mapCStock[cs.GetBuffer()];
	CDialogStockChart m_dlgStockChart;
	m_dlgStockChart.SetPointerToStock(ptr);

	INT nRet = m_dlgStockChart.DoModal();
}


void CEnzoPSEStockTradingBOTDlg::OnBnClickedButtonCheckgraph()
{
	// TODO: Add your control notification handler code here
	CDialogStockChart dlg;
	//dlg.SetPointerToStock(&m_mapCStock);
	INT nRet = dlg.DoModal();
}
