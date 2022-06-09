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
	const INFO&	Get_Info() { return m_tInfo; }
	const RECT& Get_Rect() { return m_tRect; }
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
protected:
	INFO		m_tInfo;
	RECT		m_tRect;
	LINE		m_tLine;
	const TCHAR*		m_framekey;

	float		m_fSpeed;
	float		m_fJumpPower;
	float		m_fJumpTime;
	bool		m_bDead;
	bool		m_bJump;
	int			m_iDrawid;
};

