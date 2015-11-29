#include "NetGene.h"

#include "cCore.h"







































NetGene::NetGene()
	: neuronNumPerGuide(0)
	, inAxonNumPerNeuron(0), outAxonNumPerNeuron(0)
	, inAxonDistance(0.f), outAxonDistance(0.f)
	, maxBeginSynapseNumPerAxon(0)
	, inhibitorySynapseRate(0.f)

	, hebbRate(0.00001)
	, minSynapseWeight(-2.0), maxSynapseWeight(2.0)
{

}


NetGene::NetGene(unsigned int randSeed)
{
	srand(randSeed);


	auto RandF = [](float scale) {return (rand() % 2) ? static_cast<float>(rand()) / RAND_MAX * scale : static_cast<float>(rand()) / RAND_MAX * -scale; };
	auto RandRangeF = [](int range) {return (rand() % 2) ? static_cast<float>(rand()) / RAND_MAX * (rand() % range) : static_cast<float>(rand()) / RAND_MAX * -(rand() % range); };


	/* 신경망 생성시 필요 */
	int guideCount = 8 + rand() % 32;
	for (int i = 0; i < guideCount; ++i)
	{
		D3DXVECTOR2 pos(RandRangeF(512), RandRangeF(512));
		int layerNum = rand() % 8;
		D3DXVECTOR2 dir(RandRangeF(256), RandRangeF(256));
		NeuronTypes neuronType = NeuronTypes::Normal;
		if (Util::Probable(10.0))
		{
			if (Util::Probable(50.0))
				neuronType = NeuronTypes::Positive;
			else
				neuronType = NeuronTypes::Negative;
		}

		guideList.emplace_back(pos/*평면 위치*/,
			layerNum/*레이어상 위치*/,
			dir/*방향*/,
			neuronType/*뉴런 종류*/);
	}


	neuronNumPerGuide = 3 + rand() % 64;


	inAxonNumPerNeuron = 1 + rand() % 3;
	outAxonNumPerNeuron = 1 + rand() % 3;


	inAxonDistance = 64.f + rand() % 256;
	outAxonDistance = 64.f + rand() % 256;


	maxBeginSynapseNumPerAxon = 3 + rand() % 16;


	inhibitorySynapseRate = static_cast<float>(rand()) / RAND_MAX * 100.f;


	/* 신경망 학습에 필요 */
	hebbRate = static_cast<double>(rand()) / RAND_MAX * 0.0001;


	minSynapseWeight = -0.4 + static_cast<double>(rand()) / RAND_MAX * -4.0;
	maxSynapseWeight = 0.4 + static_cast<double>(rand()) / RAND_MAX * 4.0;
}


NetGene::NetGene(const NetGene& other)
{
	this->operator=(other);
}


NetGene& NetGene::operator= (const NetGene& other)
{
	if (this == &other)
		return *this;


	guideList = other.guideList;
	neuronNumPerGuide = other.neuronNumPerGuide;
	inAxonNumPerNeuron = other.inAxonNumPerNeuron;
	outAxonNumPerNeuron = other.outAxonNumPerNeuron;
	inAxonDistance = other.inAxonDistance;
	outAxonDistance = other.outAxonDistance;
	maxBeginSynapseNumPerAxon = other.maxBeginSynapseNumPerAxon;
	inhibitorySynapseRate = other.inhibitorySynapseRate;

	hebbRate = other.hebbRate;
	minSynapseWeight = other.minSynapseWeight;
	maxSynapseWeight = other.maxSynapseWeight;


	return *this;
}

//////////////////////////////////////////////////////////////////////////////////////////////

