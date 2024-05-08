#include "stdafx.h"
#include "Terrain.h"
#include "TextureMgr.h"
#include "Device.h"
#include "ToolView.h"
#include <random>
	
CTerrain::CTerrain() : m_pMainView(NULL)
{
	m_vecTile.reserve(TILEX * TILEY);
}

CTerrain::~CTerrain()
{
	Release();
}

void CTerrain::Initialize()
{
	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/Stage/Terrain/PoketmonTile/Floor0/Ground/%d.png", TEX_MULTI, L"STAGE1", L"Tile", 46)))
	{
		AfxMessageBox(L"Tile Image Insert Failed");
		return;
	}
	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/Stage/Terrain/PoketmonTile/Floor0/Walls/%d.png", TEX_MULTI, L"STAGE1WALL", L"Walls", 51)))
	{
		AfxMessageBox(L"Tile Image Insert Failed");
		return;
	}
	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/Stage/Terrain/PoketmonTile/Floor1/Ground/%d.png", TEX_MULTI, L"STAGE2", L"Tile", 49)))
	{
		AfxMessageBox(L"Tile Image Insert Failed");
		return;
	}
	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/Stage/Terrain/PoketmonTile/Floor1/Walls/%d.png", TEX_MULTI, L"STAGE2WALL", L"Walls", 53)))
	{
		AfxMessageBox(L"Tile Image Insert Failed"); 
		return;
	}
	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/Stage/Terrain/PoketmonTile/Floor2/Ground/%d.png", TEX_MULTI, L"STAGE3", L"Tile", 50)))
	{
		AfxMessageBox(L"Tile Image Insert Failed");
		return;
	}
	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/Stage/Terrain/PoketmonTile/Floor2/Walls/%d.png", TEX_MULTI, L"STAGE3WALL", L"Walls", 49)))
	{
		AfxMessageBox(L"Tile Image Insert Failed");
		return;
	}
	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/Stage/Terrain/PoketmonTile/Floor3/Ground/%d.png", TEX_MULTI, L"STAGE4", L"Tile", 50)))
	{
		AfxMessageBox(L"Tile Image Insert Failed");
		return;
	}
	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/Stage/Terrain/PoketmonTile/Floor3/Walls/%d.png", TEX_MULTI, L"STAGE4WALL", L"Walls", 49)))
	{
		AfxMessageBox(L"Tile Image Insert Failed");
		return;
	}
	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/Stage/Util/%d.png", TEX_MULTI, L"Util", L"TileGrid", 1)))
	{
		AfxMessageBox(L"Tile Image Insert Failed");
		return;
	}


	for (int i = 0; i < 50; ++i)
	{
		for (int j = 0; j < 50; ++j)
		{
			TILE*	pTile = new TILE;

			float fX = (TILECX * j);
			float fY = (TILECY * i);
			
			pTile->vPos		= {fX, fY, 0.f};
			pTile->vSize	= { TILECX, TILECY, 0.f };
			pTile->byOption = 0;
			pTile->byDrawID = 37;
			pTile->iStageID = 0;
			pTile->UndoiIndex = 0;
			pTile->iIndex = i * TILEX + j;
			pTile->iParentIdx = 0;
			m_vecTile.push_back(pTile);
			m_TempTile.push_back(*pTile);
			m_GridTile.push_back(*pTile);
		}
	}
}

void CTerrain::Update()
{

}

