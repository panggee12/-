#include "stdafx.h"
#include "Mouse.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
CMouse::CMouse():m_iDrawID(0)
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
}

int CMouse::Update(void)
{
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
