#include "NetGuideline.h"







































NetGuideline::NetGuideline()
	: m_neuronType(NeuronTypes::Normal)
	, m_dir(0.f, 0.f)
{

}


NetGuideline::NetGuideline(const D3DXVECTOR2& pos, int layerNum,
	const D3DXVECTOR2& dir, NeuronTypes neuronType)
	: NetObject(pos.x, pos.y, layerNum)
	
	, m_neuronType(neuronType)
	, m_dir(dir)
{

}


NetGuideline::~NetGuideline()
{

}

//////////////////////////////////////////////////////////////////////////////////////////////

NeuronTypes NetGuideline::GetNeuronType() const
{
	return m_neuronType;
}


void NetGuideline::SetNeuronType(NeuronTypes neuronType)
{
	m_neuronType = neuronType;
}

//////////////////////////////////////////////////////////////////////////////////////////////

const D3DXVECTOR2* NetGuideline::GetDir() const
{
	return &m_dir;
}


void NetGuideline::GetDir(D3DXVECTOR2* pGetDir) const
{
	*pGetDir = m_dir;
}


void NetGuideline::SetDir(const D3DXVECTOR2& dir)
{
	m_dir = dir;
}

//////////////////////////////////////////////////////////////////////////////////////////////

float NetGuideline::GetLength() const
{
	return D3DXVec2Length(&m_dir);
}


float NetGuideline::GetLengthSq() const
{
	return D3DXVec2LengthSq(&m_dir);
}

