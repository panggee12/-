#include "stdafx.h"
#include "Logo.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
CLogo::CLogo()
{
}


CLogo::~CLogo()
{
}

void CLogo::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image_Maple/Logo.bmp", L"LOGO");
}

int CLogo::Update(void)
{
	
	return 0;
}

void CLogo::Late_Update(void)
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		CSceneMgr::Get_Instance()->Scene_Change(STAGE_LOBBY);
		return;
	}

}

void CLogo::Render(HDC hDC)
{
	HDC m_LOGOHDC = CBmpMgr::Get_Instance()->Find_Image(L"LOGO");


	BitBlt(hDC,
		0,
		0,
		WINCX,
		WINCY,
		m_LOGOHDC,
		0,
		0,
		SRCCOPY);
}

void CLogo::Release(void)
{
}