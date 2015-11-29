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
	// 여유공간 할당
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
	// 유전자 저장
	SAFE_DELETE(m_pNetGene);
	m_pNetGene = new NetGene(netGene);

	// 신경망 진행자에 유전자정보 설정
	m_pNetOperator->Setup(m_pNetGene, this);

	// 신경망 생성
	NetMaker netMaker;

	netMaker.Setup(netGene);

	netMaker.Create(this);


	return 0;
}


int NeuralNet::Update()
{
	// NOTE: 임시. 클릭한 뉴런을 활성화시킴
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


	// 신호흐름 진행
	m_pNetOperator->Update();


	// 호르몬 갱신
	m_pHormoneState->Update();


	return 0;
}


int NeuralNet::Render()
{
	// 시냅스 그리기
	cCore::Resource.Line.SetWidth(1.0f);
	cCore::Resource.Line.Begin();

	for (size_t i = 0; i < m_pSypList.size(); ++i)
	{
		Synapse* const pSyp = m_pSypList[i];


		pSyp->Draw();
	}

	cCore::Resource.Line.End();

	// NOTE: 임시. 마우스가 가르키는 뉴런의 전위와 입출력시냅스가중치를 출력
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

	// 뉴런층 그리기
	cCore::Sprite.BeginDraw();

	for (size_t i = 0; i < m_pLayerList.size(); ++i)
	{
		NeuronLayer* const pLayer = m_pLayerList[i];


		pLayer->Draw();
	}

	cCore::Sprite.EndDraw();


	// 신경망 진행자 표시
	m_pNetOperator->Render();


	// 신경망 정보 표시
	Util::ShowText("NeuronCnt: %u", 8.f, 128.f, 0xffffffff, &cCore::Resource.Font0,
		m_pNeuronList.size());
	Util::ShowText("SypCnt: %u", 8.f, 128.f+18.f, 0xffffffff, &cCore::Resource.Font0,
		m_pSypList.size());


	// 호르몬 정보 표시
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


	// 근처에 있는 축삭에 등록
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


	// 축삭 근처에 있는 뉴런을 등록
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

