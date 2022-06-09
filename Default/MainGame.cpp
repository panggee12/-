#include "stdafx.h"
#include "MainGame.h"


CMainGame::CMainGame()
{
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_hDC = GetDC(g_hWnd);


}

void CMainGame::Update(void)
{

}

void CMainGame::Render(void)
{

}

void CMainGame::Release(void)
{

	ReleaseDC(g_hWnd, m_hDC);
}
