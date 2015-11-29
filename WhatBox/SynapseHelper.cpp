#include "SynapseHelper.h"

#include "Synapse.h"
#include "Neuron.h"
#include "SynapsePort.h"








































bool SynapseHelper::Connect(Neuron* pIn, Synapse* pOutSyp, bool bCheckOverlap)
{
	if (pIn->GetOutSypList()->Add(pOutSyp, bCheckOverlap) < 0) return false;
	pOutSyp->SetInNeuron(pIn);


	return true;
}


bool SynapseHelper::Connect(Synapse* pInSyp, Neuron* pOut, bool bCheckOverlap)
{
	if (pOut->GetInSypList()->Add(pInSyp, bCheckOverlap) < 0) return false;
	pInSyp->SetOutNeuron(pOut);


	return true;
}


bool SynapseHelper::Connect(Neuron* pIn, Synapse* pSyp, Neuron* pOut, bool bCheckOverlap)
{
	if (pIn->GetOutSypList()->Add(pSyp, bCheckOverlap) < 0) return false;
	if (pOut->GetInSypList()->Add(pSyp, bCheckOverlap) < 0)
	{
		pIn->GetOutSypList()->Remove(pSyp); // Ãë¼Ò
		return false;
	}

	pSyp->SetInNeuron(pIn);
	pSyp->SetOutNeuron(pOut);


	return true;
}


void SynapseHelper::Disconnect(Neuron* pIn, Synapse* pOutSyp)
{
	pIn->GetOutSypList()->Remove(pOutSyp);
	pOutSyp->SetInNeuron(nullptr);
}


void SynapseHelper::Disconnect(Synapse* pInSyp, Neuron* pOut)
{
	pInSyp->SetOutNeuron(nullptr);
	pOut->GetInSypList()->Remove(pInSyp);
}


void SynapseHelper::Disconnect(Neuron* pIn, Synapse* pSyp, Neuron* pOut)
{
	pIn->GetOutSypList()->Remove(pSyp);

	pSyp->SetInNeuron(nullptr);
	pSyp->SetOutNeuron(nullptr);

	pOut->GetInSypList()->Remove(pSyp);
}

