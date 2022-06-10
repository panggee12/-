#include "stdafx.h"
#include "Stage2.h"
#include "LineMgr.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"
#include "AbstractFactory.h"
#include "Player.h"
CStage2::CStage2()
{
	m_tStage = STAGE_2;
	CLineMgr::Get_Instance()->Load_File(m_tStage);
	//CLineMgr::Get_Instance()->Load_File_Portal(m_tStage);
}


CStage2::~CStage2()
{
}

void CStage2::Initialize(void)
{

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Map/01_hunt.bmp", L"STAGE2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Map/back.bmp", L"Back2");
	//CObjMgr::Get_Instance()->Get_Player()->Set_Pos()
	m_tFrame.iFrameStart = 0;
	m_tFrame.iMotion = 1;
	m_tInfo.fCX = 800;
	m_tInfo.fCY = 600;
	CObj* m_pPlayer = CAbstractFactory<CPlayer>::Create();

	CObjMgr::Get_Instance()->Add_Obj(OBJ_PLAYER, m_pPlayer);
}

int CStage2::Update(void)
{
	CObjMgr::Get_Instance()->Update();
	CLineMgr::Get_Instance()->Update();
	
	CScrollMgr::Get_Instance()->Scroll_Lock();
	return 0;
}

void CStage2::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CStage2::Render(HDC hDC)
{
	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC STAGE2HDC = CBmpMgr::Get_Instance()->Find_Image(L"STAGE2");
	HDC BACK2HDC = CBmpMgr::Get_Instance()->Find_Image(L"Back2");

	BitBlt(hDC,
		0,
		0,
		WINCX,
		WINCY,
		BACK2HDC,
		0,
		0,
		SRCCOPY);
	/*GdiTransparentBlt(hDC,
		0,
		0,
		800,
		600,
		STAGE2HDC,
		-iScrollX,
		400-iScrollY,
		800,
		600,
		RGB(255, 0, 255));*/

	GdiTransparentBlt(hDC,
		iScrollX,
		iScrollY - 500,
		1440,
		1149,
		STAGE2HDC,
		0,
		0,
		1440,
		1149,
		RGB(255, 0, 255));

	CObjMgr::Get_Instance()->Render(hDC);
	//CLineMgr::Get_Instance()->Render(hDC);
}

void CStage2::Release(void)
{
	CObjMgr::Get_Instance()->Delete_Obj(OBJ_BLOCK);
}
