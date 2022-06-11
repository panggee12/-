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

	bool		Collision_LineX(float fX,float* fY, float* pY);
	bool		Collision_LineX_M(float fX, float* fY, float* pY,float* LX, float* RX);
	bool		Collision_LineY(float fX, float* fY,float* pX);
	//bool		Collision_Block(float fX, float fY, float* pY, float* pY1);
	void		Load_File(STAGEID _STAGEID);
	void		Save_File(void);
	//void		Load_File_Portal(STAGEID _STAGEID);
	//void		Save_File_Portal(void);

	//void		Set_Block(list<CBlock*>* _pBlock) { m_BlockList = _pBlock; }
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
	//list<CBlock*>*				m_BlockList;
	LINEPOINT					m_tLinePoint[END];
};

