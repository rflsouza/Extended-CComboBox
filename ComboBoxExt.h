#if !defined(AFX_COMBOBOXEXT_H__314E0909_0E3F_4D06_A5F9_4AB4F098D2CD__INCLUDED_)
#define AFX_COMBOBOXEXT_H__314E0909_0E3F_4D06_A5F9_4AB4F098D2CD__INCLUDED_
// reference: https://www.codeproject.com/Articles/187753/Extended-CComboBox
// https://www.codeproject.com/articles/1131087/list-combobox-control outro exemplo.


#include <afxtempl.h>
#include "ComboBoxExtList.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ComboBoxExt.h : header file

#define WMU_POSTCLOSEUP							(WM_USER + 64)
/////////////////////////////////////////////////////////////////////////////
// CComboBoxExt window

class CComboBoxExt : public CComboBox
{
// Construction
public:
	CComboBoxExt();

// Attributes
public:
	enum
	{
		MODE_STANDARD			= 0,
		MODE_DROPDOWN			= 1,
		MODE_AUTOCOMPLETE		= 2
	};
	
	static const int BIG_LIST = 100;

	enum enumEventTimer
	{
		EventTimerToolTip = 1,
		EventTimerEditchange = 2
	};

// Operations
public:
	BOOL IsAlertBkg() const {return m_bAlertBkg;}
	BOOL IsAlertText() const {return m_bAlertText;}
	BOOL IsTextColorNotFoundEnable() const { return m_bTextColorNotFoundEnable; }
	BOOL IsAdjustedDroppedWidth() const {return m_bAdjustDroppedWidth;}
	int GetMode() const {return m_nMode;}
	void SetMode(int nMode = CComboBoxExt::MODE_STANDARD){m_nMode = nMode;}
	void AdjustDroppedWidth(const BOOL bAdjustDroppedWidth = TRUE){m_bAdjustDroppedWidth = bAdjustDroppedWidth;}
	COLORREF GetAlertColorBkg() const {return m_crAlertBkg;}
	void SetAlertColorBkg(const COLORREF crColor);
	COLORREF GetAlertColorText() const {return m_crAlertText;}
	void SetAlertColorText(const COLORREF crColor){m_crAlertText = crColor;}
	COLORREF GetTextColorNotFound() const { return m_crTextColorNotFound; }
	void SetTextColorNotFound(const COLORREF crColor) { m_crTextColorNotFound = crColor; }	

	virtual int AddStringWithInfo(LPCTSTR lpszString, LPCTSTR lpszInfo, BOOL bShowItemTooltip = TRUE);
	virtual int InsertStringWithInfo(int nIndex, LPCTSTR lpszString, LPCTSTR lpszInfo, BOOL bShowItemTooltip = TRUE);
	virtual void SetLBInfo(int nIndex, LPCTSTR lpszInfo, BOOL bShowItemTooltip = TRUE);
	virtual void GetLBInfo(int nIndex, LPCTSTR lpszInfo) const;
	virtual void GetLBInfo(int nIndex, CString& rInfo) const;
	virtual void SetLBShowItemTooltip(int nIndex, const BOOL bShow = TRUE);
	virtual BOOL GetLBShowItemTooltipState(int nIndex) const;
	virtual int FindInfo(int nStartAfter, LPCTSTR lpszString) const;
	virtual int FindInfoExact(int nIndexStart, LPCTSTR lpszFind) const;
	virtual int SelectInfo(int nStartAfter, LPCTSTR lpszString);

	/* remove accents
	Convert ISO 8859-1 (ISO-Latin-1) to US-ASCII (20127)
	https://en.wikipedia.org/wiki/ISO/IEC_8859-1
	http://stackoverflow.com/questions/14094621/
	*/
	static char* removeAccented(char* str);

	/* Find ALL strings in source in sequence.

		tokens = set tokens to split find string ' '.
		searchInSequence = search all words in sequence. Default is false
	*/
	static BOOL FindAllStringOf(const CString &source, const CString &find, const CString &tokens = " ", const bool &searchInSequence = false);
	

	void AlertBkg(const BOOL bAlert = TRUE, BOOL bRedraw = FALSE)
	{
		m_bAlertBkg = bAlert;
		if(bRedraw)
			Invalidate();
	}
	void AlertText(const BOOL bAlert = TRUE, BOOL bRedraw = FALSE)
	{
		m_bAlertText = bAlert;
		if(bRedraw)
			Invalidate();
	}

	//  Enable Change Text Color in Not Found search.
	void SetTextColorNotFoundEnable(const BOOL bAlert = TRUE)
	{
		m_bTextColorNotFoundEnable = bAlert;	
	}

