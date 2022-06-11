#pragma once
#include "Obj.h"
class CBlock:public CObj
{
public:
	CBlock();
	CBlock(LINEPOINT& tLeft, LINEPOINT& tRight);
	CBlock(const LINE& tLine);
	~CBlock();

public:
	virtual void Initialize(void) override;
	virtual int	 Update(void) override;
	virtual	void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	LINE		 m_tLine;
	DWORD		 m_dwPortal;
};

