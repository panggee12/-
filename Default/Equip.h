#pragma once
#include "Obj.h"
class CEquip :
	public CObj
{
public:
	CEquip();
	virtual ~CEquip();

public:
	virtual void Initialize(void) override;
	virtual int	 Update(void) override;
	virtual	void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	vector<CObj*>* Get_vecItem() { return &m_vecItem; }
	CObj*          Get_vecItem_Iter(int i) { return m_vecItem[i]; }

	void UnEquip_Item();
private:
	vector<CObj*> m_vecItem;
};

