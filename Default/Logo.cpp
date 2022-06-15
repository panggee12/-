#include "stdafx.h"
#include "Logo.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "Mouse.h"
CLogo::CLogo()
{
	m_tStage = STAGE_LOGO;
}


CLogo::~CLogo()
{
}

void CLogo::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image_Maple/Logo.bmp", L"LOGO");

	
	CObj* m_pMouse = CAbstractFactory<CMouse>::Create();
	m_pMouse->Set_key(L"MOUSE");

	CObjMgr::Get_Instance()->Add_Obj(OBJ_MOUSE, m_pMouse);
}

int CLogo::Update(void)
{
	CObjMgr::Get_Instance()->Update();
	return 0;
}

void CLogo::Late_Update(void)
{
	
	if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
	{
		CObjMgr::Get_Instance()->Late_Update();
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

	CObjMgr::Get_Instance()->Render(hDC);
}

void CLogo::Release(void)
{
}
