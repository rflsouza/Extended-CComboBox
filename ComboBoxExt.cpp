// ComboBoxExt.cpp : implementation file
// reference: https://www.codeproject.com/Articles/187753/Extended-CComboBox
// https://www.codeproject.com/articles/1131087/list-combobox-control outro exemplo.

#include "stdafx.h"
#include "ComboBoxExt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CComboBoxExt

CComboBoxExt::CItemData::CItemData()
	:m_dwItemData(CB_ERR)
	,m_sItem(_T(""))
	,m_sItemCompared(_T(""))
	,m_bState(TRUE)
	,m_bShowItemTooltip(TRUE)
{
}

CComboBoxExt::CItemData::CItemData(DWORD dwItemData, LPCTSTR lpszString)
	:m_bState(TRUE)
	,m_bShowItemTooltip(TRUE)
{
	m_dwItemData = dwItemData;
	m_sItem = lpszString;
	m_sItemCompared = m_sItem.MakeLower();
	m_sItemCompared = CComboBoxExt::removeAccented(m_sItemCompared.GetBuffer(0));
	m_sInfo.Empty();
}

CComboBoxExt::CItemData::CItemData(DWORD dwItemData, LPCTSTR lpszString, BOOL bState)
	:m_bShowItemTooltip(TRUE)
{
	m_dwItemData = dwItemData;
	m_sItem = lpszString;
	m_sItemCompared = m_sItem.MakeLower();
	m_sItemCompared = CComboBoxExt::removeAccented(m_sItemCompared.GetBuffer(0));
	m_sInfo.Empty();
	m_bState = bState;
}

CComboBoxExt::CItemData::CItemData(DWORD dwItemData, LPCTSTR lpszString, LPCTSTR lpszInfo, BOOL bState)
	:m_bShowItemTooltip(TRUE)
{
	m_dwItemData = dwItemData;
	m_sItem = lpszString;
	m_sItemCompared = m_sItem.MakeLower();
	m_sItemCompared = CComboBoxExt::removeAccented(m_sItemCompared.GetBuffer(0));
	m_sInfo = lpszInfo;
	m_bState = bState;
}

CComboBoxExt::CItemData::CItemData(DWORD dwItemData, LPCTSTR lpszString, LPCTSTR lpszInfo, BOOL bState, BOOL bShowItemTooltip)
{
	m_dwItemData = dwItemData;
	m_sItem = lpszString;
	m_sItemCompared = m_sItem.MakeLower();
	m_sItemCompared = CComboBoxExt::removeAccented(m_sItemCompared.GetBuffer(0));
	m_sInfo = lpszInfo;
	m_bState = bState;
	m_bShowItemTooltip = bShowItemTooltip;
}

CComboBoxExt::CItemData::~CItemData()
{
}

CComboBoxExt::CComboBoxExt()
	:m_nMode(MODE_STANDARD)
	,m_bEdit(FALSE)
	,m_dwStartSel(0)
	,m_dwEndSel(0)
	,m_bAlertBkg(FALSE)
	,m_bAlertText(FALSE)
	,m_bTextColorNotFound(FALSE)
	,m_bTextColorNotFoundEnable(FALSE)
	,m_bToolActive(FALSE)
	,m_bShowTooltip(FALSE)
	,m_bTooltipOnInfo(FALSE)
	,m_bShowEditTooltipOverItem(FALSE)
	,m_bEditTooltipOverItemPos(FALSE)
	,m_bAutoComplete(TRUE)
	,m_bAutoSelection(FALSE)
	,m_bAdjustDroppedWidth(FALSE)	
	,m_sFirstTextNotFound("")	
{
	m_hWndToolTip = NULL;
	m_crAlertBkg = GetSysColor(COLOR_WINDOW);
	m_crAlertText = GetSysColor(COLOR_WINDOWTEXT);
	m_crTextColorNotFound = RGB(255, 0, 0);
	m_BrushAlert.CreateSolidBrush(m_crAlertBkg);
}

CComboBoxExt::~CComboBoxExt()
{
	TRACE("COUNT %d", m_PtrList.GetCount());

	m_BrushAlert.DeleteObject();

	if (m_hWndToolTip)
	{
		::DestroyWindow(m_hWndToolTip);
		m_hWndToolTip = NULL;
	}
}