void CTerrain::Render()
{
	D3DXMATRIX		matWorld, matScale, matTrans;

	TCHAR		szBuf[MIN_STR] = L"";
	int			iIndex(0);

	RECT		rc{};

	for (auto& pTile : m_vecTile)
	{
		D3DXMatrixIdentity(&matWorld);

		D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
		D3DXMatrixTranslation(&matTrans, 
								pTile->vPos.x - m_pMainView->GetScrollPos(0), 
								pTile->vPos.y - m_pMainView->GetScrollPos(1),
								0.f);

		matWorld = matScale * matTrans;

		GetClientRect(m_pMainView->m_hWnd, &rc);

		float	fRatioX = WINCX / float(rc.right - rc.left);
		float	fRatioY = WINCY / float(rc.bottom - rc.top);

		Set_Ratio(&matWorld, fRatioX, fRatioY);
				
		CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

		const TEXINFO* pTexInfo = nullptr;
		if (pTile->iStageID == 0)
		{
			if (pTile->byOption)
				pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"STAGE1WALL", L"Walls", pTile->byDrawID);
			else
			{
				pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"STAGE1", L"Tile", pTile->byDrawID);
			}
		}
		if (pTile->iStageID == 1)
		{
			if (pTile->byOption)
				pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"STAGE2WALL", L"Walls", pTile->byDrawID);
			else
				pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"STAGE2", L"Tile", pTile->byDrawID);
		}
		if (pTile->iStageID == 2)
		{
			if (pTile->byOption)
				pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"STAGE3WALL", L"Walls", pTile->byDrawID);
			else
				pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"STAGE3", L"Tile", pTile->byDrawID);

		}if (pTile->iStageID == 3)
		{
			if (pTile->byOption)
				pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"STAGE4WALL", L"Walls", pTile->byDrawID);
			else
				pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"STAGE4", L"Tile", pTile->byDrawID);
		}

		float	fCenterX = pTexInfo->tImgInfo.Width / 10.f;
		float	fCenterY = pTexInfo->tImgInfo.Height / 10.f;

		// Draw : 스크린 공간에 2d 스프라이트 이미지를 출력
		CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
			nullptr, // 출력할 이미지 영역에 대한 rect 구조체 주소(nullptr인 경우 이미지의 0,0 기준으로 출력)
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f), // 출력할 이미지의 중심 위치에 대한 vec3 구조체 주소(nullptr인 경우 0,0으로 중점을 조정)
			nullptr, // 출력할 위치 좌표에 대한 vec3 구조체 주소(nullptr인 경우 스크린 상의 0,0에 출력)
			D3DCOLOR_ARGB(255, 255, 255, 255));

		// 타일 인덱스 출력
		//swprintf_s(szBuf, L"%d", iIndex);

		CDevice::Get_Instance()->Get_Font()->DrawTextW(CDevice::Get_Instance()->Get_Sprite(),
			szBuf,
			lstrlen(szBuf),
			nullptr,	// 출력할 위치를 가진 렉트의 주소
			0,			// 정렬 옵션
			D3DCOLOR_ARGB(255, 255, 255, 255));

		++iIndex;
	}

	if (m_bNowGrid)
	{
		for (auto& pTile : m_GridTile)
		{
			D3DXMatrixIdentity(&matWorld);

			D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
			D3DXMatrixTranslation(&matTrans,
				pTile.vPos.x - m_pMainView->GetScrollPos(0),
				pTile.vPos.y - m_pMainView->GetScrollPos(1),
				0.f);

			matWorld = matScale * matTrans;

			GetClientRect(m_pMainView->m_hWnd, &rc);

			float	fRatioX = WINCX / float(rc.right - rc.left);
			float	fRatioY = WINCY / float(rc.bottom - rc.top);

			Set_Ratio(&matWorld, fRatioX, fRatioY);

			CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			pTile.byDrawID = 0;
			const TEXINFO* GridInfo = CTextureMgr::Get_Instance()->Get_Texture(L"Util", L"TileGrid", pTile.byDrawID);


			//----------------------------------------
			float	fCenterX = GridInfo->tImgInfo.Width / 10.f;
			float	fCenterY = GridInfo->tImgInfo.Height / 10.f;

			// Draw : 스크린 공간에 2d 스프라이트 이미지를 출력
			CDevice::Get_Instance()->Get_Sprite()->Draw(GridInfo->pTexture,
				nullptr, // 출력할 이미지 영역에 대한 rect 구조체 주소(nullptr인 경우 이미지의 0,0 기준으로 출력)
				&D3DXVECTOR3(fCenterX, fCenterY, 0.f), // 출력할 이미지의 중심 위치에 대한 vec3 구조체 주소(nullptr인 경우 0,0으로 중점을 조정)
				nullptr, // 출력할 위치 좌표에 대한 vec3 구조체 주소(nullptr인 경우 스크린 상의 0,0에 출력)
				D3DCOLOR_ARGB(255, 255, 255, 255));

			// 타일 인덱스 출력
			//swprintf_s(szBuf, L"%d", iIndex);

			CDevice::Get_Instance()->Get_Font()->DrawTextW(CDevice::Get_Instance()->Get_Sprite(),
				szBuf,
				lstrlen(szBuf),
				nullptr,	// 출력할 위치를 가진 렉트의 주소
				0,			// 정렬 옵션
				D3DCOLOR_ARGB(255, 255, 255, 255));

			++iIndex;
		}
	}

}

