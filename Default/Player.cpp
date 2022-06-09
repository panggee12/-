#include "stdafx.h"
#include "Player.h"
#include "BmpMgr.h"
CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tInfo = { 400.f, 300.f, 100.f, 100.f };
	m_fSpeed = 10.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Character/Striker/basic_left.bmp", L"PLAYERLEFT");
}

int CPlayer::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Key_Input();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
}

void CPlayer::Render(HDC hDC)
{
	HDC PLAYERLEFT=CBmpMgr::Get_Instance()->Find_Image(L"PLAYERLEFT");

	GdiTransparentBlt(hDC,
		int(m_tRect.left),
		int(m_tRect.top),
		int(m_tInfo.fCX),
		int(m_tInfo.fCY),
		PLAYERLEFT,
		m_iDrawid * (int)m_tInfo.fCX,
		0,
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
	if (GetAsyncKeyState(VK_RIGHT))
		m_tInfo.fX += m_fSpeed;

	if (GetAsyncKeyState(VK_LEFT))
		m_tInfo.fX -= m_fSpeed;

	if (GetAsyncKeyState(VK_UP))
		m_tInfo.fY -= m_fSpeed;

	if (GetAsyncKeyState(VK_DOWN))
		m_tInfo.fY += m_fSpeed;
}