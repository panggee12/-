#pragma once

#include "Obj.h"

class CPlayer :	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual void Initialize(void) override;
	virtual int	 Update(void) override;
	virtual	void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void Move_Change();
	void OffSet();
public:
	enum state {IDLE, WALK, JUMP, SIT, ATTACK1, ATTACK2, ATTACK3, UP, DOWN, STATE_END};
private:
	void		Key_Input(void);
	state		m_PreState;
	state		m_CureState;

	DWORD		m_dwAttack1;
};

