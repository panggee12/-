#include "stdafx.h"
#include "ScrollMgr.h"
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
}

