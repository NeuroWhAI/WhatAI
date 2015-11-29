#include "HormoneNeuron.h"

#include "cCore.h"

#include "SynapsePort.h"
#include "AxonPort.h"
#include "Axon.h"
#include "Synapse.h"
#include "NeuronPotential.h"
#include "HormoneState.h"







































HormoneNeuron::HormoneNeuron(const NeuronPotential& signalInfo, double hormoneValue)
	: Neuron(signalInfo)

	, m_hormoneValue(hormoneValue)
{

}


HormoneNeuron::~HormoneNeuron()
{

}

//////////////////////////////////////////////////////////////////////////////////////////////

int HormoneNeuron::Update(HormoneState* pHormoneState)
{
	Neuron::Update(pHormoneState);


	// Ȱ��ȭ�� ȣ���� �ۿ�
	if (this->IsActivated())
	{
		pHormoneState->AddPN(m_hormoneValue*m_signal*cCore::TimeMgr.GetFrameRate());

		
		/*SynapsePort& inSypList = *m_pInSypPort;
		const size_t inSypCount = inSypList.GetCount();

		for (size_t s = 0; s < inSypCount; ++s)
		{
			Synapse* const pSyp = inSypList[s];

			if (pSyp == nullptr) continue;


			// pNeuron�� �Է´����� Ȱ�������̰� ������ �ó����� �������� �ƴҶ� ����
			const double& weight = pSyp->GetWeight();
			Neuron* const pInNeuron = pSyp->GetInNeuron();

			if (weight > 0.0
				&&
				pInNeuron->IsActivated())
			{
				double dw = (2.0 - weight) * pInNeuron->GetSignal() * 0.0004;
				pSyp->SetWeight(weight + dw*cCore::TimeMgr.GetFrameRate());
			}
		}*/
	}


	return 0;
}


int HormoneNeuron::Draw()
{
	cCore::Sprite.SetColor(m_hormoneValue < 0.0 ? D3DCOLOR_ARGB(255, 255, 101, 14) : D3DCOLOR_ARGB(255, 181, 230, 29));

	Neuron::Draw();


	return 0;
}