BEGIN_MESSAGE_MAP(CComboBoxExt, CComboBox)
	//{{AFX_MSG_MAP(CComboBoxExt)
	ON_WM_DESTROY()
	ON_CONTROL_REFLECT_EX(CBN_CLOSEUP, OnCloseup)
	ON_CONTROL_REFLECT_EX(CBN_DROPDOWN, OnDropdown)
	ON_CONTROL_REFLECT_EX(CBN_SELENDOK, OnSelendok)
	ON_CONTROL_REFLECT_EX(CBN_SELCHANGE, OnSelchange)
	ON_CONTROL_REFLECT_EX(CBN_EDITCHANGE, OnEditchange)
	ON_WM_CTLCOLOR()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_MESSAGE(CB_ADDSTRING, OnAddString)
	ON_MESSAGE(CB_INSERTSTRING, OnInsertString)
	ON_MESSAGE(CB_DELETESTRING, OnDeleteString)
	ON_MESSAGE(CB_RESETCONTENT, OnResetContent)
	ON_MESSAGE(WMU_POSTCLOSEUP, OnPostCloseup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComboBoxExt message handlers

void CComboBoxExt::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class

	COMBOBOXINFO cbi = {0};
	cbi.cbSize = sizeof(COMBOBOXINFO);
	BOOL bRet = ::GetComboBoxInfo(m_hWnd, &cbi);
	if(bRet && NULL != cbi.hwndList)
	{
		if(m_ListBox.SubclassWindow(cbi.hwndList))
			m_ListBox.m_pComboBox = this;
	}

	// create tooltip
	m_hWndToolTip = ::CreateWindowEx(WS_EX_TOPMOST, 
							  TOOLTIPS_CLASS, 
							  NULL, 
							  TTS_NOPREFIX | TTS_ALWAYSTIP, 
							  CW_USEDEFAULT, 
							  CW_USEDEFAULT, 
							  CW_USEDEFAULT, 
							  CW_USEDEFAULT, 
							  NULL, 
							  NULL, 
							  NULL, 
							  NULL);
	ASSERT(m_hWndToolTip);
	// initialize toolinfo struct
	memset(&m_ToolInfo, 0, sizeof(m_ToolInfo));
#ifdef _UNICODE
	m_ToolInfo.cbSize = sizeof(TTTOOLINFOW_V2_SIZE);
#else
	m_ToolInfo.cbSize = sizeof(TTTOOLINFOA_V2_SIZE);
#endif
	m_ToolInfo.uFlags = TTF_TRACK | TTF_TRANSPARENT;
	m_ToolInfo.hwnd = m_hWnd;
	::SendMessage(m_hWndToolTip, TTM_SETMAXTIPWIDTH, (WPARAM)0, (LPARAM)SHRT_MAX);
	::SendMessage(m_hWndToolTip, TTM_ADDTOOL, (WPARAM)0, (LPARAM)(LPTOOLINFO)&m_ToolInfo);

	CComboBox::PreSubclassWindow();
}

BOOL CComboBoxExt::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class

	if(MODE_STANDARD != m_nMode && WM_KEYDOWN == pMsg->message)
	{
		if(MODE_AUTOCOMPLETE == m_nMode && (VK_DELETE == pMsg->wParam || VK_BACK == pMsg->wParam))
			m_bAutoComplete = FALSE;
	}

	return CComboBox::PreTranslateMessage(pMsg);
}

void CComboBoxExt::FitDropDownToItems()
{
	TRACE("%s\r\n", __FUNCTION__);

	if(CBS_SIMPLE == (3 & GetStyle()) || NULL == m_ListBox.GetSafeHwnd())
		return;

	CRect rectEdit, rectDropDown, rectDropDownCli;
	GetWindowRect(rectEdit);
	m_ListBox.GetWindowRect(rectDropDown);
	m_ListBox.GetClientRect(rectDropDownCli);

	int nHeight = rectDropDown.Height() - rectDropDownCli.Height();
	const int nMaxHeight = GetSystemMetrics(SM_CYSCREEN) / 2;
	const int nCount = GetCount();
	for(int nIndex = 0;nIndex < nCount;++nIndex)
	{
		nHeight += GetItemHeight(nIndex);
		if(nHeight > nMaxHeight)
			break;
	}

	CRect rcDropDownNew(rectDropDown.left, rectDropDown.top, rectDropDown.right, rectDropDown.top + nHeight);
	if(rectEdit.top > rectDropDown.top && rectEdit.top != rcDropDownNew.bottom)
		rcDropDownNew.top += (rectEdit.top - rcDropDownNew.bottom);
	m_ListBox.MoveWindow(rcDropDownNew);
}

