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

private:
	vector<CObj*> m_vecItem;
};

