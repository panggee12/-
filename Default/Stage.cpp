#include "stdafx.h"
#include "Stage.h"
#include "BmpMgr.h"
#include "Obj.h"
#include "AbstractFactory.h"
#include "Player.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "ScrollMgr.h"
#include "Ui.h"
CStage::CStage()
{
	m_tStage = STAGE_1;
	CLineMgr::Get_Instance()->Load_File(m_tStage);
	//CLineMgr::Get_Instance()->Load_File_Portal(m_tStage);
	CObjMgr::Get_Instance()->Add_Obj(OBJ_BLOCK, CAbstractFactory<CBlock>::Create(690, 400,PORTAL1));
	
}


CStage::~CStage()
{
	Release();
}

void CStage::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Map/00_special.bmp", L"STAGE1");

	CObj* m_pPlayer = CAbstractFactory<CPlayer>::Create();
	
	if (CObjMgr::Get_Instance()->Get_Player_List()->empty())
		CObjMgr::Get_Instance()->Add_Obj(OBJ_PLAYER, m_pPlayer);
	else
		CObjMgr::Get_Instance()->Get_Player()->Set_Pos(400, 400);

	
}

int CStage::Update(void)
{
	CObjMgr::Get_Instance()->Update();
	CLineMgr::Get_Instance()->Update();
	CScrollMgr::Get_Instance()->Scroll_Lock(800, 600);
	

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
	CLineMgr::Get_Instance()->Render(hDC);
}

void CStage::Release(void)
{
	CObjMgr::Get_Instance()->Delete_Obj(OBJ_BLOCK);
	CLineMgr::Get_Instance()->Destroy_Instance();
}