BOOL CComboBoxExt::OnDropdown() 
{
	TRACE("%s\r\n", __FUNCTION__);
	// TODO: Add your control notification handler code here

	SetCursor(LoadCursor(NULL, IDC_ARROW));
	::SendMessage(m_hWndToolTip, TTM_TRACKACTIVATE, (WPARAM)FALSE, (LPARAM)(LPTOOLINFO)&m_ToolInfo);

	if(! m_bAdjustDroppedWidth)
		return Default();

	int dx = 0;
	CSize sz(0,0);
	TEXTMETRIC tm;
	CString sLBText;
	CDC* pDC = GetDC();
	CFont* pFont = GetFont();
	// Select the listbox font, save the old font
	CFont* pOldFont = pDC->SelectObject(pFont);
	// Get the text metrics for avg char width
	pDC->GetTextMetrics(&tm);

	const int nCount = GetCount();
	for(int i = 0;i < nCount;++i)
	{
		GetLBText(i, sLBText);
		sz = pDC->GetTextExtent(sLBText);
		// Add the avg width to prevent clipping
		sz.cx += tm.tmAveCharWidth;
		if(sz.cx > dx)
			dx = sz.cx;
	}

	// Select the old font back into the DC
	pDC->SelectObject(pOldFont);
	ReleaseDC(pDC);

	// Adjust the width for the vertical scroll bar and the left and right border.
	dx += GetSystemMetrics(SM_CXVSCROLL) + 2 * GetSystemMetrics(SM_CXEDGE);
	if(GetDroppedWidth() < dx)
		SetDroppedWidth(dx);

	return Default();
}

HBRUSH CComboBoxExt::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	//TRACE("%s\r\n", __FUNCTION__);
	HBRUSH hbr = CComboBox::OnCtlColor(pDC, pWnd, nCtlColor);
	if(CBS_DROPDOWNLIST == (3 & GetStyle()) || CBS_SIMPLE == (3 & GetStyle()))
		return hbr;

	// TODO: Change any attributes of the DC here

	if(CTLCOLOR_EDIT == nCtlColor)
	{
		if (m_bTextColorNotFound)					
				pDC->SetTextColor(m_crTextColorNotFound);		
		else
		{
			if (!m_bAlertText)
				pDC->SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
			else
				pDC->SetTextColor(m_crAlertText);
		}

		if(! m_bAlertBkg)
			pDC->SetBkColor(GetSysColor(COLOR_WINDOW));
		else
		{
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetBkColor(m_crAlertBkg);
			hbr = (HBRUSH)m_BrushAlert.GetSafeHandle();
		}
	}

	// TODO: Return a different brush if the default is not desired

	return hbr;
}

BOOL CComboBoxExt::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult) 
{
	//TRACE("%s\r\n", __FUNCTION__);
	// TODO: Add your specialized code here and/or call the base class

	if(CBS_DROPDOWNLIST != (3 & GetStyle()) || (! m_bAlertText && ! m_bAlertBkg && ! m_bTextColorNotFound) || WM_CTLCOLOREDIT != message)
		return CComboBox::OnChildNotify(message, wParam, lParam, pLResult);

	HDC hdcChild = (HDC)wParam;
	if(NULL != hdcChild)
	{
		if (m_bTextColorNotFound)
			SetTextColor(hdcChild, m_crTextColorNotFound);
		else if(m_bAlertText)
			SetTextColor(hdcChild, m_crAlertText);
		if(m_bAlertBkg)
			SetBkColor(hdcChild, m_crAlertBkg);
		*pLResult = (LRESULT)(m_BrushAlert.GetSafeHandle());
	}

	return TRUE;
//	return CComboBox::OnChildNotify(message, wParam, lParam, pLResult);
}

void CComboBoxExt::OnDestroy() 
{
	TRACE("%s\r\n", __FUNCTION__);
	if(NULL != m_ListBox.GetSafeHwnd())
		m_ListBox.UnsubclassWindow();

	CComboBox::OnDestroy();

	// TODO: Add your message handler code here

	POSITION pos = m_PtrList.GetHeadPosition();
	while(NULL != pos)
	{
		CItemData* pData = m_PtrList.GetNext(pos);
		if(NULL != pData)
		{
			delete pData;
			pData = NULL;
		}
	}
	m_PtrList.RemoveAll();
}

LRESULT CComboBoxExt::OnResetContent(WPARAM wParam, LPARAM lParam)
{
	TRACE("%s\r\n", __FUNCTION__);
	m_sTypedText.Empty();
	m_sFirstTextNotFound.Empty();	

	POSITION pos = m_PtrList.GetHeadPosition();
	while(NULL != pos)
	{
		CItemData* pData = m_PtrList.GetNext(pos);
		if(NULL != pData)
		{
			delete pData;
			pData = NULL;
		}
	}
	m_PtrList.RemoveAll();

	return Default();
}

