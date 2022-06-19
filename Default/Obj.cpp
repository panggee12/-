#include "stdafx.h"
#include "Obj.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "Player.h"
CObj::CObj() : m_fSpeed(0.f), m_bDead(false), m_iDrawid(0), m_bJump(false), m_fJumpPower(7), m_fJumpTime(0), m_tProtal(PORTAL_END),
m_bAttacked(false), m_pTarget(nullptr), m_bGod(false), m_iDeadCount(0), m_dwDeleteEffect(GetTickCount()), m_tItem(ITEM_END), m_iMoney(0),
m_iSkillPoint(4), m_tButton(BUTTON_END), m_bAttackedDir(false), m_iPortionCount(0), m_bCrouchJump(false), m_bSaveLine(false)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
	m_framekey = 0;
	ZeroMemory(&m_tStatus, sizeof(Status));
	ZeroMemory(&m_tFrame, sizeof(FRAME));
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
		{
			m_tFrame.iFrameStart = 0;		
		}

		m_tFrame.dwFrameTime = GetTickCount();
	}
}
void CObj::Jumping()
{
	float fOnLine = 0;
	float fOverLine = 0;
	float fUnderLine = 0;
	float fRopeX = 0;
	bool CollisionLineX = CLineMgr::Get_Instance()->Collision_LineX(m_tInfo.fX, &m_tInfo.fY, &fOnLine, &fUnderLine);
	//bool CollisionLineY = CLineMgr::Get_Instance()->Collision_LineY(&m_tInfo.fX, &m_tInfo.fY, &fRopeX);
	/*if (m_bCrouchJump && !m_bSaveLine)
	{
	fOverLine = fUnderLine;
	fRopeX = fOnLine;
	m_bSaveLine = true;
	}*/
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

			//static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Rofe(false);
		}

	}
	else
	{
		if (CollisionLineX)
		{
			m_fJumpTime += 0.1f;
			m_tInfo.fY = m_tInfo.fY + 5.f * m_fJumpTime*m_fJumpTime*0.5f;
			if (m_tInfo.fY >= fOnLine)
			{
				m_tInfo.fY = fOnLine;
				m_fJumpTime = 0.f;
				//static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Rofe(false);
			}

		}
		else if (CollisionLineX&&m_tInfo.fY >= fOnLine)
		{
			m_fJumpTime = 0.f;
			m_tInfo.fY = fOnLine;
		//	static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Rofe(false);
		}

	}

}