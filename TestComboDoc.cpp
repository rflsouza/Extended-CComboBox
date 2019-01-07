// TestComboDoc.cpp : implementation of the CTestComboDoc class
//

#include "stdafx.h"
#include "TestCombo.h"

#include "TestComboDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestComboDoc

IMPLEMENT_DYNCREATE(CTestComboDoc, CDocument)

BEGIN_MESSAGE_MAP(CTestComboDoc, CDocument)
	//{{AFX_MSG_MAP(CTestComboDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestComboDoc construction/destruction

CTestComboDoc::CTestComboDoc()
{
	// TODO: add one-time construction code here

}

CTestComboDoc::~CTestComboDoc()
{
}

BOOL CTestComboDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTestComboDoc serialization

void CTestComboDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTestComboDoc diagnostics

#ifdef _DEBUG
void CTestComboDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTestComboDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestComboDoc commands
