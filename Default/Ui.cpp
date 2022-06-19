#include "stdafx.h"
#include "Ui.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "Player.h"
#include "AbstractFactory.h"
#include "Buttons.h"
#include "QuickSlot.h"
#include "KeyMgr.h"
#include "Inventory.h"
#include "Shop.h"
#include "Equip.h"
CUi::CUi():m_bShop(false), m_bInven(false), m_bSkillBook(false), m_bSkBt1(false), m_bSkBt2(false), m_bSkBt3(false), m_bSkBt4(false),
SkillOn1(0), SkillOn2(0), SkillOn3(0), SkillOn4(0), m_bItemCreate(false), m_bEquip(false),m_bStatus(false), m_bStBt1(false), m_bStBt2(false),
m_bStBt3(false), m_bStBt4(false), m_bStBt5(false)
{																										  
}																										  


CUi::~CUi()
{
}

void CUi::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Ui/screen_state.bmp", L"State"); 
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Ui/hp.bmp", L"Hp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Ui/mp.bmp", L"Mp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Ui/screen_exp.bmp", L"Exp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Ui/exp.bmp", L"NowExp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Ui/screen_quickslot.bmp", L"Quick");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Ui/level.bmp", L"Level");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Ui/store4.bmp", L"Shop");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Ui/Inven.bmp", L"Inven");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Ui/SkillBook.bmp", L"SkillBook");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Icon/Skill1Icon.bmp", L"Skill1Icon");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Icon/Skill2Icon.bmp", L"Skill2Icon");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Icon/Skill3Icon.bmp", L"Skill3Icon");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Icon/buf.bmp", L"Skill4Icon");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Ui/Equip.bmp", L"EquipUI");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Ui/stat.bmp", L"StatusUI");
	CObjMgr::Get_Instance()->Add_Obj(OBJ_QUICKSLOT, CAbstractFactory<CQuickSlot>::Create());
	CObjMgr::Get_Instance()->Add_Obj(OBJ_INVEN, CAbstractFactory<CInventory>::Create());
	CObjMgr::Get_Instance()->Add_Obj(OBJ_EQUIP, CAbstractFactory<CEquip>::Create());
}

int CUi::Update(void)
{
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	return 0;
}

void CUi::Late_Update(void)
{
}

