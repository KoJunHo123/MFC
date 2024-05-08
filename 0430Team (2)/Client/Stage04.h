#pragma once
#include "Scene.h"
#include "Include.h"

class Stage04 : public CScene
{
public:
	Stage04();
	virtual ~Stage04();

public:
	virtual HRESULT Ready_Scene() override;
	virtual void Update_Scene() override;
	virtual void Late_Update_Scene() override;
	virtual void Render_Scene() override;
	virtual void Release_Scene() override;
};

