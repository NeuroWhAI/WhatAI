#include "AxonHelper.h"

#include "Axon.h"
#include "Neuron.h"

#include "AxonPort.h"








































bool AxonHelper::Connect(Axon* pIn, Neuron* pNeuron, bool bCheckOverlap)
{
	if (pNeuron->GetInAxonList()->Add(pIn, bCheckOverlap) < 0) return false;
	pIn->SetCenterNeuron(pNeuron);


	return true;
}


bool AxonHelper::Connect(Neuron* pNeuron, Axon* pOut, bool bCheckOverlap)
{
	if (pNeuron->GetOutAxonList()->Add(pOut, bCheckOverlap) < 0) return false;
	pOut->SetCenterNeuron(pNeuron);


	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////

void AxonHelper::Disconnect(Axon* pIn, Neuron* pNeuron)
{
	pIn->SetCenterNeuron(nullptr);
	pNeuron->GetInAxonList()->Remove(pIn);
}


void AxonHelper::Disconnect(Neuron* pNeuron, Axon* pOut)
{
	pNeuron->GetOutAxonList()->Remove(pOut);
	pOut->SetCenterNeuron(nullptr);
}

