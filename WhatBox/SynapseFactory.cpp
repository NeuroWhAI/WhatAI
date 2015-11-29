#include "SynapseFactory.h"

#include "Neuron.h"
#include "Synapse.h"

#include "SynapseHelper.h"







































Synapse* SynapseFactory::CreateSynapse(Neuron* pIn, Neuron* pOut)
{
	Synapse* pSyp = new Synapse();


	SynapseHelper::Connect(pIn, pSyp, pOut);


	return pSyp;
}


Synapse* SynapseFactory::CreateSynapse(Neuron* pIn, Neuron* pOut, double weight)
{
	Synapse* pSyp = new Synapse();


	pSyp->SetWeight(weight);

	SynapseHelper::Connect(pIn, pSyp, pOut);


	return pSyp;
}

