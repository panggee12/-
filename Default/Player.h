#pragma once

#include "Obj.h"

class CPlayer :	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();
public:
	enum state { IDLE, WALK, JUMP, SIT, ATTACK1, ATTACK2, ATTACK3, UP, DOWN, ROFE,STATE_END };
public:
	virtual void Initialize(void) override;
	virtual int	 Update(void) override;
	virtual	void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void Move_Change();
	void OffSet();
	void Set_Rofe(bool rofe) { m_bRofe = rofe; }
	void Set_FixedX(bool fixedX) { m_bFixedX = fixedX; }
	void Set_State(int i) { m_CureState = state(i); }
	bool Get_Rofe() { return m_bRofe; }
private:
	void		Key_Input(void);
	
	state		m_PreState;
	state		m_CureState;

	DWORD		m_dwAttack1;
	DWORD		m_dwAttackDelay;

	bool		m_bRofe;
	bool		m_bFixedX;
};

