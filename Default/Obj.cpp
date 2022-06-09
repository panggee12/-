#include "stdafx.h"
#include "Obj.h"

CObj::CObj() : m_fSpeed(0.f), m_bDead(false), m_iDrawid(0)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
	m_framekey = 0;
}

CObj::~CObj()
{
}

void CObj::Update_Rect(void)
{
	m_tRect.left	= int(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.top		= int(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRect.right	= int(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom	= int(m_tInfo.fY + (m_tInfo.fCY * 0.5f));
}
