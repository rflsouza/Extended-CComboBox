// TestComboView.cpp : implementation of the CTestComboView class
//

#include "stdafx.h"
#include "TestCombo.h"

#include "TestComboDoc.h"
#include "TestComboView.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestComboView

IMPLEMENT_DYNCREATE(CTestComboView, CFormView)

BEGIN_MESSAGE_MAP(CTestComboView, CFormView)
	//{{AFX_MSG_MAP(CTestComboView)
	ON_CBN_KILLFOCUS(IDC_COMBO1, OnKillfocusCombo1)
	ON_BN_CLICKED(IDC_BUTTON_TEXT, OnButtonText)
	ON_BN_CLICKED(IDC_BUTTON_BKG, OnButtonBkg)
	ON_BN_CLICKED(IDC_RADIO_STANDARD, OnRadioStandard)
	ON_BN_CLICKED(IDC_RADIO_AC, OnRadioAc)
	ON_BN_CLICKED(IDC_RADIO_DD, OnRadioDd)
	ON_CBN_SELENDOK(IDC_COMBO1, OnSelendokCombo1)
	ON_BN_CLICKED(IDC_RADIO_OVEREDIT, OnRadioOveredit)
	ON_BN_CLICKED(IDC_RADIO_ABOVEEDIT, OnRadioAboveedit)
	ON_CBN_CLOSEUP(IDC_COMBO1, OnCloseupCombo1)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestComboView construction/destruction

CTestComboView::CTestComboView()
	: CFormView(CTestComboView::IDD)
{
	//{{AFX_DATA_INIT(CTestComboView)
	//}}AFX_DATA_INIT
	// TODO: add construction code here

	m_bAlertText = FALSE;
	m_bAlertBkg = FALSE;
}

CTestComboView::~CTestComboView()
{
}

void CTestComboView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestComboView)
	DDX_Control(pDX, IDC_COMBO4, m_Combo4);
	DDX_Control(pDX, IDC_COMBO3, m_Combo3);
	DDX_Control(pDX, IDC_COMBO2, m_Combo2);
	DDX_Control(pDX, IDC_COMBO1, m_Combo1);
	DDX_Control(pDX, IDC_COMBO5, m_Combo5);
	//}}AFX_DATA_MAP
}

