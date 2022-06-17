#include "stdafx.h"
#include "Npc.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"
#include "Ui.h"
#include "ObjMgr.h"

CNpc::CNpc()
{
}


CNpc::~CNpc()
{
}

void CNpc::Initialize(void)
{
	m_tInfo.fCX = 58.f;
	m_tInfo.fCY = 76.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Npc/PotionNpc.bmp", L"NPC");

	m_tFrame.iMotion = 0;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 27;

	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();


	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	m_tRect.left = int(m_tInfo.fX - (m_tInfo.fCX * 0.5f) + iScrollX);
	m_tRect.top = int(m_tInfo.fY - (m_tInfo.fCY * 0.5f) + iScrollY + 70);
	m_tRect.right = int(m_tInfo.fX + (m_tInfo.fCX * 0.5f) + iScrollX);
	m_tRect.bottom = int(m_tInfo.fY + (m_tInfo.fCY * 0.5f) + iScrollY + 70);
}

int CNpc::Update(void)
{

	Move_Frame();
	Update_Rect_Shop();
	return 0;
}

void CNpc::Late_Update(void)
{
}

void CNpc::Render(HDC hDC)
{
	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC NPCHDC = CBmpMgr::Get_Instance()->Find_Image(L"NPC");

	GdiTransparentBlt(hDC,
		int(m_tRect.left),
		int(m_tRect.top),
		int(m_tInfo.fCX),
		int(m_tInfo.fCY),
		NPCHDC,
		m_tFrame.iFrameStart*m_tInfo.fCX,
		m_tFrame.iMotion*m_tInfo.fCY,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(0, 0, 1));
}

void CNpc::Release(void)
{
}

void CNpc::Update_Rect_Shop()
{
	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	m_tRect.left = int(m_tInfo.fX - (m_tInfo.fCX * 0.5f) + iScrollX);
	m_tRect.top = int(m_tInfo.fY - (m_tInfo.fCY * 0.5f) + iScrollY + 70);
	m_tRect.right = int(m_tInfo.fX + (m_tInfo.fCX * 0.5f) + iScrollX);
	m_tRect.bottom = int(m_tInfo.fY + (m_tInfo.fCY * 0.5f) + iScrollY + 70);
}
