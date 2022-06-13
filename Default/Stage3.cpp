#include "stdafx.h"
#include "Stage3.h"
#include "LineMgr.h"
#include "BmpMgr.h"
#include "AbstractFactory.h"
#include "Player.h"
#include "ObjMgr.h"
#include "Ui.h"
#include "ScrollMgr.h"
CStage3::CStage3()
{
	m_tStage = STAGE_3;
	CLineMgr::Get_Instance()->Load_File(m_tStage);
	CLineMgr::Get_Instance()->Load_File_Rofe(m_tStage);
	CObjMgr::Get_Instance()->Add_Obj(OBJ_BLOCK, CAbstractFactory<CBlock>::Create(1830, 680, PORTAL3));
}


CStage3::~CStage3()
{
}

void CStage3::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Map/03_town_level.bmp", L"STAGE3");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Map/back.bmp", L"Back3");

	m_tInfo.fCX = 1949;
	m_tInfo.fCY = 940;

	CObj* m_pPlayer = CAbstractFactory<CPlayer>::Create();

	CObjMgr::Get_Instance()->Add_Obj(OBJ_PLAYER, m_pPlayer);

	CObjMgr::Get_Instance()->Get_Player()->Set_Pos(150, -100);

	CObj* m_pUi = CAbstractFactory<CUi>::Create();

	CObjMgr::Get_Instance()->Add_Obj(OBJ_UI, m_pUi);
}

int CStage3::Update(void)
{
	CObjMgr::Get_Instance()->Update();
	CLineMgr::Get_Instance()->Update();

	CScrollMgr::Get_Instance()->Scroll_Lock(m_tInfo.fCX, m_tInfo.fCY);
	return 0;
}

void CStage3::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CStage3::Render(HDC hDC)
{
	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC STAGE3HDC = CBmpMgr::Get_Instance()->Find_Image(L"STAGE3");
	HDC BACK3HDC = CBmpMgr::Get_Instance()->Find_Image(L"Back3");

	BitBlt(hDC,
		0,
		0,
		WINCX,
		WINCY,
		BACK3HDC,
		0,
		0,
		SRCCOPY);

	GdiTransparentBlt(hDC,
		iScrollX,
		iScrollY,
		m_tInfo.fCX,
		m_tInfo.fCY,
		STAGE3HDC,
		0,
		0,
		m_tInfo.fCX,
		m_tInfo.fCY,
		RGB(255, 0, 255));

	CObjMgr::Get_Instance()->Render(hDC);
	CLineMgr::Get_Instance()->Render(hDC);
}

void CStage3::Release(void)
{
	CObjMgr::Get_Instance()->Delete_Obj(OBJ_BLOCK);
	CLineMgr::Get_Instance()->Destroy_Instance();
}
