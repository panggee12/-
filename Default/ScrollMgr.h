#pragma once
class CScrollMgr
{
public:
	CScrollMgr();
	~CScrollMgr();

	void Set_ScrollX(float _X) { m_fScrollX += _X; }
	void Set_ScrollY(float _Y) { m_fScrollY += _Y; }

	float  Get_ScrollX() { return m_fScrollX; }
	float  Get_ScrollY() { return m_fScrollY; }
public:
	static		CScrollMgr*		Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CScrollMgr;

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
	static CScrollMgr* m_pInstance;

	float m_fScrollX;
	float m_fScrollY;
};

