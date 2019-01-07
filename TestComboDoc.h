// TestComboDoc.h : interface of the CTestComboDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTCOMBODOC_H__939B886B_3068_11E0_8FFC_0050BF29759A__INCLUDED_)
#define AFX_TESTCOMBODOC_H__939B886B_3068_11E0_8FFC_0050BF29759A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTestComboDoc : public CDocument
{
protected: // create from serialization only
	CTestComboDoc();
	DECLARE_DYNCREATE(CTestComboDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestComboDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTestComboDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTestComboDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTCOMBODOC_H__939B886B_3068_11E0_8FFC_0050BF29759A__INCLUDED_)
