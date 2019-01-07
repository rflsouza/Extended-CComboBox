// TestCombo.h : main header file for the TESTCOMBO application
//

#if !defined(AFX_TESTCOMBO_H__939B8865_3068_11E0_8FFC_0050BF29759A__INCLUDED_)
#define AFX_TESTCOMBO_H__939B8865_3068_11E0_8FFC_0050BF29759A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestComboApp:
// See TestCombo.cpp for the implementation of this class
//

class CTestComboApp : public CWinApp
{
public:
	CTestComboApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestComboApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CTestComboApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTCOMBO_H__939B8865_3068_11E0_8FFC_0050BF29759A__INCLUDED_)
