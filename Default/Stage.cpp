#include "stdafx.h"
#include "Stage.h"
#include "BmpMgr.h"
#include "Obj.h"
#include "AbstractFactory.h"
#include "Player.h"
#include "ObjMgr.h"
CStage::CStage()
{
}


CStage::~CStage()
{
}

void CStage::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Map/00_special.bmp", L"STAGE1");

	CObj* m_pPlayer = CAbstractFactory<CPlayer>::Create();
	
	CObjMgr::Get_Instance()->Add_Obj(OBJ_PLAYER,m_pPlayer);
}

int CStage::Update(void)
{
	CObjMgr::Get_Instance()->Update();
	return 0;
}

void CStage::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CStage::Render(HDC hDC)
{
	HDC STAGE1HDC=CBmpMgr::Get_Instance()->Find_Image(L"STAGE1");

	BitBlt(hDC,
		0,
		0,
		WINCX,
		WINCY,
		STAGE1HDC,
		0,
		0,
		SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);
}

void CStage::Release(void)
{
}
