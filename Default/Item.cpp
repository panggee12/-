#include "stdafx.h"
#include "Item.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
CItem::CItem() : m_dwUPDOWN(GetTickCount()), m_bDrop(false), m_ItemCheck(false), m_iRand(0)
{
}


CItem::~CItem()
{
}

void CItem::Initialize(void)
{
	m_tInfo.fCX = 32.f;
	m_tInfo.fCY = 32.f;
	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Item/meso3.bmp", L"Money");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Item/hptest2.bmp", L"Hpportion");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Item/mptest.bmp", L"Mpportion");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Item/weapon1.bmp", L"Weapon");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Item/wear1.bmp", L"Wear");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Item/glove.bmp", L"Glove");
	m_iRand = rand() % 3;
}

int CItem::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;
	/*if ((!m_bDrop&&m_tItem == HP) || (!m_bDrop&&m_tItem == MP))
	{
		if (m_iPortionCount < 0)
			m_tItem = ITEM_END;
	}*/
	
	if (m_bDrop)
	{
		m_tInfo.fY -= m_fSpeed;		
		if (m_dwUPDOWN + 1200 < GetTickCount())
		{
			m_fSpeed *= -1.f;
			m_dwUPDOWN = GetTickCount();
		}
		Move_Frame();	
		if (!m_ItemCheck)
		{
			m_tItem = ITEMID(m_iRand);
			m_fSpeed = 0.3f;
			if (m_tItem == MONEY)
			{
				m_tInfo.fCX = 30.f;
				m_tInfo.fCY = 29.f; 
				

				m_tFrame.iMotion = 0;
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 3;

				m_tFrame.dwFrameSpeed = 200;
				m_tFrame.dwFrameTime = GetTickCount();

				m_iMoney = rand() % 100 + 1000;
				m_framekey = L"Money";
				
			}
		}

	}
	if (m_tItem == HP)
		m_framekey = L"Hpportion";
	else if (m_tItem == MP)
		m_framekey = L"Mpportion";
	else if (m_tItem == WEAPON)
		m_framekey = L"Weapon";
	else if (m_tItem == WEAR)
		m_framekey = L"Wear";
	else if (m_tItem == GLOVE)
		m_framekey = L"Glove";
	else if (m_tItem == MONEY)
		m_framekey = L"Money";
	else
		m_framekey = L"";
	Update_Rect();
	return OBJ_NOEVENT;
}

void CItem::Late_Update(void)
{
	
}

void CItem::Render(HDC hDC)
{
	HDC ITEMHDC = CBmpMgr::Get_Instance()->Find_Image(m_framekey);

	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();
	this;
	if (m_bDrop&&m_tItem == MONEY)
		GdiTransparentBlt(hDC,
			int(m_tRect.left) + iScrollX,
			int(m_tRect.top) - 10 + iScrollY,
			int(m_tInfo.fCX),
			int(m_tInfo.fCY),
			ITEMHDC,
			m_tFrame.iFrameStart*m_tInfo.fCX,
			m_tFrame.iMotion*m_tInfo.fCY,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));
	else if(m_bDrop&&m_tItem != MONEY)
		GdiTransparentBlt(hDC,
			int(m_tRect.left) + iScrollX,
			int(m_tRect.top) - 10 + iScrollY,
			int(m_tInfo.fCX),
			int(m_tInfo.fCY),
			ITEMHDC,
			0,
			0,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(255, 255, 255));
	else if (m_tItem == HP || m_tItem == MP)
	{

		GdiTransparentBlt(hDC,
			int(m_tRect.left),
			int(m_tRect.top),
			int(m_tInfo.fCX),
			int(m_tInfo.fCY),
			ITEMHDC,
			0,
			0,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));
		if (m_iPortionCount > 1)
		{
			TCHAR	szText[32] = L"";
			swprintf_s(szText, L" %d", m_iPortionCount);
			SetBkMode(hDC, TRANSPARENT);	// Text 배경 투명하게
											//TextOut(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY, szText, lstrlen(szText));
			DrawText(hDC, szText, lstrlen(szText), &m_tRect, DT_RIGHT);
		}
	}
	else
		GdiTransparentBlt(hDC,
			int(m_tRect.left),
			int(m_tRect.top),
			int(m_tInfo.fCX),
			int(m_tInfo.fCY),
			ITEMHDC,
			0,
			0,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));
	
	
}

void CItem::Release(void)
{
}
