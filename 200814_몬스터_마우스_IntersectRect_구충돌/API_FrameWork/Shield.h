#pragma once
#include "Obj.h"
class CShield :public CObj
{
private:
	const float* m_fTargetX;
	const float* m_fTargetY;
	float m_fRadian;
public:
	CShield();
	virtual ~CShield();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

	void SetTarget(const float* _fTargetX, const float* _fTargetY) { m_fTargetX = _fTargetX; m_fTargetY = _fTargetY; }
};

