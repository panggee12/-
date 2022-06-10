#include "stdafx.h"
#include "ScrollMgr.h"
CScrollMgr* CScrollMgr::m_pInstance = nullptr;

CScrollMgr::CScrollMgr():m_iScrollX(WINCX-500), m_iScrollY()
{
}


CScrollMgr::~CScrollMgr()
{
}

void CScrollMgr::Scroll_Lock()
{
	if (m_iScrollX > 0)
		m_iScrollX = 0;
	if (m_iScrollY > 0)
		m_iScrollY = 0;
	if (WINCX - 1440 > m_iScrollX)
		m_iScrollX = WINCX - 1440;
	if (WINCY - 1159 > m_iScrollY)
		m_iScrollY = WINCY - 1159;
}

