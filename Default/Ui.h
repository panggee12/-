#pragma once
#include "Obj.h"
class CUi :
	public CObj
{
public:
	CUi();
	virtual ~CUi();

public:
	virtual void Initialize(void) override;
	virtual int	 Update(void) override;
	virtual	void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void Shop_On_Off(bool bShop) { m_bShop = bShop; }
	bool Get_Shop() { return m_bShop; }
	void Inven_On_Off(bool bInven) { m_bInven = bInven; }
	bool Get_Inven() { return m_bInven; }
	void SkillBook_On_Off(bool bSkillbook) { m_bSkillBook = bSkillbook; }
	bool Get_SkillBook() { return m_bSkillBook; }
private:
	bool m_bShop;
	bool m_bInven;
	bool m_bSkillBook;
};

