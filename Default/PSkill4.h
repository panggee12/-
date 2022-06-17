#pragma once
#include "Obj.h"
class CPSkill4 :
	public CObj
{
public:
	CPSkill4();
	virtual ~CPSkill4();

public:
	virtual void Initialize(void) override;
	virtual int	 Update(void) override;
	virtual	void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

