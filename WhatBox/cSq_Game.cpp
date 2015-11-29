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
	cCore::Sprite.OnCamera(); // 2D 카메라 켜기


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



int cSq_Game::OnDelete()   //일반 변수들 '삭제'(해제가 아님)
{
	


	return 0;
}



cSequence* cSq_Game::OnUpdate()
{
	cSequence* pNext = this;
	/*--------------------------------*/


	if(cCore::Input.KeyDown(VK_ESCAPE)) // ESC키로 메인메뉴로 이동
		return new cSq_Main();


	cCore::Camera2D.Control(); // 2D 스프라이트 카메라 조작


	// 시뮬레이션 속도 조절
	if (cCore::Input.KeyDown(VK_OEM_4))
		cCore::TimeMgr.SetSpeed(cCore::TimeMgr.GetSpeed() / 2.0);
	else if (cCore::Input.KeyDown(VK_OEM_6))
		cCore::TimeMgr.SetSpeed(cCore::TimeMgr.GetSpeed() * 2.0);


	// FPS 갱신
	m_pFpsViewer->Update();


	// 테스트 AI 갱신
	m_pTestAI->Update();


	/*--------------------------------*/
	return pNext;
}


int cSq_Game::OnRender()
{
	// 테스트 AI 출력
	m_pTestAI->Render();


	// FPS 출력
	m_pFpsViewer->Render();


	return 0;
}

