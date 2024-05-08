#include "stdafx.h"
#include "MyTerrain.h"
#include "Device.h"
#include "TextureMgr.h"
#include "TimeMgr.h"


CMyTerrain::CMyTerrain()
{
}


CMyTerrain::~CMyTerrain()
{
	Release();
}

HRESULT CMyTerrain::Initialize(void)
{

	// ---------------임시---------------
	if (FAILED(Load_Tile(L"../Data/Test.dat")))
	{
		ERR_MSG(L"Tile Data Load Failed");
		return E_FAIL;
	}
	if (m_MAPID == STAGE01)
	{
		if (FAILED(Load_Tile(L"../Data/Test.dat")))
		{
			ERR_MSG(L"Tile Data Load Failed");
			return E_FAIL;
		}
	}
	if (m_MAPID == STAGE02)
	{
		if (FAILED(Load_Tile(L"../Data/Test.dat")))
		{
			ERR_MSG(L"Tile Data Load Failed");
			return E_FAIL;
		}
	}
	if (m_MAPID == STAGE03)
	{
		if (FAILED(Load_Tile(L"../Data/Test.dat")))
		{
			ERR_MSG(L"Tile Data Load Failed");
			return E_FAIL;
		}
	}
	if (m_MAPID == STAGE04)
	{
		if (FAILED(Load_Tile(L"../Data/Test.dat")))
		{
			ERR_MSG(L"Tile Data Load Failed");
			return E_FAIL;
		}
	}
		

	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/Stage/Terrain/PoketmonTile/Floor0/Ground/%d.png", TEX_MULTI, L"STAGE1", L"Tile", 46)))
	{
		return E_FAIL;
	}
	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/Stage/Terrain/PoketmonTile/Floor0/Walls/%d.png", TEX_MULTI, L"STAGE1WALL", L"Walls", 51)))
	{
		return E_FAIL;
	}
	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/Stage/Terrain/PoketmonTile/Floor1/Ground/%d.png", TEX_MULTI, L"STAGE2", L"Tile", 49)))
	{
		return E_FAIL;
	}
	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/Stage/Terrain/PoketmonTile/Floor1/Walls/%d.png", TEX_MULTI, L"STAGE2WALL", L"Walls", 53)))
	{
		return E_FAIL;
	}
	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/Stage/Terrain/PoketmonTile/Floor2/Ground/%d.png", TEX_MULTI, L"STAGE3", L"Tile", 50)))
	{
		return E_FAIL;
	}
	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/Stage/Terrain/PoketmonTile/Floor2/Walls/%d.png", TEX_MULTI, L"STAGE3WALL", L"Walls", 49)))
	{
		return E_FAIL;
	}
	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/Stage/Terrain/PoketmonTile/Floor3/Ground/%d.png", TEX_MULTI, L"STAGE4", L"Tile", 40)))
	{
		return E_FAIL;
	}
	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/Stage/Terrain/PoketmonTile/Floor3/Walls/%d.png", TEX_MULTI, L"STAGE4WALL", L"Walls", 49)))
	{
		return E_FAIL;
	}

	if (FAILED(Ready_Adj()))
	{
		ERR_MSG(L"Ready_Adj Failed");
		return E_FAIL;
	}
	return S_OK;
}

int CMyTerrain::Update(void)
{

	if (0.f > ::Get_Mouse().x)
	{
		if ((float)m_vScroll.x >= -10)
			m_vScroll.x -= 300.f * CTimeMgr::Get_Instance()->Get_TimeDelta();
		m_vScroll.x += 300.f * CTimeMgr::Get_Instance()->Get_TimeDelta();
	}
	if (WINCX < ::Get_Mouse().x)
	{
		if ((float)m_vScroll.x < -390)
			m_vScroll.x += 300.f * CTimeMgr::Get_Instance()->Get_TimeDelta();
		m_vScroll.x -= 300.f * CTimeMgr::Get_Instance()->Get_TimeDelta();
	}
	if (0.f > ::Get_Mouse().y)
	{
		if ((float)m_vScroll.y > -10)
			m_vScroll.y -= 300.f * CTimeMgr::Get_Instance()->Get_TimeDelta();
		m_vScroll.y += 300.f * CTimeMgr::Get_Instance()->Get_TimeDelta();
	}
	if (WINCY < ::Get_Mouse().y)
	{
		if ((float)m_vScroll.y < -590)
			m_vScroll.y += 300.f * CTimeMgr::Get_Instance()->Get_TimeDelta();
		m_vScroll.y -= 300.f * CTimeMgr::Get_Instance()->Get_TimeDelta();
	}


	return 0;
}

void CMyTerrain::Late_Update(void)
{
}

