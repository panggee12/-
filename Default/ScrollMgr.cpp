#include "stdafx.h"
#include "ScrollMgr.h"
#include "Player.h"
#include "ObjMgr.h"
CScrollMgr* CScrollMgr::m_pInstance = nullptr;

CScrollMgr::CScrollMgr():m_iScrollX(WINCX-500), m_iScrollY(400)
{
}


CScrollMgr::~CScrollMgr()
{
}

void CScrollMgr::Scroll_Lock(int _iX, int _iY)
{
	if (m_iScrollX > 0)
		m_iScrollX = 0;
	if (m_iScrollY > 0)
		m_iScrollY = 0;
	if (WINCX - _iX > m_iScrollX)
		m_iScrollX = WINCX - _iX;
	if (WINCY - _iY > m_iScrollY)
		m_iScrollY = WINCY - _iY;

	if (CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX<30)
		CObjMgr::Get_Instance()->Get_Player()->Set_PosX(5.f);
	else if(CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX>_iX-30)
		CObjMgr::Get_Instance()->Get_Player()->Set_PosX(-5.f);
}

void CScrollMgr::Move_Lock(int _iX, int _iY)
{
	
	
}

