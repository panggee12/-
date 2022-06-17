#include "stdafx.h"
#include "Icon.h"
#include "BmpMgr.h"

CIcon::CIcon()
{
}


CIcon::~CIcon()
{
}

void CIcon::Initialize(void)
{
	m_tInfo.fCX = 32.f;
	m_tInfo.fCY = 32.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Icon/ann.bmp", L"Skill1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Icon/ascend.bmp", L"Skill2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Icon/bolt.bmp", L"Skill3");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Icon/bufOnly.bmp", L"Skill4");	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Item/hptest2.bmp", L"Hpportion");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Item/mptest.bmp", L"Mpportion");
}

int CIcon::Update(void)
{

	if (m_tSkill == PSKILL1)
		m_framekey = L"Skill1";
	else if (m_tSkill == PSKILL2)
		m_framekey = L"Skill2";
	else if (m_tSkill == PSKILL3)
		m_framekey = L"Skill3";
	else if (m_tSkill == PSKILL4)
		m_framekey = L"Skill4";
	else if (m_tItem == HP)
		m_framekey = L"Hpportion";
	else if (m_tItem == MP)
		m_framekey = L"Mpportion";

	
	
	Update_Rect();
	return 0;
}

void CIcon::Late_Update(void)
{
}

void CIcon::Render(HDC hDC)
{
	HDC ICONHDC = CBmpMgr::Get_Instance()->Find_Image(m_framekey);
	GdiTransparentBlt(hDC,
		int(m_tRect.left),
		int(m_tRect.top),
		m_tInfo.fCX,
		m_tInfo.fCY,
		ICONHDC,
		0,
		0,
		m_tInfo.fCX,
		m_tInfo.fCY,
		RGB(255, 255, 255));
}

void CIcon::Release(void)
{
}
