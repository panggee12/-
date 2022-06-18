#include "stdafx.h"
#include "Lobby.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Buttons.h"

CLobby::CLobby()
{
	m_tStage = STAGE_LOBBY;
}


CLobby::~CLobby()
{
	Release();
}

void CLobby::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Title/title2.bmp", L"LOBBY");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Button/loginBt.bmp", L"LOGINBT");

	CObj* m_pButton = CAbstractFactory<CButtons>::Create(477, 306, PORTAL_END, ITEM_END, LOBBY_BUTTON);
	m_pButton->Set_key(L"LOGINBT");

	CObjMgr::Get_Instance()->Add_Obj(OBJ_BUTTONS, m_pButton);

}
int CLobby::Update(void)
{
	CObjMgr::Get_Instance()->Update();
	
	return 0;
}

void CLobby::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CLobby::Render(HDC hDC)
{
	HDC	LOBBYHDC = CBmpMgr::Get_Instance()->Find_Image(L"LOBBY");
	
	BitBlt(hDC,
		0,
		0,
		WINCX,
		WINCY,
		LOBBYHDC,
		0,
		0,
		SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);
}

void CLobby::Release(void)
{
	CObjMgr::Get_Instance()->Delete_Obj(OBJ_BUTTONS);
}
