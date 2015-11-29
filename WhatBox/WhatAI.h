#pragma once
#include <d3dx9.h>

class NeuralNet;
class NetGene;







































class WhatAI
{
public:
	WhatAI();
	virtual ~WhatAI();


private:
	NeuralNet* m_pNet;


public:
	int Init(const NetGene& netGene);
	int Update();
	int Render();
};

