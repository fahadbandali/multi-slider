#include <wx/wx.h>

class slidercontrol : public wxFrame
{
public:
	slidercontrol(const wxString& title);

	void select1(wxCommandEvent & event);
	void select2(wxCommandEvent & event);
	void select3(wxCommandEvent & event);
	void select4(wxCommandEvent & event);

	int getselect();

	int selected;

	wxCheckBox* slider1check;
	wxCheckBox* slider2check;
	wxCheckBox* slider3check;
	wxCheckBox* slider4check;

};

enum {

	ID_SLIDE1 = 420,
	ID_SLIDE2 = 422,
	ID_SLIDE3 = 424,
	ID_SLIDE4 = 426,

};