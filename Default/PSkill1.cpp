#include "stdafx.h"
#include "PSkill1.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
CPSkill1::CPSkill1()
{
}


CPSkill1::~CPSkill1()
{
}

void CPSkill1::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Skill/Striker/Annihilation_RIGHT_630230_13.bmp", L"SKILLR1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Skill/Striker/Annihilation_LEFT_630230_13.bmp", L"SKILLL1");
	m_tInfo.fCX = 630.f;
	m_tInfo.fCY = 230.f;

	m_dwSkillTime = GetTickCount();
	m_dwNoSkill = 1300;
	
	m_tFrame.iMotion = 0;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 12;

	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CPSkill1::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;
	if (m_framekey == L"PLAYERRIGHT")
		m_tInfo.fX += 5.f;
	else
		m_tInfo.fX -= 5.f;
	Update_Rect();
	Move_Frame();
	return OBJ_NOEVENT;
}

void CPSkill1::Late_Update(void)
{
	if (m_dwSkillTime + m_dwNoSkill <= GetTickCount())
		m_bDead = true;
}

void CPSkill1::Render(HDC hDC)
{
	HDC SKILLLHDC=CBmpMgr::Get_Instance()->Find_Image(L"SKILLL1");
	HDC SKILLRHDC = CBmpMgr::Get_Instance()->Find_Image(L"SKILLR1");
	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();
	if(m_framekey == L"PLAYERRIGHT")
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

void CPSkill1::Release(void)
{
}
