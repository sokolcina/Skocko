
/* 
 Created by Stefan Sokolovic 2017
*/

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Skocko.h"
#endif

#include "SkockoDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSkockoDoc

IMPLEMENT_DYNCREATE(CSkockoDoc, CDocument)

BEGIN_MESSAGE_MAP(CSkockoDoc, CDocument)
END_MESSAGE_MAP()


// CSkockoDoc construction/destruction

CSkockoDoc::CSkockoDoc()
{
	// TODO: add one-time construction code here
	restart();
}

CSkockoDoc::~CSkockoDoc()
{
}

void CSkockoDoc::izbaciKombinaciju() // generate combination
{
	
	srand(time(NULL));
	for (int i = 0; i < 4; i++)
	{
		rand();
		int broj = rand() % 6 + 1;
		kombinacija.push_back(broj);
	}
}

void CSkockoDoc::restart()
{
	brojPokusaja = 0; // number of tries
	brojPoena = 30; // number of points
	trenutnaKomb.resize(4); // temporary combination
	
	// definition and initialization
	pokusaji.resize(8); // tries

	for (int i = 0; i < 8; i++)
		pokusaji[i].resize(4);

	pogodjeno.resize(8); // 

	for (int i = 0; i < 8; i++)
		pogodjeno[i].resize(4);

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 4; j++)
		{
			pokusaji[i][j] = 1;
			pogodjeno[i][j] = 0;
		}

	for (int i = 0; i < 4; i++)
		trenutnaKomb[i] = 1;

	izbaciKombinaciju(); 
}

void CSkockoDoc::updatePokusaji() // update tries
{
	for (int i = 0; i < 4; i++)
		pokusaji[brojPokusaja][i] = trenutnaKomb[i];
}

bool CSkockoDoc::proveri() // test user combination
{

	int brC = 0;
	for (int i = 0; i < 4; i++) {
		if (trenutnaKomb[i] == kombinacija[i]) // calculate red, which means right color on right place
			brC++;
	}

	bool pom[4] = { false, false, false, false }; // array for help logic with place in right combination
	int brZ = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (trenutnaKomb[i] == kombinacija[j] && pom[j] == false) { // calculate yellow, which means right color but not right place
				pom[j] = true;
				brZ++;
				break;
			}
		}
	}
	
	brZ -= brC;
	
	int indeks = 0;
	for (int i = 0; i < brC; i++) 
		pogodjeno[brojPokusaja][indeks++] = 2; // for red

	for (int i = 0; i < brZ; i++)
		pogodjeno[brojPokusaja][indeks++] = 1; // for yellow
	

	if (brC == 4) {
		if (brojPokusaja >= 6) // change points
			brojPoena = 20;
		return true;
	}

	for (int i = 0; i < 4; i++)
		 trenutnaKomb[i] = 1; // reset colors (symbols) on start color

	brojPokusaja++; // increment number of tries

	return false;
}

BOOL CSkockoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CSkockoDoc serialization

void CSkockoDoc::Serialize(CArchive& ar)
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

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CSkockoDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CSkockoDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CSkockoDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CSkockoDoc diagnostics

#ifdef _DEBUG
void CSkockoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSkockoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSkockoDoc commands
