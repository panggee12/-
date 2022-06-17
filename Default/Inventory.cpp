#include "stdafx.h"
#include "Inventory.h"
#include "Item.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "Ui.h"
#include "Mouse.h"
#include "KeyMgr.h"
CInventory::CInventory()
{
}


CInventory::~CInventory()
{
	Release();
}

void CInventory::Initialize(void)
{
	for (int i = 223; i < 433; i += 35)
	{
		for (int j = 530; j < 670; j += 35)
		{
			CObj* pItem = CAbstractFactory<CItem>::Create(j, i, PSKILL_END, ITEM_END);
			m_vecItem.push_back(pItem);
		}
	}
}

int CInventory::Update(void)
{
	for (auto& iter : m_vecItem)
		iter->Update();

	Picking_Item();
	Change_Item_pos();

	return 0;
}

void CInventory::Late_Update(void)
{
	for (auto& iter : m_vecItem)
		iter->Late_Update();
}

void CInventory::Render(HDC hDC)
{
	if (static_cast<CUi*>(CObjMgr::Get_Instance()->Get_Ui())->Get_Inven())
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 6; ++j)
			{
				int iIndex = i * 6 + j;

				m_vecItem[iIndex]->Render(hDC);
			}
		}
	}
}

void CInventory::Release(void)
{
	for (auto& iter : m_vecItem)
		Safe_Delete(iter);
	m_vecItem.clear();
}

void CInventory::Picking_Item()
{
	pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	int iIndex = 0;
	if (dynamic_cast<CUi*>(CObjMgr::Get_Instance()->Get_Ui())->Get_Inven())
	{
		for (int i = 200; i < 410; i += 35)
		{
			for (int j = 506; j < 646; j += 35)
			{
				if (pt.x >= j&&pt.x <= j + 35 && pt.y >= i && pt.y <= i + 35)
				{
					if (m_vecItem[iIndex]->Get_Item() == ITEM_END&&dynamic_cast<CMouse*>(CObjMgr::Get_Instance()->Get_Mouse())->Get_Grab()&& 
						CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON) && CObjMgr::Get_Instance()->Get_Mouse()->Get_Item()!=ITEM_END)
					{
						m_vecItem[iIndex]->Set_Item(CObjMgr::Get_Instance()->Get_Mouse()->Get_Item());
						dynamic_cast<CMouse*>(CObjMgr::Get_Instance()->Get_Mouse())->Set_Grab(false);
						CObjMgr::Get_Instance()->Get_Mouse()->Set_Item(ITEM_END);
						break;
					}
					else if(m_vecItem[iIndex]->Get_Item() != ITEM_END&&dynamic_cast<CMouse*>(CObjMgr::Get_Instance()->Get_Mouse())->Get_Grab() &&
						CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON) && CObjMgr::Get_Instance()->Get_Mouse()->Get_Item() != ITEM_END)
					{
						ITEMID m_itemid;
						m_itemid = m_vecItem[iIndex]->Get_Item(); //인벤토리 아이템 종류 임시 저장
						m_vecItem[iIndex]->Set_Item(CObjMgr::Get_Instance()->Get_Mouse()->Get_Item()); //인벤토리 아이템 종류에 마우스가 가진 아이템 종류 입력
						CObjMgr::Get_Instance()->Get_Mouse()->Set_Item(m_itemid);  //마우스 아이템 종류에 임시로 저장해줬던 인벤토리 아이템 종류 저장
						break; //마우스 그랩은 그대로 트루인 상태 
					}
					else if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON)&& !dynamic_cast<CMouse*>(CObjMgr::Get_Instance()->Get_Mouse())->Get_Grab())
					{
						dynamic_cast<CMouse*>(CObjMgr::Get_Instance()->Get_Mouse())->Set_Grab(true);
						CObjMgr::Get_Instance()->Get_Mouse()->Set_Item(m_vecItem[iIndex]->Get_Item());
						m_vecItem[iIndex]->Set_Item(ITEM_END);
						break;
					}
				}
				++iIndex;
				
			}
		}
	}
}

void CInventory::Change_Item_pos()
{
	/*pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	int iIndex = 0;
	if (dynamic_cast<CUi*>(CObjMgr::Get_Instance()->Get_Ui())->Get_Inven())
	{
		for (int i = 200; i < 410; i += 35)
		{
			for (int j = 506; j < 646; j += 35)
			{

				if (pt.x >= j&&pt.x <= j + 35 && pt.y >= i && pt.y <= i + 35 && CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON)&& 
					)
				{
					
				}

				++iIndex;
			}
		}
	}*/
}

void CInventory::Use_Item(ITEMID _portion)
{
	for (auto& iter : m_vecItem)
	{
		if (iter->Get_Item() == _portion&&dynamic_cast<CItem*>(iter)->Get_PortionCount()>0)
		{
			dynamic_cast<CItem*>(iter)->Set_PortionCount(-1);
			if (dynamic_cast<CItem*>(iter)->Get_PortionCount() <= 0)
				iter->Set_Item(ITEM_END);
		}
	}
}

bool CInventory::Portion_Check(ITEMID _portion)
{
	for (auto& iter : m_vecItem)
	{
		if (iter->Get_Item() == _portion)
		{
			return true;
		}
	}
	return false;
}
