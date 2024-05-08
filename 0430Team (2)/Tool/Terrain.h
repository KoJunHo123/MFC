#pragma once

//#include "UndoCareTake.h"
#include "Include.h"
//#include "Undo.h"
class CToolView;
//class Undo;

class CTerrain
{

public:
	//void setTile(const vector<TILE*>& newTile) { m_vecTile = newTile; }
	//const vector<TILE*>& getTile() const { return m_vecTile; }
	//Undo* CreateUndo() const { return new Undo(m_vecTile); }
	//void UndoTile(Undo* _Undo) { m_vecTile = _Undo->Getstate(); }
private:

public:
	CTerrain();
	~CTerrain();

public:
	vector<TILE>   Get_TempTile() { return  m_TempTile; }
	void			Set_TempTile(vector<TILE> _Tile) { m_TempTile = _Tile; }

	vector<TILE*>& Get_VecTile() { return  m_vecTile; }
	void		Set_VecTile(vector<TILE*> _pTile) { m_vecTile = _pTile;  }

public:
	void		Initialize();
	void		Update();
	void		Render();
	void		Mini_Render();
	void		Release();

public:
	int		Get_TileIdx(const D3DXVECTOR3& vPos);
	void	Tile_Change(const D3DXVECTOR3& vPos, const int& iOption, const int& iDrawID, const int& _iStageID, const int& BrushSize);
	bool	Picking(const D3DXVECTOR3& vPos, const int& iIndex);
	bool	Picking_Dot(const D3DXVECTOR3& vPos, const int& iIndex);

	
	vector<TILE>	Get_SaveTileIdx();
	//vector<TILE*> Get_SaveCopyTileIdx();

	void	Stack_NewTerrainList(CTerrain* _pTerrain) { m_TerrainList.push_back(_pTerrain->Get_TempTile()); }

	
	//void	Set_TerrainInfo(vector<TILE*> _Tile);
	void	Undo_TerrainList();
	void	Set_Grid(bool _bGird) { m_bNowGrid = _bGird; }
	void	Set_Paint(bool _bPaint) { m_bNowPaint = _bPaint; }

	void	PaintTile(const int& iOption, const int& iDrawID, const int& _iStageID, const int& index);
	void BSP(int stageId = 0);

private:
	POINT Divide_Map(int _count = 0,
		POINT _LT = { 0, 0 },
		POINT _RB = { TILEX - 1, TILEY - 1 });
	POINT Create_Room(POINT _LT, POINT _RB);
	POINT Connect_Road(POINT _first, POINT _second, POINT _center);

	int Get_Random_Num(int _a, int _b);

public:
	void		Set_MainView(CToolView* pMainView) 
	{ 
			m_pMainView = pMainView;
	}
	void		Set_Ratio(D3DXMATRIX* pOut, float fRatioX, float fRatioY);

	void Set_Tile_Stage1();
	void Set_Tile_Stage2();
	void Set_Tile_Stage3();
	void Set_Tile_Stage4();

private:
	TILE				m_pTmpTILE;

	vector<TILE*>		m_vecTile;
	vector<TILE>		m_TempTile;
	vector<TILE>		m_GridTile;

	bool				m_bNowGrid = false;
	bool				m_bNowPaint = false;

	vector<vector<TILE>>	m_TerrainList;

	CTerrain*			m_NewTerrain;
	vector<CTerrain*>	m_TerrainAllList;

	CToolView*			m_pMainView;


};

