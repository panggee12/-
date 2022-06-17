#include "stdafx.h"
#include "Stage2.h"
#include "LineMgr.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"
#include "AbstractFactory.h"
#include "Player.h"
#include "Monster.h"
#include "UI.h"
CStage2::CStage2()
{
	m_tStage = STAGE_2;
	CLineMgr::Get_Instance()->Load_File(m_tStage);
	CLineMgr::Get_Instance()->Load_File_Rofe(m_tStage);
	CObjMgr::Get_Instance()->Add_Obj(OBJ_BLOCK, CAbstractFactory<CBlock>::Create(1380, 830, PORTAL2));//89 257
	CObjMgr::Get_Instance()->Add_Obj(OBJ_BLOCK, CAbstractFactory<CBlock>::Create(50, 830, PORTAL2_1));
	for (int i = 0; i < 10; ++i)
	{
		CObj* m_pMonster = CAbstractFactory<CMonster>::Create();

		CObjMgr::Get_Instance()->Add_Obj(OBJ_MONSTER, m_pMonster);
	}

}


CStage2::~CStage2()
{
	Release();
}

void CStage2::Initialize(void)
{

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Map/01_hunt.bmp", L"STAGE2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Map/back.bmp", L"Back2");
	
	m_tFrame.iFrameStart = 0;
	m_tFrame.iMotion = 1;
	m_tInfo.fCX = 1440;
	m_tInfo.fCY = 1149;
	/*CObj* m_pPlayer = CAbstractFactory<CPlayer>::Create();

	CObjMgr::Get_Instance()->Add_Obj(OBJ_PLAYER, m_pPlayer);*/

	CObjMgr::Get_Instance()->Get_Player()->Set_Pos(50, 830);

	/*CObj* m_pUi = CAbstractFactory<CUi>::Create();

	CObjMgr::Get_Instance()->Add_Obj(OBJ_UI, m_pUi);*/

	
}

int CStage2::Update(void)
{
	CObjMgr::Get_Instance()->Update();
	CLineMgr::Get_Instance()->Update();
	
	CScrollMgr::Get_Instance()->Scroll_Lock(1440,1149);
	if (CObjMgr::Get_Instance()->Get_Monster()->size() != 10&&m_bFullStage)
	{
		m_dwRespawn = GetTickCount();
		m_bFullStage = false;
	}

	if (!m_bFullStage && m_dwRespawn + 5000 < GetTickCount())
	{
		while (CObjMgr::Get_Instance()->Get_Monster()->size() != 10)
		{
			if (CObjMgr::Get_Instance()->Get_Monster()->size() >= 10)
				break;
			CObj* m_pMonster = CAbstractFactory<CMonster>::Create();

			CObjMgr::Get_Instance()->Add_Obj(OBJ_MONSTER, m_pMonster);
		}
		m_bFullStage = true;
	}
	return 0;
}

void CStage2::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
	for (auto& iter = CObjMgr::Get_Instance()->Get_Monster()->begin(); iter != CObjMgr::Get_Instance()->Get_Monster()->end(); ++iter)
	{
		if ((*iter)->Get_Info().fX < 100)
			(*iter)->Set_PosX(2);
		else if ((*iter)->Get_Info().fX > m_tInfo.fCX - 100)
			(*iter)->Set_PosX(-2);
	}
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

	GdiTransparentBlt(hDC,
		iScrollX,
		iScrollY,
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
	CObjMgr::Get_Instance()->Delete_Obj(OBJ_MONSTER);
	CObjMgr::Get_Instance()->Delete_Obj(OBJ_ITEM);
	CLineMgr::Get_Instance()->Destroy_Instance();
}
