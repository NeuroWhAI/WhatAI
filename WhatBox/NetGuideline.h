#pragma once
#include "NetObject.h"

#include "Types.h"






































class NetGuideline : public NetObject
{
public:
	NetGuideline();
	NetGuideline(const D3DXVECTOR2& pos, int layerNum,
		const D3DXVECTOR2& dir, NeuronTypes neuronType);
	virtual ~NetGuideline();


private:
	NeuronTypes m_neuronType;
	D3DXVECTOR2 m_dir;


public:
	NeuronTypes GetNeuronType() const;
	void SetNeuronType(NeuronTypes neuronType);


public:
	const D3DXVECTOR2* GetDir() const;
	void GetDir(D3DXVECTOR2* pGetDir) const;
	void SetDir(const D3DXVECTOR2& dir);


public:
	float GetLength() const;
	float GetLengthSq() const;
};

