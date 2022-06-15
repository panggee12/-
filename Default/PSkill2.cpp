#include "stdafx.h"
#include "PSkill2.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CPSkill2::CPSkill2()
{
}


CPSkill2::~CPSkill2()
{
}

void CPSkill2::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Skill/Striker/ascend_right_400400_10.bmp", L"SKILLR2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Skill/Striker/ascend_left_400400_10.bmp", L"SKILLL2");
	m_tInfo.fCX = 400.f;
	m_tInfo.fCY = 400.f;

	m_dwSkillTime = GetTickCount();
	m_dwNoSkill = 1000;

	m_tFrame.iMotion = 0;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 9;

	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CPSkill2::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;
	
	Update_Rect();
	Move_Frame();
	return OBJ_NOEVENT;
}

void CPSkill2::Late_Update(void)
{
	if (m_dwSkillTime + m_dwNoSkill <= GetTickCount())
		m_bDead = true;
}

void CPSkill2::Render(HDC hDC)
{
	HDC SKILLLHDC = CBmpMgr::Get_Instance()->Find_Image(L"SKILLL2");
	HDC SKILLRHDC = CBmpMgr::Get_Instance()->Find_Image(L"SKILLR2");
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

void CPSkill2::Release(void)
{
}
