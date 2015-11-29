#include "WhatAI.h"

#include "cCore.h"

#include "NeuralNet.h"







































WhatAI::WhatAI()
	: m_pNet(new NeuralNet())
{

}


WhatAI::~WhatAI()
{
	SAFE_DELETE(m_pNet);
}

//////////////////////////////////////////////////////////////////////////////////////////////

int WhatAI::Init(const NetGene& netGene)
{
	m_pNet->Init(netGene);


	return 0;
}


int WhatAI::Update()
{
	m_pNet->Update();


	return 0;
}


int WhatAI::Render()
{
	m_pNet->Render();


	return 0;
}

