#include "stdafx.h"
#include "Player.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "LineMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Pattack.h"
#include "PSkill1.h"
#include "PSkill2.h"
#include "PSkill3.h"
#include "PSkill4.h"
#include "Ui.h"
#include "QuickSlot.h"
#include "Effect.h"
#include "Inventory.h"
CPlayer::CPlayer() :m_CureState(IDLE), m_PreState(STATE_END), m_dwAttack1(GetTickCount()), m_dwAttackDelay(GetTickCount() - 700), 
m_dwAttackDelay2(GetTickCount() - 1200),m_bRofe(false), m_bFixedX(false), m_iSkill1(0), m_iSkill2(0), m_iSkill3(0), m_iSkill4(0), 
m_AttackedTime(GetTickCount()), m_fPull(10.f), m_dwSkill4Cool(GetTickCount()), m_bSkill4On(false), m_bSkill4Status(false),
m_dwBlink(GetTickCount())
{
	m_tStatus = { 1,142,142,142,142,0,100 ,100};
	m_iMoney = 10000;
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

	
	if (m_dwSkill4Con + 10000 < GetTickCount() && m_bSkill4On)
	{
		m_bSkill4On = false;
		m_tStatus.m_iDamage /= 2;
	}
	if (m_tStatus.m_iExp >= m_tStatus.m_iMaxExp)
		Set_LvUp();
	/*if (m_bAttacked&&m_dwAttackedTime + 500 >= GetTickCount())
	{
		if (m_framekey == L"PLAYERRIGHT")
			m_tInfo.fX -= m_fSpeed;
		else
			m_tInfo.fX += m_fSpeed;
		m_CureState = JUMP;
		m_bGod = true;

	}*/
	if (m_bAttacked)
	{
		m_fJumpTime += 0.1f;
		if (m_bAttackedDir == false&&!m_bJump)
		{
			m_tInfo.fY = m_tInfo.fY - m_fPull*m_fJumpTime + 3.f * m_fJumpTime*m_fJumpTime*0.5f;
			m_tInfo.fX = m_tInfo.fX - m_fPull*m_fJumpTime*0.5f + 3.f * m_fJumpTime*m_fJumpTime*0.5f;
		}
		else if (m_bAttackedDir == true && !m_bJump)
		{
			m_tInfo.fY = m_tInfo.fY - m_fPull*m_fJumpTime + 3.f * m_fJumpTime*m_fJumpTime*0.5f;
			m_tInfo.fX = m_tInfo.fX + m_fPull*m_fJumpTime*0.5f - 3.f * m_fJumpTime*m_fJumpTime*0.5f;
		}
		m_CureState = JUMP;
		m_AttackedTime = GetTickCount();
	}
	if (m_bAttacked&&m_dwAttackedTime + 500 < GetTickCount())
	{
		m_CureState = IDLE;
		m_fJumpTime += 0.f;
		m_bAttacked = false;
	}
	if (m_dwAttackedTime + 2000 < GetTickCount())
	{
		m_bGod = false;
	}

	Key_Input();
	Jumping();
	Rofing();
	OffSet();
	/*if (m_bRofe)
		m_CureState = ROFE;*/
	Move_Change();
	if(m_CureState !=ROFE)
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
	HDC SKILL4HDC = CBmpMgr::Get_Instance()->Find_Image(L"Skill4");
	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	if (m_bAttacked)
	{
		if (m_dwBlink + 50 < GetTickCount())
		{
			m_dwBlink = GetTickCount();
			GdiTransparentBlt(hDC,
				int(m_tRect.left) + iScrollX,
				int(m_tRect.top) - 30 + iScrollY,
				int(m_tInfo.fCX),
				int(m_tInfo.fCY),
				PLAYERHDC,
				m_tFrame.iFrameStart*m_tInfo.fCX,
				m_tFrame.iMotion*m_tInfo.fCY,
				(int)m_tInfo.fCX,
				(int)m_tInfo.fCY,
				RGB(255, 0, 255));
		}
	}
	else
		GdiTransparentBlt(hDC,
			int(m_tRect.left) + iScrollX,
			int(m_tRect.top) - 30 + iScrollY,
			int(m_tInfo.fCX),
			int(m_tInfo.fCY),
			PLAYERHDC,
			m_tFrame.iFrameStart*m_tInfo.fCX,
			m_tFrame.iMotion*m_tInfo.fCY,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));
	

	if(m_bSkill4On)
		GdiTransparentBlt(hDC,
			768,
			0,
			32,
			32,
			SKILL4HDC,
			0,
			0,
			32,
			32,
			RGB(255, 0, 255));
}