HRESULT CMyTerrain::Ready_Adj()
{
	m_vecAdj.resize(m_vecTile.size());

	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			int      iIndex = i * TILEX + j;

			if (iIndex - TILEX < 0)
				int stop = 0;
			if (iIndex + TILEX >= TILEX * TILEY)
				int stop = 0;


			if (0 != i)
			{
				// 홀 -> 짝 20 감소, 짝 -> 홀 21 감소
				// 홀수이고, byOption이 0이면
				if (!m_vecTile[iIndex - TILEX]->byOption)
				{
					m_vecAdj[iIndex].push_back(m_vecTile[iIndex - TILEX]);
				}
			}

			// 맨 윗줄 && 맨 오른쪽 줄 -> 맨오른쪽, 맨 위는 우상단이 없음
			if ((TILEX - 1) != iIndex % (TILEX))
			{
				if (!m_vecTile[iIndex + 1]->byOption)
				{
					m_vecAdj[iIndex].push_back(m_vecTile[iIndex + 1]);
				}
			}

			// 맨 아랫줄 && 맨 왼쪽 줄 -> 맨왼쪽, 맨 아래는 좌하단이 없음
			if (0 != iIndex % (TILEX))
			{
				// 홀 -> 짝 20 증가, 짝 -> 홀 19 증가
				if ((!m_vecTile[iIndex - 1]->byOption))
				{
					m_vecAdj[iIndex].push_back(m_vecTile[iIndex - 1]);
				}
			}

			// 맨 아랫줄 && 맨 오른쪽 줄 -> 맨오른쪽, 맨 아래는 우하단이 없음
			if (TILEY - 1 != i)
			{
				if (!m_vecTile[iIndex + TILEX]->byOption)
				{
					m_vecAdj[iIndex].push_back(m_vecTile[iIndex + TILEX]);
				}
			}
		}
	}

	return S_OK;
}

void CMyTerrain::Render(void)
{
	D3DXMATRIX		matScale, matRotZ, matTrans;

	TCHAR		szBuf[MIN_STR] = L"";
	int			iIndex(0);

	int		iCullX = int(-m_vScroll.x) / (TILECX);
	int		iCullY = int(-m_vScroll.y) / (TILECY);

	int		iMaxX = WINCX / (TILECX / 2);
	int		iMaxY = WINCY / (TILECY / 2);

	for(int i = iCullY; i < iCullY + iMaxY; ++i)
	{ 
		for (int j = iCullX; j < iCullX + iMaxX; ++j)
		{
			int		iIndex = i * TILEX + j;

			if (0 > iIndex || (size_t)iIndex >= m_vecTile.size())
				continue;

			D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
			D3DXMatrixTranslation(&matTrans,
				m_vecTile[iIndex]->vPos.x + m_vScroll.x,	// 0인 경우 x 스크롤 값
				m_vecTile[iIndex]->vPos.y + m_vScroll.y,	// 1인 경우 y 스크롤 값
				m_vecTile[iIndex]->vPos.z);

			m_tInfo.matWorld = matScale * matTrans;

			CDevice::Get_Instance()->Get_Sprite()->SetTransform(&m_tInfo.matWorld);

			const TEXINFO* pTexInfo = nullptr;
			if (m_vecTile[iIndex]->iStageID == 0)
			{
				if (m_vecTile[iIndex]->byOption == 1)
					pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"STAGE1WALL", L"Walls", m_vecTile[iIndex]->byDrawID);
				else
					pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"STAGE1", L"Tile", m_vecTile[iIndex]->byDrawID);
			}
			if (m_vecTile[iIndex]->iStageID == 1)
			{
				if (m_vecTile[iIndex]->byOption == 1)
					pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"STAGE2WALL", L"Walls", m_vecTile[iIndex]->byDrawID);
				else
					pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"STAGE2", L"Tile", m_vecTile[iIndex]->byDrawID);
			}
			if (m_vecTile[iIndex]->iStageID == 2)
			{
				if (m_vecTile[iIndex]->byOption == 1)
					pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"STAGE3WALL", L"Walls", m_vecTile[iIndex]->byDrawID);
				else
					pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"STAGE3", L"Tile", m_vecTile[iIndex]->byDrawID);
			}if (m_vecTile[iIndex]->iStageID == 3)
			{
				if (m_vecTile[iIndex]->byOption == 1)
					pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"STAGE4WALL", L"Walls", m_vecTile[iIndex]->byDrawID);
				else
					pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"STAGE4", L"Tile", m_vecTile[iIndex]->byDrawID);
			}

			if (nullptr == pTexInfo)
				return;

			float	fCenterX = pTexInfo->tImgInfo.Width / 10.f;
			float	fCenterY = pTexInfo->tImgInfo.Height / 10.f;

			CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
				nullptr,
				&D3DXVECTOR3(fCenterX, fCenterY, 0.f),
				nullptr,
				D3DCOLOR_ARGB(255, 255, 255, 255));

			//swprintf_s(szBuf, L"%d", iIndex);

			CDevice::Get_Instance()->Get_Font()->DrawTextW(CDevice::Get_Instance()->Get_Sprite(),
				szBuf,
				lstrlen(szBuf),
				nullptr,
				0,
				D3DCOLOR_ARGB(255, 255, 255, 255));

			++iIndex;
		}
	}



}

void CMyTerrain::Release(void)
{
	for_each(m_vecTile.begin(), m_vecTile.end(), CDeleteObj());
	m_vecTile.clear();
}

HRESULT CMyTerrain::Load_Tile(const TCHAR * pFilePath)
{
	HANDLE hFile = CreateFile(pFilePath, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	if (INVALID_HANDLE_VALUE == hFile)
		return E_FAIL;

	Release();

	DWORD		dwByte(0);
	TILE*		pTile = nullptr;
	
	while (true)
	{
		pTile = new TILE;

		ReadFile(hFile, pTile, sizeof(TILE), &dwByte, nullptr);

		if (0 == dwByte)
		{
			Safe_Delete(pTile);
			break;
		}

		m_vecTile.push_back(pTile);
	}
	return S_OK;
}