void CTerrain::Mini_Render()
{
	D3DXMATRIX		matWorld, matScale, matTrans;

	for (auto& pTile : m_vecTile)
	{
		D3DXMatrixIdentity(&matWorld);

		D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
		D3DXMatrixTranslation(&matTrans,
			pTile->vPos.x,
			pTile->vPos.y,
			0.f);

		matWorld = matScale * matTrans;

		Set_Ratio(&matWorld, 0.5f, 0.5f);

		CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

		const TEXINFO* pTexInfo = nullptr;
		if (pTile->iStageID == 0)
		{
			if (pTile->byOption)
				pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"STAGE1WALL", L"Walls", pTile->byDrawID);
			else
				pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"STAGE1", L"Tile", pTile->byDrawID);
		}
		if (pTile->iStageID == 1)
		{
			if (pTile->byOption)
				pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"STAGE2WALL", L"Walls", pTile->byDrawID);
			else
				pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"STAGE2", L"Tile", pTile->byDrawID);
		}
		if (pTile->iStageID == 2)
		{
			if (pTile->byOption)
				pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"STAGE3WALL", L"Walls", pTile->byDrawID);
			else
				pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"STAGE3", L"Tile", pTile->byDrawID);
		}if (pTile->iStageID == 3)
		{
			if (pTile->byOption)
				pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"STAGE4WALL", L"Walls", pTile->byDrawID);
			else
				pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"STAGE4", L"Tile", pTile->byDrawID);
		}

		float	fCenterX = pTexInfo->tImgInfo.Width / 10.f;
		float	fCenterY = pTexInfo->tImgInfo.Height / 10.f;

		// Draw : 스크린 공간에 2d 스프라이트 이미지를 출력
		CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
			nullptr, // 출력할 이미지 영역에 대한 rect 구조체 주소(nullptr인 경우 이미지의 0,0 기준으로 출력)
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f), // 출력할 이미지의 중심 위치에 대한 vec3 구조체 주소(nullptr인 경우 0,0으로 중점을 조정)
			nullptr, // 출력할 위치 좌표에 대한 vec3 구조체 주소(nullptr인 경우 스크린 상의 0,0에 출력)
			D3DCOLOR_ARGB(255, 255, 255, 255));	
	}
}

void CTerrain::Release()
{
	for_each(m_vecTile.begin(), m_vecTile.end(), [](auto& pTile)
	{
		if (pTile)
		{
			delete pTile;
			pTile = nullptr;
		}
	});

	m_vecTile.clear();
	m_vecTile.shrink_to_fit();
}

int CTerrain::Get_TileIdx(const D3DXVECTOR3 & vPos)
{
	for (size_t index = 0; index < m_TempTile.size(); ++index)
	{
		if (Picking_Dot(vPos, index))
		{
			return index;
		}
	}

	return -1;
}
//0   1   2   3   4   5   6... 49
//50  51  52  53  54  55  56... 99
//100 101 102 103 104 105 106... 149
//150 151 152 153 154 155 156... 199
//200 201 202 203 204 206 207... 249
//250 251 252 253 254 256 257... 299
//300 301 302 303 304 305 306... 349

//1 0 = 1,0 = 1
//2 1 = 8,9 = 3
//3 2 = 24,25 = 5
//4 3 = 48, 49 = 7
//5 4 = 80, 81 = 9
// 5 =	120,121	= 11
void CTerrain::Tile_Change(const D3DXVECTOR3 & vPos, const int& iOption,const int& iDrawID, const int& _iStageID,const int& BrushSize)
{
	int	iIndex = Get_TileIdx(vPos);
	int Tempindex;
	int Count(0);
	if (-1 == iIndex)
		return;
	if (m_bNowPaint)
	{
		PaintTile(iOption, iDrawID, _iStageID, iIndex);
	}
	else
	{
		for (int i = 0; i < BrushSize; i++)
		{
			if (BrushSize >= 1) // 3
			{
				Tempindex = iIndex + (TILEX * i);  // 50 51 100 101
				Count = 0;
				for (int j = 0; j < BrushSize; j++)
				{
					if (j == 0)
					{
						Tempindex = Tempindex + 0;
					}
					else
					{
						Tempindex = Tempindex + 1;
					}
					m_vecTile[Tempindex]->byOption = iOption;
					m_vecTile[Tempindex]->byDrawID = iDrawID;
					m_vecTile[Tempindex]->iStageID = _iStageID;
					m_vecTile[Tempindex]->UndoiIndex = iIndex;

					m_TempTile[Tempindex].byOption = iOption;
					m_TempTile[Tempindex].byDrawID = iDrawID;
					m_TempTile[Tempindex].iStageID = _iStageID;
					m_TempTile[Tempindex].UndoiIndex = iIndex;
				}
				
			}
			else
			{
				m_vecTile[iIndex]->byOption = iOption;
				m_vecTile[iIndex]->byDrawID = iDrawID;
				m_vecTile[iIndex]->iStageID = _iStageID;
				m_vecTile[iIndex]->UndoiIndex = iIndex;

				m_TempTile[iIndex].byOption = iOption;
				m_TempTile[iIndex].byDrawID = iDrawID;
				m_TempTile[iIndex].iStageID = _iStageID;
				m_TempTile[iIndex].UndoiIndex = iIndex;
			}
		}
	}
	
}


