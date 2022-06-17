#include "stdafx.h"
#include "PSkill4.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
CPSkill4::CPSkill4()
{
}


CPSkill4::~CPSkill4()
{
}

void CPSkill4::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Skill/buf.bmp", L"SKILL4");
	
	m_tInfo.fCX = 178.f;
	m_tInfo.fCY = 244.f;

	m_dwSkillTime = GetTickCount();
	m_dwNoSkill = 1800;

	m_tFrame.iMotion = 0;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 17;

	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CPSkill4::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	m_pTarget = CObjMgr::Get_Instance()->Get_Player();

	m_tInfo.fX = m_pTarget->Get_Info().fX;
	m_tInfo.fY = m_pTarget->Get_Info().fY - 150;
	Move_Frame();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CPSkill4::Late_Update(void)
{
	if (m_dwSkillTime + m_dwNoSkill <= GetTickCount())
		m_bDead = true;
}

void CPSkill4::Render(HDC hDC)
{
	HDC SKILLHDC = CBmpMgr::Get_Instance()->Find_Image(L"SKILL4");
	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	GdiTransparentBlt(hDC,
		int(m_tRect.left) + iScrollX,
		int(m_tRect.top) - 30 + iScrollY,
		int(m_tInfo.fCX),
		int(m_tInfo.fCY),
		SKILLHDC,
		m_tFrame.iFrameStart*m_tInfo.fCX,
		m_tFrame.iMotion*m_tInfo.fCY,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(0, 0, 0));
}

void CPSkill4::Release(void)
{
}
