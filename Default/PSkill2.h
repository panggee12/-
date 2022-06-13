#pragma once
#include "Obj.h"
class CPSkill2 :
	public CObj
{
public:
	CPSkill2();
	virtual ~CPSkill2();

public:
	virtual void Initialize(void) override;
	virtual int	 Update(void) override;
	virtual	void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

