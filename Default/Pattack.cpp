#include "stdafx.h"
#include "Pattack.h"


CPattack::CPattack()
{
}


CPattack::~CPattack()
{
}

void CPattack::Initialize(void)
{
	if (m_tSkill == NORMAL)
	{
		m_tInfo.fCX = 50.f;
		m_tInfo.fCY = 50.f;

		m_dwSkillTime = GetTickCount();
		m_dwNoSkill = 1000;
	}

}

int CPattack::Update(void)
{
	if (m_dwSkillTime + m_dwNoSkill < GetTickCount()||m_bDead)
		return OBJ_DEAD;

	Update_Rect();

	return OBJ_NOEVENT;
}

void CPattack::Late_Update(void)
{
}

void CPattack::Render(HDC hDC)
{
}

void CPattack::Release(void)
{
}
