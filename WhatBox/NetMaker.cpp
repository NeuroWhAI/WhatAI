#include "NetMaker.h"

#include <assert.h>
#include <numeric>

#include "cCore.h"

#include "NetGene.h"
#include "NeuralNet.h"
#include "Neuron.h"

#include "Synapse.h"
#include "Axon.h"

#include "NeuronFactory.h"
#include "SynapseFactory.h"
#include "AxonFactory.h"
#include "SynapsePort.h"







































NetMaker::NetMaker()
	: m_pNetGene(nullptr)
{

}


NetMaker::~NetMaker()
{
	SAFE_DELETE(m_pNetGene);
}

//////////////////////////////////////////////////////////////////////////////////////////////

int NetMaker::Setup(const NetGene& netGene)
{
	SAFE_DELETE(m_pNetGene);
	m_pNetGene = new NetGene(netGene);


	return 0;
}


int NetMaker::Create(NeuralNet* pNet)
{
	if (m_pNetGene == nullptr)
	{
		assert(false);
		return -1;
	}


	std::vector<DirNeuron> neuronList;
	std::vector<Axon*> pAxonList;


	// 안내선을 중심으로 근처에 뉴런을 배치
	const size_t guideCnt = m_pNetGene->guideList.size();
	for (size_t g = 0; g < guideCnt; ++g)
	{
		NetGuideline& guideline = m_pNetGene->guideList[g];
		const D3DXVECTOR2* const pGuidePos = guideline.GetPos();
		const int guideLayerNum = guideline.GetLayerNum();
		const NeuronTypes neuronType = guideline.GetNeuronType();


		for (int n = 0; n < m_pNetGene->neuronNumPerGuide; ++n)
		{
			// 뉴런 생성
			D3DXVECTOR2 neuronPos(Util::GetRandomF(64.f), Util::GetRandomF(64.f));
			D3DXVec2Add(&neuronPos, pGuidePos, &neuronPos);
			neuronPos.x += Util::GetRandomF(16.f);
			neuronPos.y += Util::GetRandomF(16.f);
			Neuron* const pNeuron = NeuronFactory::CreateNeuron(neuronType,
				neuronPos, guideLayerNum, pNet->GetSignalInfo());

			// 목록과 신경망에 추가
			neuronList.emplace_back(pNeuron);
			pNet->AddNeuron(pNeuron);
		}
	}


	// 안내선을 이용해서 뉴런의 방향을 계산하고 축삭을 배치
	const size_t neuronCnt = neuronList.size();
	for (size_t n = 0; n < neuronCnt; ++n)
	{
		DirNeuron& dirNeuron = neuronList[n];
		const D3DXVECTOR2* const pNeuronPos = dirNeuron.pNeuron->GetPos();


		// 방향계산
		for (size_t g = 0; g < guideCnt; ++g)
		{
			NetGuideline& guideline = m_pNetGene->guideList[g];


			// 안내선의 방향에 뉴런과의 거리를 나눠서 뉴런의 방향에 더함
			float distance = cCore::ShapeMath.GetDistance(pNeuronPos, guideline.GetPos());
			if (distance > 2048.f) continue; // 너무 멀리있으면 그냥 계산하지않음
			else if (distance < std::numeric_limits<float>::epsilon()) distance = std::numeric_limits<float>::epsilon();

			D3DXVECTOR2 addVec = *guideline.GetDir() / (distance * 0.1f);

			D3DXVec2Add(&dirNeuron.dir, &dirNeuron.dir, &addVec);
		}


		// 축삭배치 준비
		const float neuronDirDegree = D3DXToDegree(atan2f(dirNeuron.dir.y, dirNeuron.dir.x));

		// 입력축삭 배치
		for (int inAxonCnt = 0; inAxonCnt < m_pNetGene->inAxonNumPerNeuron; ++inAxonCnt)
		{
			float randomDegree = neuronDirDegree + 180.f + Util::GetRandomF(32.f);
			D3DXVECTOR2 axonRelativePos;
			cCore::ShapeMath.GetPosition(&axonRelativePos,
				m_pNetGene->inAxonDistance,
				randomDegree);

			// 축삭생성 (내부적으로 뉴런과 연결을 이룸)
			Axon* pAxon = AxonFactory::CreateAxon(AxonTypes::Input, dirNeuron.pNeuron,
				axonRelativePos);

			// 목록과 신경망에 추가 (내부적으로 인접뉴런목록도 작성함)
			pAxonList.emplace_back(pAxon);
			pNet->AddAxon(pAxon);
		}

		// 출력축삭 배치
		for (int outAxonCnt = 0; outAxonCnt < m_pNetGene->outAxonNumPerNeuron; ++outAxonCnt)
		{
			float randomDegree = neuronDirDegree + Util::GetRandomF(16.f);
			D3DXVECTOR2 axonRelativePos;
			cCore::ShapeMath.GetPosition(&axonRelativePos,
				m_pNetGene->outAxonDistance,
				randomDegree);

			// 축삭생성 (내부적으로 뉴런과 연결을 이룸)
			Axon* pAxon = AxonFactory::CreateAxon(AxonTypes::Output, dirNeuron.pNeuron,
				axonRelativePos);

			// 목록과 신경망에 추가 (내부적으로 인접뉴런목록도 작성함)
			pAxonList.emplace_back(pAxon);
			pNet->AddAxon(pAxon);
		}
	}


	// 축삭의 정보로 시냅스 생성후 초기연결
	const double inhibitorySynapseRate = static_cast<double>(m_pNetGene->inhibitorySynapseRate);

	size_t axonCnt = pAxonList.size();
	for (size_t a = 0; a < axonCnt; ++a)
	{
		Axon* const pAxon = pAxonList[a];


		auto nearNeuronList = pAxon->GetNearNeuronList();
		size_t nearNeuronCnt = nearNeuronList.size();
		if (nearNeuronCnt > CAST(m_pNetGene->maxBeginSynapseNumPerAxon, size_t))
			nearNeuronCnt = CAST(m_pNetGene->maxBeginSynapseNumPerAxon, size_t);
		Neuron* pCenterNeuron = pAxon->GetCenterNeuron();

		if (pAxon->GetAxonType() == AxonTypes::Input)
		{
			for (size_t neuronLoopCnt = 0; neuronLoopCnt < nearNeuronCnt; ++neuronLoopCnt)
			{
				if (nearNeuronList[neuronLoopCnt]->GetOutSypList()->CheckOutputOverlap(pCenterNeuron) == false)
				{
					Synapse* pSyp = SynapseFactory::CreateSynapse(nearNeuronList[neuronLoopCnt], pCenterNeuron,
						Util::Probable(inhibitorySynapseRate)
						? -fabsf(Util::GetRandomF(1.f)) : fabsf(Util::GetRandomF(0.1f)));

					// 신경망에 추가
					pNet->AddSynapse(pSyp);
				}
			}
		}
		else if (pAxon->GetAxonType() == AxonTypes::Output)
		{
			for (size_t neuronLoopCnt = 0; neuronLoopCnt < nearNeuronCnt; ++neuronLoopCnt)
			{
				if (nearNeuronList[neuronLoopCnt]->GetInSypList()->CheckInputOverlap(pCenterNeuron) == false)
				{
					Synapse* pSyp = SynapseFactory::CreateSynapse(pCenterNeuron, nearNeuronList[neuronLoopCnt],
						Util::Probable(inhibitorySynapseRate)
						? -fabsf(Util::GetRandomF(1.f)) : fabsf(Util::GetRandomF(0.1f)));

					// 신경망에 추가
					pNet->AddSynapse(pSyp);
				}
			}
		}
	}


	return 0;
}

