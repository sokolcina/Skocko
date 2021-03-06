
// SkockoDoc.h : interface of the CSkockoDoc class
//
#include <vector>

using namespace std;

#pragma once


class CSkockoDoc : public CDocument
{
protected: // create from serialization only
	CSkockoDoc();
	DECLARE_DYNCREATE(CSkockoDoc)

// Attributes
public:
	vector<vector<int>> pokusaji; // tries
	vector<vector<int>> pogodjeno; // what is temporary correct
	vector<int> kombinacija; // computer combination
	vector<int> trenutnaKomb; // temporary user combination
	int brojPokusaja,brojPoena; // number of tries and points
	
// Operations
public:
	void izbaciKombinaciju();
	void restart();
	void updatePokusaji();
	bool proveri();
// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CSkockoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