void CTerrain::PaintTile(const int& iOption, const int& iDrawID, const int& _iStageID, const int& index)
{
	/*if (m_pTmpTILE == )
	{
		m_pTmpTILE.byDrawID = m_TempTile[index].byDrawID;
		m_pTmpTILE.byOption = m_TempTile[index].byOption;
		m_pTmpTILE.iStageID = m_TempTile[index].iStageID;
	}*/
	int Tempindex(0);
	if ((0 > index) || (TILEX * TILEY <= index))
		return;
	//if ((m_TempTile[index].byDrawID != m_pTmpTILE->byDrawID))
		//return;

	m_vecTile[index]->byOption = iOption;
	m_vecTile[index]->byDrawID = iDrawID;
	m_vecTile[index]->iStageID = _iStageID;
	m_vecTile[index]->UndoiIndex = index;

	m_TempTile[index].byOption = iOption;
	m_TempTile[index].byDrawID = iDrawID;
	m_TempTile[index].iStageID = _iStageID;
	m_TempTile[index].UndoiIndex = index;

		for (int i = 0; i < 4; i++)
		{
			if (i == 0)
			{
				PaintTile(iOption, iDrawID, _iStageID, index -1);
			}
			if (i == 1)
			{
				PaintTile(iOption, iDrawID, _iStageID, index + 1);
			}
			if (i == 2)
			{
				PaintTile(iOption, iDrawID, _iStageID, index + TILEX);
			}
			if (i == 3)
			{
				PaintTile(iOption, iDrawID, _iStageID, index - TILEX);
			}
		}
}

bool CTerrain::Picking(const D3DXVECTOR3 & vPos, const int & iIndex)
{

	float		fGradient[4]{

		(TILECY ) / (TILECX) * -1.f,
		(TILECY ) / (TILECX),
		(TILECY ) / (TILECX) * -1.f,
		(TILECY ) / (TILECX)
	};

	// 12, 3, 6, 9
	D3DXVECTOR3	vPoint[4] = {

		{ m_TempTile[iIndex].vPos.x, m_TempTile[iIndex].vPos.y + (TILECY), 0.f },
		{ m_TempTile[iIndex].vPos.x + (TILECX), m_TempTile[iIndex].vPos.y, 0.f },
		{ m_TempTile[iIndex].vPos.x, m_TempTile[iIndex].vPos.y - (TILECY), 0.f },
		{ m_TempTile[iIndex].vPos.x - (TILECX), m_TempTile[iIndex].vPos.y, 0.f }

	};

	// y = ax + b ->  b = y - ax

	float	fB[4]{

		vPoint[0].y - fGradient[0] * vPoint[0].x,
		vPoint[1].y - fGradient[1] * vPoint[1].x,
		vPoint[2].y - fGradient[2] * vPoint[2].x,
		vPoint[3].y - fGradient[3] * vPoint[3].x
	};

	// 0 == ax + b - y : 직선 상에 있는 상태
	// 0 >	ax + b - y  : 직선 위쪽에 있는 상태
	// 0 <	ax + b - y  : 직선 아래 쪽에 있는 상태

	bool	bCheck[4]{ false };

	if (0 < fGradient[0] * vPos.x + fB[0] - vPos.y)
		bCheck[0] = true;

	if (0 >= fGradient[1] * vPos.x + fB[1] - vPos.y)
		bCheck[1] = true;

	if (0 >= fGradient[2] * vPos.x + fB[2] - vPos.y)
		bCheck[2] = true;

	if (0 < fGradient[3] * vPos.x + fB[3] - vPos.y)
		bCheck[3] = true;

	return bCheck[0] && bCheck[1] && bCheck[2] && bCheck[3];
}

