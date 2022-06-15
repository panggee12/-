#include "stdafx.h"
#include "Effect.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "Monster.h"
CEffect::CEffect()
{
}


CEffect::~CEffect()
{
}

void CEffect::Initialize(void)
{
	
	if (m_tSkill == PSKILL1)
	{

		m_tInfo.fCX = 250;
		m_tInfo.fCY = 300;

		m_tFrame.iMotion = 0;
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 4;

		m_tFrame.dwFrameSpeed = 100;
		m_tFrame.dwFrameTime = GetTickCount();
		CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Effect/Annihilationhit_250300_5.bmp", L"Effect1");
		m_framekey = L"Effect1";
	}
	else if (m_tSkill == PSKILL2)
	{
		m_tInfo.fCX = 250;
		m_tInfo.fCY = 250;

		m_tFrame.iMotion = 0;
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 5;

		m_tFrame.dwFrameSpeed = 100;
		m_tFrame.dwFrameTime = GetTickCount();
		CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Effect/ascend_hit.bmp", L"Effect2");	
		m_framekey = L"Effect2";
	}
}

int CEffect::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;
	m_tInfo.fX = m_pTarget->Get_Info().fX-20;
	m_tInfo.fY = m_pTarget->Get_Info().fY-20;
	

	Move_Frame();
	Update_Rect();
	return 0;
}

void CEffect::Late_Update(void)
{
	if (!m_pTarget)
		m_bDead = true;
	if (m_tFrame.dwFrameSpeed*m_tFrame.iFrameEnd+ m_dwDeleteEffect <=GetTickCount())
		m_bDead = true;
}

void CEffect::Render(HDC hDC)
{
	HDC EFFECTHDC = CBmpMgr::Get_Instance()->Find_Image(m_framekey);

	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	GdiTransparentBlt(hDC,
		m_pTarget->Get_Rect().left + iScrollX,
		m_pTarget->Get_Rect().top - 30 + iScrollY,
		int(m_tInfo.fCX),
		int(m_tInfo.fCY),
		EFFECTHDC,
		m_tFrame.iFrameStart*m_tInfo.fCX,
		m_tFrame.iMotion*m_tInfo.fCY,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(255, 255, 250));
}

void CEffect::Release(void)
{
}
