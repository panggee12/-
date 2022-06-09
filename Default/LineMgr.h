#pragma once

#include "Line.h"
#include "Block.h"
class CLineMgr
{
private:
	CLineMgr();
	~CLineMgr();

public:
	void		Initialize(void);
	void		Update(void);
	void		Render(HDC hDC);
	void		Release(void);

	bool		Collision_Line(float fX,float fY, float* pY,float* pY1);
	bool		Collision_Block(float fX, float fY, float* pY, float* pY1);
	void		Load_File(void);
	void		Save_File(void);
public:
	static		CLineMgr*		Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CLineMgr;

		return m_pInstance;
	}

	static		void			Destroy_Instance(void)
	{
		if (nullptr != m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
private:
	static		CLineMgr*		m_pInstance;
	list<CLine*>				m_LineList;
	list<CBlock*>				m_BlockList;
	LINEPOINT					m_tLinePoint[END];
};

