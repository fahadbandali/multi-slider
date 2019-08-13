#include <wx/wx.h>
#include "myDoubleSlider.h"
#include "mytripleslider.h"

class play : public wxFrame
{
public:
	play(const wxString& title);


	void OnSpinCtrl1Change(wxSpinEvent & event);

	int Getstep();

	wxBitmapButton *playbutton;
	wxBitmapButton *pausebutton;
	wxBitmapButton *forwardbutton;
	wxBitmapButton *rewindbutton;

	wxSlider *m_slider;
	int pos;
	int step;

	wxSpinCtrl *Spin;


};

