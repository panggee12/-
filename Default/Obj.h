#pragma once

#include "Include.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	void		Set_Pos(float _fX, float _fY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}
	void		Set_PosX(float _fX)
	{
		m_tInfo.fX += _fX;
	}
	void		Set_PosY(float _fY)
	{
		m_tInfo.fY += _fY;
	}
	void		Set_Portal(PORTALID _pId)
	{
		m_tProtal = _pId;
	}

	const INFO&	Get_Info() { return m_tInfo; }
	const RECT& Get_Rect() { return m_tRect; }
	const LINE& Get_Line() { return m_tLine; }
	const PORTALID& Get_Portal() { return m_tProtal; }
	POINT		Get_Cursor() { return pt; }
	SKILLID		Get_Skill() { return m_tSkill; }
	DWORD		Get_AttackedTime() { return m_dwAttackedTime; }
	Status		Get_Status() { return m_tStatus; }
	int			Get_Damage() { return m_iDamage; }
	bool		Get_Attacked() { return m_bAttacked; }
	bool		Get_God() { return m_bGod; }
	bool		Get_AlreadyDead() { return m_iDeadCount; }
	bool		Get_Dead() { return m_bDead; }
	const TCHAR* Get_FrameKey() { return m_framekey; }

	void		Set_Rect(int left, int top, int right, int bottom) { m_tRect.left = left; m_tRect.top = top; m_tRect.right = right; m_tRect.bottom = bottom; }
	void		Set_Target(CObj* Target) { m_pTarget = Target; }
	void		Set_Attacked() { m_dwAttackedTime = GetTickCount(); }
	void		Set_key(const TCHAR* _key) { m_framekey = _key; }
	void		Set_DrawID(int DID) { m_iDrawid = DID; }
	void		Set_Attacked(bool Attacked) { m_bAttacked = Attacked; m_bGod = true; }
	void		Set_Skill(SKILLID SID) { m_tSkill = SID; }
	void		Set_MinusHp(int Damage) { m_tStatus.m_iHp -= Damage; }
	void		Set_Damage(int Damage) { m_iDamage = Damage; }
	void		Set_Dead() { m_bDead = true; }
	void		Set_ExpUp(int _iExp) { m_tStatus.m_iExp += _iExp; }
	void		Set_LvUp() { m_tStatus.m_iLv += 1; m_tStatus.m_iExp -= m_tStatus.m_iMaxExp; m_tStatus.m_iMaxExp += 100;
								m_tStatus.m_iMaxHp += 142; m_tStatus.m_iHp = m_tStatus.m_iMaxHp;
								m_tStatus.m_iMaxMp += 142; m_tStatus.m_iMp = m_tStatus.m_iMaxMp;}
public:
	virtual		void	Initialize(void)	PURE;
	virtual		int		Update(void)		PURE;
	virtual		void	Late_Update(void)	PURE;
	virtual		void	Render(HDC hDC)		PURE;
	virtual		void	Release(void)		PURE;

protected:
	void		Update_Rect(void);
	void		Move_Frame();
	void		Jumping();
protected:
	INFO		m_tInfo;
	RECT		m_tRect;
	LINE		m_tLine;
	FRAME		m_tFrame;
	PORTALID	m_tProtal;
	POINT		pt;
	const TCHAR*		m_framekey;
	CObj*		m_pTarget;
	SKILLID		m_tSkill;
	DWORD		m_dwAttackedTime;
	Status		m_tStatus;
	float		m_fSpeed;
	float		m_fJumpPower;
	float		m_fJumpTime;
	bool		m_bDead;
	bool		m_bJump;
	bool		m_bAttacked;
	bool		m_bGod;
	int			m_iDeadCount;
	int			m_iDrawid;
	int			m_iDamage;
	DWORD		m_dwSkillTime;
	DWORD		m_dwNoSkill;
	DWORD		m_dwDeleteEffect;
};

