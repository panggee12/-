#include "stdafx.h"
#include "PSkill3.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
CPSkill3::CPSkill3()
{
}


CPSkill3::~CPSkill3()
{
}

void CPSkill3::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Skill/Striker/Bolt_left730427_15.bmp", L"SKILLL3");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Skill/Striker/Bolt_right730427_15.bmp", L"SKILLR3");
	m_tInfo.fCX = 730.f;
	m_tInfo.fCY = 427.f;

	m_dwSkillTime = GetTickCount();
	m_dwNoSkill = 1500;

	m_tFrame.iMotion = 0;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 14;

	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CPSkill3::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();
	Move_Frame();
	return OBJ_NOEVENT;
}

void CPSkill3::Late_Update(void)
{
	if (m_dwSkillTime + m_dwNoSkill <= GetTickCount())
		m_bDead = true;
}

void CPSkill3::Render(HDC hDC)
{
	HDC SKILLLHDC = CBmpMgr::Get_Instance()->Find_Image(L"SKILLL3");
	HDC SKILLRHDC = CBmpMgr::Get_Instance()->Find_Image(L"SKILLR3");
	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();
	if (m_framekey == L"PLAYERRIGHT")
		GdiTransparentBlt(hDC,
			int(m_tRect.left) + iScrollX,
			int(m_tRect.top) - 30 + iScrollY,
			int(m_tInfo.fCX),
			int(m_tInfo.fCY),
			SKILLRHDC,
			m_tFrame.iFrameStart*m_tInfo.fCX,
			m_tFrame.iMotion*m_tInfo.fCY,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(255, 255, 250));
	else
		GdiTransparentBlt(hDC,
			int(m_tRect.left) + iScrollX,
			int(m_tRect.top) - 30 + iScrollY,
			int(m_tInfo.fCX),
			int(m_tInfo.fCY),
			SKILLLHDC,
			m_tFrame.iFrameStart*m_tInfo.fCX,
			m_tFrame.iMotion*m_tInfo.fCY,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(255, 255, 250));
}

void CPSkill3::Release(void)
{
}
