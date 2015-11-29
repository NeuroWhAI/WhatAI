#pragma once
#include <vector>

#include "NetGuideline.h"







































class NetGene
{
public:
	NetGene();
	explicit NetGene(unsigned int randSeed);
	NetGene(const NetGene& other);
	NetGene& operator= (const NetGene& other);


public: /* 신경망 생성시 필요 */
	std::vector<NetGuideline> guideList;					// 안내선 목록
	int neuronNumPerGuide;									// 안내선당 뉴런 수
	int inAxonNumPerNeuron, outAxonNumPerNeuron;			// 뉴런당 입력/출력 축삭 수
	float inAxonDistance, outAxonDistance;					// 뉴런과 입력/출력 축삭과의 거리
	int maxBeginSynapseNumPerAxon;							// 초기 시냅스 배치시 최대 수
	float inhibitorySynapseRate;							// 전체 시냅스에서 억제성 시냅스의 비율


public: /* 신경망 학습에 필요 */
	double hebbRate;										// 햅가소성 학습률
	double minSynapseWeight, maxSynapseWeight;				// 최소/최대 시냅스 가중치값
};

