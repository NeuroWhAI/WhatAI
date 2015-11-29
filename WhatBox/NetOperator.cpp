#include "NetOperator.h"

#include <assert.h>

#include "cCore.h"

#include "Neuron.h"
#include "NetGene.h"
#include "NeuralNet.h"
#include "HormoneState.h"

#include "SynapsePort.h"
#include "Synapse.h"
#include "AxonPort.h"
#include "Axon.h"
#include "SynapseFactory.h"
#include "NeuronPotential.h"







































NetOperator::NetOperator()
	: m_pNetGene(nullptr)
	, m_pNeuralNet(nullptr)
	, m_pHormoneState(nullptr)
{
	m_pCurrNeuronList.reserve(256/*여유공간*/);
	m_pUpdateNeuronList.reserve(256/*여유공간*/);
	m_pNextNeuronList.reserve(256/*여유공간*/);
}


NetOperator::~NetOperator()
{

}

//////////////////////////////////////////////////////////////////////////////////////////////

int NetOperator::Setup(const NetGene* pNetGene, NeuralNet* pNeuralNet)
{
#ifdef _DEBUG
	if (pNetGene == nullptr || pNeuralNet == nullptr
		||
		pNeuralNet->GetHormoneState() == nullptr)
	{
		assert(false);
		return -1;
	}
#endif

	m_pNetGene = pNetGene;
	m_pNeuralNet = pNeuralNet;
	m_pHormoneState = pNeuralNet->GetHormoneState();


	return 0;
}


int NetOperator::Update()
{
	// 갱신이 필요한 뉴런 갱신
	const size_t updateListCount = m_pUpdateNeuronList.size();
	for (size_t i = 0; i < updateListCount; ++i)
	{
		Neuron* const pNeuron = m_pUpdateNeuronList[i];

		if (pNeuron == nullptr) continue;


		// 갱신
		pNeuron->Update(m_pHormoneState);


		// 더이상 갱신할 필요가 없으면
		if (pNeuron->IsUpdateEnd())
		{
			// 목록에서 제거
			RemoveUpdateNeuronAt(i);
		}
	}


	// 출력측 계산
	const size_t currListCount = m_pCurrNeuronList.size();
	for (size_t i = 0; i < currListCount; ++i)
	{
		Neuron* const pNeuron = m_pCurrNeuronList[i];

		if (pNeuron == nullptr) continue;


		if (pNeuron->IsActivated())
		{
			const double inSignal = pNeuron->GetSignal();


			// 신호 전달
			SynapsePort& outSypList = *pNeuron->GetOutSypList();
			const size_t outSypCount = outSypList.GetCount();

			for (size_t s = 0; s < outSypCount; ++s)
			{
				Synapse* const pSyp = outSypList[s];

				if (pSyp == nullptr) continue;


				// 출력측 뉴런에 값 전달
				Neuron* const pNextNeuron = pSyp->GetOutNeuron();
				if (pNextNeuron->IsActivated() == false)
				{
					const double addSignal = inSignal * pSyp->GetWeight();
					pNextNeuron->AddSignal(addSignal * cCore::TimeMgr.GetFrameRate());

					// 다음단으로 예약
					m_pNextNeuronList.emplace_back(pNextNeuron);
				}
			}


			// 뉴런이 활동중일때 적용되는 규칙
			OnNeuronActivated(pNeuron, m_pNetGene);
		}
		else
		{
			RemoveNeuronAt(i);
		}
	}


	// 다음단 추가
	size_t nextListCount = m_pNextNeuronList.size();
	for (size_t i = 0; i < nextListCount; ++i)
	{
		Neuron* const pNeuron = m_pNextNeuronList[i];

		if (pNeuron->IsActivated()
			&&
			pNeuron->IsOnActivateUpdate() == false)
		{
			pNeuron->Activate();
			AddNeuron(pNeuron, true/*중복검사*/);
		}
		else
		{
			AddUpdateNeuron(pNeuron, true/*중복검사*/);
		}
	}
	m_pNextNeuronList.clear();


	return 0;
}


