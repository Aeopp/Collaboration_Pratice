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
	void SetShield(list<CObj*>* _pShield) { m_pShield = _pShield; }

private:
	CObj* Create_Bullet();
	CObj* Create_Bullet(BULLET::DIR _eDir);
	CObj* Create_Bullet(VECTOR _tDirection,BOOL _bIsScrewed = FALSE);

	CObj* CreateShield();

private:
	list<CObj*>*	m_pBullet;
	list<CObj*>*	m_pShield;

};

#endif // !__PLAYER_H__