bool CTerrain::Picking_Dot(const D3DXVECTOR3 & vPos, const int & iIndex)
{
	// 12, 3, 6, 9
	D3DXVECTOR3	vPoint[4] = {

		{ m_TempTile[iIndex].vPos.x, m_TempTile[iIndex].vPos.y + (TILECY), 0.f },
		{ m_TempTile[iIndex].vPos.x + (TILECX), m_TempTile[iIndex].vPos.y, 0.f },
		{ m_TempTile[iIndex].vPos.x, m_TempTile[iIndex].vPos.y - (TILECY), 0.f },
		{ m_TempTile[iIndex].vPos.x - (TILECX), m_TempTile[iIndex].vPos.y, 0.f }

	};
	
	D3DXVECTOR3	vDir[4]
	{
		vPoint[1] - vPoint[0],
		vPoint[2] - vPoint[1],
		vPoint[3] - vPoint[2],
		vPoint[0] - vPoint[3]
	};

	// (x, y) -> (-y, x)

	D3DXVECTOR3	vNormal[4]
	{
		{ -vDir[0].y, vDir[0].x, 0.f},
		{ -vDir[1].y, vDir[1].x, 0.f },
		{ -vDir[2].y, vDir[2].x, 0.f },
		{ -vDir[3].y, vDir[3].x, 0.f }
	};

	D3DXVECTOR3	vMouseDir[4]
	{
		vPos - vPoint[0],
		vPos - vPoint[1],
		vPos - vPoint[2],
		vPos - vPoint[3]
	};

	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3Normalize(&vNormal[i], &vNormal[i]);
		D3DXVec3Normalize(&vMouseDir[i], &vMouseDir[i]);
	}

	for (int i = 0; i < 4; ++i)
	{
		// 양수 -> 예각 -> 타일 바깥 쪽을 클릭
		if (0.f < D3DXVec3Dot(&vNormal[i], &vMouseDir[i]))
			return false;
	}
	
	return true;
}

vector<TILE> CTerrain::Get_SaveTileIdx()
{
	return m_TempTile;
}

void CTerrain::Undo_TerrainList()
{
	if (m_TerrainList.empty())
		return;

	m_TerrainList.pop_back();

	auto& iter = m_TerrainList.back();
	m_TempTile = iter;
	
	//auto& iter = m_TerrainList.front();
	for_each(m_vecTile.begin(), m_vecTile.end(), [](auto& pTile)
		{
			if (pTile)
			{
				delete pTile;
				pTile = nullptr;
			}
		});
	m_vecTile.clear();
	for (auto& pTile : m_TempTile)
	{
		TILE* Temp = new TILE;
		Temp->byDrawID = pTile.byDrawID;
		Temp->byOption = pTile.byOption;
		Temp->iIndex = pTile.iIndex;
		Temp->iParentIdx = pTile.iParentIdx;
		Temp->iStageID = pTile.iStageID;
		Temp->UndoiIndex = pTile.UndoiIndex;
		Temp->vPos = pTile.vPos;
		Temp->vSize = pTile.vSize;

		m_vecTile.push_back(Temp);
	}
	
}


void CTerrain::Set_Ratio(D3DXMATRIX * pOut, float fRatioX, float fRatioY)
{
	pOut->_11 *= fRatioX;
	pOut->_21 *= fRatioX;
	pOut->_31 *= fRatioX;
	pOut->_41 *= fRatioX;

	pOut->_12 *= fRatioY;
	pOut->_22 *= fRatioY;
	pOut->_32 *= fRatioY;
	pOut->_42 *= fRatioY;

}


void CTerrain::BSP(int stageId)
{
	// 시작할때 싹다 option 1로 박고 시작.
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		m_vecTile[i]->byOption = 1;
		m_vecTile[i]->byDrawID = 0;
		m_vecTile[i]->iStageID = stageId;
	}

	Divide_Map();

	if (0 == m_vecTile[0]->iStageID)
		Set_Tile_Stage1();
	if (1 == m_vecTile[0]->iStageID)
		Set_Tile_Stage2();;
	if (2 == m_vecTile[0]->iStageID)
		Set_Tile_Stage3();
	if (3 == m_vecTile[0]->iStageID)
		Set_Tile_Stage4();
}

