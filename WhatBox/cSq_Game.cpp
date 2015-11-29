#include "cSq_Game.h"

#include "cCore.h"

#include "FpsViewer.h"
#include "WhatAI.h"

#include "NetGene.h"

#include "cSq_Main.h"





































cSq_Game::cSq_Game()
	: m_pFpsViewer(new FpsViewer())

	, m_pTestAI(new WhatAI())
{
	
}


cSq_Game::~cSq_Game()
{
	SAFE_DELETE(m_pFpsViewer);

	SAFE_DELETE(m_pTestAI);
}

/*----------------------------------------------------------------------------------*/

int cSq_Game::OnInit()
{
	cCore::Sprite.OnCamera(); // 2D ī�޶� �ѱ�


	NetGene randNetGene(rand());
	m_pTestAI->Init(randNetGene);


	return 0;
}


int cSq_Game::OnCleanUp()
{
	


	return 0;
}



int cSq_Game::OnRestore()
{



	return 0;
}


int cSq_Game::OnRelease()
{



	return 0;
}



int cSq_Game::OnDelete()   //�Ϲ� ������ '����'(������ �ƴ�)
{
	


	return 0;
}



cSequence* cSq_Game::OnUpdate()
{
	cSequence* pNext = this;
	/*--------------------------------*/


	if(cCore::Input.KeyDown(VK_ESCAPE)) // ESCŰ�� ���θ޴��� �̵�
		return new cSq_Main();


	cCore::Camera2D.Control(); // 2D ��������Ʈ ī�޶� ����


	// �ùķ��̼� �ӵ� ����
	if (cCore::Input.KeyDown(VK_OEM_4))
		cCore::TimeMgr.SetSpeed(cCore::TimeMgr.GetSpeed() / 2.0);
	else if (cCore::Input.KeyDown(VK_OEM_6))
		cCore::TimeMgr.SetSpeed(cCore::TimeMgr.GetSpeed() * 2.0);


	// FPS ����
	m_pFpsViewer->Update();


	// �׽�Ʈ AI ����
	m_pTestAI->Update();


	/*--------------------------------*/
	return pNext;
}


int cSq_Game::OnRender()
{
	// �׽�Ʈ AI ���
	m_pTestAI->Render();


	// FPS ���
	m_pFpsViewer->Render();


	return 0;
}

