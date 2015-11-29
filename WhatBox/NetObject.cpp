#include "NetObject.h"

#include <assert.h>







































NetObject::NetObject()
	: m_pos(0.f, 0.f)
	, m_layerNum(0)
{

}


NetObject::NetObject(float x, float y, int layerNum)
	: m_pos(x, y)
	, m_layerNum(layerNum)
{

}


NetObject::~NetObject()
{

}

//////////////////////////////////////////////////////////////////////////////////////////////

const D3DXVECTOR2* NetObject::GetPos() const
{
	return &m_pos;
}


void NetObject::GetPos(D3DXVECTOR2* pGet)
{
#ifdef _DEBUG
	if (pGet == nullptr)
	{
		assert(false);
		return;
	}
#endif

	*pGet = m_pos;
}


float NetObject::GetXPos() const
{
	return m_pos.x;
}


float NetObject::GetYPos() const
{
	return m_pos.y;
}


int NetObject::GetLayerNum() const
{
	return m_layerNum;
}


void NetObject::SetPos(const D3DXVECTOR2& pos)
{
	m_pos = pos;
}


void NetObject::SetPos(const D3DXVECTOR2* pPos)
{
#ifdef _DEBUG
	if (pPos == nullptr)
	{
		assert(false);
		return;
	}
#endif

	m_pos = *pPos;
}


void NetObject::SetPos(float x, float y)
{
	m_pos.x = x;
	m_pos.y = y;
}


void NetObject::SetLayerNum(int layerNum)
{
	m_layerNum = layerNum;
}


void NetObject::AddPos(const D3DXVECTOR2& addPos)
{
	m_pos.x += addPos.x;
	m_pos.y += addPos.y;
}


void NetObject::AddPos(const D3DXVECTOR2* pAddPos)
{
#ifdef _DEBUG
	if (pAddPos == nullptr)
	{
		assert(false);
		return;
	}
#endif

	m_pos.x += pAddPos->x;
	m_pos.y += pAddPos->y;
}


void NetObject::AddPos(float x, float y)
{
	m_pos.x += x;
	m_pos.y += y;
}


void NetObject::AddLayerNum(int addNum)
{
	m_layerNum += addNum;
}


void NetObject::SetXPos(float x)
{
	m_pos.x = x;
}


void NetObject::SetYPos(float y)
{
	m_pos.y = y;
}


void NetObject::AddXPos(float x)
{
	m_pos.x += x;
}


void NetObject::AddYPos(float y)
{
	m_pos.y += y;
}