BOOL CTestComboView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CTestComboView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	CheckRadioButton(IDC_RADIO_STANDARD, IDC_RADIO_DD, IDC_RADIO_STANDARD);
	CheckRadioButton(IDC_RADIO_OVEREDIT, IDC_RADIO_ABOVEEDIT, IDC_RADIO_OVEREDIT);

	//m_Combo1.AdjustDroppedWidth();

	// To performance
	// Initialize the storage of the combo box to be 10000 strings with 
	// about 1024 characters per string, performance improvement. 
	int nAlloc = m_Combo1.InitStorage(8100, 1024);
	ASSERT(nAlloc != CB_ERRSPACE);
	BOOL teste;
	teste = m_Combo1.ModifyStyle(CBS_SORT | LBS_SORT, 0);
	

	int nIndex = CB_ERR;
	m_Combo1.ResetContent();	
	nIndex = m_Combo1.AddStringWithInfo(_T("Lorem ipsum dolor sit amet, consectetuer adipiscing elit"), _T("Ação\n Lorem\n ipsum dolor sit amet, consectetuer adipiscing elit"));
	m_Combo1.SetItemData(nIndex,4567);
	nIndex = m_Combo1.AddString(_T("One"));
	m_Combo1.SetItemData(nIndex,100);
	nIndex = m_Combo1.AddString(_T("Two"));
	m_Combo1.SetItemData(nIndex,200);
	nIndex = m_Combo1.AddString(_T("Three"));
	m_Combo1.SetItemData(nIndex,300);
	nIndex = m_Combo1.AddString(_T("Four"));
	m_Combo1.SetItemData(nIndex,400);
	nIndex = m_Combo1.AddString(_T("Five"));
	m_Combo1.SetItemData(nIndex,500);
	nIndex = m_Combo1.AddString(_T("Six"));
	m_Combo1.SetItemData(nIndex,600);
	nIndex = m_Combo1.AddString(_T("Seven"));
	m_Combo1.SetItemData(nIndex,700);
	nIndex = m_Combo1.AddString(_T("Eight"));
	m_Combo1.SetItemData(nIndex,800);
	nIndex = m_Combo1.AddString(_T("Nine"));
	m_Combo1.SetItemData(nIndex,900);
	nIndex = m_Combo1.AddString(_T("Ten"));
	m_Combo1.SetItemData(nIndex,1000);
	nIndex = m_Combo1.AddString(_T("Eleven"));
	m_Combo1.SetItemData(nIndex,1100);
	nIndex = m_Combo1.AddString(_T("Twelve"));
	m_Combo1.SetItemData(nIndex,1200);
	nIndex = m_Combo1.AddString(_T("Thirteen"));
	m_Combo1.SetItemData(nIndex,1300);

	m_Combo1.AddString(_T("Romania"));
	m_Combo1.AddString(_T("Switzerland"));
	m_Combo1.AddString(_T("Norway"));
	m_Combo1.AddString(_T("France"));
	m_Combo1.AddString(_T("United kindom"));
	m_Combo1.AddString(_T("Spain"));
	m_Combo1.AddString(_T("Bulgaria"));
	m_Combo1.AddString(_T("Belgium"));
	m_Combo1.AddString(_T("Maroc"));
	m_Combo1.AddString(_T("Libia"));
	m_Combo1.AddString(_T("Hungary"));
	m_Combo1.AddString(_T("Moldova"));
	m_Combo1.AddString(_T("Austria"));
	m_Combo1.AddString(_T("Algeria"));
	m_Combo1.AddString(_T("Korea"));
	m_Combo1.AddString(_T("Suedia"));
	m_Combo1.AddString(_T("Dutch"));
	m_Combo1.AddString(_T("Brazilia"));
	m_Combo1.AddString(_T("Italia"));
	m_Combo1.AddString(_T("Ucraina"));
	m_Combo1.AddString(_T("Cehia"));
	m_Combo1.AddString(_T("Australia"));
	m_Combo1.AddString(_T("New Zeeland"));
	m_Combo1.AddString(_T("South Africa"));
	m_Combo1.AddString(_T("Egipt"));
	m_Combo1.AddString(_T("United states of america"));
	m_Combo1.AddStringWithInfo(_T("acao é agora quero só ver!"), _T("Ação Lorem ipsum dolor sit amet, consectetuer adipiscing elit"));
	m_Combo1.AddStringWithInfo(_T("acão é agora quero só ver!"), _T("Ação Lorem ipsum dolor sit amet, consectetuer adipiscing elit"));
	m_Combo1.AddStringWithInfo(_T("açao é agora quero só ver!"), _T("Ação Lorem ipsum dolor sit amet, consectetuer adipiscing elit"));
	m_Combo1.AddStringWithInfo(_T("ação é agora quero só ver!"), _T("Ação Lorem ipsum dolor sit amet, consectetuer adipiscing elit"));
	m_Combo1.AddStringWithInfo(_T("Ação é agora quero só ver!"), _T("Ação Lorem ipsum dolor sit amet, consectetuer adipiscing elit"));
	m_Combo1.AddStringWithInfo(_T("AÇÃO é agora quero só ver!"), _T("Ação Lorem ipsum dolor sit amet, consectetuer adipiscing elit"));
	
	CString temp;
	for (int x = 0; x < 8000; x++) {
		temp.Format("Adicionando a String[%d] de teste, quero ver o comportamento agora. AÇÃO é agora quero só ver! %d", x, x);
		//m_Combo1.AddStringWithInfo(temp, temp);
	}
	
	m_Combo1.AdjustDroppedWidth();
	m_Combo1.SetEditTooltip(TRUE);	
	m_Combo1.SetListTooltip(TRUE, TRUE);	

	m_Combo1.SetAlertColorBkg(RGB(255, 0, 0));
	m_Combo1.SetAlertColorText(RGB(255, 0, 0));
	m_Combo1.SetTextColorNotFoundEnable(TRUE);	

	/*//////////////////////////////////////////////
		m_Combo1.SetTextColorNotFound(RGB(0, 255, 0));
		m_Combo1.AlertBkg();
		m_Combo1.AlertText();
	///*//////////////////////////////////////////////
	

	if(! m_ToolTips.GetSafeHwnd())
	{
		CButton *pRadioStandard, *pRadioAc, *pRadioDd, *pButtonText, *pButtonBkg;
		pRadioStandard = (CButton*)GetDlgItem(IDC_RADIO_STANDARD);
		pRadioAc = (CButton*)GetDlgItem(IDC_RADIO_AC);
		pRadioDd = (CButton*)GetDlgItem(IDC_RADIO_DD);
		pButtonText = (CButton*)GetDlgItem(IDC_BUTTON_TEXT);
		pButtonBkg = (CButton*)GetDlgItem(IDC_BUTTON_BKG);
		CButton* pRadioOverEdit = (CButton*)GetDlgItem(IDC_RADIO_OVEREDIT);
		CButton* pRadioAboveEdit = (CButton*)GetDlgItem(IDC_RADIO_ABOVEEDIT);

		m_ToolTips.Create(this);
		m_ToolTips.AddTool(pRadioStandard, _T("ComboBox will behave in standard mode"));
		m_ToolTips.AddTool(pRadioDd, _T("ComboBox will show a dropdown list with items that match with what you type in edit area"));
		m_ToolTips.AddTool(pRadioAc, _T("ComboBox will auto completes the word that match with letters typed, and will show a dropdown list with items that match with what you already typed in edit area"));
		m_ToolTips.AddTool(pButtonText, _T("The text within edit area will become red"));
		m_ToolTips.AddTool(pButtonBkg, _T("The background within edit area will become red"));
		m_ToolTips.AddTool(pRadioOverEdit, _T("By this option the edit tooltip will be positioned right over editbox item"));
		m_ToolTips.AddTool(pRadioAboveEdit, _T("By this option the edit tooltip will be positioned above editbox item"));
	}

	m_Combo2.AddStringWithInfo(_T("Picture landscape mountain.bmp"), _T("File size: 1340 KB"));
	m_Combo2.AddStringWithInfo(_T("Picture on sea.bmp"), _T("File size: 205 KB"));
	m_Combo2.AddStringWithInfo(_T("Portraint.bmp"), _T("File size: 490 KB"));
	m_Combo2.AddStringWithInfo(_T("Me and my friends.bmp"), _T(""));
	m_Combo2.AddStringWithInfo(_T("Happy days.bmp"), _T("File size: 488 KB"));
	m_Combo2.AddStringWithInfo(_T("FileNumber6"), _T("File size: 2058 KB"));
	m_Combo2.SetEditTooltip(TRUE, TRUE);
	m_Combo2.SetListTooltip(TRUE, TRUE);
	m_Combo2.AdjustDroppedWidth();

	m_Combo3.AddStringWithInfo(_T("C:\\Progra...Include"), _T("C:\\Program Files\\Microsoft Visual Studio\\VC98\\Include"));
	m_Combo3.AddStringWithInfo(_T("C:\\Progr...r\\en-US"), _T("C:\\Program Files\\Microsoft Games\\Minesweeper\\en-US"));
	m_Combo3.AddStringWithInfo(_T("D:\\Temp"), _T("D:\\Temp"), FALSE);
	m_Combo3.AddStringWithInfo(_T("D:\\Tempx"), _T("D:\\Tempx"), FALSE);
	m_Combo3.AddStringWithInfo(_T("D:\\Share\\Us...ement"), _T("D:\\Share\\User management"), TRUE);
	m_Combo3.AddStringWithInfo(_T("E:\\MyStuff"), _T("E:\\MyStuff"), FALSE);
	m_Combo3.AddStringWithInfo(_T("G:\\DVD\\Mov...edies"), _T("G:\\DVD\\Movies\\Comedies"), TRUE);
	m_Combo3.SetEditTooltip(TRUE, TRUE, TRUE);
	m_Combo3.SetListTooltip(TRUE, TRUE, TRUE, 80);

	m_Combo4.AddStringWithInfo(_T("C:\\Progra...Include"), _T("C:\\Program Files\\Microsoft Visual Studio\\VC98\\Include"));
	m_Combo4.AddStringWithInfo(_T("C:\\Progr...r\\en-US"), _T("C:\\Program Files\\Microsoft Games\\Minesweeper\\en-US"));
	m_Combo4.AddStringWithInfo(_T("D:\\Temp"), _T("D:\\Temp"), FALSE);
	m_Combo4.AddStringWithInfo(_T("D:\\Tempx"), _T("D:\\Tempx"), FALSE);
	m_Combo4.AddStringWithInfo(_T("D:\\Share\\Us...ement"), _T("D:\\Share\\User management"), TRUE);
	m_Combo4.AddStringWithInfo(_T("E:\\MyStuff"), _T("E:\\MyStuff"), FALSE);
	m_Combo4.AddStringWithInfo(_T("G:\\DVD\\Mov...edies"), _T("G:\\DVD\\Movies\\Comedies"), TRUE);
	m_Combo4.SetCurSel(0);
	m_Combo4.SetEditTooltip(TRUE, TRUE, TRUE);


	
	m_Combo5.SetMode(CComboBoxExt::MODE_DROPDOWN);

	nIndex = CB_ERR;
	m_Combo5.ResetContent();	
	nIndex = m_Combo5.AddStringWithInfo(_T("One"), _T("Tooltip One"));
	m_Combo5.SetItemData(nIndex, 100);
	nIndex = m_Combo5.AddStringWithInfo(_T("Two"), _T("Tooltip Two"));
	m_Combo5.SetItemData(nIndex, 200);
	
	nIndex = m_Combo5.AddStringWithInfo(_T("acao é agora quero só ver!"), _T("acao é agora quero só ver!\nacao é agora quero só ver!\nacao é agora quero só ver!"));
	m_Combo5.SetItemData(nIndex, 300);
	nIndex = m_Combo5.AddStringWithInfo(_T("acão é agora quero só ver!"), _T("acao é agora quero só ver! acao é agora quero só ver! acao é agora quero só ver!"));
	m_Combo5.SetItemData(nIndex, 400);
	nIndex = m_Combo5.AddStringWithInfo(_T("açao é agora quero só ver!"), _T("Ação"));
	m_Combo5.SetItemData(nIndex, 500);
	nIndex = m_Combo5.AddStringWithInfo(_T("ação é agora quero só ver!"), _T("Ação"));
	m_Combo5.SetItemData(nIndex, 600);
	nIndex = m_Combo5.AddStringWithInfo(_T("Ação é agora quero só ver!"), _T("Ação"));
	m_Combo5.SetItemData(nIndex, 700);
	nIndex = m_Combo5.AddStringWithInfo(_T("AÇÃO é agora quero só ver!"), _T("Ação"));
	m_Combo5.SetItemData(nIndex, 800);
	
	m_Combo5.AdjustDroppedWidth();
	m_Combo5.SetEditTooltip(TRUE);	
	m_Combo5.SetListTooltip(TRUE, TRUE, FALSE, 250);
}

