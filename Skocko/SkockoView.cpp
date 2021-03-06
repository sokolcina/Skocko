
// SkockoView.cpp : implementation of the CSkockoView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Skocko.h"
#endif

#include "SkockoDoc.h"
#include "SkockoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSkockoView

#define B1 RGB(150,20,0)
#define B2 RGB(2,220,0)
#define B3 RGB(0,50,220)
#define B4 RGB(100,30,200)
#define B5 RGB(140,180,40)
#define B6 RGB(135, 87, 124)
#define Postoji RGB(252, 248, 15)
#define Pogodjen RGB(240,0,0)
#define Bela RGB(255,255,255)

IMPLEMENT_DYNCREATE(CSkockoView, CView)

BEGIN_MESSAGE_MAP(CSkockoView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSkockoView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_BN_CLICKED(1,okButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CSkockoView construction/destruction

CSkockoView::CSkockoView()
{
	// TODO: add construction code here
	fromLeft = 30;
	fromTop = 30;
	fromRight = 100;
	fromBtm = 20;
	polje = 0;
}

CSkockoView::~CSkockoView()
{
}

BOOL CSkockoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

void CSkockoView::MyDraw(CDC* pDC, CSkockoDoc* pDoc, CPen *pen, int i, int j)
{
	// here we have drawing squares and circles for every try
	CRect r1(fromLeft + j * 5 + j * polje, fromTop + i * 10 + i * polje,
		fromLeft + j * 5 + (j + 1) * polje, fromTop + i * 10 + (i + 1) * polje);

	RECT r2;
	r2.left = fromLeft + j * 5 + j * polje + 4 * polje + 20;
	r2.top = fromTop + i * 10 + i * polje;
	r2.right = fromLeft + j * 5 + (j + 1) * polje + 4 * polje + 20;
	r2.bottom = fromTop + i * 10 + (i + 1) * polje;
	CBrush b1(B1), b2(B2), b3(B3), b4(B4), b5(B5), b6(B6), bela(Bela);
	CBrush postoji(Postoji), pogodjen(Pogodjen);
	switch (pDoc->pokusaji[i][j]) {
	case 1:
		pDC->SelectObject(&b1);
		pDC->FillRect(&r1, &b1);
		break;
	case 2:
		pDC->SelectObject(&b2);
		pDC->FillRect(&r1, &b2);
		break;
	case 3:
		pDC->SelectObject(&b3);
		pDC->FillRect(&r1, &b3);
		break;
	case 4:
		pDC->SelectObject(&b4);
		pDC->FillRect(&r1, &b4);
		break;
	case 5:
		pDC->SelectObject(&b5);
		pDC->FillRect(&r1, &b5);
		break;
	case 6:
		pDC->SelectObject(&b6);
		pDC->FillRect(&r1, &b6);
		break;
	}

	switch (pDoc->pogodjeno[i][j])
	{
	case 0:
		pDC->SelectObject(&bela);
		pDC->Ellipse(&r2);
		break;
	case 1:
		pDC->SelectObject(&postoji);
		pDC->Ellipse(&r2);
		break;
	case 2:
		pDC->SelectObject(&pogodjen);
		pDC->Ellipse(&r2);
	}
}

// CSkockoView drawing

void CSkockoView::OnDraw(CDC* pDC)
{
	CSkockoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;


	CRect rect;
	GetClientRect(&rect);

	// calculate for drawing
	int min = rect.Width();
	min = (min - fromLeft - fromRight - 35) / 8;
	polje = rect.Height();
	polje = (polje - fromBtm - fromTop - 70) / 8;
	// calculate field for squares in pixels
	if (min < polje) polje = min; 

	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	pDC->SelectObject(&pen);

	int brPokusaja = GetDocument()->brojPokusaja;

	for (int i = 0; i <=brPokusaja && i<8; i++)
		for (int j = 0; j < 4; j++)
			MyDraw(pDC, pDoc, &pen, i, j);
		
	
	if(brPokusaja < 8)
	{ 
		// move button for next try
		CRect Rdugme = CRect(fromLeft + 8 * polje + 80,
		fromTop + brPokusaja * 10 + brPokusaja * polje,
		fromLeft + 8 * polje + 180,
		fromTop + brPokusaja * 10 + (brPokusaja + 1)* polje);
		ok.MoveWindow(Rdugme);
	}
}


// CSkockoView printing


void CSkockoView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CSkockoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSkockoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSkockoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CSkockoView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSkockoView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

void CSkockoView::okButton()
{
	CString st;
		if (GetDocument()->proveri())
			{
				// the user has solved the combination
				st.Format(_T("Uspesno ste resili kombinaciju i imate %d poena. "), GetDocument()->brojPoena);
				Invalidate();
				AfxMessageBox(st);
				GetDocument()->restart();
				Invalidate();	
			}
		else
			{
				// the user has more tries
				if (GetDocument()->brojPokusaja != 8)
					Invalidate();
				else
				{
					// the user did not solve the combination
					AfxMessageBox(L"Niste uspeli da resite kombinaciju probajte ponovo.");
					GetDocument()->restart();
					Invalidate();
				}
			}
			
		
		
	

}




// CSkockoView diagnostics

#ifdef _DEBUG
void CSkockoView::AssertValid() const
{
	CView::AssertValid();
}

void CSkockoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSkockoDoc* CSkockoView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSkockoDoc)));
	return (CSkockoDoc*)m_pDocument;
}
#endif //_DEBUG


// CSkockoView message handlers


void CSkockoView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	int x = point.x;
	int y = point.y;

	if(x-fromLeft < 0 || y-fromTop < 0) return;

	// calculate place between squares using logic
	int j = (x - fromLeft) / (polje + 5);
	int i = (y - fromTop) / (polje + 10);
	

	int pj = x - fromLeft - (j*polje) - (j * 5);
	int pi = y - fromTop - (i* polje) - (i * 10);

	if (pi == 0 || pi > polje || pj == 0 || pj > polje)
		return;
	// changing colors of squares
	if (j < 4 && i == GetDocument()->brojPokusaja) {
		if (GetDocument()->trenutnaKomb[j] < 6)
			GetDocument()->trenutnaKomb[j]++;
		else GetDocument()->trenutnaKomb[j] = 1;
		GetDocument()->updatePokusaji();
		Invalidate();
	}
	
	CView::OnLButtonDown(nFlags, point);
}


int CSkockoView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect Rdugme = CRect(0, 0, 0, 0);
	// create button
	ok.Create(L"OK", WS_CHILD | WS_VISIBLE, Rdugme, this, 1); 
	
	return 0;
}


