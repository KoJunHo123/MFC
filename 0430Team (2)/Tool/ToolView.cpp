
// ToolView.cpp : CToolView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "Tool.h"
#endif

#include "ToolDoc.h"
#include "ToolView.h"
#include "Device.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HWND	g_hWnd;


// CToolView

IMPLEMENT_DYNCREATE(CToolView, CScrollView)

BEGIN_MESSAGE_MAP(CToolView, CScrollView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_DESTROY()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CToolView ����/�Ҹ�

CToolView::CToolView() //: m_pSingle(nullptr)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
}

CToolView::~CToolView()
{
}

BOOL CToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CScrollView::PreCreateWindow(cs);
}

void CToolView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	
	CWnd::SetTimer(0, 500, NULL);


	// SetScrollSizes : ��ũ�� ���� ����� �����ϴ� cscrollview�� ��� �Լ�
	// MM_TEXT : �ȼ� ������ �����ϰڴٴ� �ɼ�
	// CSize : MFC���� �����ϴ� ����� �����ϱ� ���� �뵵�� Ŭ���� �ڷ���

	SetScrollSizes(MM_TEXT, CSize(TILEX* 24, TILEX * 24));
	
	// AfxGetMainWnd : ������ ���� �����츦 ��ȯ�ϴ� ���� �Լ�		
	CMainFrame*		pMainFrm = (CMainFrame*)AfxGetMainWnd();


	CMiniView* pMiniView = dynamic_cast<CMiniView*>(pMainFrm->m_SecondSplitter.GetPane(0, 0));
	CMyForm* pMyForm = dynamic_cast<CMyForm*>(pMainFrm->m_SecondSplitter.GetPane(1, 0));
	CMapTool* pMapTool = &(pMyForm->m_MapTool);


	RECT	rcWnd{};

	// GetWindowRect : ���� �������� RECT ������ ������ �Լ�
	pMainFrm->GetWindowRect(&rcWnd);		

	// SetRect : ������ �Ű� ������� RECT ������ ������ִ� �Լ�
	SetRect(&rcWnd, 0, 0, rcWnd.right - rcWnd.left, rcWnd.bottom - rcWnd.top);

	RECT		rcMainView{};
	//GetClientRect : ���� view â�� RECT ������ ������ �Լ�
	GetClientRect(&rcMainView);

	float	fRowFrm = float(rcWnd.right - rcMainView.right);
	float	fColFrm = float(rcWnd.bottom - rcMainView.bottom);

	// SetWindowPos : �Ű� ������� ���Ӱ� ������ ��ġ�� ũ�⸦ �����ϴ� �Լ�
	// SetWindowPos(��ġ�� �������� z������ ���� ������, x��ǥ, y��ǥ, ���� ũ��, ���� ũ��, ��ġ�� �������� ũ�� �� ��ġ ���� �ɼ�)
	// nullptr : ���� �������� ����
	// SWP_NOZORDER : ���� ������ �����ϰ���
	pMainFrm->SetWindowPos(nullptr, 0, 0, int(WINCX + fRowFrm), int(WINCY + fColFrm), SWP_NOZORDER);


	g_hWnd = m_hWnd;

	if (FAILED(CDevice::Get_Instance()->Init_Device()))
	{
		AfxMessageBox(L"Init_Device Failed");
		return;
	}

	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/Cube.png", TEX_SINGLE, L"Cube")))
	{
		AfxMessageBox(L"Cube Image Insert Failed");
		return;
	}

	m_pTerrain = new CTerrain;
	m_pTerrain->Initialize();
	m_pTerrain->Set_MainView(this);
	m_pTerrain->Stack_NewTerrainList(m_pTerrain);
	//m_pTerrain->Stack_TerrainList();

}



void CToolView::OnDraw(CDC* /*pDC*/)
{
	CToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	

	CDevice::Get_Instance()->Render_Begin();

	m_pTerrain->Render();

	CDevice::Get_Instance()->Render_End();			
}


void CToolView::OnDestroy()
{
	CScrollView::OnDestroy();

	Safe_Delete(m_pTerrain);

	CTextureMgr::Destroy_Instance();
	CDevice::Destroy_Instance();
}


void CToolView::UpdateUndo()
{
	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CMiniView* pMiniView = dynamic_cast<CMiniView*>(pMainFrm->m_SecondSplitter.GetPane(0, 0));
	
	pMiniView->Invalidate(FALSE);
	Invalidate(FALSE);
}

