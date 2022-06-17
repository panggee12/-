#pragma once
#include "Obj.h"
class CDamage :
	public CObj
{
public:
	CDamage();
	virtual ~CDamage();

public:
	virtual void Initialize(void) override;
	virtual int	 Update(void) override;
	virtual	void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	int m_iDamageCount;
	list<int> m_DamageList;
	bool m_bAlreadyPrint;
};