void CUi::Render(HDC hDC)
{
	HDC  STATEhdc=CBmpMgr::Get_Instance()->Find_Image(L"State");
	HDC  HPhdc=CBmpMgr::Get_Instance()->Find_Image(L"Hp");
	HDC  MPhdc=CBmpMgr::Get_Instance()->Find_Image(L"Mp");
	HDC  EXPhdc=CBmpMgr::Get_Instance()->Find_Image(L"Exp");
	HDC  NOWEXPhdc=CBmpMgr::Get_Instance()->Find_Image(L"NowExp");
	HDC  QUICKhdc=CBmpMgr::Get_Instance()->Find_Image(L"Quick");
	HDC  LEVELhdc = CBmpMgr::Get_Instance()->Find_Image(L"Level");
	HDC  SHOPHDC= CBmpMgr::Get_Instance()->Find_Image(L"Shop");
	HDC  INVENHDC = CBmpMgr::Get_Instance()->Find_Image(L"Inven");
	HDC  SKILLBOOKHDC = CBmpMgr::Get_Instance()->Find_Image(L"SkillBook");
	HDC  SKILL1ICONHDC=CBmpMgr::Get_Instance()->Find_Image(L"Skill1Icon");
	HDC  SKILL2ICONHDC=CBmpMgr::Get_Instance()->Find_Image(L"Skill2Icon");
	HDC  SKILL3ICONHDC=CBmpMgr::Get_Instance()->Find_Image(L"Skill3Icon");
	HDC  SKILL4ICONHDC=CBmpMgr::Get_Instance()->Find_Image(L"Skill4Icon");
	HDC  EQUIPHDC = CBmpMgr::Get_Instance()->Find_Image(L"EquipUI");
	HDC  STATUSHDC = CBmpMgr::Get_Instance()->Find_Image(L"StatusUI");

	

	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();
	GdiTransparentBlt(hDC,312,WINCY - 80,172,66,STATEhdc,0,0,172,66,RGB(255, 0, 255));
	GdiTransparentBlt(hDC,340,WINCY - 72,10,12,LEVELhdc,10 * (CObjMgr::Get_Instance()->Get_Player()->Get_Status().m_iLv / 10),0,10,12,RGB(255, 0, 255));
	GdiTransparentBlt(hDC,350,WINCY - 72,10,12,LEVELhdc,10 * (CObjMgr::Get_Instance()->Get_Player()->Get_Status().m_iLv % 10),0,10,12,RGB(255, 0, 255));
	GdiTransparentBlt(hDC,336,WINCY-52,CObjMgr::Get_Instance()->Get_Player()->Get_Status().m_iHp / CObjMgr::Get_Instance()->Get_Player()->Get_Status().m_iLv,13,HPhdc,0,0,142,13,RGB(255, 0, 255));
	GdiTransparentBlt(hDC,336,WINCY - 36,CObjMgr::Get_Instance()->Get_Player()->Get_Status().m_iMp / CObjMgr::Get_Instance()->Get_Player()->Get_Status().m_iLv,13,MPhdc,0,0,142,13,RGB(255, 0, 255));
	GdiTransparentBlt(hDC,0,WINCY-12,800,10,EXPhdc,0,0,800,10,RGB(255, 0, 255));
	GdiTransparentBlt(hDC,16,WINCY - 12,int((CObjMgr::Get_Instance()->Get_Player()->Get_Status().m_iExp / CObjMgr::Get_Instance()->Get_Player()->Get_Status().m_iLv)*7.84f),9,NOWEXPhdc,0,0,784,9,RGB(255, 0, 255));
	GdiTransparentBlt(hDC,608,WINCY - 78,192,64,QUICKhdc,0,0,192,64,RGB(255, 0, 255));
	if (m_bShop)
	{
		GdiTransparentBlt(hDC,200,50,276,505,SHOPHDC,0,0,276,505,RGB(255, 0, 255));
		m_tRect = { 390, 90, 470, 110 };
		m_Exitrc = { 390, 120, 470, 140 };
		
		if (!m_bItemCreate)
		{
			CObjMgr::Get_Instance()->Add_Obj(OBJ_SHOP, CAbstractFactory<CShop>::Create(335, 195, PSKILL_END, HP));
			CObjMgr::Get_Instance()->Add_Obj(OBJ_SHOP, CAbstractFactory<CShop>::Create(335, 235, PSKILL_END, MP));
			CObjMgr::Get_Instance()->Add_Obj(OBJ_SHOP, CAbstractFactory<CShop>::Create(335, 275, PSKILL_END, WEAPON));
			CObjMgr::Get_Instance()->Add_Obj(OBJ_SHOP, CAbstractFactory<CShop>::Create(335, 315, PSKILL_END, WEAR));
			CObjMgr::Get_Instance()->Add_Obj(OBJ_SHOP, CAbstractFactory<CShop>::Create(335, 355, PSKILL_END, GLOVE));
			m_bItemCreate = true;
		}
	}
	if (m_bInven)
	{
		GdiTransparentBlt(hDC,500,150,172,335,INVENHDC,0,0,172,335,RGB(255, 0, 255));
		m_Invenrc = { 605,436,655,456 };
		TCHAR	szText[32] = L"";
		swprintf_s(szText, L" %d", CObjMgr::Get_Instance()->Get_Player()->Get_Money());
		SetBkMode(hDC, TRANSPARENT);	// Text 배경 투명하게
										//TextOut(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY, szText, lstrlen(szText));
		DrawText(hDC, szText, lstrlen(szText), &m_Invenrc, DT_CENTER);
	}
	if (m_bEquip)
	{
		GdiTransparentBlt(hDC, 300, 150, 184, 290, EQUIPHDC, 0, 0, 184, 290, RGB(255, 0, 255));
	}
	if (m_bStatus)
	{
		GdiTransparentBlt(hDC, 50, 150, 212, 318, STATUSHDC, 0, 0, 212, 318, RGB(255, 0, 255));
		RECT rcPoint = { 114,329,140,345 };
		TCHAR	szText1[32] = L"";
		swprintf_s(szText1, L" %d", CObjMgr::Get_Instance()->Get_Player()->Get_Status().m_iAbPoint);
		SetBkMode(hDC, TRANSPARENT);	
		DrawText(hDC, szText1, lstrlen(szText1), &rcPoint, DT_CENTER);
		RECT rcMp = { 134,287,200,303 };
		TCHAR	szText2[32] = L"";
		swprintf_s(szText2, L" %d / %d", CObjMgr::Get_Instance()->Get_Player()->Get_Status().m_iMp, CObjMgr::Get_Instance()->Get_Player()->Get_Status().m_iMaxMp);
		SetBkMode(hDC, TRANSPARENT);
		DrawText(hDC, szText2, lstrlen(szText2), &rcMp, DT_CENTER);
		RECT rcHp = { 134,269,200,285 };
		TCHAR	szText3[32] = L"";
		swprintf_s(szText3, L" %d / %d", CObjMgr::Get_Instance()->Get_Player()->Get_Status().m_iHp, CObjMgr::Get_Instance()->Get_Player()->Get_Status().m_iMaxHp);
		SetBkMode(hDC, TRANSPARENT);
		DrawText(hDC, szText3, lstrlen(szText3), &rcHp, DT_CENTER);
		RECT rcAttack = { 134,251,200,267 };
		TCHAR	szText4[32] = L"";
		swprintf_s(szText4, L" %d ", CObjMgr::Get_Instance()->Get_Player()->Get_Status().m_iDamage);
		SetBkMode(hDC, TRANSPARENT);
		DrawText(hDC, szText4, lstrlen(szText4), &rcAttack, DT_CENTER);
		RECT rcSTR = { 114,356,180,372 };
		TCHAR	szText5[32] = L"";
		swprintf_s(szText5, L" %d ", CObjMgr::Get_Instance()->Get_Player()->Get_Status().m_iSTR);
		SetBkMode(hDC, TRANSPARENT);
		DrawText(hDC, szText5, lstrlen(szText5), &rcSTR, DT_CENTER);
		RECT rcDEX = { 114,374,180,390 };
		TCHAR	szText6[32] = L"";
		swprintf_s(szText6, L" %d ", CObjMgr::Get_Instance()->Get_Player()->Get_Status().m_iDEX);
		SetBkMode(hDC, TRANSPARENT);
		DrawText(hDC, szText6, lstrlen(szText6), &rcDEX, DT_CENTER);
		RECT rcINT = { 114,392,180,408 };
		TCHAR	szText7[32] = L"";
		swprintf_s(szText7, L" %d ", CObjMgr::Get_Instance()->Get_Player()->Get_Status().m_iINT);
		SetBkMode(hDC, TRANSPARENT);
		DrawText(hDC, szText7, lstrlen(szText7), &rcINT, DT_CENTER);
		RECT rcLUK = { 114,410,180,426 };
		TCHAR	szText8[32] = L"";
		swprintf_s(szText8, L" %d ", CObjMgr::Get_Instance()->Get_Player()->Get_Status().m_iLUK);
		SetBkMode(hDC, TRANSPARENT);
		DrawText(hDC, szText8, lstrlen(szText8), &rcLUK, DT_CENTER);

		if (CObjMgr::Get_Instance()->Get_Player()->Get_Status().m_iAbPoint > 0)
		{
			if (!m_bStBt1)
			{
				CObjMgr::Get_Instance()->Add_Obj(OBJ_BUTTONS, CAbstractFactory<CButtons>::Create(244, 364, PORTAL_END, ITEM_END, STATUS_BUTTON1));
				m_bStBt1 = true;
			}
			if (!m_bStBt2)
			{
				CObjMgr::Get_Instance()->Add_Obj(OBJ_BUTTONS, CAbstractFactory<CButtons>::Create(244, 382, PORTAL_END, ITEM_END, STATUS_BUTTON2));
				m_bStBt2 = true;
			}
			if (!m_bStBt3)
			{
				CObjMgr::Get_Instance()->Add_Obj(OBJ_BUTTONS, CAbstractFactory<CButtons>::Create(244, 400, PORTAL_END, ITEM_END, STATUS_BUTTON3));
				m_bStBt3 = true;
			}
			if (!m_bStBt4)
			{
				CObjMgr::Get_Instance()->Add_Obj(OBJ_BUTTONS, CAbstractFactory<CButtons>::Create(244, 418, PORTAL_END, ITEM_END, STATUS_BUTTON4));
				m_bStBt4 = true;
			}
			if (!m_bStBt5)
			{
				CObjMgr::Get_Instance()->Add_Obj(OBJ_BUTTONS, CAbstractFactory<CButtons>::Create(210, 330, PORTAL_END, ITEM_END, STATUS_AUTO));
				m_bStBt5 = true;
			}
		}	
	}
	if (m_bSkillBook)
	{
		SkillOn1 = static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_Skill1();
		SkillOn2 = static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_Skill2();
		SkillOn3 = static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_Skill3();
		SkillOn4 = static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_Skill4();
		if (SkillOn1 >= 1)
			SkillOn1 = 1;
		else
			SkillOn1 = 0;
		if (SkillOn2 >= 1)
			SkillOn2 = 1;
		else
			SkillOn2 = 0;
		if (SkillOn3 >= 1)
			SkillOn3 = 1;
		else
			SkillOn3 = 0;
		if (SkillOn4 >= 1)
			SkillOn4 = 1;
		else
			SkillOn4 = 0;
		GdiTransparentBlt(hDC,500,150,174,300,SKILLBOOKHDC,0,0,174,300,RGB(0, 255, 0));
		GdiTransparentBlt(hDC,512,245,32,32,SKILL1ICONHDC,32* SkillOn1,0,32,32,RGB(0, 255, 0));
		m_rc1 = { 512,245,544,277 };
		GdiTransparentBlt(hDC,512,285,32,32,SKILL2ICONHDC,32 * SkillOn2,0,32,32,RGB(0, 255, 0));
		m_rc2 = { 512,285,544,317 };
		GdiTransparentBlt(hDC,512,325,32,32,SKILL3ICONHDC,32 * SkillOn3,0,32,32,RGB(0, 255, 0));
		m_rc3 = { 512,325,544,357 };
		GdiTransparentBlt(hDC,512,365,32,32,SKILL4ICONHDC,32 * SkillOn4,0,32,32,RGB(0, 255, 0));
		m_rc4 = { 512,365,544,397 };
		if (PtInRect(&(m_rc1), pt)&&CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON)&&SkillOn1)
		{
			static_cast<CMouse*>(CObjMgr::Get_Instance()->Get_Mouse())->Set_Grab(true);
			CObjMgr::Get_Instance()->Get_Mouse()->Set_Skill(PSKILL1);
		}
		else if (PtInRect(&(m_rc2), pt)&&CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON) && SkillOn2)
		{
			static_cast<CMouse*>(CObjMgr::Get_Instance()->Get_Mouse())->Set_Grab(true);
			CObjMgr::Get_Instance()->Get_Mouse()->Set_Skill(PSKILL2);
		}
		else if (PtInRect(&(m_rc3), pt)&&CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON) && SkillOn3)
		{
			static_cast<CMouse*>(CObjMgr::Get_Instance()->Get_Mouse())->Set_Grab(true);
			CObjMgr::Get_Instance()->Get_Mouse()->Set_Skill(PSKILL3);
		}
		else if (PtInRect(&(m_rc4), pt)&&CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON) && SkillOn4)
		{
			static_cast<CMouse*>(CObjMgr::Get_Instance()->Get_Mouse())->Set_Grab(true);
			CObjMgr::Get_Instance()->Get_Mouse()->Set_Skill(PSKILL4);
		}

		m_tRect = { 632,405,652,425 };
		TCHAR	szText[32] = L"";
		swprintf_s(szText, L" %d", CObjMgr::Get_Instance()->Get_Player()->Get_SkillPoint());
		SetBkMode(hDC, TRANSPARENT);	// Text 배경 투명하게
										//TextOut(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY, szText, lstrlen(szText));
		DrawText(hDC, szText, lstrlen(szText), &m_tRect, DT_CENTER);
		if (CObjMgr::Get_Instance()->Get_Player()->Get_SkillPoint() > 0)
		{
			if (!m_bSkBt1)
			{
				CObjMgr::Get_Instance()->Add_Obj(OBJ_BUTTONS, CAbstractFactory<CButtons>::Create(643, 269, PORTAL_END, ITEM_END, SKILL_BUTTON1));
				m_bSkBt1 = true;
			}
			if (!m_bSkBt2)
			{
				CObjMgr::Get_Instance()->Add_Obj(OBJ_BUTTONS, CAbstractFactory<CButtons>::Create(643, 309, PORTAL_END, ITEM_END, SKILL_BUTTON2));
				m_bSkBt2 = true;
			}
			if (!m_bSkBt3)
			{
				CObjMgr::Get_Instance()->Add_Obj(OBJ_BUTTONS, CAbstractFactory<CButtons>::Create(643, 349, PORTAL_END, ITEM_END, SKILL_BUTTON3));
				m_bSkBt3 = true;
			}
			if (!m_bSkBt4)
			{
				CObjMgr::Get_Instance()->Add_Obj(OBJ_BUTTONS, CAbstractFactory<CButtons>::Create(643, 389, PORTAL_END, ITEM_END, SKILL_BUTTON4));
				m_bSkBt4 = true;
			}
		}
	}

}

void CUi::Release(void)
{
	CObjMgr::Get_Instance()->Delete_Obj(OBJ_BUTTONS);
}
