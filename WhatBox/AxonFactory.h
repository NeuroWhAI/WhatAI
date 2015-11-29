#pragma once
#include <d3dx9.h>

#include "Types.h"

class Axon;
class Neuron;






































class AxonFactory
{
private:
	AxonFactory() = delete;


public:
	static Axon* CreateAxon(AxonTypes type, Neuron* pCenterNeuron, const D3DXVECTOR2& relativePos);
};

