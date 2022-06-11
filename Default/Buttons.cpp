#include "stdafx.h"
#include "Buttons.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "ObjMgr.h"
CButtons::CButtons()
{
}


CButtons::~CButtons()
{
}

void CButtons::Initialize(void)
{
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;

	
}

int CButtons::Update(void)
{

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
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON))
		{
			if(!lstrcmp(m_framekey,L"LOGINBT"))
				CSceneMgr::Get_Instance()->Scene_Change(STAGE_1);
			return;
		}
		
		m_iDrawid = 1;
	}
	else
		m_iDrawid = 0;
}

void CButtons::Render(HDC hDC)
{
	HDC LOGINHDC=CBmpMgr::Get_Instance()->Find_Image(m_framekey);

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

void CButtons::Release(void)
{
}
