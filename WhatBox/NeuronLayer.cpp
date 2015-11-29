#include "NeuronLayer.h"

#include "cCore.h"

#include "Neuron.h"







































NeuronLayer::NeuronLayer()
{

}


NeuronLayer::~NeuronLayer()
{

}

//////////////////////////////////////////////////////////////////////////////////////////////

int NeuronLayer::Draw()
{
	for (size_t i = 0; i < m_pNeuronList.size(); ++i)
	{
		Neuron* const pCurrNeuron = m_pNeuronList[i];


		pCurrNeuron->Draw();
	}


	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////

int NeuronLayer::AddNeuron(Neuron* pNeuron, bool bCheckOverlap)
{
	if (pNeuron == nullptr) return -2;


	if (bCheckOverlap)
	{
		for (size_t i = 0; i < m_pNeuronList.size(); ++i)
		{
			Neuron* const pCurrNeuron = m_pNeuronList[i];

			if (pCurrNeuron == pNeuron)
			{
				return -1;
			}
		}
	}


	m_pNeuronList.emplace_back(pNeuron);


	return 0;
}

