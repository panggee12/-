#include "stdafx.h"
#include "MainGame.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"
#include "LineMgr.h"
#include "AbstractFactory.h"
CMainGame::CMainGame():m_dwTime(GetTickCount()),m_iFPS(0)
{
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_hDC = GetDC(g_hWnd);

	CSceneMgr::Get_Instance()->Scene_Change(STAGE_3);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image_Maple/Back.bmp", L"Back");
	
}

void CMainGame::Update(void)
{
	CSceneMgr::Get_Instance()->Update();
}

void CMainGame::Late_Update(void)
{
	CSceneMgr::Get_Instance()->Late_Update();
}

void CMainGame::Render(void)
{
	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();
	++m_iFPS;

	if (m_dwTime + 500 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}

	HDC backHDC = CBmpMgr::Get_Instance()->Find_Image(L"Back");

	CSceneMgr::Get_Instance()->Render(backHDC);

	BitBlt(m_hDC,
		0,
		0,
		WINCX,
		WINCY,
		backHDC,
		0,
		0,
		SRCCOPY);
	
}

void CMainGame::Release(void)
{
	CSceneMgr::Get_Instance()->Destroy_Instance();
	CBmpMgr::Get_Instance()->Destroy_Instance();
	CObjMgr::Get_Instance()->Destroy_Instance();
	CScrollMgr::Get_Instance()->Destroy_Instance();
	CKeyMgr::Get_Instance()->Destroy_Instance();
	CLineMgr::Get_Instance()->Destroy_Instance();
	ReleaseDC(g_hWnd, m_hDC);
}