	void SetEditTooltip(const BOOL bShowTooltip, BOOL bTooltipOnInfo = FALSE, BOOL bShowEditTooltipOverItem = FALSE)
	{
		m_bShowTooltip = bShowTooltip;
		m_bTooltipOnInfo = bTooltipOnInfo;
		m_bShowEditTooltipOverItem = bShowEditTooltipOverItem;
	}
	void GetEditTooltip(BOOL& bShowTooltip, BOOL& bTooltipOnInfo, BOOL& bShowEditTooltipOverItem)
	{
		bShowTooltip = m_bShowTooltip;
		bTooltipOnInfo = m_bTooltipOnInfo;
		bShowEditTooltipOverItem = m_bShowEditTooltipOverItem;
	}
	void SetListTooltip(const BOOL bShowTooltip, BOOL bTooltipOnInfo = FALSE, BOOL bShowListTooltipOverItem = FALSE, int nMaxTipWidth = SHRT_MAX)
	{
		m_ListBox.m_bShowTooltip = bShowTooltip;
		m_ListBox.m_bTooltipOnInfo = bTooltipOnInfo;
		m_ListBox.m_bShowListTooltipOverItem = bShowListTooltipOverItem;
		m_ListBox.SetMaxTipWidth(nMaxTipWidth);
	}
	void GetListTooltip(BOOL& bShowTooltip, BOOL& bTooltipOnInfo, BOOL& bShowListTooltipOverItem)
	{
		bShowTooltip = m_ListBox.m_bShowTooltip;
		bTooltipOnInfo = m_ListBox.m_bTooltipOnInfo;
		bShowListTooltipOverItem = m_ListBox.m_bShowListTooltipOverItem;
	}
	void SetEditTooltipOverItemPosition(const BOOL bAbove = TRUE)
	{
		m_bEditTooltipOverItemPos = bAbove;
	}
	BOOL GetEditTooltipOverItemPosition() const
	{
		return m_bEditTooltipOverItemPos;
	}

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComboBoxExt)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CComboBoxExt();
	virtual DWORD GetItemData(int nIndex) const;
	virtual int SetItemData(int nIndex, DWORD dwItemData);
	CComboBoxExtList* GetListBox(){return &m_ListBox;}

protected:
	BOOL m_bEdit;
	BOOL m_bAutoSelection;
	BOOL m_bToolActive;
	HWND m_hWndToolTip;
	TOOLINFO m_ToolInfo;
	CString m_sTypedText;
	CString m_sCloseupText;	
	/* First text that was not found in the search.
	   Field is cleared when the search is find result.
	   Used to better performance. when there are many items in the list.
	*/
	CString m_sFirstTextNotFound;
	//List with the results.
	CComboBoxExtList m_ListBox;
	DWORD m_dwStartSel, m_dwEndSel;

protected:
	int m_nMode;
	BOOL m_bAlertBkg;
	BOOL m_bAlertText;
	BOOL m_bTextColorNotFound; // use in OnCtlColor	
	// Enable Change Text Color in Not Found search.
	BOOL m_bTextColorNotFoundEnable;
	BOOL m_bAdjustDroppedWidth;
	BOOL m_bAutoComplete;
	BOOL m_bShowTooltip;
	BOOL m_bTooltipOnInfo;
	BOOL m_bShowEditTooltipOverItem;	// this has meaning only when m_bTooltipOnInfo == TRUE
	BOOL m_bEditTooltipOverItemPos;		// this has meaning only when m_bShowEditTooltipOverItem == TRUE
	CBrush m_BrushAlert;
	COLORREF m_crAlertBkg;
	COLORREF m_crAlertText;
	COLORREF m_crTextColorNotFound;

	class CItemData : public CObject
	{
    // Attributes
	public:
		DWORD m_dwItemData;
		CString m_sItem;
		CString m_sItemCompared;
		CString m_sInfo;
		BOOL m_bState;
		BOOL m_bShowItemTooltip;

    // Implementation
	public:
		CItemData();
		CItemData(DWORD dwItemData, LPCTSTR lpszString);
		CItemData(DWORD dwItemData, LPCTSTR lpszString, BOOL bState);
		CItemData(DWORD dwItemData, LPCTSTR lpszString, LPCTSTR lpszInfo, BOOL bState);
		CItemData(DWORD dwItemData, LPCTSTR lpszString, LPCTSTR lpszInfo, BOOL bState, BOOL bShowItemTooltip);
		virtual ~CItemData();
	};

	CTypedPtrList<CPtrList, CItemData*> m_PtrList;

protected:
	virtual void FitDropDownToItems();
	virtual int AddItem(CItemData* pData);
	virtual int DeleteItem(CItemData* pData);

// Generated message map functions
protected:
	//{{AFX_MSG(CComboBoxExt)
	afx_msg void OnDestroy();
	afx_msg BOOL OnCloseup();
	afx_msg BOOL OnDropdown();
	afx_msg BOOL OnSelendok();
	afx_msg BOOL OnSelchange();
	afx_msg BOOL OnEditchange();
	BOOL SearchText();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	afx_msg LRESULT OnAddString(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnInsertString(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDeleteString(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnResetContent(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnPostCloseup(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMBOBOXEXT_H__314E0909_0E3F_4D06_A5F9_4AB4F098D2CD__INCLUDED_)