BOOL CComboBoxExt::OnSelendok() 
{
	TRACE("%s\r\n", __FUNCTION__);
	// TODO: Add your control notification handler code here

	::SendMessage(m_hWndToolTip, TTM_TRACKACTIVATE, (WPARAM)FALSE, (LPARAM)(LPTOOLINFO)&m_ToolInfo);

	if(! GetDroppedState())
		return Default();

	int nIndex = GetCurSel();
	if(CB_ERR != nIndex)
	{
		GetLBText(nIndex, m_sTypedText);
		SetWindowText(m_sTypedText);
		m_dwStartSel = m_dwEndSel = m_sTypedText.GetLength();
		SetEditSel(m_dwStartSel, m_dwEndSel);
	}

	return Default();
}

BOOL CComboBoxExt::OnSelchange() 
{
	TRACE("%s\r\n", __FUNCTION__);
	// TODO: Add your control notification handler code here

	::SendMessage(m_hWndToolTip, TTM_TRACKACTIVATE, (WPARAM)FALSE, (LPARAM)(LPTOOLINFO)&m_ToolInfo);

	if(GetDroppedState())
	{
		m_dwStartSel = 0;
		m_dwEndSel = -1;
	}

	if(m_bEdit || MODE_STANDARD == m_nMode || CBS_SIMPLE == (3 & GetStyle()))
		return Default();

	const int nIndex = GetCurSel();
	if(CB_ERR != nIndex)
	{
		GetLBText(nIndex, m_sTypedText);
		SetWindowText(m_sTypedText);
	}

	return Default();
}

BOOL CComboBoxExt::OnEditchange()
{
	if (BIG_LIST < m_PtrList.GetCount())
	{
		//waiting more char to search text. (prevent slow screen).
		KillTimer(EventTimerEditchange);
		SetTimer(EventTimerEditchange, 500, NULL);
		return Default();
	}
	else
	{
		SearchText();
	}
}

BOOL CComboBoxExt::SearchText()
{
	TRACE("%s\r\n", __FUNCTION__);
	// TODO: Add your control notification handler code here

	::SendMessage(m_hWndToolTip, TTM_TRACKACTIVATE, (WPARAM)FALSE, (LPARAM)(LPTOOLINFO)&m_ToolInfo);

	if(MODE_STANDARD == m_nMode || CBS_SIMPLE == (3 & GetStyle()))
		return Default();

	SendMessage(CB_GETEDITSEL, (WPARAM)&m_dwStartSel, (LPARAM)&m_dwEndSel);

	GetWindowText(m_sTypedText);
	CString sEditText(m_sTypedText);

	if (BIG_LIST < m_PtrList.GetCount() && sEditText.GetLength() < 3) {
		ShowDropDown(FALSE);		
		return Default();
	}

	sEditText.Trim();
	sEditText.MakeLower();
	sEditText = removeAccented(sEditText.GetBuffer(0));	

 	if (!m_sTypedText.IsEmpty() && !m_sFirstTextNotFound.IsEmpty() && m_sTypedText.Find(m_sFirstTextNotFound) >= 0)
	{
		return Default();
	}	

	SetRedraw(FALSE);
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_WAIT));

	DWORD tickStart = GetTickCount();
	TRACE("%s - Start. Busca:%s Items:%d \r\n", __FUNCTION__, m_sTypedText.GetBuffer(0), GetCount());

	m_bEdit = TRUE;
	CString sTemp, sFirstOccurrence;
	POSITION pos = m_PtrList.GetHeadPosition();
	while(! m_sTypedText.IsEmpty() && pos)
	{
		CItemData* pData = m_PtrList.GetNext(pos);
		sTemp = pData->m_sItemCompared;		

		if(MODE_AUTOCOMPLETE == m_nMode && 0 == sTemp.Find(sEditText)) /*encontra no começo da string, para o autocomplete*/
			AddItem(pData);	
		else if (FindAllStringOf(sTemp, sEditText)) /*encontra em qualquer lugar da string*/		
			AddItem(pData);		
		else		
			DeleteItem(pData);		
	}

	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
	SetRedraw(TRUE);
	Invalidate();

	if(GetCount() < 1 || m_sTypedText.IsEmpty())
	{
		if (m_bTextColorNotFoundEnable) 
			m_bTextColorNotFound = TRUE;

		if (m_sFirstTextNotFound.IsEmpty() || m_sTypedText.Find(m_sFirstTextNotFound) == -1)
			m_sFirstTextNotFound = m_sTypedText;		
			
		if(GetDroppedState())
			ShowDropDown(FALSE);
		else
		{
			if (BIG_LIST > m_PtrList.GetCount())
			{
				pos = m_PtrList.GetHeadPosition();
				while (NULL != pos)
					AddItem(m_PtrList.GetNext(pos));
			}			
		}
	}
	else
	{
		if (m_bTextColorNotFoundEnable)
			m_bTextColorNotFound = FALSE;

		m_sFirstTextNotFound.Empty();
		ShowDropDown();
		FitDropDownToItems();
		if(MODE_AUTOCOMPLETE == m_nMode && GetCount() > 0)
			GetLBText(0, sFirstOccurrence);
	}

	if(MODE_AUTOCOMPLETE == m_nMode && m_bAutoComplete && ! sFirstOccurrence.IsEmpty())
	{
		m_bAutoSelection = TRUE;
		SetWindowText(sFirstOccurrence);
		PostMessage(CB_SETEDITSEL, 0, MAKELPARAM(m_dwEndSel, sFirstOccurrence.GetLength()));
	}
	else
	{
		m_bAutoSelection = FALSE;
		SetWindowText(m_sTypedText);
		SetEditSel(m_dwStartSel, m_dwEndSel);
	}

	m_bAutoComplete = TRUE;

	TRACE("%s - End. Busca:%s Items:%d Tempo:%ds \r\n", __FUNCTION__, m_sTypedText.GetBuffer(0), GetCount(), GetTickCount()-tickStart);

	return Default();
}

