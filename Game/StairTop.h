#pragma once
#include "GameObject.h"

class CStairTop : public CGameObject
{

public:
	CStairTop(float l, float t, float r, float b);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};
