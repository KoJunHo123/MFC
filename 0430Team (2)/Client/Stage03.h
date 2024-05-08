#pragma once
#include "Scene.h"
#include "Include.h"

class Stage03 : public CScene
{
public:
	Stage03();
	virtual ~Stage03();

public:
	virtual HRESULT Ready_Scene() override;
	virtual void Update_Scene() override;
	virtual void Late_Update_Scene() override;
	virtual void Render_Scene() override;
	virtual void Release_Scene() override;
};

