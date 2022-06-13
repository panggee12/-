#pragma once
#include "Obj.h"
class CMonster :
	public CObj
{
public:
	CMonster();
	virtual ~CMonster();

	enum state { IDLE, ATTACKED, JUMP, WALK, DIE, END };
public:
	virtual void Initialize(void) override;
	virtual int	 Update(void) override;
	virtual	void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void Move_Change();
	void Jumping_M();
	void Set_State(state _State) { m_CureState = _State; }
	void Set_Effect_Delay() { m_dwEffectDelay = GetTickCount(); }

	DWORD Get_Effect_Delay() { return m_dwEffectDelay; }
	DWORD Get_PatternTime() { return m_PatternTime; }
private:
	

	state		m_PreState;
	state		m_CureState;

	DWORD		m_PatternTime;
	DWORD		m_AttackedTime;
	DWORD		m_dwEffectDelay;
	bool		m_bGuide;
};