void CPlayer::Release(void)
{	
}

void CPlayer::Key_Input(void)
{
	// GetKeyState()
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT)&&!m_bFixedX)
	{
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_SPACE))
		{
			m_bJump = true;
			m_CureState = JUMP;
			m_tInfo.fX += m_fSpeed;
			m_framekey = L"PLAYERRIGHT";
			Normal_Attack();

		}
		else
		{
			m_tInfo.fX += m_fSpeed;
			m_framekey = L"PLAYERRIGHT";
			m_CureState = WALK;
			Normal_Attack();
		}
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT) && !m_bFixedX)
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
			Normal_Attack();
		}
		
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP) && m_bRofe)
	{

		m_framekey = L"PLAYERRIGHT";
		m_CureState = UP;

	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN)&&m_bRofe)
	{
		
		m_framekey = L"PLAYERRIGHT";
		m_CureState = DOWN;

	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN) && !m_bRofe)
	{

		m_framekey = L"PLAYERRIGHT";
		m_CureState = SIT;

	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_SPACE))
	{
		m_bJump = true;
		m_CureState = JUMP;
		Normal_Attack();
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_CONTROL))
	{
		m_CureState = ATTACK1;
		if (m_dwAttackDelay + 700 < GetTickCount())
		{
			if (m_framekey == L"PLAYERRIGHT")
				CObjMgr::Get_Instance()->Add_Obj(OBJ_PATTACK, CAbstractFactory<CPattack>::Create(m_tInfo.fX + 20, m_tInfo.fY, m_framekey, m_tStatus.m_iDamage,  NORMAL));
			else
				CObjMgr::Get_Instance()->Add_Obj(OBJ_PATTACK, CAbstractFactory<CPattack>::Create(m_tInfo.fX - 20, m_tInfo.fY, m_framekey, m_tStatus.m_iDamage,  NORMAL));
			m_dwAttackDelay = GetTickCount();
		}
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing('A'))
	{	
		known_Key(0);
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing('S'))
	{
		known_Key(1);
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing('D'))
	{
		known_Key(2);
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing('1'))
	{
		known_Key(3);
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing('2'))
	{
		known_Key(4);
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing('3'))
	{
		known_Key(5);
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing('Z'))
	{
		known_Key(6);
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing('X'))
	{
		known_Key(7);
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing('C'))
	{
		known_Key(8);
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing('4'))
	{
		known_Key(9);
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing('5'))
	{
		known_Key(10);
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing('6'))
	{
		known_Key(11);
	}
	else
	{
		if (m_CureState == ATTACK1&&m_dwAttack1 + 700 >= GetTickCount())
		{
			return;
		}
		else if (m_bRofe)
			m_CureState = ROFE;
		else
			m_CureState = IDLE;
	}
	this;
	if(static_cast<CUi*>(CObjMgr::Get_Instance()->Get_Ui())->Get_Inven()&&CKeyMgr::Get_Instance()->Key_Down('I'))
		static_cast<CUi*>(CObjMgr::Get_Instance()->Get_Ui())->Inven_On_Off(false);
	else if (CKeyMgr::Get_Instance()->Key_Down('I'))
		static_cast<CUi*>(CObjMgr::Get_Instance()->Get_Ui())->Inven_On_Off(true);

	if (static_cast<CUi*>(CObjMgr::Get_Instance()->Get_Ui())->Get_SkillBook() && CKeyMgr::Get_Instance()->Key_Down('K'))
	{
		static_cast<CUi*>(CObjMgr::Get_Instance()->Get_Ui())->SkillBook_On_Off(false);
		if (CObjMgr::Get_Instance()->Get_Buttons()->size())
		{
			CObjMgr::Get_Instance()->Delete_Obj(OBJ_BUTTONS);
			static_cast<CUi*>(CObjMgr::Get_Instance()->Get_Ui())->Set_ButtonF();
		}
	}\
	else if (CKeyMgr::Get_Instance()->Key_Down('K'))
		static_cast<CUi*>(CObjMgr::Get_Instance()->Get_Ui())->SkillBook_On_Off(true);
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

			m_tFrame.dwFrameSpeed = 350;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CPlayer::ATTACK3:
			m_tFrame.iMotion = 6;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;

			m_tFrame.dwFrameSpeed = 400;
			m_tFrame.dwFrameTime = GetTickCount();
			break;		
		/*case CPlayer::CROUCH:
			m_tFrame.iMotion = 7;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;

			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;*/
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
		case CPlayer::ROFE:
			m_tFrame.iMotion = 10;
			m_tFrame.iFrameStart = 1;
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

