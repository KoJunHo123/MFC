#include "stdafx.h"
#include "Undo.h"
#include "MainFrm.h"
#include "ToolView.h"
void Undo::init()
{

	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CToolView* pMainView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplitter.GetPane(0, 1));

	CTerrain* pTerrain = pMainView->m_pTerrain;
	vector<TILE*>& vecTile = pTerrain->Get_VecTile();

	if (vecTile.empty())
		return;
	else
	{
		m_vUndo = vecTile;
	}

	for (auto& pTile : m_vUndo)
	{
		//pTile->byDrawID;
	}
}
