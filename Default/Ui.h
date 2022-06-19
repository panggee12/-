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

	void Delete_Shop(){ m_bItemCreate = false; }
	void Shop_On_Off(bool bShop) { m_bShop = bShop; }
	bool Get_Shop() { return m_bShop; }
	void Inven_On_Off(bool bInven) { m_bInven = bInven; }
	bool Get_Inven() { return m_bInven; }
	void SkillBook_On_Off(bool bSkillbook) { m_bSkillBook = bSkillbook; }
	bool Get_SkillBook() { return m_bSkillBook; }
	void Equip_On_Off(bool bEquip) { m_bEquip = bEquip; }
	bool Get_Equip() { return m_bEquip; }
	void Status_On_Off(bool bStatus) { m_bStatus = bStatus; }
	bool Get_Status() { return m_bStatus; }
	
	void Set_ButtonSkF() { m_bSkBt1 = false; m_bSkBt2 = false; m_bSkBt3 = false; m_bSkBt4 = false; }
	void Set_ButtonStF() { m_bStBt1 = false; m_bStBt2 = false; m_bStBt3 = false; m_bStBt4 = false; m_bStBt5 = false; }

	RECT Get_ExitBt() { return m_Exitrc; }
private:			   
	bool m_bShop;
	bool m_bItemCreate;
	bool m_bInven;	    
	bool m_bSkillBook;
	bool m_bSkBt1;
	bool m_bSkBt2;
	bool m_bSkBt3;
	bool m_bSkBt4;
	bool m_bStBt1;
	bool m_bStBt2;
	bool m_bStBt3;
	bool m_bStBt4;
	bool m_bStBt5;
	bool m_bEquip;
	bool m_bStatus;

	int SkillOn1;
	int SkillOn2;
	int SkillOn3;
	int SkillOn4;
	RECT m_rc1;
	RECT m_rc2;
	RECT m_rc3;
	RECT m_rc4;
	RECT m_Invenrc;
	RECT m_Exitrc;
};

