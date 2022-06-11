#include "stdafx.h"
#include "Ui.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
CUi::CUi()
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
}

void CUi::Release(void)
{
}
