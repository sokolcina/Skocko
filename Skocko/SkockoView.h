
// SkockoView.h : interface of the CSkockoView class
//

#pragma once


class CSkockoView : public CView
{
protected: // create from serialization only
	CSkockoView();
	DECLARE_DYNCREATE(CSkockoView)

// Attributes
public:
	CSkockoDoc* GetDocument() const;
	int fromLeft, fromTop, fromRight, polje, fromBtm; // pixels
	CButton ok;
// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	void MyDraw(CDC* pDC, CSkockoDoc* pDoc, CPen* pen, int i, int j);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CSkockoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void okButton();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#ifndef _DEBUG  // debug version in SkockoView.cpp
inline CSkockoDoc* CSkockoView::GetDocument() const
   { return reinterpret_cast<CSkockoDoc*>(m_pDocument); }
#endif

