#include "stdafx.h"
#include "Shop.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "Mouse.h"
#include "Ui.h"
#include "Inventory.h"
#include "Item.h"
CShop::CShop()
{
}


CShop::~CShop()
{
}

void CShop::Initialize(void)
{
	m_tInfo.fCX = 250.f;
	m_tInfo.fCY = 35.f;
	

}

int CShop::Update(void)
{
	

	Update_Rect();
	return 0;
}

void CShop::Late_Update(void)
{
	pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	if (PtInRect(&m_tRect, pt) && CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		dynamic_cast<CMouse*>(CObjMgr::Get_Instance()->Get_Mouse())->Set_Buy(true);
		CObjMgr::Get_Instance()->Get_Mouse()->Set_Item(m_tItem);
	}
	else if (PtInRect(&(dynamic_cast<CUi*>(CObjMgr::Get_Instance()->Get_Ui())->Get_ExitBt()), pt) && CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON)&&
		CObjMgr::Get_Instance()->Get_Player()->Get_Money()>=m_iMoney&&dynamic_cast<CMouse*>(CObjMgr::Get_Instance()->Get_Mouse())->Get_Buy())
	{
		dynamic_cast<CMouse*>(CObjMgr::Get_Instance()->Get_Mouse())->Set_Buy(false);
		for (auto& iter = dynamic_cast<CInventory*>(CObjMgr::Get_Instance()->Get_Inven())->Get_vecItem()->begin();
			iter != dynamic_cast<CInventory*>(CObjMgr::Get_Instance()->Get_Inven())->Get_vecItem()->end();)
		{
			if ((*iter)->Get_Item() == ITEM_END)
			{
				(*iter)->Set_Item(CObjMgr::Get_Instance()->Get_Mouse()->Get_Item());
				CObjMgr::Get_Instance()->Get_Player()->Set_MoneyUp(-CObjMgr::Get_Instance()->Get_Mouse()->Get_Money());
				if (CObjMgr::Get_Instance()->Get_Mouse()->Get_Item() == HP || CObjMgr::Get_Instance()->Get_Mouse()->Get_Item() == MP)
					dynamic_cast<CItem*>(*iter)->Set_PortionCount(1);
				CObjMgr::Get_Instance()->Get_Mouse()->Set_Item(ITEM_END);
				break;
			}
			else if ((*iter)->Get_Item() == HP&&CObjMgr::Get_Instance()->Get_Mouse()->Get_Item() == HP)
			{

				dynamic_cast<CItem*>(*iter)->Set_PortionCount(1);
				CObjMgr::Get_Instance()->Get_Mouse()->Set_Item(ITEM_END);
				CObjMgr::Get_Instance()->Get_Player()->Set_MoneyUp(-CObjMgr::Get_Instance()->Get_Mouse()->Get_Money());
				break;
			}
			else if ((*iter)->Get_Item() == MP&&CObjMgr::Get_Instance()->Get_Mouse()->Get_Item() == MP)
			{
				
					dynamic_cast<CItem*>(*iter)->Set_PortionCount(1);
				CObjMgr::Get_Instance()->Get_Mouse()->Set_Item(ITEM_END);
				CObjMgr::Get_Instance()->Get_Player()->Set_MoneyUp(-CObjMgr::Get_Instance()->Get_Mouse()->Get_Money());
				break;
				
			}
			else
				++iter;
		}
	}

}

void CShop::Render(HDC hDC)
{
	
}


void CShop::Release(void)
{
}


