#include "stdafx.h"
#include "Obj.h"
#include "LineMgr.h"
CObj::CObj() : m_fSpeed(0.f), m_bDead(false), m_iDrawid(0), m_bJump(false), m_fJumpPower(6), m_fJumpTime(0), m_tProtal(PORTAL_END)
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

void CObj::Jumping()
{
	float fOnLine=0;
	float fOverLine = 0;
	float fUnderLine = 0;

	bool CollisionLine = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX,&m_tInfo.fY,&fOnLine);
	if (m_fJumpTime >= 3.5f)
		m_fJumpTime = 3.5f;
	//bool CollisionBlock= CLineMgr::Get_Instance()->Collision_Block(m_tInfo.fX, m_tInfo.fY, &_fyNotLine, &_fyLine);
	if (m_bJump)
	{				
		m_fJumpTime += 0.1f;
		m_tInfo.fY = m_tInfo.fY - m_fJumpPower*m_fJumpTime + 5.f * m_fJumpTime*m_fJumpTime*0.5f;
		
		if (CollisionLine&&m_tInfo.fY > fOnLine)
		{
			m_fJumpTime = 0.f;
			m_bJump = false;
			m_tInfo.fY = fOnLine;
		}
	}
	else
		if (CollisionLine&&m_tInfo.fY < fOnLine)
		{
			m_fJumpTime += 0.1f;
			m_tInfo.fY = m_tInfo.fY + 5.f * m_fJumpTime*m_fJumpTime*0.5f;
			if (m_tInfo.fY >= fOnLine)
			{
				m_tInfo.fY = fOnLine;
				m_fJumpTime = 0.f;
			}
			
		}
		else if (CollisionLine&&m_tInfo.fY >= fOnLine)
		{
			m_fJumpTime = 0.f;
			m_tInfo.fY = fOnLine;
		}
}

void CObj::Move_Frame()
{
	if (m_tFrame.dwFrameSpeed + m_tFrame.dwFrameTime < GetTickCount())
	{
		++m_tFrame.iFrameStart;

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = 0;

		m_tFrame.dwFrameTime = GetTickCount();
	}
}
