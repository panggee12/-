#pragma once
#include "Scene.h"
class CStage4 :
	public CScene
{
public:
	CStage4();
	virtual ~CStage4();

public:
	virtual void Initialize(void) override;
	virtual int	 Update(void) override;
	virtual	void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

