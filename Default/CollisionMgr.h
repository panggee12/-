#pragma once
#include "Obj.h"
class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

	static bool Collision_Rect(list<CObj*> _Dest,list<CObj*> _Sour);
	static bool	Collision_Item(list<CObj*> _Dest, list<CObj*> _Sour);
	static bool	Collision_Portal(list<CObj*> _Dest, list<CObj*> _Sour);
	static bool Collision_Check(CObj* _Dest, CObj* _Sour, float& fx, float& fy);

};

