#include "AxonFactory.h"

#include "Axon.h"
#include "Neuron.h"

#include "AxonHelper.h"







































Axon* AxonFactory::CreateAxon(AxonTypes type, Neuron* pCenterNeuron, const D3DXVECTOR2& relativePos)
{
	Axon* pAxon = nullptr;


	switch (type)
	{
	case AxonTypes::None:
		pAxon = nullptr;
		break;

	case AxonTypes::Input:
		pAxon = new Axon(type, pCenterNeuron);
		AxonHelper::Connect(pAxon, pCenterNeuron);
		break;

	case AxonTypes::Output:
		pAxon = new Axon(type, pCenterNeuron);
		AxonHelper::Connect(pCenterNeuron, pAxon);
		break;
	}


	if (pAxon != nullptr)
	{
		pAxon->SetPos(&relativePos);

		if (pCenterNeuron != nullptr)
		{
			pAxon->SetLayerNum(pCenterNeuron->GetLayerNum());
		}
	}


	return pAxon;
}

