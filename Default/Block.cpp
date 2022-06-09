#include "stdafx.h"
#include "Block.h"
#include "ScrollMgr.h"

CBlock::CBlock()
{
}

CBlock::CBlock(LINEPOINT& tLeft, LINEPOINT& tRight)
{
	m_tLine.LINEL = tLeft;
	m_tLine.LINER = tRight;
}

CBlock::~CBlock()
{
}

void CBlock::Initialize(void)
{
}

int CBlock::Update(void)
{
	Update_Rect();
	return OBJ_NOEVENT;
}

void CBlock::Late_Update(void)
{
}

void CBlock::Render(HDC hDC)
{
	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();

	Rectangle(hDC, m_tLine.LINEL.fX, m_tLine.LINEL.fY, m_tLine.LINER.fX, m_tLine.LINER.fY);
}

void CBlock::Release(void)
{
}
