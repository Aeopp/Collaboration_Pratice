#pragma once

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Obj.h"
class CPlayer : public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update();
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

public:
	void Set_Bullet(list<CObj*>* _pBullet) { m_pBullet = _pBullet; }

private:
	CObj* Create_Bullet(VECTOR _tDirection);

private:
	list<CObj*>*	m_pBullet;

	DWORD			m_dwTime;
	bool			m_bFire;

};

#endif // !__PLAYER_H__
