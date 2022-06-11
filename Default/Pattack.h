#pragma once
#include "Obj.h"
class CPattack :
	public CObj
{
public:
	CPattack();
	virtual ~CPattack();

public:
	virtual void Initialize(void) override;
	virtual int	 Update(void) override;
	virtual	void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	DWORD m_dwSkillTime;
	DWORD m_dwNoSkill;
};