BOOL CComboBoxExt::OnCloseup() 
{
	TRACE("%s\r\n", __FUNCTION__);
	// TODO: Add your control notification handler code here

	::SendMessage(*m_ListBox.GetToolTipHwnd(), TTM_TRACKACTIVATE, (WPARAM)FALSE, (LPARAM)(LPTOOLINFO)m_ListBox.GetToolInfo());

	if (BIG_LIST > m_PtrList.GetCount())
	{
		POSITION pos = m_PtrList.GetHeadPosition();
		while(NULL != pos)
			AddItem(m_PtrList.GetNext(pos));
	}	

	if(m_bEdit && CBS_DROPDOWN == (3 & GetStyle()))
	{
		m_sCloseupText.Empty();
		GetWindowText(m_sCloseupText);
		if(! m_sCloseupText.IsEmpty())
			PostMessage(WMU_POSTCLOSEUP, (WPARAM)0, (LPARAM)(LPCTSTR)m_sCloseupText);
	}

	m_bEdit = FALSE;

	return Default();
}

LRESULT CComboBoxExt::OnPostCloseup(WPARAM wParam, LPARAM lParam)
{
	TRACE("%s\r\n", __FUNCTION__);
	CString sAutoCompletedText = (LPCTSTR)lParam;
	if(m_bAutoSelection || 0 != sAutoCompletedText.CompareNoCase(m_sTypedText))
		m_sTypedText = sAutoCompletedText;

	int nIndex = FindStringExact(-1, m_sTypedText);
	SetCurSel(nIndex);
	if(CB_ERR == nIndex)
		SetWindowText(m_sTypedText);

	if(! m_bAutoSelection)
	{
		if(0 == m_dwStartSel && 0 == m_dwEndSel && CB_ERR != FindStringExact(-1, m_sTypedText))
			PostMessage(CB_SETEDITSEL, (WPARAM)0, MAKELPARAM(m_sTypedText.GetLength(), m_sTypedText.GetLength()));
		else
			PostMessage(CB_SETEDITSEL, (WPARAM)0, MAKELPARAM(m_dwStartSel, m_dwEndSel));
	}

	return (LRESULT)1;
}

LRESULT CComboBoxExt::OnAddString(WPARAM wParam, LPARAM lParam)
{
	TRACE("%s\r\n", __FUNCTION__);
	int nIndex = (int)Default();

	POSITION pos = (POSITION)wParam;
	if(NULL == pos)
	{
		CItemData* pData = new CItemData(CB_ERR, (LPCTSTR)lParam);
		m_PtrList.AddTail(pData);
		SetItemDataPtr(nIndex, pData);
	}

	return nIndex;
}

LRESULT CComboBoxExt::OnInsertString(WPARAM wParam, LPARAM lParam)
{
	TRACE("%s\r\n", __FUNCTION__);
	int nIndex = (int)Default();

	POSITION pos = (POSITION)wParam;
	if(NULL == pos)
	{
		CItemData* pData = new CItemData(CB_ERR, (LPCTSTR)lParam);
		m_PtrList.AddTail(pData);
		SetItemDataPtr(nIndex, pData);
	}

	return nIndex;
}

