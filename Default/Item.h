#pragma once
#include "Obj.h"
class CItem :
	public CObj
{
public:
	CItem();
	virtual ~CItem();

public:
	virtual void Initialize(void) override;
	virtual int	 Update(void) override;
	virtual	void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void Set_Drop() { m_bDrop = true; }
	
private:
	bool		m_bDrop;
	bool		m_ItemCheck;
	DWORD		m_dwUPDOWN;
	int			m_iRand;

};

