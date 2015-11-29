#include "cSq_Main.h"

#include "cCore.h"

#include "cSq_Game.h"
#include "cSq_NetGeneEditor.h"






















cSq_Main::cSq_Main()
{

}


cSq_Main::~cSq_Main()
{

}

/*----------------------------------------------------------------------------------*/

int cSq_Main::OnInit()
{
	


	return 0;
}


int cSq_Main::OnCleanUp()
{
	


	return 0;
}



int cSq_Main::OnRestore()
{



	return 0;
}


int cSq_Main::OnRelease()
{



	return 0;
}



int cSq_Main::OnDelete()   //일반 변수들 '삭제'(해제가 아님)
{
	


	return 0;
}



cSequence* cSq_Main::OnUpdate()
{
	cSequence* pNext = this;
	/*--------------------------------*/


	if(cCore::Input.KeyDown(VK_ESCAPE)) // NOTE: ESC키로 종료. 필요시 삭제.
		return EXIT_SEQ;


	if (cCore::Input.KeyDown(VK_F1))
		return new cSq_Game;
	else if (cCore::Input.KeyDown(VK_F2))
		return new cSq_NetGeneEditor;


	/*--------------------------------*/
	return pNext;
}


int cSq_Main::OnRender()
{
	cCore::Resource.Font1.ShowText("F1 : 테스트\nF2 : 신경망 제작",
		cCore::fWinSize.x / 2.f, cCore::fWinSize.y / 2.f,
		0xffffffff, DT_CENTER);


	return 0;
}

