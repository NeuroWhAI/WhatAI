#pragma once
#include <d3dx9.h>

#include "Types.h"

class Neuron;
class NeuronPotential;






































class NeuronFactory
{
private:
	NeuronFactory() = delete;


public:
	static Neuron* CreateNeuron(NeuronTypes type, const D3DXVECTOR2& pos, int layerNum, const NeuronPotential& signalInfo);
};

