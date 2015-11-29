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


public: /* �Ű�� ������ �ʿ� */
	std::vector<NetGuideline> guideList;					// �ȳ��� ���
	int neuronNumPerGuide;									// �ȳ����� ���� ��
	int inAxonNumPerNeuron, outAxonNumPerNeuron;			// ������ �Է�/��� ��� ��
	float inAxonDistance, outAxonDistance;					// ������ �Է�/��� ������ �Ÿ�
	int maxBeginSynapseNumPerAxon;							// �ʱ� �ó��� ��ġ�� �ִ� ��
	float inhibitorySynapseRate;							// ��ü �ó������� ������ �ó����� ����


public: /* �Ű�� �н��� �ʿ� */
	double hebbRate;										// �ݰ��Ҽ� �н���
	double minSynapseWeight, maxSynapseWeight;				// �ּ�/�ִ� �ó��� ����ġ��
};