LRESULT CComboBoxExt::OnDeleteString(WPARAM wParam, LPARAM lParam)
{
	TRACE("%s\r\n", __FUNCTION__);
	POSITION pos = (POSITION)lParam;
	if(NULL == pos)
	{
		CItemData* pData = (CItemData*)GetItemDataPtr((int)wParam);
		if(NULL != pData)
		{
			POSITION pos = m_PtrList.Find(pData);
			if(NULL != pos)
			{
				delete pData;
				m_PtrList.RemoveAt(pos);
			}
		}
	}

	return Default();
}
// Add item in dropdown list
int CComboBoxExt::AddItem(CItemData* pData)
{
	//TRACE("%s\r\n", __FUNCTION__);
	if(NULL == pData || TRUE == pData->m_bState)
		return CB_ERR;

	TRACE("%s ADD\r\n", __FUNCTION__);

	int nIndex = SendMessage(CB_ADDSTRING, (WPARAM)m_PtrList.Find(pData), (LPARAM)(LPCTSTR)pData->m_sItem);
	if(CB_ERR == nIndex || CB_ERRSPACE == nIndex)
		return nIndex;

	pData->m_bState = TRUE;
	SetItemData(nIndex, pData->m_dwItemData);
	SetItemDataPtr(nIndex, pData);

	return nIndex;
}
// Delete item from dropdown list
int CComboBoxExt::DeleteItem(CItemData* pData)
{
	//TRACE("%s\r\n", __FUNCTION__);
	int nIndex = CB_ERR;

	if(NULL == pData || FALSE == pData->m_bState)
		return nIndex;

	TRACE("%s Delete\r\n", __FUNCTION__);

	pData->m_bState = FALSE;
	const int nCount = GetCount();
	for(int i = 0;i < nCount;++i)
	{
		if(pData == (CItemData*)GetItemDataPtr(i))
		{
			nIndex = SendMessage(CB_DELETESTRING, (WPARAM)i, (LPARAM)m_PtrList.Find(pData));
			break;
		}
	}

	return nIndex;
}

int CComboBoxExt::SetItemData(int nIndex, DWORD dwItemData)
{
	TRACE("%s\r\n", __FUNCTION__);
	if(CB_ERR == nIndex)
		return nIndex;

	CItemData* pData = (CItemData*)GetItemDataPtr(nIndex);
	if(NULL != pData)
	{
		pData->m_dwItemData = dwItemData;
		return 0;
	}

	return CB_ERR;
}

DWORD CComboBoxExt::GetItemData(int nIndex) const
{
	TRACE("%s\r\n", __FUNCTION__);
	if(CB_ERR == nIndex)
		return nIndex;

	DWORD dwItemData = CB_ERR;

	CItemData* pData = (CItemData*)GetItemDataPtr(nIndex);
	if(NULL != pData)
		dwItemData = pData->m_dwItemData;

	return dwItemData;
}

void CComboBoxExt::SetAlertColorBkg(const COLORREF crColor)
{
	TRACE("%s\r\n", __FUNCTION__);
	m_crAlertBkg = crColor;
	m_BrushAlert.DeleteObject();
	m_BrushAlert.CreateSolidBrush(m_crAlertBkg);
}

