#include "stdafx.h"
#include "Player.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "LineMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Pattack.h"
CPlayer::CPlayer():m_CureState(IDLE),m_PreState(STATE_END), m_dwAttack1(GetTickCount()), m_dwAttackDelay(GetTickCount()-700)
{
	m_tStatus = { 1,142,142,142,142,0,100 };
}


CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tInfo = { 400.f, 350.f, 100.f, 100.f };
	m_fSpeed = 5.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Character/Striker/basic_left.bmp", L"PLAYERLEFT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Character/Striker/basic_right.bmp", L"PLAYERRIGHT");

	m_tFrame.iMotion = 0;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;

	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();

	

	m_framekey = L"PLAYERRIGHT";
}

int CPlayer::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Key_Input();
	Jumping();
	OffSet();
	Move_Change();
	Move_Frame();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
}

void CPlayer::Render(HDC hDC)
{
	HDC PLAYERHDC=CBmpMgr::Get_Instance()->Find_Image(m_framekey);

	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	GdiTransparentBlt(hDC,
		int(m_tRect.left)+ iScrollX,
		int(m_tRect.top)-30+ iScrollY,
		int(m_tInfo.fCX),
		int(m_tInfo.fCY),
		PLAYERHDC,
		m_tFrame.iFrameStart*m_tInfo.fCX,
		m_tFrame.iMotion*m_tInfo.fCY,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));
}

void CPlayer::Release(void)
{	
}

void CPlayer::Key_Input(void)
{
	// GetKeyState()
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
	{
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_SPACE))
		{			
			m_bJump = true;
			m_CureState = JUMP;
			m_tInfo.fX += m_fSpeed;
			m_framekey = L"PLAYERRIGHT";
			
		}
		else
		{
			m_tInfo.fX += m_fSpeed;
			m_framekey = L"PLAYERRIGHT";
			m_CureState = WALK;
		}
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
	{
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_SPACE))
		{
			m_bJump = true;
			m_CureState = JUMP;
			m_tInfo.fX -= m_fSpeed;
			m_framekey = L"PLAYERLEFT";
		}
		else
		{
			m_tInfo.fX -= m_fSpeed;
			m_framekey = L"PLAYERLEFT";
			m_CureState = WALK;
		}
		
	}
	/*else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
	{
		m_tInfo.fY -= m_fSpeed;
		m_framekey = L"PLAYERRIGHT";
		m_CureState = UP;
	}*/
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
	{
		m_tInfo.fY += m_fSpeed;
		m_framekey = L"PLAYERRIGHT";
		m_CureState = DOWN;

	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_SPACE))
	{
		m_bJump = true;
		m_CureState = JUMP;
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing('A'))
	{
		m_CureState = ATTACK1;
		if (m_dwAttackDelay + 700 < GetTickCount())
		{
			if (m_framekey == L"PLAYERRIGHT")
				CObjMgr::Get_Instance()->Add_Obj(OBJ_PATTACK, CAbstractFactory<CPattack>::Create(m_tInfo.fX + 20, m_tInfo.fY, 100, NORMAL));
			else
				CObjMgr::Get_Instance()->Add_Obj(OBJ_PATTACK, CAbstractFactory<CPattack>::Create(m_tInfo.fX - 20, m_tInfo.fY, 100, NORMAL));
			m_dwAttackDelay = GetTickCount();
		}
	}
	else
	{
		if (m_CureState == ATTACK1&&m_dwAttack1 + 700>=GetTickCount())
		{
			return;
		}
		else
			m_CureState = IDLE;
	}
}

void CPlayer::Move_Change()
{
	if (m_PreState != m_CureState)
	{
		switch (m_CureState)
		{
		case CPlayer::IDLE:
			m_tFrame.iMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;

			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CPlayer::WALK:
			m_tFrame.iMotion = 1;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;

			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CPlayer::JUMP:
			m_tFrame.iMotion = 2;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;

			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CPlayer::SIT:
			m_tFrame.iMotion = 3;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;

			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CPlayer::ATTACK1:
			m_tFrame.iMotion = 4;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;

			m_tFrame.dwFrameSpeed = 350;
			m_tFrame.dwFrameTime = GetTickCount();
			m_dwAttack1 = GetTickCount();
			break;
		case CPlayer::ATTACK2:
			m_tFrame.iMotion = 5;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;

			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CPlayer::ATTACK3:
			m_tFrame.iMotion = 6;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;

			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CPlayer::UP:
			m_tFrame.iMotion = 9;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;

			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CPlayer::DOWN:
			m_tFrame.iMotion = 10;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;

			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CPlayer::STATE_END:
			break;
		default:
			break;
		}
		m_PreState = m_CureState;
	}
}

void CPlayer::OffSet()
{
	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	int iScrollXMin = 300;
	int iScrollXMax = 500;

	int iScrollYMin = 250;
	int iScrollYMax = 350;

	if (iScrollXMin > m_tInfo.fX+iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed);
	else if (iScrollXMax < m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);

	if (iScrollYMin > m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(m_fSpeed);
	else if (iScrollYMax <  m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(-m_fSpeed);
}
