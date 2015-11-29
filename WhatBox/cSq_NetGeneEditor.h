#pragma once
#include "cSequence.h"

class FpsViewer;
class WhatAI;
class NetGeneEditor;

















class cSq_NetGeneEditor : public cSequence
{
public:
	cSq_NetGeneEditor();
	~cSq_NetGeneEditor();


private:
	FpsViewer* m_pFpsViewer;


private:
	NetGeneEditor* m_pNetEditor;
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

