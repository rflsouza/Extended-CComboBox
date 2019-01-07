// TestComboView.h : interface of the CTestComboView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTCOMBOVIEW_H__939B886D_3068_11E0_8FFC_0050BF29759A__INCLUDED_)
#define AFX_TESTCOMBOVIEW_H__939B886D_3068_11E0_8FFC_0050BF29759A__INCLUDED_

#include "ComboBoxExt.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTestComboView : public CFormView
{
protected: // create from serialization only
	CTestComboView();
	DECLARE_DYNCREATE(CTestComboView)

public:
	//{{AFX_DATA(CTestComboView)
	enum { IDD = IDD_TESTCOMBO_FORM };
	CComboBoxExt	m_Combo4;
	CComboBoxExt	m_Combo3;
	CComboBoxExt m_Combo2;
	CComboBoxExt m_Combo1;
	CComboBoxExt m_Combo5;
	//}}AFX_DATA

// Attributes
public:
	CTestComboDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestComboView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTestComboView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CToolTipCtrl m_ToolTips;
	BOOL m_bAlertText, m_bAlertBkg;

// Generated message map functions
protected:
	//{{AFX_MSG(CTestComboView)
	afx_msg void OnKillfocusCombo1();
	afx_msg void OnButtonText();
	afx_msg void OnButtonBkg();
	afx_msg void OnRadioStandard();
	afx_msg void OnRadioAc();
	afx_msg void OnRadioDd();
	afx_msg void OnSelendokCombo1();
	afx_msg void OnRadioOveredit();
	afx_msg void OnRadioAboveedit();
	afx_msg void OnCloseupCombo1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TestComboView.cpp
inline CTestComboDoc* CTestComboView::GetDocument()
   { return (CTestComboDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTCOMBOVIEW_H__939B886D_3068_11E0_8FFC_0050BF29759A__INCLUDED_)
