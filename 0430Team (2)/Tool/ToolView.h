
// ToolView.h : CToolView 클래스의 인터페이스
//

#pragma once

#include "Include.h"
#include "TextureMgr.h"
#include "Terrain.h"
//#include "Undo.h"
//#include "UndoCareTake.h"
class CToolDoc;
class CToolView : public CScrollView
{
protected: // serialization에서만 만들어집니다.
	CToolView();
	DECLARE_DYNCREATE(CToolView)

// 특성입니다.
public:
	CToolDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:



// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnDestroy();


	void UpdateUndo();
	afx_msg void onTimer(UINT nIDEVENE);
	//afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);

public:
	//void setTile(const vector<TILE*>& newTile) { m_vTile = newTile; }
	//const vector<TILE*>& getTile() const { return m_vTile; }
	//Undo* CreateUndo() const { return new Undo(m_vTile); }
	//void UndoTile(Undo* _Undo) { m_vTile = _Undo->Getstate(); }
	//void Stackm_vTile();
private:
public:
	CTerrain* m_pTerrain;
	bool	m_DePressMouse = true;
	bool	m_KeyDown = false;
};

#ifndef _DEBUG  // ToolView.cpp의 디버그 버전
inline CToolDoc* CToolView::GetDocument() const
   { return reinterpret_cast<CToolDoc*>(m_pDocument); }
#endif

// 1. 직선의 방정식을 이용하여 마우스와 타일 충돌을 체크하고 내가 원하는 타일 이미지로 교체하기
// y = ax + b (a : 기울기,  b : y 절편)

// 2. 미니맵을 출력(600장의 타일 이미지가 모두 출력 되도록 만들기)