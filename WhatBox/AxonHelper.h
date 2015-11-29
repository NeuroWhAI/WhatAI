#pragma once

class Axon;
class Neuron;







































class AxonHelper
{
private:
	AxonHelper() = delete;


public:
	static bool Connect(Axon* pIn, Neuron* pNeuron, bool bCheckOverlap = false);
	static bool Connect(Neuron* pNeuron, Axon* pOut, bool bCheckOverlap = false);

	static void Disconnect(Axon* pIn, Neuron* pNeuron);
	static void Disconnect(Neuron* pNeuron, Axon* pOut);
};