void CToolView::onTimer(UINT nIDEVENE)
{
	/*Invalidate(TRUE);

	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CMiniView* pMiniView = dynamic_cast<CMiniView*>(pMainFrm->m_SecondSplitter.GetPane(0, 0));
	CMyForm* pMyForm = dynamic_cast<CMyForm*>(pMainFrm->m_SecondSplitter.GetPane(1, 0));
	CMapTool* pMapTool = &(pMyForm->m_MapTool);

	switch (nIDEVENE)
	{
	case 0:
		break;
	}
	Invalidate(FALSE);*/

}

void CToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CScrollView::OnLButtonDown(nFlags, point);

	CMainFrame*		pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CMiniView*		pMiniView = dynamic_cast<CMiniView*>(pMainFrm->m_SecondSplitter.GetPane(0, 0));
	CMyForm*		pMyForm = dynamic_cast<CMyForm*>(pMainFrm->m_SecondSplitter.GetPane(1, 0));
	CMapTool*		pMapTool = &(pMyForm->m_MapTool);

	m_pTerrain->Tile_Change(D3DXVECTOR3((float)point.x + GetScrollPos(0),
										(float)point.y + GetScrollPos(1),
										0.f),
										pMapTool->m_iOptionID,
										pMapTool->m_iDrawID,
										pMapTool->m_StageNumber,
										pMapTool->m_BrushSize);

	if (!m_DePressMouse)
	{
		//m_pTerrain->Stack_NewTerrainList(m_pTerrain);
	}

	pMapTool->Set_bUndo();

	m_DePressMouse = false;


	pMiniView->Invalidate(FALSE);

	// ��ŷ ó�� �Լ�

	// Invalidate : ȣ�� �� �����쿡 WM_PAINT�� WM_ERASEBKGND �޼����� �߻���Ŵ
	// FALSE : WM_PAINT�� �߻�
	// TRUE : WM_PAINT, WM_ERASEBKGND ���ÿ� �߻�

	Invalidate(FALSE);
}

void CToolView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CScrollView::OnMouseMove(nFlags, point);



	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CMiniView* pMiniView = dynamic_cast<CMiniView*>(pMainFrm->m_SecondSplitter.GetPane(0, 0));
	CMyForm* pMyForm = dynamic_cast<CMyForm*>(pMainFrm->m_SecondSplitter.GetPane(1, 0));
	CMapTool* pMapTool = &(pMyForm->m_MapTool);


	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && !pMapTool->Get_bUndo())
	{
		pMapTool->Set_bUndo();
		
		m_pTerrain->Tile_Change(D3DXVECTOR3((float)point.x + GetScrollPos(0),
			(float)point.y + GetScrollPos(1),
			0.f),
			pMapTool->m_iOptionID,
			pMapTool->m_iDrawID,
			pMapTool->m_StageNumber,
			pMapTool->m_BrushSize
		);

		Invalidate(FALSE);

		m_DePressMouse = false;
		pMiniView->Invalidate(FALSE);
	}
	else if(!GetAsyncKeyState(VK_LBUTTON) & 0x8000 && !m_DePressMouse)
	{
		m_pTerrain->Stack_NewTerrainList(m_pTerrain);
		m_DePressMouse = true;
	}
	Invalidate(FALSE);


}

//void CToolView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
//{
//	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
//	//CScrollView::OnKeyDown(nFlags, nFlags, nFlags);
//
//
//	if (GetAsyncKeyState('Z') && GetAsyncKeyState(VK_CONTROL))
//	{
//		//Invalidate(TRUE);
//		m_pTerrain->Undo_TerrainList();
//		UpdateUndo();
//		m_KeyDown = true;
//			//m_KeyDown = false;
//	}
//
//	//Invalidate(FALSE);
//}
//
//
//void CToolView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
//{
//	CWnd::OnKeyUp(nChar, nRepCnt, nFlags);
//	//CScrollView::OnKeyDown(nFlags, nFlags, nFlags);
//	
//	if (!GetAsyncKeyState('Z') && GetAsyncKeyState(VK_CONTROL))
//	{
//		//m_pTerrain->Undo_TerrainList();
//		//UpdateUndo();
//
//	}
//
//	m_KeyDown = false;
//
//}

BOOL CToolView::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (GetAsyncKeyState(VK_LCONTROL) && 0x8000)
		{
			if (pMsg->wParam == 90)
			{
				m_pTerrain->Undo_TerrainList();
				UpdateUndo();
			}
				//pMsg->wParam = VK_TAB;
		}
	}
	return CScrollView::PreTranslateMessage(pMsg);
}

#pragma region ����

// CToolView �μ�

BOOL CToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CToolView ����

#ifdef _DEBUG
void CToolView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CToolView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CToolDoc* CToolView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolDoc)));
	return (CToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CToolView �޽��� ó����

#pragma endregion ����