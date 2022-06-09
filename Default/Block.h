#pragma once
#include "Obj.h"
class CBlock:public CObj
{
public:
	CBlock();
	CBlock(LINEPOINT& tLeft, LINEPOINT& tRight);
	~CBlock();

public:
	virtual void Initialize(void) override;
	virtual int	 Update(void) override;
	virtual	void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

