#include "stdafx.h"
#include "Buttons.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "ObjMgr.h"
#include "Player.h"
#include "AbstractFactory.h"
#include "Ui.h"
CButtons::CButtons()
{
}


CButtons::~CButtons()
{
}

void CButtons::Initialize(void)
{
	if (m_tButton == LOBBY_BUTTON)
	{
		m_tInfo.fCX = 50.f;
		m_tInfo.fCY = 50.f;
	}
	else if (m_tButton == STATUS_AUTO)
	{
		m_tInfo.fCX = 70.f;
		m_tInfo.fCY = 40.f;

		CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Ui/SkillAuto.bmp", L"SkillAutoUp");
		m_framekey = L"SkillAutoUp";
	}
	else
	{
		m_tInfo.fCX = 17.f;
		m_tInfo.fCY = 11.f;
		
		CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Ui/SkillUp.bmp", L"SkillUp");
		m_framekey = L"SkillUp";
	}
	
}

int CButtons::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;
	Update_Rect();

	return OBJ_NOEVENT;
}

void CButtons::Late_Update(void)
{
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	
	if (PtInRect(&m_tRect, pt))
	{	
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			if (!lstrcmp(m_framekey, L"LOGINBT"))
			{
				CSceneMgr::Get_Instance()->Scene_Change(STAGE_1);
				CObj* m_pUi = CAbstractFactory<CUi>::Create();

				CObjMgr::Get_Instance()->Add_Obj(OBJ_UI, m_pUi);
			}
			else if (!lstrcmp(m_framekey, L"SkillUp"))
			{
				switch (m_tButton)
				{
				case SKILL_BUTTON1:
					static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_SkillLvup(1, 0, 0, 0);
					break;
				case SKILL_BUTTON2:
					static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_SkillLvup(0, 1, 0, 0);

					break;
				case SKILL_BUTTON3:
					static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_SkillLvup(0, 0, 1, 0);

					break;
				case SKILL_BUTTON4:
					static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_SkillLvup(0, 0, 0, 1);

					break;
				case STATUS_BUTTON1:
					static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_StatusUp(1, 0, 0, 0,1);

					break;
				case STATUS_BUTTON2:
					static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_StatusUp(0, 1, 0, 0,1);

					break;
				case STATUS_BUTTON3:
					static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_StatusUp(0, 0, 1, 0,1);

					break;
				case STATUS_BUTTON4:
					static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_StatusUp(0, 0, 0, 1,1);

					break;

				}
				
			}
			else if (!lstrcmp(m_framekey, L"SkillAutoUp"))
			{
				static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_StatusUp(CObjMgr::Get_Instance()->Get_Player()->Get_Status().m_iAbPoint, 0, 0, 0, CObjMgr::Get_Instance()->Get_Player()->Get_Status().m_iAbPoint);
			}
			return;
		}
		
		m_iDrawid = 1;
	}
	else
		m_iDrawid = 0;

	if (m_tButton >= SKILL_BUTTON1&&m_tButton <= SKILL_BUTTON4)
	{
		if (CObjMgr::Get_Instance()->Get_Player()->Get_SkillPoint() <= 0)
			m_bDead = true;
		else if(!dynamic_cast<CUi*>(CObjMgr::Get_Instance()->Get_Ui())->Get_SkillBook())
			m_bDead = true;
	}
	else if(m_tButton>=STATUS_BUTTON1&&m_tButton< STATUS_AUTO)
	{
		if (CObjMgr::Get_Instance()->Get_Player()->Get_Status().m_iAbPoint <= 0)
			m_bDead = true;
		else if (!dynamic_cast<CUi*>(CObjMgr::Get_Instance()->Get_Ui())->Get_Status())
			m_bDead = true;
	}
	else if (m_tButton == STATUS_AUTO)
	{
		if (CObjMgr::Get_Instance()->Get_Player()->Get_Status().m_iAbPoint <= 0)
			m_bDead = true;
		else if (!dynamic_cast<CUi*>(CObjMgr::Get_Instance()->Get_Ui())->Get_Status())
			m_bDead = true;
	}
		
}

void CButtons::Render(HDC hDC)
{
	if (m_tButton == LOBBY_BUTTON)
	{
		HDC LOGINHDC = CBmpMgr::Get_Instance()->Find_Image(m_framekey);
		GdiTransparentBlt(hDC,
			int(m_tRect.left),
			int(m_tRect.top),
			int(m_tInfo.fCX),
			int(m_tInfo.fCY),
			LOGINHDC,
			m_iDrawid * (int)m_tInfo.fCX,
			0,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(255, 255, 255));
	}
	if (m_tButton >= SKILL_BUTTON1&&m_tButton < STATUS_AUTO)
	{
		HDC  SKILLUPHDC = CBmpMgr::Get_Instance()->Find_Image(L"SkillUp");
			GdiTransparentBlt(hDC,
				int(m_tRect.left),
				int(m_tRect.top),
				int(m_tInfo.fCX),
				int(m_tInfo.fCY),
				SKILLUPHDC,
				0,
				0,
				int(m_tInfo.fCX),
				int(m_tInfo.fCY),
				RGB(255, 255, 255));
	}
	if (m_tButton == STATUS_AUTO)
	{
		HDC  STATUSUPHDC = CBmpMgr::Get_Instance()->Find_Image(L"SkillAutoUp");
		GdiTransparentBlt(hDC,
			int(m_tRect.left),
			int(m_tRect.top),
			int(m_tInfo.fCX),
			int(m_tInfo.fCY),
			STATUSUPHDC,
			0,
			0,
			int(m_tInfo.fCX),
			int(m_tInfo.fCY),
			RGB(255, 255, 255));
	}
}

void CButtons::Release(void)
{
}
