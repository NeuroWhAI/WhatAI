#pragma once

class Synapse;
class Neuron;







































class SynapseHelper
{
private:
	SynapseHelper() = delete;


public:
	static bool Connect(Neuron* pIn, Synapse* pOutSyp, bool bCheckOverlap = false);
	static bool Connect(Synapse* pInSyp, Neuron* pOut, bool bCheckOverlap = false);
	static bool Connect(Neuron* pIn, Synapse* pSyp, Neuron* pOut, bool bCheckOverlap = false);

	static void Disconnect(Neuron* pIn, Synapse* pOutSyp);
	static void Disconnect(Synapse* pInSyp, Neuron* pOut);
	static void Disconnect(Neuron* pIn, Synapse* pSyp, Neuron* pOut);
};