// 타일 벡터 받아서 참조로 옵션 변경.
POINT CTerrain::Divide_Map(int _count, POINT _LT, POINT _RB)
{
	if (_count > 4)
	{
		// 여기서 방 만들기
		return Create_Room(_LT, _RB);
	}

	// 여기서 나누기
	POINT first_LT{}, first_RB{}, second_LT{}, second_RB{};


	int ranNum = Get_Random_Num(3, 7);
	bool choice = Get_Random_Num(0, 1);

	// Width가 더 길 때 -> x좌표가 기준
	if (_RB.x - _LT.x >= _RB.y - _LT.y)
	{
		first_LT = _LT;
		first_RB = { _LT.x + ((_RB.x - _LT.x) * ranNum / 10), _RB.y };

		second_LT = { first_RB.x, _LT.y };
		second_RB = _RB;
	}
	// Height가 더 길 때 -> y좌표가 기준
	else
	{
		first_LT = _LT;
		first_RB = { _RB.x, _LT.y + ((_RB.y - _LT.y) * ranNum / 10) };

		second_LT = { _LT.x, first_RB.y };
		second_RB = _RB;
	}

	++_count;

	POINT first = Divide_Map(_count, first_LT, first_RB);
	POINT second = Divide_Map(_count, second_LT, second_RB);

	POINT center = { _LT.x + (_RB.x - _LT.x) / 2, _LT.y + (_RB.y - _LT.y) / 2 };

	return Connect_Road(first, second, center);
	//  길 잇기

	// return POINT{};
}

POINT CTerrain::Create_Room(POINT _LT, POINT _RB)
{
	// 범위 내의 더 작은 랜덤한 범위를 만들어서 그곳의 LT, RB를 반환

	size_t Left = 0;	//((_RB.x - _LT.x) * Get_Random_Num(0, 3) / 10);
	size_t Top = 0;	//((_RB.y - _LT.y) * Get_Random_Num(0, 3) / 10);
	size_t Right = 0;	//((_RB.x - _LT.x) * Get_Random_Num(0, 3) / 10);
	size_t Bottom = 0;	//((_RB.y - _LT.y) * Get_Random_Num(0, 3) / 10);

	if (1 >= Left)
		Left = 2;

	if (1 >= Top)
		Top = 2;

	if (1 >= Right)
		Right = 2;

	if (1 >= Bottom)
		Bottom = 2;

	POINT vRoomLT =
	{
		_LT.x + Left,
		_LT.y + Top
	};
	POINT vRoomRB =
	{
		_RB.x - Right,
		_RB.y - Bottom
	};

	if (vRoomLT.x == 0)
	{
		int a = 0;
	}

	for (int i = vRoomLT.y; i <= vRoomRB.y; ++i)
	{
		for (int j = vRoomLT.x; j <= vRoomRB.x; ++j)
		{
			int iIndex = j + TILEX * i;

			if (!Get_Random_Num(0, 3))
				m_vecTile[iIndex]->byDrawID = Get_Random_Num(0, 40);
			else
				m_vecTile[iIndex]->byDrawID = 38;

			m_vecTile[iIndex]->byOption = 0;
		}
	}

	return { _LT.x + (_RB.x - _LT.x) / 2, _LT.y + (_RB.y - _LT.y) / 2 };
}

POINT CTerrain::Connect_Road(POINT _first, POINT _second, POINT _center)
{
	POINT center{};

	// 수직(위 아래)
	if (_first.x == _second.x)
	{
		for (int i = _first.y; i <= _second.y; ++i)
		{
			int iIndex = _first.x + TILEX * i;

			if (!Get_Random_Num(0, 3))
				m_vecTile[iIndex]->byDrawID = Get_Random_Num(0, 40);
			else
				m_vecTile[iIndex]->byDrawID = 38;

			m_vecTile[iIndex]->byOption = 0;
		}
		center = { _first.x, _center.y };

	}
	// 수평(좌 우)
	else if (_first.y == _second.y)
	{
		for (int i = _first.x; i <= _second.x; ++i)
		{
			int iIndex = i + TILEX * _first.y;

			if (!Get_Random_Num(0, 3))
				m_vecTile[iIndex]->byDrawID = Get_Random_Num(0, 40);
			else
				m_vecTile[iIndex]->byDrawID = 38;

			m_vecTile[iIndex]->byOption = 0;
		}
		center = { _center.x, _first.y };
	}

	return center;
}

