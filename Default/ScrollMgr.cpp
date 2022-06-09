#include "stdafx.h"
#include "ScrollMgr.h"
CScrollMgr* CScrollMgr::m_pInstance = nullptr;

CScrollMgr::CScrollMgr():m_fScrollX(0), m_fScrollY(0)
{
}


CScrollMgr::~CScrollMgr()
{
}
