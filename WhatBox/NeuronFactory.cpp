#include "NeuronFactory.h"

#include "Neuron.h"
#include "HormoneNeuron.h"







































Neuron* NeuronFactory::CreateNeuron(NeuronTypes type, const D3DXVECTOR2& pos, int layerNum, const NeuronPotential& signalInfo)
{
	Neuron* pNeuron = nullptr;


	switch (type)
	{
	case NeuronTypes::None:
		pNeuron = nullptr;
		break;

	case NeuronTypes::Normal:
		pNeuron = new Neuron(signalInfo);
		break;

	case NeuronTypes::Positive:
		pNeuron = new HormoneNeuron(signalInfo, 0.0001/*ȣ���� ����*/);
		break;

	case NeuronTypes::Negative:
		pNeuron = new HormoneNeuron(signalInfo, -0.0001/*ȣ���� ����*/);
		break;
	}


	if (pNeuron != nullptr)
	{
		pNeuron->SetPos(&pos);
		pNeuron->SetLayerNum(layerNum);
	}


	return pNeuron;
}

