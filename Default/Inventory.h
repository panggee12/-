#pragma once
#include "Obj.h"
class CInventory :
	public CObj
{
public:
	CInventory();
	virtual ~CInventory();

public:
	virtual void Initialize(void) override;
	virtual int	 Update(void) override;
	virtual	void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void Picking_Item();
	void Change_Item_pos();
	void Use_Item(ITEMID _portion);
	bool Portion_Check(ITEMID _portion);
	vector<CObj*>* Get_vecItem() { return &m_vecItem; }
private:
	vector<CObj*> m_vecItem;
	
};