void CComboBoxExt::OnMouseMove(UINT nFlags, CPoint point) 
{
	//TRACE("%s\r\n", __FUNCTION__);
	// TODO: Add your message handler code here and/or call default

	CComboBox::OnMouseMove(nFlags, point);

	if(! m_bShowTooltip)
		return;

	CRect rectClient;
	GetClientRect(&rectClient);
	const int nComboButtonWidth = GetSystemMetrics(SM_CXHTHUMB) + 2;
	rectClient.right = rectClient.right - nComboButtonWidth;

	if(rectClient.PtInRect(point) && ! m_bEdit && ! GetDroppedState())
	{
		const int nIndex = GetCurSel();
		ClientToScreen(&rectClient);

		CString sText;
		if(! m_bTooltipOnInfo)
			GetWindowText(sText);
		else
		{
			if(CB_ERR != nIndex)
				GetLBInfo(nIndex, sText);
		}
		m_ToolInfo.lpszText = (LPTSTR)(LPCTSTR)sText;

		if(! m_bTooltipOnInfo)
		{
			HDC hDC = ::GetDC(m_hWnd);
			ASSERT(hDC);
			CFont* pFont = GetFont();
			HFONT hOldFont = (HFONT)::SelectObject(hDC, (HFONT)*pFont);
			SIZE size;
			::GetTextExtentPoint32(hDC, sText, sText.GetLength(), &size);
			::SelectObject(hDC, hOldFont);
			::ReleaseDC(m_hWnd, hDC);

			if(! m_bToolActive && size.cx > rectClient.Width() - 6)
			{
				rectClient.left += 1;
				rectClient.top += 3;
				::SendMessage(m_hWndToolTip, TTM_UPDATETIPTEXT, (WPARAM)0, (LPARAM)&m_ToolInfo);
				::SendMessage(m_hWndToolTip, TTM_TRACKPOSITION, (WPARAM)0, (LPARAM)MAKELONG(rectClient.left, m_bEditTooltipOverItemPos ? rectClient.top - nComboButtonWidth - 1 : rectClient.top));
				::SendMessage(m_hWndToolTip, TTM_TRACKACTIVATE, (WPARAM)TRUE, (LPARAM)(LPTOOLINFO)&m_ToolInfo);
				m_bToolActive = TRUE;
				SetTimer(EventTimerToolTip, 80, NULL);
			}
			else	// text fits inside client rect
			{
				SetTimer(EventTimerToolTip, 80, NULL);
			}
		}
		else	// tooltip text is retrieved from additional info
		{
			if(! m_bToolActive && CB_ERR != nIndex && TRUE == GetLBShowItemTooltipState(nIndex) && ! sText.IsEmpty())
			{
				::SendMessage(m_hWndToolTip, TTM_UPDATETIPTEXT, (WPARAM)0, (LPARAM)&m_ToolInfo);
				::SendMessage(m_hWndToolTip, TTM_TRACKPOSITION, (WPARAM)0, (LPARAM)MAKELONG(m_bShowEditTooltipOverItem ? rectClient.left + 1 : rectClient.right + nComboButtonWidth - 1, m_bEditTooltipOverItemPos ? rectClient.top - nComboButtonWidth - 1 : rectClient.top + 3));
				::SendMessage(m_hWndToolTip, TTM_TRACKACTIVATE, (WPARAM)TRUE, (LPARAM)(LPTOOLINFO)&m_ToolInfo);
				m_bToolActive = TRUE;
				SetTimer(EventTimerToolTip, 80, NULL);
			}
			else
			{
				SetTimer(EventTimerToolTip, 80, NULL);
			}
		}
	}
	else	// not inside client rect
	{
		::SendMessage(m_hWndToolTip, TTM_TRACKACTIVATE, (WPARAM)FALSE, (LPARAM)(LPTOOLINFO)&m_ToolInfo);
		m_bToolActive = FALSE;
		SetTimer(EventTimerToolTip, 80, NULL);
	}
}

void CComboBoxExt::OnTimer(UINT nIDEvent) 
{
	//TRACE("%s\r\n", __FUNCTION__);
	// TODO: Add your message handler code here and/or call default

	CComboBox::OnTimer(nIDEvent);

	// ToolTipEvent Timer
	if (nIDEvent == EventTimerToolTip)
	{	
		CPoint point;
		::GetCursorPos(&point);
		ScreenToClient(&point);

		CRect rectClient;
		GetClientRect(&rectClient);
		int nComboButtonWidth = GetSystemMetrics(SM_CXHTHUMB) + 2;
		rectClient.right = rectClient.right - nComboButtonWidth;

		if(! rectClient.PtInRect(point))
		{
			KillTimer(nIDEvent);
			::SendMessage(m_hWndToolTip, TTM_TRACKACTIVATE, (WPARAM)FALSE, (LPARAM)(LPTOOLINFO)&m_ToolInfo);
			m_bToolActive = FALSE;
		}
	}
	// textChangeEvent Timer
	else if (nIDEvent == EventTimerEditchange)
	{
		KillTimer(nIDEvent);
		SearchText();		
	}
}

int CComboBoxExt::AddStringWithInfo(LPCTSTR lpszString, LPCTSTR lpszInfo, BOOL bShowItemTooltip/* = TRUE*/)
{
	TRACE("%s\r\n", __FUNCTION__);
	int nIndex = (int)SendMessage(CB_ADDSTRING, (WPARAM)0, (LPARAM)lpszString);
	SetLBInfo(nIndex, lpszInfo, bShowItemTooltip);

	return nIndex;
}

int CComboBoxExt::InsertStringWithInfo(int nIndex, LPCTSTR lpszString, LPCTSTR lpszInfo, BOOL bShowItemTooltip/* = TRUE*/)
{
	SendMessage(CB_INSERTSTRING, (WPARAM)nIndex, (LPARAM)lpszString);
	SetLBInfo(nIndex, lpszInfo, bShowItemTooltip);

	return nIndex;
}

