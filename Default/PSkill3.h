#pragma once
#include "Obj.h"
class CPSkill3 :
	public CObj
{
public:
	CPSkill3();
	virtual ~CPSkill3();

public:
	virtual void Initialize(void) override;
	virtual int	 Update(void) override;
	virtual	void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

