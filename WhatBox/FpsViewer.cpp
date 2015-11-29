#include "FpsViewer.h"

#include "cCore.h"







































FpsViewer::FpsViewer()
{

}


FpsViewer::~FpsViewer()
{

}

//////////////////////////////////////////////////////////////////////////////////////////////

int FpsViewer::Update()
{



	return 0;
}


int FpsViewer::Render()
{
	Util::ShowText("FPS:%.1f\nx%.3lf", 8.f, 8.f, 0xff00ff00, &cCore::Resource.Font0,
		1000.f/(cCore::ElapsedTime*1000.f), cCore::TimeMgr.GetSpeed());


	return 0;
}

