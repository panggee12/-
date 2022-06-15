#pragma once
#include "Obj.h"

class CQuickSlot :
	public CObj
{
public:
	CQuickSlot();
	virtual ~CQuickSlot();

public:
	virtual void Initialize(void) override;
	virtual int	 Update(void) override;
	virtual	void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	vector<CObj*> Get_VecSlot() { return m_vecSlot; }
private:
	vector<CObj*> m_vecSlot;
};

