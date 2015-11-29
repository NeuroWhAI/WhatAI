#pragma once
#include <d3dx9.h>

class Synapse;
class Neuron;






































class SynapseFactory
{
private:
	SynapseFactory() = delete;


public:
	static Synapse* CreateSynapse(Neuron* pIn, Neuron* pOut);
	static Synapse* CreateSynapse(Neuron* pIn, Neuron* pOut, double weight);
};

