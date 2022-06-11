#pragma once
#include "Obj.h"
class CMonster :
	public CObj
{
public:
	CMonster();
	virtual ~CMonster();

public:
	virtual void Initialize(void) override;
	virtual int	 Update(void) override;
	virtual	void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void Move_Change();
	void Jumping_M();
private:
	enum state{IDLE,ATTACKED, JUMP,WALK,DIE,END};

	state		m_PreState;
	state		m_CureState;

	DWORD		m_PatternTime;
	DWORD		m_AttackedTime;
	bool		m_bGuide;
};

