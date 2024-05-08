
// ToolView.h : CToolView Ŭ������ �������̽�
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
protected: // serialization������ ��������ϴ�.
	CToolView();
	DECLARE_DYNCREATE(CToolView)

// Ư���Դϴ�.
public:
	CToolDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:



// ������ �޽��� �� �Լ�
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

#ifndef _DEBUG  // ToolView.cpp�� ����� ����
inline CToolDoc* CToolView::GetDocument() const
   { return reinterpret_cast<CToolDoc*>(m_pDocument); }
#endif

// 1. ������ �������� �̿��Ͽ� ���콺�� Ÿ�� �浹�� üũ�ϰ� ���� ���ϴ� Ÿ�� �̹����� ��ü�ϱ�
// y = ax + b (a : ����,  b : y ����)

// 2. �̴ϸ��� ���(600���� Ÿ�� �̹����� ��� ��� �ǵ��� �����)