/////////////////////////////////////////////////////////////////////////////
// CTestComboView printing

BOOL CTestComboView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTestComboView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTestComboView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CTestComboView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CTestComboView diagnostics

#ifdef _DEBUG
void CTestComboView::AssertValid() const
{
	CFormView::AssertValid();
}

void CTestComboView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CTestComboDoc* CTestComboView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestComboDoc)));
	return (CTestComboDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestComboView message handlers

BOOL CTestComboView::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class

	switch(pMsg->message)
	{
		case WM_MOUSEMOVE:
			m_ToolTips.RelayEvent(pMsg);
			break;
/*///
		case WM_KEYDOWN:
			if(VK_RETURN == pMsg->wParam)
			{
				COMBOBOXINFO cbi = {0};
				cbi.cbSize = sizeof(COMBOBOXINFO);
				BOOL bRet = ::GetComboBoxInfo(m_Combo1.m_hWnd, &cbi);
				if(bRet && pMsg->hwnd == cbi.hwndItem)
				{
					CString sText;
					m_Combo1.GetWindowText(sText);
					TRACE("The choosen text is: '%s' and has the index: %d\n", sText, m_Combo1.FindString(-1, sText));
				}
			}
			break;
///*////
	}

	return CFormView::PreTranslateMessage(pMsg);
}

