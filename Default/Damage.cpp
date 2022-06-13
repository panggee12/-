#include "stdafx.h"
#include "Damage.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CDamage::CDamage():m_iDamageCount(0)
{
}


CDamage::~CDamage()
{
}

void CDamage::Initialize(void)
{
	m_tInfo.fCX = 149.f;
	m_tInfo.fCY = 69.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Effect/DamageEffect.bmp", L"Damage");
}

int CDamage::Update(void)
{
	return 0;
}

void CDamage::Late_Update(void)
{
}

void CDamage::Render(HDC hDC)
{
	HDC DAMAGEHDC = CBmpMgr::Get_Instance()->Find_Image(L"Damage");

	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	GdiTransparentBlt(hDC,
		int(m_tRect.left) + iScrollX,
		int(m_tRect.top) - 30 + iScrollY,
		int(m_tInfo.fCX),
		int(m_tInfo.fCY),
		DAMAGEHDC,
		m_tFrame.iFrameStart*m_tInfo.fCX,
		m_tFrame.iMotion*m_tInfo.fCY,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));
}

void CDamage::Release(void)
{
}
