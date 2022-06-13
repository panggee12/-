#include "stdafx.h"
#include "Item.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
CItem::CItem()
{
}


CItem::~CItem()
{
}

void CItem::Initialize(void)
{
	if (m_tItem == MONEY)
	{
		m_tInfo.fCX = 30.f;
		m_tInfo.fCY = 29.f;

		CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Item/meso3.bmp", L"Money");

		m_tFrame.iMotion = 0;
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 3;

		m_tFrame.dwFrameSpeed = 200;
		m_tFrame.dwFrameTime = GetTickCount();

		m_framekey = L"Money";
	}
}

int CItem::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Move_Frame();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CItem::Late_Update(void)
{

}

void CItem::Render(HDC hDC)
{
	HDC ITEMHDC = CBmpMgr::Get_Instance()->Find_Image(m_framekey);

	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	GdiTransparentBlt(hDC,
		int(m_tRect.left) + iScrollX,
		int(m_tRect.top) - 30 + iScrollY,
		int(m_tInfo.fCX),
		int(m_tInfo.fCY),
		ITEMHDC,
		m_tFrame.iFrameStart*m_tInfo.fCX,
		m_tFrame.iMotion*m_tInfo.fCY,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));
}

void CItem::Release(void)
{
}
