#include "stdafx.h"
#include "Block.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
CBlock::CBlock():m_dwPortal(GetTickCount())
{
	
}

CBlock::CBlock(LINEPOINT& tLeft, LINEPOINT& tRight)
{
	m_tLine.LINEL = tLeft;
	m_tLine.LINER = tRight;
}

CBlock::CBlock(const LINE& tLine)
	: m_tLine(tLine)
{

}

CBlock::~CBlock()
{
}

void CBlock::Initialize(void)
{
	if (m_tProtal != PORTAL_END)
	{
		CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Etc/portal2.bmp", L"Portal");
		m_tFrame.dwFrameSpeed = 200.f;
		m_tFrame.dwFrameTime = GetTickCount();
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 7;
		m_tFrame.iMotion = 0;
		m_tInfo.fCX = 89.f;
		m_tInfo.fCY = 257.f;
	}
	else if (m_tProtal == ROFE)
		return;
	
}

int CBlock::Update(void)
{
	
	Move_Frame();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CBlock::Late_Update(void)
{

}

void CBlock::Render(HDC hDC)
{
	if (m_tProtal != PORTAL_END)
	{
		int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
		int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

		HDC PORTALHDC = CBmpMgr::Get_Instance()->Find_Image(L"Portal");

		GdiTransparentBlt(hDC,
			int(m_tRect.left) + iScrollX,
			int(m_tRect.top) - 30 + iScrollY,
			int(m_tInfo.fCX),
			int(m_tInfo.fCY),
			PORTALHDC,
			m_tFrame.iFrameStart*int(m_tInfo.fCX),
			0,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(255, 255, 255));
	}
	else
		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBlock::Release(void)
{
}
