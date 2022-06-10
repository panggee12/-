#pragma once

#include "Include.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	void		Set_Pos(float _fX, float _fY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}
	void		Set_PosX(float _fX)
	{
		m_tInfo.fX += _fX;
	}
	void		Set_PosY(float _fY)
	{
		m_tInfo.fY += _fY;
	}
	void		Set_Portal(PORTALID _pId)
	{
		m_tProtal = _pId;
	}

	const INFO&	Get_Info() { return m_tInfo; }
	const RECT& Get_Rect() { return m_tRect; }
	const LINE& Get_Line() { return m_tLine; }
	const PORTALID& Get_Portal() { return m_tProtal; }
	
	void		Set_key(const TCHAR* _key) { m_framekey = _key; }

public:
	virtual		void	Initialize(void)	PURE;
	virtual		int		Update(void)		PURE;
	virtual		void	Late_Update(void)	PURE;
	virtual		void	Render(HDC hDC)		PURE;
	virtual		void	Release(void)		PURE;

protected:
	void		Update_Rect(void);
	void		Jumping();
	void		Move_Frame();
protected:
	INFO		m_tInfo;
	RECT		m_tRect;
	LINE		m_tLine;
	FRAME		m_tFrame;
	PORTALID	m_tProtal;
	const TCHAR*		m_framekey;

	float		m_fSpeed;
	float		m_fJumpPower;
	float		m_fJumpTime;
	bool		m_bDead;
	bool		m_bJump;
	int			m_iDrawid;
};

