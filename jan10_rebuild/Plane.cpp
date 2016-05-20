#include "Plane.h"


/*
PLane::PLane(const XMFLOAT3& origin, const XMFLOAT3& normal) {
	this->m_Normal = normal;
	this->m_Origin = origin;
	equation[0] = normal.x;
	equation[1] = normal.y;
	equation[2] = normal.z;
	equation[3] = -(normal.x*origin.x + normal.y*origin.y
		+ normal.z*origin.z);
}
// Construct from triangle:
PLane::PLane(const XMFLOAT3& p1, const XMFLOAT3& p2, const XMFLOAT3& p3)
{
	m_Normal = (p2 - p1).cross(p3 - p1);
	XMVECTOR tempNormalize = XMLoadFloat3(&m_Origin);
	XMVector3Normalize(tempNormalize);
	m_Origin.normalize();
	m_Origin = p1;
	equation[0] = m_Normal.x;
	equation[1] = m_Normal.y;
	equation[2] = m_Normal.z;
	equation[3] = -(m_Normal.x*origin.x + m_Normal.y*origin.y
		+ normal.z*origin.z);
}
bool PLane::IsFrontFacingTo(const XMFLOAT3& direction) const {
	XMVECTOR tempNormal = XMLoadFloat3(&m_Normal);
	XMVECTOR tempDirection = XMLoadFloat3(&direction);
	XMFLOAT3 tempDot;
	XMStoreFloat3(&tempDot, XMVector3Dot(tempNormal, tempDirection));
	double dot = tempDot.x;
	return (dot <= 0);


}
double PLane::SignedDistanceTo(const XMFLOAT3& point) const {
	XMVECTOR tempNormal = XMLoadFloat3(&m_Normal);
	XMVECTOR tempPoint = XMLoadFloat3(&point);
	XMFLOAT3 tempDot;
	XMStoreFloat3(&tempDot, XMVector3Dot(tempNormal, tempPoint));


	return (tempDot.x + equation[3]);
}

*/