void CTestComboView::OnButtonText() 
{
	// TODO: Add your control notification handler code here

	m_bAlertText = ! m_bAlertText;
	m_Combo1.AlertText(m_bAlertText, TRUE);

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->SetMessageText(_T("You ca toggle text alert pressing again 'Alert Text' button"));
}

void CTestComboView::OnButtonBkg() 
{
	// TODO: Add your control notification handler code here

	m_bAlertBkg = ! m_bAlertBkg;
	m_Combo1.AlertBkg(m_bAlertBkg,TRUE);

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->SetMessageText(_T("You ca toggle background alert pressing again 'Alert Bkg' button"));
}

void CTestComboView::OnRadioStandard() 
{
	// TODO: Add your control notification handler code here

	m_Combo1.SetMode(CComboBoxExt::MODE_STANDARD);
}

void CTestComboView::OnRadioAc() 
{
	// TODO: Add your control notification handler code here

	m_Combo1.SetMode(CComboBoxExt::MODE_AUTOCOMPLETE);
}

void CTestComboView::OnRadioDd() 
{
	// TODO: Add your control notification handler code here

	m_Combo1.SetMode(CComboBoxExt::MODE_DROPDOWN);
}

void CTestComboView::OnRadioOveredit() 
{
	// TODO: Add your control notification handler code here

	m_Combo4.SetEditTooltipOverItemPosition(FALSE);
}

