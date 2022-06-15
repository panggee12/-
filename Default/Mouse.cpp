#include "stdafx.h"
#include "Mouse.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
CMouse::CMouse():m_iDrawID(0),m_bGrab(false)
{
}


CMouse::~CMouse()
{
}

void CMouse::Initialize(void)
{
	m_tInfo.fCX = 32.f;
	m_tInfo.fCY = 32.f;
	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Mouse/cursor.bmp", L"MOUSE");
	/*CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Icon/ann.bmp", L"Skill1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Icon/ascend.bmp", L"Skill2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Icon/bolt.bmp", L"Skill3");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Icon/buf.bmp", L"Skill4");*/
	
}

int CMouse::Update(void)
{
	if (m_tSkill == PSKILL1)
		m_framekey = L"Skill1";
	else if (m_tSkill == PSKILL2)
		m_framekey = L"Skill2";
	else if (m_tSkill == PSKILL3)
		m_framekey = L"Skill3";
	else if (m_tSkill == PSKILL4)
		m_framekey = L"Skill4";
	pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	m_tInfo.fX = pt.x;
	m_tInfo.fY = pt.y;
	ShowCursor(false);
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON))
	{
		m_iDrawID = 1;
	}
	else
		m_iDrawID = 0;
	Update_Rect();
	return OBJ_NOEVENT;
}

void CMouse::Late_Update(void)
{
}

void CMouse::Render(HDC hDC)
{
	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC MOUSEHDC=CBmpMgr::Get_Instance()->Find_Image(L"MOUSE");
	HDC ICONHDC = CBmpMgr::Get_Instance()->Find_Image(m_framekey);
	if (m_bGrab)
	{
		GdiTransparentBlt(hDC,
			pt.x,
			pt.y,
			32,
			32,
			ICONHDC,
			0,
			0,
			32,
			32,
			RGB(255, 0, 255));
	}

	GdiTransparentBlt(hDC,
		pt.x ,
		pt.y ,
		int(m_tInfo.fCX),
		int(m_tInfo.fCY),
		MOUSEHDC,
		0,
		m_tInfo.fCY*m_iDrawID,
		(int)m_tInfo.fCX,
		int(m_tInfo.fCY),
		RGB(255, 0, 255));

	TCHAR m_szBuff[32] = L"";
	swprintf_s(m_szBuff, L"X : %f Y : %f", float(pt.x)-iScrollX,float(pt.y)-iScrollY);
	TextOut(hDC, float(pt.x), float(pt.y), m_szBuff, lstrlen(m_szBuff));
}

void CMouse::Release(void)
{
}