void CTerrain::Set_Tile_Stage1()
{
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		m_vecTile[i]->iStageID = 0;
		if (m_vecTile[i]->byOption)
		{
			char cState(0);
			if (0 <= i - TILEX && 0 == m_vecTile[i - TILEX]->byOption)
			{
				cState |= TOP;
			}

			if (TILEX * TILEY > i + TILEX && 0 == m_vecTile[i + TILEX]->byOption)
			{
				cState |= BOTTOM;
			}

			if (0 != i % TILEX && 0 < i && 0 == m_vecTile[i - 1]->byOption)
			{
				cState |= LEFT;
			}

			if (49 != i % TILEX && i < (TILEX * TILEY - 1) && 0 == m_vecTile[i + 1]->byOption)
			{
				cState |= RIGHT;
			}


			BYTE drawId(0);
			if (cState & LEFT)
			{
				drawId = 32;
				if (cState & TOP)
				{
					drawId = 0;
					if (cState & RIGHT)
					{
						drawId = 8;
						if (cState & BOTTOM)
						{
							drawId = 5;
						}
					}
					else if (cState & BOTTOM)
					{
						drawId = 9;
					}
				}
				else if (cState & RIGHT)
				{
					drawId = 4;
					if (cState & BOTTOM)
					{
						drawId = 13;
					}
				}
				else if (cState & BOTTOM)
				{
					drawId = 48;
				}
			}
			else if (cState & RIGHT)
			{
				drawId = 46;
				if (cState & TOP)
				{
					drawId = 21;
					if (cState & BOTTOM)
					{
						drawId = 12;
					}
				}
				else if (cState & BOTTOM)
				{
					drawId = 50;
				}
			}
			else if (cState & TOP)
			{
				drawId = 10;
				if (cState & BOTTOM)
				{
					drawId = 2;
				}
			}
			else if (cState & BOTTOM)
			{
				drawId = 49;
			}
			else
			{
				int ranNum = Get_Random_Num(0, 2);
				if (0 == ranNum)
				{
					drawId = 43;
				}
				else if (1 == ranNum)
				{
					drawId = 45;
				}
				else
				{
					drawId = 47;
				}
			}

			m_vecTile[i]->byDrawID = drawId;
		}
	}
}

void CTerrain::Set_Tile_Stage2()
{
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		m_vecTile[i]->iStageID = 1;

		if (m_vecTile[i]->byOption)
		{
			char cState(0);
			if (0 <= i - TILEX && 0 == m_vecTile[i - TILEX]->byOption)
			{
				cState |= TOP;
			}

			if (TILEX * TILEY > i + TILEX && 0 == m_vecTile[i + TILEX]->byOption)
			{
				cState |= BOTTOM;
			}

			if (0 != i % TILEX && 0 < i && 0 == m_vecTile[i - 1]->byOption)
			{
				cState |= LEFT;
			}

			if (49 != i % TILEX && i < (TILEX * TILEY - 1) && 0 == m_vecTile[i + 1]->byOption)
			{
				cState |= RIGHT;
			}

			BYTE drawId(0);
			if (cState & LEFT)
			{
				drawId = 12;
				if (cState & TOP)
				{
					drawId = 0;
					if (cState & RIGHT)
					{
						drawId = 30;
						if (cState & BOTTOM)
						{
							drawId = 27;
						}
					}
					else if (cState & BOTTOM)
					{
						drawId = 31;
					}
				}
				else if (cState & RIGHT)
				{
					drawId = 26;
					if (cState & BOTTOM)
					{
						drawId = 34;
					}
				}
				else if (cState & BOTTOM)
				{
					drawId = 19;
				}
			}
			else if (cState & RIGHT)
			{
				drawId = 14;
				if (cState & TOP)
				{
					drawId = 2;
					if (cState & BOTTOM)
					{
						drawId = 33;
					}
				}
				else if (cState & BOTTOM)
				{
					drawId = 21;
				}
			}
			else if (cState & TOP)
			{
				drawId = 1;
				if (cState & BOTTOM)
				{
					drawId = 24;
				}
			}
			else if (cState & BOTTOM)
			{
				drawId = 20;
			}
			else
			{
				int ranNum = Get_Random_Num(0, 2);
				if (0 == ranNum)
				{
					drawId = 13;
				}
				else if (1 == ranNum)
				{
					drawId = 16;
				}
				else
				{
					drawId = 18;
				}
			}
			m_vecTile[i]->byDrawID = drawId;
		}
	}
}

