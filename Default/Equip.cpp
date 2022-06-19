#include "stdafx.h"
#include "Equip.h"
#include "Item.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "Ui.h"
#include "KeyMgr.h"
#include "Inventory.h"
CEquip::CEquip()
{
}


CEquip::~CEquip()
{
	Release();
}

void CEquip::Initialize(void)
{
	CObj* pEquip = CAbstractFactory<CItem>::Create(458, 294, PSKILL_END, ITEM_END);
	m_vecItem.push_back(pEquip);
	pEquip = CAbstractFactory<CItem>::Create(326, 327, PSKILL_END, ITEM_END);
	m_vecItem.push_back(pEquip);
	pEquip = CAbstractFactory<CItem>::Create(392, 295, PSKILL_END, ITEM_END);
	m_vecItem.push_back(pEquip);
	
}

int CEquip::Update(void)
{
	for (auto& iter : m_vecItem)
		iter->Update();
	UnEquip_Item();
	return 0;
}

void CEquip::Late_Update(void)
{
	for (auto& iter : m_vecItem)
		iter->Late_Update();
}

void CEquip::Render(HDC hDC)
{
	if (dynamic_cast<CUi*>(CObjMgr::Get_Instance()->Get_Ui())->Get_Equip())
	{
		for (auto& iter : m_vecItem)
			iter->Render(hDC);
	}
}

void CEquip::Release(void)
{
	for (auto& iter : m_vecItem)
		Safe_Delete(iter);
	m_vecItem.clear();
}

void CEquip::UnEquip_Item()
{
	pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd,&pt);
	if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
	{
		for (auto& iter : m_vecItem)
		{
			if (PtInRect(&(iter->Get_Rect()), pt)&& iter->Get_Item()!=ITEM_END)
			{
				dynamic_cast<CInventory*>(CObjMgr::Get_Instance()->Get_Inven())->UnEquip(iter->Get_Item());
				CObjMgr::Get_Instance()->Get_Player()->Set_StatusUp(-iter->Get_Status().m_iSTR, 0, 0, 0, 0);
				iter->Set_Item(ITEM_END);
			}
		}
	}
}