void CComboBoxExt::SetLBInfo(int nIndex, LPCTSTR lpszInfo, BOOL bShowItemTooltip/* = TRUE*/)
{
	ASSERT(::IsWindow(m_hWnd));
	ASSERT(nIndex >= 0 && nIndex < GetCount());

	CItemData* pData = (CItemData*)GetItemDataPtr(nIndex);
	if(NULL != pData)
	{
		pData->m_sInfo = lpszInfo;
		pData->m_bShowItemTooltip = bShowItemTooltip;
	}
}

void CComboBoxExt::GetLBInfo(int nIndex, CString& rInfo) const
{
	ASSERT(::IsWindow(m_hWnd));
	ASSERT(nIndex >= 0 && nIndex < GetCount());

	CItemData* pData = (CItemData*)GetItemDataPtr(nIndex);
	if(NULL != pData)
		rInfo = pData->m_sInfo;
}
void CComboBoxExt::GetLBInfo(int nIndex, LPCTSTR lpszInfo) const
{
	GetLBInfo(nIndex, lpszInfo);
}

void CComboBoxExt::SetLBShowItemTooltip(int nIndex, const BOOL bShow/* = TRUE*/)
{
	ASSERT(::IsWindow(m_hWnd));
	ASSERT(nIndex >= 0 && nIndex < GetCount());

	CItemData* pData = (CItemData*)GetItemDataPtr(nIndex);
	if(NULL != pData)
		pData->m_bShowItemTooltip = bShow;
}

BOOL CComboBoxExt::GetLBShowItemTooltipState(int nIndex) const
{
	ASSERT(::IsWindow(m_hWnd));
	ASSERT(nIndex >= 0 && nIndex < GetCount());

	CItemData* pData = (CItemData*)GetItemDataPtr(nIndex);
	if(NULL != pData)
		return pData->m_bShowItemTooltip;

	return FALSE;
}
// find an list item by info string
int CComboBoxExt::FindInfo(int nStartAfter, LPCTSTR lpszString) const
{
	TRACE("%s\r\n", __FUNCTION__);
	int nIndex = CB_ERR;
	CString sString(lpszString), sItem;
	sString.MakeLower();
	for(int i = nStartAfter + 1;i < GetCount();++i)
	{
		GetLBInfo(i, sItem);
		sItem.MakeLower();
		if(sItem.Find(sString) >= 0)
		{
			nIndex = i;
			break;
		}
	}

	return nIndex;
}
// find an list item by info string exact
int CComboBoxExt::FindInfoExact(int nIndexStart, LPCTSTR lpszFind) const
{
	TRACE("%s\r\n", __FUNCTION__);
	CString sItem;
	int nIndex = CB_ERR;
	for(int i = nIndexStart + 1;i < GetCount();++i)
	{
		GetLBInfo(i, sItem);
		if(0 == sItem.CompareNoCase(lpszFind))
		{
			nIndex = i;
			break;
		}
	}

	return nIndex;
}
// select an list item by info string
int CComboBoxExt::SelectInfo(int nStartAfter, LPCTSTR lpszString)
{
	TRACE("%s\r\n", __FUNCTION__);
	int nIndex = CB_ERR;
	CString sString(lpszString), sItem;
	sString.MakeLower();
	for(int i = nStartAfter + 1;i < GetCount();++i)
	{
		GetLBInfo(i, sItem);
		sItem.MakeLower();
		if(sItem.Find(sString) >= 0)
		{
			nIndex = i;
			SetCurSel(nIndex);
			break;
		}
	}

	return nIndex;
}

char* CComboBoxExt::removeAccented(char* str) {
	char *p = str;
	while ((*p) != 0) {
		const char*
			//   "ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ"
			tr = "AAAAAAECEEEEIIIIDNOOOOOx0UUUUYPsaaaaaaeceeeeiiiiOnooooo/0uuuuypy";
		unsigned char ch = (*p);
		if (ch >= 192) {
			(*p) = tr[ch - 192];
		}
		++p;
	}
	return str;
}

BOOL CComboBoxExt::FindAllStringOf(const CString & source, const CString & find, const CString & tokens /*= " "*/, const bool &searchInSequence /*= false*/)
{	
	int idxFind = 0, idxSource = 0;
	for (CString word = find.Tokenize(tokens, idxFind); idxFind >= 0; word = find.Tokenize(tokens, idxFind)) {
		
		idxSource = source.Find(word, idxSource);

		if (!searchInSequence && idxSource > 0)
			idxSource = 0;

		if (idxSource == -1)
			return FALSE;
	}		
	return TRUE;
}
