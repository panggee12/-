#include "stdafx.h"
#include "QuickSlot.h"
#include "AbstractFactory.h"
#include "Icon.h"
#include "Mouse.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "inventory.h"
CQuickSlot::CQuickSlot()
{
}


CQuickSlot::~CQuickSlot()
{
	Release();
}

void CQuickSlot::Initialize(void)
{
	for (int i = 538; i <= 570; i+=32)
	{
		for (int j = 624; j < 800; j+=32)
		{
			CObj* pSlot = CAbstractFactory<CIcon>::Create(j, i, PSKILL_END,ITEM_END);
			m_vecSlot.push_back(pSlot);
		}
	}
}

int CQuickSlot::Update(void)
{
	for (auto& iter : m_vecSlot)
		iter->Update();

	if (static_cast<CMouse*>(CObjMgr::Get_Instance()->Get_Mouse())->Get_Grab())
	{
		POINT pt = {};
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd,&pt);
		int iArrayx = 0;
		int iArrayy = 0;
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			for (int i = 538; i <= 570; i += 32)
			{
				for (int j = 624; j < 800; j += 32)
				{
					
					if (pt.x >= j - 16 && pt.x <= j + 16)
						iArrayx = (pt.x - 624) / 32;
					if (pt.y >= i - 16 && pt.y <= i + 16)
						iArrayy = (pt.y - 538) / 32;
				}
			}
			if (pt.x > 624 || pt.y > 538)
			{
				int iIndex = iArrayy * 6 + iArrayx;
				//퀵슬롯에 물약 아이템을 놓으면 인벤토리에서 없어지지 않아야한다 
				//인벤토리 벡터 이터를 돌면서 빈자리에 마우스가 가진 정보를 돌려준다

				m_vecSlot[iIndex]->Set_Skill(CObjMgr::Get_Instance()->Get_Mouse()->Get_Skill());
				if (CObjMgr::Get_Instance()->Get_Mouse()->Get_Item() == HP || (CObjMgr::Get_Instance()->Get_Mouse()->Get_Item() == MP))
				{
					m_vecSlot[iIndex]->Set_Item(CObjMgr::Get_Instance()->Get_Mouse()->Get_Item()); 
					for (auto& iter = dynamic_cast<CInventory*>(CObjMgr::Get_Instance()->Get_Inven())->Get_vecItem()->begin();
						iter != dynamic_cast<CInventory*>(CObjMgr::Get_Instance()->Get_Inven())->Get_vecItem()->end(); ++iter)
					{
						if ((*iter)->Get_Item() == ITEM_END)
						{
							(*iter)->Set_Item(CObjMgr::Get_Instance()->Get_Mouse()->Get_Item());
							break;
						}
					}
				}
				static_cast<CMouse*>(CObjMgr::Get_Instance()->Get_Mouse())->Set_Grab(false);
				CObjMgr::Get_Instance()->Get_Mouse()->Set_Item(ITEM_END);
				CObjMgr::Get_Instance()->Get_Mouse()->Set_Skill(PSKILL_END);
			}
		}
	}
	return 0;
}

void CQuickSlot::Late_Update(void)
{
	for (auto& iter : m_vecSlot)
		iter->Late_Update();
}

void CQuickSlot::Render(HDC hDC)
{
	for (int i = 0; i <2; ++i)
	{
		for (int j = 0; j <6; ++j)
		{
			int iIndex = i*6+j;
			
			m_vecSlot[iIndex]->Render(hDC);
		}
	}
}

void CQuickSlot::Release(void)
{
	for (auto& iter : m_vecSlot)
		Safe_Delete(iter);
	m_vecSlot.clear();
}
