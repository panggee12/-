#include "stdafx.h"
#include "Obj.h"
#include "LineMgr.h"
CObj::CObj() : m_fSpeed(0.f), m_bDead(false), m_iDrawid(0), m_bJump(false), m_fJumpPower(5), m_fJumpTime(0)
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
	float _fyLine=0;
	float _fyNotLine = 0;

	
	//bool CollisionLine = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX,m_tInfo.fY,&_fyNotLine,&_fyLine);
	bool CollisionBlock= CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, m_tInfo.fY, &_fyNotLine, &_fyLine);
	if (m_bJump)
	{
		m_fJumpTime += 0.1f;
		m_tInfo.fY = m_tInfo.fY - m_fJumpPower*m_fJumpTime + 5 * m_fJumpTime*m_fJumpTime*0.5f;
		
		if (m_tInfo.fY >= _fyLine&&CollisionBlock)
		{
			m_fJumpTime = 0.f;
			m_bJump = false;
			m_tInfo.fY = _fyNotLine;
		}
	}
	else
		if (CollisionBlock&&m_tInfo.fY <= _fyLine)
		{
			m_fJumpTime += 0.1f;
			m_tInfo.fY = m_tInfo.fY + 5 * m_fJumpTime*m_fJumpTime*0.5f;			
			
		}
		else if (CollisionBlock&&m_tInfo.fY == _fyNotLine)
			m_tInfo.fY = _fyNotLine;
		
		

}
