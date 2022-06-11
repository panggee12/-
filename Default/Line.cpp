#include "stdafx.h"
#include "Line.h"
#include "ScrollMgr.h"


CLine::CLine()
{
}


CLine::CLine(LINEPOINT& tLeft, LINEPOINT& tRight)
	: m_tInfo(tLeft, tRight)
{

}

CLine::CLine(const LINE& tLine)
	: m_tInfo(tLine)
{

}

CLine::~CLine()
{
	Release();
}

void CLine::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	MoveToEx(hDC, (int)m_tInfo.LINEL.fX + iScrollX, (int)m_tInfo.LINEL.fY+ iScrollY, nullptr);
	LineTo(hDC, (int)m_tInfo.LINER.fX + iScrollX, (int)m_tInfo.LINER.fY+ iScrollY);
}

void CLine::Release(void)
{

}
