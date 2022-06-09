#pragma once
#include "Scene.h"
class CStage2 :
	public CScene
{
public:
	CStage2();
	virtual ~CStage2();

public:
	virtual void Initialize(void) override;
	virtual int	 Update(void) override;
	virtual	void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

