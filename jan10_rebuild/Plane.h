#pragma once
#include "Common.h"

class PLane {
public:
	

				PLane				(const XMFLOAT3& origin, const XMFLOAT3& normal);
				PLane				(const XMFLOAT3& p1, const XMFLOAT3& p2, const XMFLOAT3& p3);
	bool		IsFrontFacingTo		(const XMFLOAT3& direction) const;
	double		SignedDistanceTo	(const XMFLOAT3& point) const;


private:


	float		equation[4];
	XMFLOAT3	m_Origin;
	XMFLOAT3	m_Normal;



};




