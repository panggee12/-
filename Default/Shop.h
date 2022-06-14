#pragma once
#include "Obj.h"
class CShop :
	public CObj
{
public:
	CShop();
	virtual ~CShop();

public:
	virtual void Initialize(void) override;
	virtual int	 Update(void) override;
	virtual	void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void Update_Rect_Shop();
};