void CTestComboView::OnRadioAboveedit() 
{
	// TODO: Add your control notification handler code here

	m_Combo4.SetEditTooltipOverItemPosition();
}

void CTestComboView::OnKillfocusCombo1() 
{
	// TODO: Add your control notification handler code here

	CString sTemp;
	int nIndex = m_Combo1.GetCurSel();
	if(CB_ERR != nIndex)
		sTemp.Format(_T("Index: %d, itemdata: %d"),m_Combo1.GetCurSel(),m_Combo1.GetItemData(m_Combo1.GetCurSel()));
	else
		sTemp.Format("null");
	TRACE("OnKillfocusCombo1 %s\n", sTemp);
	SetDlgItemText(IDC_EDIT1, sTemp);
}

void CTestComboView::OnSelendokCombo1() 
{
	// TODO: Add your control notification handler code here

	CString sTemp;
	const int nIndex = m_Combo1.GetCurSel();
	if(CB_ERR != nIndex)
	{
		m_Combo1.GetLBText(nIndex, sTemp);
		TRACE("OnSelendokCombo **** The chosen item was: %s\n", sTemp);
	}
}

void CTestComboView::OnCloseupCombo1() 
{
	// TODO: Add your control notification handler code here

	CString sTemp;
	m_Combo1.GetWindowText(sTemp);	
	int idx = m_Combo1.GetCurSel();
	TRACE("OnCloseupCombo **** The chosen item id[%d] was: %s\n", idx, sTemp);
}
