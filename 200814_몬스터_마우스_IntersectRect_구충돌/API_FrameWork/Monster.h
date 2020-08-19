#pragma once

#ifndef __MONSTER_H__
#define __MONSTER_H__


#include "Obj.h"
class CMonster : public CObj
{
private:
	const float* m_fTargetX;
	const float* m_fTargetY;
	float m_fDirection;
public:
	CMonster();
	virtual ~CMonster();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

	void SetTarget(const float* _fTargetX, const float* _fTargetY) { m_fTargetX = _fTargetX; m_fTargetY = _fTargetY; }

private:
	float CalculateRadian(float _fStartX, float _fStartY, float _fEndX, float _fEndY);
};


#endif // !__MONSTER_H__

