#pragma once
#include "Obj.h"
class CMouse :
	public CObj
{
public:
	CMouse();
	virtual ~CMouse();

public:
	virtual void Initialize(void) override;
	virtual int	 Update(void) override;
	virtual	void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void	Set_Grab(bool bgrab) { m_bGrab = bgrab; }
	bool	Get_Grab() { return m_bGrab; }
	void	Set_Buy(bool bbuy) { m_bBuy = bbuy; }
	bool	Get_Buy() { return m_bBuy; }
private:
	int		m_iDrawID;
	bool	m_bGrab;
	bool	m_bBuy;
	POINT	pt;
};

