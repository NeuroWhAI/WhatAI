#pragma once
#include "cSequence.h"

class FpsViewer;
class WhatAI;








































class cSq_Game : public cSequence
{
public:
	cSq_Game();
	~cSq_Game();


private:
	FpsViewer* m_pFpsViewer;


private:
	WhatAI* m_pTestAI;


private:
	virtual int OnInit();
	virtual int OnCleanUp();

	virtual int OnRestore();
	virtual int OnRelease();

	virtual int OnDelete();   //�Ϲ� ������ '����'(������ �ƴ�)
	
	virtual cSequence* OnUpdate();
	virtual int OnRender();
};

