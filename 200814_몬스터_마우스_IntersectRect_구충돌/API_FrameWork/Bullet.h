#pragma once

#ifndef __BULLET_H__
#define __BULLET_H__


#include "Obj.h"
class CBullet : public CObj
{
public:
	CBullet();
	virtual ~CBullet();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update();
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

public:
	void Set_Dir(BULLET::DIR _eDir) { m_eDir = _eDir; }
	void Set_Dir(VECTOR _tDir) { m_tDirection = _tDir; }

	void SetPivot(float _fPivotX, float _fPivotY) { m_fPivotX = _fPivotX; m_fPivotY = _fPivotY; }
private:
	BULLET::DIR		m_eDir;
	float m_fPivotX;
	float m_fPivotY;
	float m_fRadian;
};


#endif // !__BULLET_H__
