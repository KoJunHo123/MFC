#include "stdafx.h"
#include "Player.h"
#include "Device.h"
#include "TextureMgr.h"
#include "AstarMgr.h"
#include "TimeMgr.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
	Release();
}

HRESULT CPlayer::Initialize(void)
{
	m_tInfo.vPos = { 100.f, 100.f,0.f };
	m_wstrObjKey = L"Down";
	m_wstrStateKey = L"Move";
	
	m_tInfo.vDir.y = 1.f;
	m_tFrame = { 0.f, 2.f };

	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/Stage/Player/Up/Bulbasaur_Up_Move_%d.png", TEX_MULTI, L"Up", L"Move", 2)))
	{
		ERR_MSG(L"ImgPath Load Failed");
		return E_FAIL;
	}
	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/Stage/Player/Down/Bulbasaur_Down_Move_%d.png", TEX_MULTI, L"Down", L"Move", 2)))
	{
		ERR_MSG(L"ImgPath Load Failed");
		return E_FAIL;
	}
	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/Stage/Player/Left/Bulbasaur_Left_Move_%d.png", TEX_MULTI, L"Left", L"Move", 2)))
	{
		ERR_MSG(L"ImgPath Load Failed");
		return E_FAIL;
	}
	return S_OK;
}

int CPlayer::Update(void)
{
	D3DXMATRIX		matScale, matRotZ, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x + m_vScroll.x,	// 0인 경우 x 스크롤 값
		m_tInfo.vPos.y + m_vScroll.y,	// 1인 경우 y 스크롤 값
		m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matTrans;

	return 0;
}

void CPlayer::Late_Update(void)
{
	__super::Move_Frame();

	if (GetAsyncKeyState(VK_LBUTTON))
	{
		CAstarMgr::Get_Instance()->Start_Astar(m_tInfo.vPos, ::Get_Mouse() - CObj::m_vScroll);
	}

	Move_AStar();
}

void CPlayer::Render(void)
{
	
	Set_Texture();
	const TEXINFO* pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(m_wstrObjKey.c_str(), m_wstrStateKey.c_str(), (int)m_tFrame.fFrame);
	CDevice::Get_Instance()->Get_Sprite()->SetTransform(&m_tInfo.matWorld);

	if (nullptr == pTexInfo)
		return;

	float	fCenterX = pTexInfo->tImgInfo.Width / 2.f;
	float	fCenterY = pTexInfo->tImgInfo.Height / 2.f;

	CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
		nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr,
		D3DCOLOR_ARGB(255, 255, 255, 255));

}

void CPlayer::Release(void)
{
}

void CPlayer::Move_AStar()
{
	list<TILE*>&		BestList = CAstarMgr::Get_Instance()->Get_BestList();

	if (!BestList.empty())
	{
		D3DXVECTOR3	vDir = BestList.front()->vPos - m_tInfo.vPos;

		float	fDistance = D3DXVec3Length(&vDir);
		D3DXVec3Normalize(&vDir, &vDir);

		m_tInfo.vPos += vDir * 100.f * CTimeMgr::Get_Instance()->Get_TimeDelta();
		m_tInfo.vDir = vDir;
		if (3.f >= fDistance)
			BestList.pop_front();
	}

}

void CPlayer::Set_Texture()
{
	if (abs(m_tInfo.vDir.x) > abs(m_tInfo.vDir.y))
	{
		m_wstrObjKey = L"Left";
		if (m_tInfo.vDir.x > 0)
		{
			m_tInfo.matWorld._11 *= -1.f;
		}
	}
	else
	{
		if (m_tInfo.vDir.y > 0)
			m_wstrObjKey = L"Down";
		else
			m_wstrObjKey = L"Up";
	}

	 
}