int NetOperator::Render()
{
	/*int count = 0;
	for (size_t i = 0; i < m_pCurrNeuronList.size(); ++i)
		if (m_pCurrNeuronList[i] != nullptr) ++count;
	Util::ShowText("Curr: %d/%u", 8.f, 128.f, 0xffffffff, &cCore::Resource.Font0,
		count, m_pCurrNeuronList.size());

	count = 0;
	for (size_t i = 0; i < m_pUpdateNeuronList.size(); ++i)
		if (m_pUpdateNeuronList[i] != nullptr) ++count;
	Util::ShowText("Updt: %d/%u", 8.f, 128.f+18.f, 0xffffffff, &cCore::Resource.Font0,
		count, m_pUpdateNeuronList.size());*/


	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////

int NetOperator::AddNeuron(Neuron* pNeuron, bool bCheckOverlap)
{
#ifdef _DEBUG
	if (pNeuron == nullptr)
	{
		assert(false);


		return -2;
	}
#endif


	AddUpdateNeuron(pNeuron, bCheckOverlap);


	const size_t listCount = m_pCurrNeuronList.size();

	size_t nullIdx = listCount;

	// 중복검사
	if (bCheckOverlap)
	{
		for (size_t i = 0; i < listCount; ++i)
		{
			if (m_pCurrNeuronList[i] == pNeuron)
			{
				return -1;
			}

			if (nullIdx == listCount && m_pCurrNeuronList[i] == nullptr)
			{
				nullIdx = i;
			}
		}
	}


	// 뉴런이 딱 활성화된 순간에 적용되는 규칙
	if (pNeuron->IsOnActivateUpdate())
	{
		WhenNeuronActivated(pNeuron, m_pNetGene);
	}


	if (nullIdx == listCount) nullIdx = 0;

	// 빈공간이 있으면 넣고 아니면 뒤에 추가
	for (size_t i = nullIdx; i < listCount; ++i)
	{
		if (m_pCurrNeuronList[i] == nullptr)
		{
			m_pCurrNeuronList[i] = pNeuron;


			return 0;
		}
	}

	m_pCurrNeuronList.emplace_back(pNeuron);


	return 0;
}


int NetOperator::RemoveNeuron(const Neuron* pNeuron)
{
	for (size_t i = 0; i < m_pCurrNeuronList.size(); ++i)
	{
		if (m_pCurrNeuronList[i] == pNeuron)
		{
			m_pCurrNeuronList[i] = nullptr;


			return 0;
		}
	}


	return -1;
}


int NetOperator::RemoveNeuronAt(int index)
{
	m_pCurrNeuronList[index] = nullptr;


	return 0;
}


int NetOperator::RemoveNeuronAt(size_t index)
{
	m_pCurrNeuronList[index] = nullptr;


	return 0;
}


std::vector<Neuron*>& NetOperator::GetCurrNeuronList()
{
	return m_pCurrNeuronList;
}

//////////////////////////////////////////////////////////////////////////////////////////////

int NetOperator::AddUpdateNeuron(Neuron* pNeuron, bool bCheckOverlap)
{
#ifdef _DEBUG
	if (pNeuron == nullptr)
	{
		assert(false);


		return -2;
	}
#endif


	const size_t listCount = m_pUpdateNeuronList.size();

	size_t nullIdx = listCount;

	// 중복검사
	if (bCheckOverlap)
	{
		for (size_t i = 0; i < listCount; ++i)
		{
			if (m_pUpdateNeuronList[i] == pNeuron)
			{
				return -1;
			}

			if (nullIdx == listCount && m_pUpdateNeuronList[i] == nullptr)
			{
				nullIdx = i;
			}
		}
	}

	if (nullIdx == listCount) nullIdx = 0;

	// 빈공간이 있으면 넣고 아니면 뒤에 추가
	for (size_t i = nullIdx; i < listCount; ++i)
	{
		if (m_pUpdateNeuronList[i] == nullptr)
		{
			m_pUpdateNeuronList[i] = pNeuron;


			return 0;
		}
	}

	m_pUpdateNeuronList.emplace_back(pNeuron);


	return 0;
}


int NetOperator::RemoveUpdateNeuron(const Neuron* pNeuron)
{
	for (size_t i = 0; i < m_pUpdateNeuronList.size(); ++i)
	{
		if (m_pUpdateNeuronList[i] == pNeuron)
		{
			m_pUpdateNeuronList[i] = nullptr;


			return 0;
		}
	}


	return -1;
}


int NetOperator::RemoveUpdateNeuronAt(int index)
{
	m_pUpdateNeuronList[index] = nullptr;


	return 0;
}


int NetOperator::RemoveUpdateNeuronAt(size_t index)
{
	m_pUpdateNeuronList[index] = nullptr;


	return 0;
}


std::vector<Neuron*>& NetOperator::GetUpdateNeuronList()
{
	return m_pUpdateNeuronList;
}

//////////////////////////////////////////////////////////////////////////////////////////////

int NetOperator::WhenNeuronActivated(Neuron* pNeuron, const NetGene* pNetGene)
{
	// Auto Synapse Creation
	AutoSynapseCreation(pNeuron, pNetGene);


	return 0;
}


int NetOperator::AutoSynapseCreation(Neuron* pNeuron, const NetGene* pNetGene)
{
	const double signal = pNeuron->GetSignal();

	AxonPort* const pAxonPort = pNeuron->GetInAxonList();

	const size_t axonCnt = pAxonPort->GetCount();
	for (size_t a = 0; a < axonCnt; ++a)
	{
		auto& neuronList = pAxonPort->At(a)->GetNearNeuronList();


		size_t neuronCnt = neuronList.size();
		for (size_t n = 0; n < neuronCnt; ++n)
		{
			Neuron* const pInNeuron = neuronList[n];


			if (pInNeuron->GetSignal() > signal)
			{
				if (pInNeuron->GetOutSypList()->CheckOutputOverlap(pNeuron) == false)
				{
					Synapse* pNewSyp = SynapseFactory::CreateSynapse(pInNeuron, pNeuron, 0.0001);

					if (pNewSyp != nullptr)
					{
						m_pNeuralNet->AddSynapse(pNewSyp);
					}
				}
			}
		}
	}


	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////

int NetOperator::OnNeuronActivated(Neuron* pNeuron, const NetGene* pNetGene)
{
	// Hebbian Learning Rule
	HebbLearningRule(pNeuron, pNetGene);

	// Hormone Effect
	HormoneEffect(pNeuron, pNetGene);


	return 0;
}


int NetOperator::HebbLearningRule(Neuron* pNeuron, const NetGene* pNetGene)
{
	SynapsePort& inSypList = *pNeuron->GetInSypList();
	const size_t inSypCount = inSypList.GetCount();

	for (size_t s = 0; s < inSypCount; ++s)
	{
		Synapse* const pSyp = inSypList[s];

		if (pSyp == nullptr) continue;


		// pNeuron의 입력뉴런이 활성상태이고 사이의 시냅스가 억제성이 아닐때 적용
		const double& weight = pSyp->GetWeight();
		Neuron* const pInNeuron = pSyp->GetInNeuron();

		if (weight > 0.0
			&&
			pInNeuron->IsActivated())
		{
			double dw = (pNetGene->maxSynapseWeight - weight) * pInNeuron->GetSignal() * pNetGene->hebbRate;
			pSyp->SetWeight(weight + dw*cCore::TimeMgr.GetFrameRate());
		}
	}


	return 0;
}


int NetOperator::HormoneEffect(Neuron* pNeuron, const NetGene* pNetGene)
{
	const double& SIGNAL_REST = m_pNeuralNet->GetSignalInfo().rest;
	double pnHormone = m_pHormoneState->GetPN();

	// 입력 시냅스에 대하여 호르몬 작용
	SynapsePort& inSypList = *pNeuron->GetInSypList();
	const size_t inSypCount = inSypList.GetCount();

	for (size_t s = 0; s < inSypCount; ++s)
	{
		Synapse* const pSyp = inSypList[s];

		if (pSyp == nullptr) continue;


		if (pSyp->GetInNeuron()->IsActivated() == false) continue;


		double weight = pSyp->GetWeight();
		double dw = (pNeuron->GetSignal() - SIGNAL_REST)*pnHormone*cCore::TimeMgr.GetFrameRate();
		
		if (dw < 0.0)
		{
			dw *= abs(m_pNetGene->minSynapseWeight - weight)*0.001; // 최솟값 제한
		}
		else
		{
			dw *= abs(m_pNetGene->maxSynapseWeight - weight)*0.001; // 최댓값 제한
		}

		// 가중치 변경
		pSyp->SetWeight(weight + dw);
	}


	return 0;
}