void CPlayer::Rofing()
{
	float py=0;
	bool CollisionY = CLineMgr::Get_Instance()->Collision_LineY(&m_tInfo.fX, &m_tInfo.fY, &py);
	if (CollisionY)
	{
		if (CKeyMgr::Get_Instance()->Key_Down(VK_UP))
		{
			m_tInfo.fX=py;
			m_bFixedX=true;
			m_bRofe=true;
			if (m_bJump)
			{
				m_bJump = false;
				m_fJumpTime = 0.f;
			} 
		}
		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
		{
			m_tInfo.fX = py;
			m_bFixedX = true;
			Set_PosY(-2.f);
			m_bRofe = true;
		}
		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
		{
			m_tInfo.fX = py;
			m_bFixedX = true;
			Set_PosY(2.f);
			m_bRofe = true;
		}
		else if (m_bRofe)
		{
			m_tInfo.fX = py;
			m_bFixedX = true;
			m_CureState = ROFE;
		}

		//else

		//else if (static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_Rofe())
	}
	else
	{
		m_bFixedX = false;
		m_bRofe = false;
	}
	this;
}

void CPlayer::known_Key(int KeyNum)
{
	if (dynamic_cast<CQuickSlot*>(CObjMgr::Get_Instance()->Get_Slot())->Get_VecSlot()[KeyNum]->Get_Skill() == PSKILL1)
	{
		m_CureState = ATTACK1;
		if (m_dwAttackDelay + 700 < GetTickCount())
		{
			if (m_framekey == L"PLAYERRIGHT")
				CObjMgr::Get_Instance()->Add_Obj(OBJ_PATTACK, CAbstractFactory<CPSkill1>::Create(m_tInfo.fX + 100, m_tInfo.fY, m_framekey, m_tStatus.m_iDamage*3+ rand()% (m_tStatus.m_iDamage/2), PSKILL1));
			else
				CObjMgr::Get_Instance()->Add_Obj(OBJ_PATTACK, CAbstractFactory<CPSkill1>::Create(m_tInfo.fX - 100, m_tInfo.fY, m_framekey, m_tStatus.m_iDamage * 3 + rand() % (m_tStatus.m_iDamage / 2), PSKILL1));
			m_dwAttackDelay = GetTickCount();
		}
	}
	else if (dynamic_cast<CQuickSlot*>(CObjMgr::Get_Instance()->Get_Slot())->Get_VecSlot()[KeyNum]->Get_Skill() == PSKILL2)
	{
		m_CureState = ATTACK2;
		if (m_dwAttackDelay + 700 < GetTickCount())
		{
			if (m_framekey == L"PLAYERRIGHT")
				CObjMgr::Get_Instance()->Add_Obj(OBJ_PATTACK, CAbstractFactory<CPSkill2>::Create(m_tInfo.fX + 100, m_tInfo.fY - 100, m_framekey, m_tStatus.m_iDamage*2 + rand() % (m_tStatus.m_iDamage / 2), PSKILL2));
			else
				CObjMgr::Get_Instance()->Add_Obj(OBJ_PATTACK, CAbstractFactory<CPSkill2>::Create(m_tInfo.fX - 100, m_tInfo.fY - 100, m_framekey, m_tStatus.m_iDamage*2 + rand() % (m_tStatus.m_iDamage / 2), PSKILL2));
			m_dwAttackDelay = GetTickCount();
		}
	}
	else if (dynamic_cast<CQuickSlot*>(CObjMgr::Get_Instance()->Get_Slot())->Get_VecSlot()[KeyNum]->Get_Skill() == PSKILL3)
	{
		m_CureState = ATTACK3;
		if (m_dwAttackDelay2 + 1200 < GetTickCount())
		{
			if (m_framekey == L"PLAYERRIGHT")
				CObjMgr::Get_Instance()->Add_Obj(OBJ_PATTACK, CAbstractFactory<CPSkill3>::Create(m_tInfo.fX + 100, m_tInfo.fY - 100, m_framekey, m_tStatus.m_iDamage*4 + rand() % (m_tStatus.m_iDamage / 2), PSKILL3));
			else
				CObjMgr::Get_Instance()->Add_Obj(OBJ_PATTACK, CAbstractFactory<CPSkill3>::Create(m_tInfo.fX - 100, m_tInfo.fY - 100, m_framekey, m_tStatus.m_iDamage*4 + rand() % (m_tStatus.m_iDamage / 2), PSKILL3));
			m_dwAttackDelay2 = GetTickCount();
		}
	}
	else if (dynamic_cast<CQuickSlot*>(CObjMgr::Get_Instance()->Get_Slot())->Get_VecSlot()[KeyNum]->Get_Skill() == PSKILL4&&m_dwSkill4Cool+2000<GetTickCount())
	{
		m_CureState = IDLE;
		CObjMgr::Get_Instance()->Add_Obj(OBJ_PATTACK, CAbstractFactory<CPSkill4>::Create(m_tInfo.fX + 100, m_tInfo.fY - 150,PSKILL4,ITEM_END));
		m_dwSkill4Con = GetTickCount();
		m_dwSkill4Cool = GetTickCount();
		m_bSkill4On = true;
		m_tStatus.m_iDamage *= 2;
	}
	else if (dynamic_cast<CInventory*>(CObjMgr::Get_Instance()->Get_Inven())->Portion_Check(HP)&&
		dynamic_cast<CQuickSlot*>(CObjMgr::Get_Instance()->Get_Slot())->Get_VecSlot()[KeyNum]->Get_Item() == HP)
	{
		m_tStatus.m_iHp += 50;
		if (m_tStatus.m_iHp >= m_tStatus.m_iMaxHp)
			m_tStatus.m_iHp = m_tStatus.m_iMaxHp;
		dynamic_cast<CInventory*>(CObjMgr::Get_Instance()->Get_Inven())->Use_Item(HP);
		
	}
	else if (dynamic_cast<CInventory*>(CObjMgr::Get_Instance()->Get_Inven())->Portion_Check(MP) &&
		dynamic_cast<CQuickSlot*>(CObjMgr::Get_Instance()->Get_Slot())->Get_VecSlot()[KeyNum]->Get_Item() == MP)
	{
		m_tStatus.m_iMp += 50;
		if (m_tStatus.m_iMp >= m_tStatus.m_iMaxMp)
			m_tStatus.m_iMp = m_tStatus.m_iMaxMp;
		dynamic_cast<CInventory*>(CObjMgr::Get_Instance()->Get_Inven())->Use_Item(MP);

	}
}

void CPlayer::Normal_Attack()
{
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_CONTROL))
	{
		m_CureState = ATTACK1;
		if (m_dwAttackDelay + 700 < GetTickCount())
		{
			if (m_framekey == L"PLAYERRIGHT")
				CObjMgr::Get_Instance()->Add_Obj(OBJ_PATTACK, CAbstractFactory<CPattack>::Create(m_tInfo.fX + 20, m_tInfo.fY, m_framekey, m_tStatus.m_iDamage + rand() % (m_tStatus.m_iDamage / 2), NORMAL));
			else
				CObjMgr::Get_Instance()->Add_Obj(OBJ_PATTACK, CAbstractFactory<CPattack>::Create(m_tInfo.fX - 20, m_tInfo.fY, m_framekey, m_tStatus.m_iDamage + rand() % (m_tStatus.m_iDamage / 2), NORMAL));
			m_dwAttackDelay = GetTickCount();
		}
	}
}
