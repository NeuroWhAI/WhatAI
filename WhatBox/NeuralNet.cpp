#include "NeuralNet.h"

#include <assert.h>

#include "cCore.h"

#include "Neuron.h"
#include "Synapse.h"
#include "NeuronLayer.h"
#include "NetOperator.h"
#include "Axon.h"
#include "NetGene.h"
#include "NeuronPotential.h"
#include "HormoneState.h"

#include "NeuronFactory.h"
#include "SynapseFactory.h"

#include "NetMaker.h"
#include "SynapsePort.h"







































NeuralNet::NeuralNet()
	: m_pNetGene(nullptr)
	, m_pSignalInfo(new NeuronPotential())
	, m_pHormoneState(new HormoneState())
	
	, m_pNetOperator(new NetOperator())
{
	// �������� �Ҵ�
	m_pNeuronList.reserve(256);
	m_pSypList.reserve(512);
	m_pAxonList.reserve(256);

	m_pLayerList.reserve(8);
}


NeuralNet::~NeuralNet()
{
	SAFE_DELETE(m_pNetGene);
	SAFE_DELETE(m_pSignalInfo);
	SAFE_DELETE(m_pHormoneState);


	for (size_t i = 0; i < m_pNeuronList.size(); ++i)
	{
		SAFE_DELETE(m_pNeuronList[i]);
	}

	for (size_t i = 0; i < m_pSypList.size(); ++i)
	{
		SAFE_DELETE(m_pSypList[i]);
	}

	for (size_t i = 0; i < m_pAxonList.size(); ++i)
	{
		SAFE_DELETE(m_pAxonList[i]);
	}


	for (size_t i = 0; i < m_pLayerList.size(); ++i)
	{
		SAFE_DELETE(m_pLayerList[i]);
	}


	SAFE_DELETE(m_pNetOperator);
}

//////////////////////////////////////////////////////////////////////////////////////////////

int NeuralNet::Init(const NetGene& netGene)
{
	// ������ ����
	SAFE_DELETE(m_pNetGene);
	m_pNetGene = new NetGene(netGene);

	// �Ű�� �����ڿ� ���������� ����
	m_pNetOperator->Setup(m_pNetGene, this);

	// �Ű�� ����
	NetMaker netMaker;

	netMaker.Setup(netGene);

	netMaker.Create(this);


	return 0;
}


int NeuralNet::Update()
{
	// NOTE: �ӽ�. Ŭ���� ������ Ȱ��ȭ��Ŵ
	if (cCore::Input.MouseDown(VK_LBUTTON) || cCore::Input.MousePress(VK_LBUTTON))
	{
		for (size_t i = 0; i < m_pNeuronList.size(); ++i)
		{
			Neuron* const pCurrNeuron = m_pNeuronList[i];


			if (cCore::ShapeMath.GetDistanceSq(&cCore::Input.fCursorPos(), pCurrNeuron->GetPos())
				< 8.f*8.f)
			{
				pCurrNeuron->Activate();
				m_pNetOperator->AddNeuron(pCurrNeuron, true);

				break;
			}
		}
	}


	// ��ȣ�帧 ����
	m_pNetOperator->Update();


	// ȣ���� ����
	m_pHormoneState->Update();


	return 0;
}


int NeuralNet::Render()
{
	// �ó��� �׸���
	cCore::Resource.Line.SetWidth(1.0f);
	cCore::Resource.Line.Begin();

	for (size_t i = 0; i < m_pSypList.size(); ++i)
	{
		Synapse* const pSyp = m_pSypList[i];


		pSyp->Draw();
	}

	cCore::Resource.Line.End();

	// NOTE: �ӽ�. ���콺�� ����Ű�� ������ ������ ����½ó�������ġ�� ���
	for (size_t i = 0; i < m_pNeuronList.size(); ++i)
	{
		Neuron* const pCurrNeuron = m_pNeuronList[i];


		if (cCore::ShapeMath.GetDistanceSq(&cCore::Input.fCursorPos(), pCurrNeuron->GetPos())
			< 8.f*8.f)
		{
			pCurrNeuron->GetInSypList()->Foreach([](Synapse* pSyp) {
				pSyp->RenderWeight();
			});
			pCurrNeuron->GetOutSypList()->Foreach([](Synapse* pSyp) {
				pSyp->RenderWeight();
			});

			Util::TempOffCamera tempOffCam;
			Util::ShowNumber(pCurrNeuron->GetSignal(), (int)cCore::Input.fCursorPos().x + 8,
				(int)cCore::Input.fCursorPos().y - 8, 0xffffffff);

			break;
		}
	}

	// ������ �׸���
	cCore::Sprite.BeginDraw();

	for (size_t i = 0; i < m_pLayerList.size(); ++i)
	{
		NeuronLayer* const pLayer = m_pLayerList[i];


		pLayer->Draw();
	}

	cCore::Sprite.EndDraw();


	// �Ű�� ������ ǥ��
	m_pNetOperator->Render();


	// �Ű�� ���� ǥ��
	Util::ShowText("NeuronCnt: %u", 8.f, 128.f, 0xffffffff, &cCore::Resource.Font0,
		m_pNeuronList.size());
	Util::ShowText("SypCnt: %u", 8.f, 128.f+18.f, 0xffffffff, &cCore::Resource.Font0,
		m_pSypList.size());


	// ȣ���� ���� ǥ��
	m_pHormoneState->Render();


	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////

int NeuralNet::AddNeuron(Neuron* pNeuron)
{
#ifdef _DEBUG
	if (pNeuron == nullptr)
	{
		assert(false);
		return -1;
	}
#endif


	m_pNeuronList.emplace_back(pNeuron);


	int layerNum = pNeuron->GetLayerNum();

	if (layerNum >= 0)
	{
		while (CAST(layerNum, size_t) >= m_pLayerList.size())
		{
			m_pLayerList.emplace_back(new NeuronLayer());
		}

		m_pLayerList[layerNum]->AddNeuron(pNeuron, false);
	}


	// ��ó�� �ִ� ��迡 ���
	size_t axonCnt = m_pAxonList.size();
	for (size_t i = 0; i < axonCnt; ++i)
	{
		Axon* const pAxon = m_pAxonList[i];


		if (pAxon->CheckNeuronInNear(pNeuron))
		{
			pAxon->AddNearNeuron(pNeuron);
		}
	}


	return 0;
}


int NeuralNet::AddSynapse(Synapse* pSyp)
{
#ifdef _DEBUG
	if (pSyp == nullptr)
	{
		assert(false);
		return -1;
	}
#endif


	m_pSypList.emplace_back(pSyp);


	return 0;
}


int NeuralNet::AddAxon(Axon* pAxon)
{
#ifdef _DEBUG
	if (pAxon == nullptr)
	{
		assert(false);
		return -1;
	}
#endif


	m_pAxonList.emplace_back(pAxon);


	// ��� ��ó�� �ִ� ������ ���
	size_t neuronCnt = m_pNeuronList.size();
	for (size_t i = 0; i < neuronCnt; ++i)
	{
		Neuron* const pNeuron = m_pNeuronList[i];


		if (pAxon->CheckNeuronInNear(pNeuron))
		{
			pAxon->AddNearNeuron(pNeuron);
		}
	}


	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////

const NeuronPotential& NeuralNet::GetSignalInfo() const
{
	return *m_pSignalInfo;
}


HormoneState* NeuralNet::GetHormoneState()
{
	return m_pHormoneState;
}

//////////////////////////////////////////////////////////////////////////////////////////////

int NeuralNet::ActivatePNHormone(double hormoneValue)
{
	// TODO: 


	return 0;
}

