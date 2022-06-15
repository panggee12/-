#include "stdafx.h"
#include "Inventory.h"
#include "Icon.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "Ui.h"
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
			CObj* pItem = CAbstractFactory<CIcon>::Create(j, i, PSKILL_END, ITEM_END);
			m_vecItem.push_back(pItem);
		}
	}
}

int CInventory::Update(void)
{
	for (auto& iter : m_vecItem)
		iter->Update();

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
