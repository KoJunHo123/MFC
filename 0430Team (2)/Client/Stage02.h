#pragma once
#include "Scene.h"
#include "Include.h"


class Stage02 : public CScene
{

public:
	Stage02();
	virtual ~Stage02();

public:
	virtual HRESULT Ready_Scene() override;
	virtual void Update_Scene() override;
	virtual void Late_Update_Scene() override;
	virtual void Render_Scene() override;
	virtual void Release_Scene() override;
};

