#include "stdafx.h"
#include "Ui.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "Player.h"
#include "AbstractFactory.h"
#include "Buttons.h"
CUi::CUi():m_bShop(false), m_bInven(false), m_bSkillBook(false)
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
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Ui/shopitem_0.bmp", L"Shop");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Ui/Inven.bmp", L"Inven");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Ui/SkillBook.bmp", L"SkillBook");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Icon/Skill1Icon.bmp", L"Skill1Icon");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Icon/Skill2Icon.bmp", L"Skill2Icon");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Icon/Skill3Icon.bmp", L"Skill3Icon");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Icon/buf.bmp", L"Skill4Icon");
	

}

int CUi::Update(void)
{
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
	

	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();
	GdiTransparentBlt(hDC,
		312,
		WINCY-80,
		172,
		66,
		STATEhdc,
		0,
		0,
		172,
		66,
		RGB(255, 0, 255));
	GdiTransparentBlt(hDC,
		340,
		WINCY - 72,
		10,
		12,
		LEVELhdc,
		10 * (CObjMgr::Get_Instance()->Get_Player()->Get_Status().m_iLv / 10),
		0,
		10,
		12,
		RGB(255, 0, 255));
	GdiTransparentBlt(hDC,
		350,
		WINCY - 72,
		10,
		12,
		LEVELhdc,
		10 * (CObjMgr::Get_Instance()->Get_Player()->Get_Status().m_iLv % 10),
		0,
		10,
		12,
		RGB(255, 0, 255));
	GdiTransparentBlt(hDC,
		336,
		WINCY-52,
		142,
		13,
		HPhdc,
		0,
		0,
		CObjMgr::Get_Instance()->Get_Player()->Get_Status().m_iHp/CObjMgr::Get_Instance()->Get_Player()->Get_Status().m_iLv,
		13,
		RGB(255, 0, 255));
	GdiTransparentBlt(hDC,
		336,
		WINCY - 36,
		142,
		13,
		MPhdc,
		0,
		0,
		CObjMgr::Get_Instance()->Get_Player()->Get_Status().m_iMp / CObjMgr::Get_Instance()->Get_Player()->Get_Status().m_iLv,
		13,
		RGB(255, 0, 255));
	GdiTransparentBlt(hDC,
		0,
		WINCY-12,
		800,
		10,
		EXPhdc,
		0,
		0,
		800,
		10,
		RGB(255, 0, 255));
	GdiTransparentBlt(hDC,
		16,
		WINCY - 12,
		int((CObjMgr::Get_Instance()->Get_Player()->Get_Status().m_iExp / CObjMgr::Get_Instance()->Get_Player()->Get_Status().m_iLv)*7.84f),
		9,
		NOWEXPhdc,
		0,
		0,
		784,
		9,
		RGB(255, 0, 255));
	GdiTransparentBlt(hDC,
		608,
		WINCY - 78,
		192,
		64,
		QUICKhdc,
		0,
		0,
		192,
		64,
		RGB(255, 0, 255));
	if (m_bShop)
	{
		GdiTransparentBlt(hDC,
			200,
			50,
			508,
			505,
			SHOPHDC,
			0,
			0,
			508,
			505,
			RGB(255, 0, 255));
		m_tRect = { 390, 90, 470, 110 };
	}
	if (m_bInven)
	{
		GdiTransparentBlt(hDC,
			500,
			150,
			172,
			335,
			INVENHDC,
			0,
			0,
			172,
			335,
			RGB(255, 0, 255));
	}
	if (m_bSkillBook)
	{
		GdiTransparentBlt(hDC,
			500,
			150,
			174,
			300,
			SKILLBOOKHDC,
			0,
			0,
			174,
			300,
			RGB(0, 255, 0));
		GdiTransparentBlt(hDC,
			512,
			245,
			32,
			32,
			SKILL1ICONHDC,
			32*static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_Skill1(),
			0,
			32,
			32,
			RGB(0, 255, 0));
		GdiTransparentBlt(hDC,
			512,
			285,
			32,
			32,
			SKILL2ICONHDC,
			32 * static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_Skill2(),
			0,
			32,
			32,
			RGB(0, 255, 0));
		GdiTransparentBlt(hDC,
			512,
			325,
			32,
			32,
			SKILL3ICONHDC,
			32 * static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_Skill3(),
			0,
			32,
			32,
			RGB(0, 255, 0));
		GdiTransparentBlt(hDC,
			512,
			365,
			32,
			32,
			SKILL4ICONHDC,
			32 * static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_Skill4(),
			0,
			32,
			32,
			RGB(0, 255, 0));
		if (CObjMgr::Get_Instance()->Get_Player()->Get_SkillPoint() > 0)
		{
			CObjMgr::Get_Instance()->Add_Obj(OBJ_BUTTONS, CAbstractFactory<CButtons>::Create(643, 269, PORTAL_END, ITEM_END, SKILL_BUTTON1));
			CObjMgr::Get_Instance()->Add_Obj(OBJ_BUTTONS, CAbstractFactory<CButtons>::Create(643, 269, PORTAL_END, ITEM_END, SKILL_BUTTON2));
			CObjMgr::Get_Instance()->Add_Obj(OBJ_BUTTONS, CAbstractFactory<CButtons>::Create(643, 269, PORTAL_END, ITEM_END, SKILL_BUTTON3));
			CObjMgr::Get_Instance()->Add_Obj(OBJ_BUTTONS, CAbstractFactory<CButtons>::Create(643, 269, PORTAL_END, ITEM_END, SKILL_BUTTON4));
		}
	}

}

void CUi::Release(void)
{
}
