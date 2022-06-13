#include "stdafx.h"
#include "Monster.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "AbstractFactory.h"
#include "Effect.h"
#include "Item.h"
CMonster::CMonster() :m_PreState(END), m_CureState(IDLE), m_PatternTime(GetTickCount()), m_bGuide(false), m_AttackedTime(GetTickCount()), m_dwEffectDelay(GetTickCount())
{
	m_bJump = false;
	m_tStatus={1, 100, 100,0,0, 10, 0};
}


CMonster::~CMonster()
{
}

void CMonster::Initialize(void)
{
	m_tInfo = { float(rand()%1200+100), float(rand()%600), 100.f, 100.f };

	m_fSpeed = 2.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Character/Slim/SlimL.bmp", L"SlimL");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Character/Slim/SlimR.bmp", L"SlimR");

	m_tFrame.iMotion = 0;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 2;

	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();

	m_framekey = L"SlimL";
}

int CMonster::Update(void)
{
	if (m_bDead&&m_PatternTime + 800 < GetTickCount())
	{
		CObj* pItem = CAbstractFactory<CItem>::Create(m_tInfo.fX, m_tInfo.fY,PORTAL_END,MONEY);
		CObjMgr::Get_Instance()->Add_Obj(OBJ_ITEM, pItem);

		return OBJ_DEAD;
	}
	
	if (m_bAttacked&&m_dwAttackedTime + 500 >= GetTickCount())
	{
		if (m_framekey == L"SlimR")
			m_tInfo.fX -= m_fSpeed;
		else
			m_tInfo.fX += m_fSpeed;
		m_CureState = ATTACKED;
		m_bGod = true;

	}
	else
	{
		m_bAttacked = false;
		m_bGod = false;
	}
	m_pTarget = CObjMgr::Get_Instance()->Get_Player();
	float fWrith = m_tInfo.fX - m_pTarget->Get_Info().fX;
	float fHeight = m_tInfo.fY - m_pTarget->Get_Info().fY;

	float fRadian = atan2f(fHeight,fWrith);

	int Pattern = rand()%4;
	if (m_CureState == WALK)
	{
		if (m_framekey == L"SlimL")
			m_tInfo.fX -= m_fSpeed;
		else
			m_tInfo.fX += m_fSpeed;
	}

	if (((m_tFrame.iFrameEnd+1)*m_tFrame.dwFrameSpeed+ m_PatternTime<GetTickCount()))
	{
		m_CureState = state(rand() % 4);
		if(m_CureState==ATTACKED)
			while(m_CureState ==ATTACKED)
				m_CureState = state(rand() % 4);
		if (m_framekey == L"SlimL")
			m_framekey = L"SlimR";
		else
			m_framekey = L"SlimL";
	}
	else if (m_bAttacked)
	{
		if(CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX>=m_tInfo.fX)
			m_framekey = L"SlimR";
		else
			m_framekey = L"SlimL";
		m_CureState = ATTACKED;
		m_bGuide = true;
		m_AttackedTime = GetTickCount();
	}
	if (m_tStatus.m_iHp <= 0)
		m_CureState = DIE;
	if (m_bGuide)
		m_tInfo.fX -= cosf(fRadian);
	Jumping();
	Move_Change();
	Move_Frame();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CMonster::Late_Update(void)
{

}

void CMonster::Render(HDC hDC)
{
	HDC SLIMHDC = CBmpMgr::Get_Instance()->Find_Image(m_framekey);
	
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	GdiTransparentBlt(hDC,
		int(m_tRect.left) + iScrollX,
		int(m_tRect.top)-40 + iScrollY,
		int(m_tInfo.fCX),
		int(m_tInfo.fCY),
		SLIMHDC,
		m_tFrame.iFrameStart*m_tInfo.fCX,
		m_tFrame.iMotion*m_tInfo.fCY,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));
	if (m_bGuide)
	{
		HBRUSH myBrush1 = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));

		HBRUSH oldBrush1 = (HBRUSH)SelectObject(hDC, myBrush1);

		Rectangle(hDC, int(m_tRect.left) + iScrollX, int(m_tRect.top)  - m_tInfo.fCY*0.3f+iScrollY,
			int(m_tRect.right) + iScrollX, int(m_tRect.top)  - m_tInfo.fCY*0.2f + iScrollY);

		SelectObject(hDC, oldBrush1);
		DeleteObject(myBrush1);

		HBRUSH myBrush2 = (HBRUSH)CreateSolidBrush(RGB(0, 255, 0));

		HBRUSH oldBrush2 = (HBRUSH)SelectObject(hDC, myBrush2);

		if(m_tStatus.m_iHp>0)
		Rectangle(hDC, int(m_tRect.left) + iScrollX, int(m_tRect.top) - m_tInfo.fCY*0.3f + iScrollY,
			int(m_tRect.left) + m_tStatus.m_iHp + iScrollX, int(m_tRect.top) -  m_tInfo.fCY*0.2f + iScrollY);
		


		SelectObject(hDC, oldBrush2);
		DeleteObject(myBrush2);
	}

}
void CMonster::Move_Change()
{
	if (m_PreState != m_CureState)
	{


		switch (m_CureState)
		{
		case IDLE:
			m_tFrame.iMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;

			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			m_PatternTime = GetTickCount();
			break;
		case ATTACKED:
			m_tFrame.iMotion = 1;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;

			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			m_PatternTime = GetTickCount();
			break;
		case JUMP:
			m_tFrame.iMotion = 2;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;

			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			m_PatternTime = GetTickCount();
			m_bJump = true;
			break;
		case WALK:
			m_tFrame.iMotion = 3;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;

			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			m_PatternTime = GetTickCount();	
			
			break;
		case DIE:
			m_tFrame.iMotion = 4;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;

			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			m_PatternTime = GetTickCount();
			m_bDead = true;
			CObjMgr::Get_Instance()->Get_Player()->Set_ExpUp(m_tStatus.m_iExp);
			break;
		}
		m_PreState = m_CureState;
	}
	
}
void CMonster::Jumping_M()
{
	float fOnLine = 0;
	float fOverLine = 0;
	float fUnderLine = 0;
	float fRopeX = 0;
	float fLx = 0.f;
	float fRx = 0.f;
	bool CollisionLineX = CLineMgr::Get_Instance()->Collision_LineX_M(m_tInfo.fX, &m_tInfo.fY, &fOnLine,&fLx,&fRx);
	bool CollisionLineY = CLineMgr::Get_Instance()->Collision_LineY(&m_tInfo.fX, &m_tInfo.fY, &fRopeX);
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
		if (m_tInfo.fX <= fLx || m_tInfo.fX >= fRx)
			m_fSpeed *= -1.f;
	}
	else
	{
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
		if (m_tInfo.fX <= fLx || m_tInfo.fX >= fRx)
			m_fSpeed *= -1.f;
	}
}

void CMonster::Release(void)
{
}


