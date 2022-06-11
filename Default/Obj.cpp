#include "stdafx.h"
#include "Obj.h"
#include "LineMgr.h"
#include "KeyMgr.h"
CObj::CObj() : m_fSpeed(0.f), m_bDead(false), m_iDrawid(0), m_bJump(false), m_fJumpPower(7), m_fJumpTime(0), m_tProtal(PORTAL_END),
m_bAttacked(false), m_pTarget(nullptr), m_iDamage(0)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
	m_framekey = 0;
	ZeroMemory(&m_tStatus, sizeof(Status));
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
void CObj::Jumping()
{
	float fOnLine = 0;
	float fOverLine = 0;
	float fUnderLine = 0;
	float fRopeX = 0;
	bool CollisionLineX = CLineMgr::Get_Instance()->Collision_LineX(m_tInfo.fX, &m_tInfo.fY, &fOnLine);
	bool CollisionLineY = CLineMgr::Get_Instance()->Collision_LineY(m_tInfo.fX, &m_tInfo.fY, &fRopeX);
	if (m_fJumpTime >= 3.5f)
		m_fJumpTime = 3.5f;

	if (m_bJump)
	{
		m_fJumpTime += 0.1f;
		m_tInfo.fY = m_tInfo.fY - m_fJumpPower*m_fJumpTime + 5.f * m_fJumpTime*m_fJumpTime*0.5f;

		if (CollisionLineX&&m_tInfo.fY > fOnLine)
		{
			m_fJumpTime = 0.f;
			m_bJump = false;
			m_tInfo.fY = fOnLine;
		}
		else if (CollisionLineY&&CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
		{
			m_tInfo.fX = fRopeX;
			m_tInfo.fY -= m_fSpeed;
			m_fJumpTime = 0.f;
			m_bJump = false;
		}
	}
	else
		if (CollisionLineX&&m_tInfo.fY < fOnLine)
		{
			m_fJumpTime += 0.1f;
			m_tInfo.fY = m_tInfo.fY + 5.f * m_fJumpTime*m_fJumpTime*0.5f;
			if (m_tInfo.fY >= fOnLine)
			{
				m_tInfo.fY = fOnLine;
				m_fJumpTime = 0.f;
			}

		}
		else if (CollisionLineX&&m_tInfo.fY >= fOnLine)
		{
			m_fJumpTime = 0.f;
			m_tInfo.fY = fOnLine;
		}
		else if (CollisionLineY&&CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
		{
			m_tInfo.fX = fRopeX;
			m_tInfo.fY -= m_fSpeed;
		}
}