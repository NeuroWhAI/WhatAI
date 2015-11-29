#include "cSq_NetGeneEditor.h"

#include "cCore.h"

#include "cSq_Main.h"

#include "FpsViewer.h"
#include "WhatAI.h"
#include "NetGeneEditor.h"

#include "NetGene.h"


















cSq_NetGeneEditor::cSq_NetGeneEditor()
	: m_pFpsViewer(new FpsViewer())

	, m_pNetEditor(new NetGeneEditor())
	, m_pTestAI(nullptr)
{

}


cSq_NetGeneEditor::~cSq_NetGeneEditor()
{
	SAFE_DELETE(m_pFpsViewer);

	SAFE_DELETE(m_pNetEditor);
	SAFE_DELETE(m_pTestAI);
}

/*----------------------------------------------------------------------------------*/

int cSq_NetGeneEditor::OnInit()
{
	cCore::Sprite.OnCamera(); // 2D 카메라 켜기


	if (m_pTestAI != nullptr)
	{
		NetGene randomNetGene(rand());
		m_pTestAI->Init(randomNetGene);
	}


	return 0;
}


int cSq_NetGeneEditor::OnCleanUp()
{



	return 0;
}



int cSq_NetGeneEditor::OnRestore()
{



	return 0;
}


int cSq_NetGeneEditor::OnRelease()
{



	return 0;
}



int cSq_NetGeneEditor::OnDelete()   //일반 변수들 '삭제'(해제가 아님)
{



	return 0;
}



cSequence* cSq_NetGeneEditor::OnUpdate()
{
	cSequence* pNext = this;
	/*--------------------------------*/


	cCore::Camera2D.Control(); // 2D 스프라이트 카메라 조작


	if (cCore::Input.KeyDown(VK_ESCAPE))
	{
		if (m_pTestAI != nullptr)
		{
			SAFE_DELETE(m_pTestAI);
		}
		else
		{
			return new cSq_Main;
		}
	}
	else if (cCore::Input.KeyDown(VK_RETURN))
	{
		SAFE_DELETE(m_pTestAI);

		NetGene tempGene;
		m_pNetEditor->GetGene(&tempGene);

		m_pTestAI = new WhatAI();
		m_pTestAI->Init(tempGene);
	}


	// 시뮬레이션 속도 조절
	if (cCore::Input.KeyDown(VK_OEM_4))
		cCore::TimeMgr.SetSpeed(cCore::TimeMgr.GetSpeed() / 2.0);
	else if (cCore::Input.KeyDown(VK_OEM_6))
		cCore::TimeMgr.SetSpeed(cCore::TimeMgr.GetSpeed() * 2.0);


	// FPS 갱신
	m_pFpsViewer->Update();


	// 테스트 AI 갱신
	if (m_pTestAI != nullptr)
	{
		m_pTestAI->Update();
	}
	else
	{
		m_pNetEditor->Update();
	}


	/*--------------------------------*/
	return pNext;
}


int cSq_NetGeneEditor::OnRender()
{
	// 테스트 AI 출력
	if (m_pTestAI != nullptr)
	{
		m_pTestAI->Render();
	}
	else
	{
		m_pNetEditor->Render();
	}


	// FPS 출력
	m_pFpsViewer->Render();


	return 0;
}