void CTerrain::Set_Tile_Stage3()
{
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		m_vecTile[i]->iStageID = 2;

		if (m_vecTile[i]->byOption)
		{
			char cState(0);
			if (0 <= i - TILEX && 0 == m_vecTile[i - TILEX]->byOption)
			{
				cState |= TOP;
			}

			if (TILEX * TILEY > i + TILEX && 0 == m_vecTile[i + TILEX]->byOption)
			{
				cState |= BOTTOM;
			}

			if (0 != i % TILEX && 0 < i && 0 == m_vecTile[i - 1]->byOption)
			{
				cState |= LEFT;
			}

			if (49 != i % TILEX && i < (TILEX * TILEY - 1) && 0 == m_vecTile[i + 1]->byOption)
			{
				cState |= RIGHT;
			}

			BYTE drawId(0);
			if (cState & LEFT)
			{
				drawId = 6;
				if (cState & TOP)
				{
					drawId = 0;
					if (cState & RIGHT)
					{
						drawId = 21;
						if (cState & BOTTOM)
						{
							drawId = 18;
						}
					}
					else if (cState & BOTTOM)
					{
						drawId = 22;
					}
				}
				else if (cState & RIGHT)
				{
					drawId = 17;
					if (cState & BOTTOM)
					{
						drawId = 25;
					}
				}
				else if (cState & BOTTOM)
				{
					drawId = 11;
				}
			}
			else if (cState & RIGHT)
			{
				drawId = 8;
				if (cState & TOP)
				{
					drawId = 2;
					if (cState & BOTTOM)
					{
						drawId = 24;
					}
				}
				else if (cState & BOTTOM)
				{
					drawId = 13;
				}
			}
			else if (cState & TOP)
			{
				drawId = 1;
				if (cState & BOTTOM)
				{
					drawId = 15;
				}
			}
			else if (cState & BOTTOM)
			{
				drawId = 12;
			}
			else
			{
				drawId = 7;
			}
			m_vecTile[i]->byDrawID = drawId;
		}
	}
}

void CTerrain::Set_Tile_Stage4()
{
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		m_vecTile[i]->iStageID = 3;

		if (m_vecTile[i]->byOption)
		{
			char cState(0);
			if (0 <= i - TILEX && 0 == m_vecTile[i - TILEX]->byOption)
			{
				cState |= TOP;
			}

			if (TILEX * TILEY > i + TILEX && 0 == m_vecTile[i + TILEX]->byOption)
			{
				cState |= BOTTOM;
			}

			if (0 != i % TILEX && 0 < i && 0 == m_vecTile[i - 1]->byOption)
			{
				cState |= LEFT;
			}

			if (49 != i % TILEX && i < (TILEX * TILEY - 1) && 0 == m_vecTile[i + 1]->byOption)
			{
				cState |= RIGHT;
			}

			BYTE drawId(0);
			if (cState & LEFT)
			{
				drawId = 6;
				if (cState & TOP)
				{
					drawId = 0;
					if (cState & RIGHT)
					{
						drawId = 21;
						if (cState & BOTTOM)
						{
							drawId = 18;
						}
					}
					else if (cState & BOTTOM)
					{
						drawId = 22;
					}
				}
				else if (cState & RIGHT)
				{
					drawId = 17;
					if (cState & BOTTOM)
					{
						drawId = 25;
					}
				}
				else if (cState & BOTTOM)
				{
					drawId = 11;
				}
			}
			else if (cState & RIGHT)
			{
				drawId = 8;
				if (cState & TOP)
				{
					drawId = 2;
					if (cState & BOTTOM)
					{
						drawId = 24;
					}
				}
				else if (cState & BOTTOM)
				{
					drawId = 13;
				}
			}
			else if (cState & TOP)
			{
				drawId = 1;
				if (cState & BOTTOM)
				{
					drawId = 15;
				}
			}
			else if (cState & BOTTOM)
			{
				drawId = 12;
			}
			else
			{
				drawId = 7;
			}
			m_vecTile[i]->byDrawID = drawId;
		}
	}

}


// a~b사이의 난수 반환
int CTerrain::Get_Random_Num(int _a, int _b)
{
	std::random_device rd;

	// random_device 를 통해 난수 생성 엔진을 초기화 한다.
	// minstd_rand -> 메모리 부족하면
	// mt19937 -> 메모리 여유 있으면
	std::minstd_rand gen(rd());

	// 0 부터 99 까지 균등하게 나타나는 난수열을 생성하기 위해 균등 분포 정의.
	std::uniform_int_distribution<int> dis(_a, _b);

	return dis(gen);
}
