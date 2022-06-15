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
	int  Get_Skill1() { return m_iSkill1; }
	int  Get_Skill2() { return m_iSkill2; }
	int  Get_Skill3() { return m_iSkill3; }
	int  Get_Skill4() { return m_iSkill4; }
	void Set_SkillLvup(int S1, int S2, int S3, int S4) { m_iSkill1 += S1; m_iSkill2 += S2; m_iSkill3 += S3; m_iSkill4 += S4;}

	void Key_Input();
	void known_Key(int KeyNum);
	void Normal_Attack();
private:
	
	state		m_PreState;
	state		m_CureState;

	DWORD		m_dwAttack1;
	DWORD		m_dwAttackDelay;
	DWORD		m_AttackedTime;

	bool		m_bRofe;
	bool		m_bFixedX;

	int			m_iSkill1;
	int			m_iSkill2;
	int			m_iSkill3;
	int			m_iSkill4;
	
	float		m_fPull;
};

