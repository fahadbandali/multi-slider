#include "main.h"
#include "play.h"
#include "selectslidercontrol.h"

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{

	play *bb = new play(wxT("BitmapButton"));
	bb->Show(true);

	slidercontrol *slide = new slidercontrol(wxT("Slider Control"));
	slide->Show(true);

	return true;
}