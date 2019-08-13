#include "selectslidercontrol.h"
#include <wx/checkbox.h>
#include <wx/wx.h>

slidercontrol::slidercontrol(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(500, 470))
{

	wxPanel *main = new wxPanel(this, wxID_ANY);
	wxBoxSizer *mainVertical = new wxBoxSizer(wxVERTICAL);
	
	wxBoxSizer *slider1sizer = new wxBoxSizer(wxHORIZONTAL);
	wxCheckBox *slider1check = new wxCheckBox(main, ID_SLIDE1, "slider1");
	wxTextCtrl *TimeText1 = new wxTextCtrl(main, wxID_ANY, _("Time1"));
	wxTextCtrl *FrameText1 = new wxTextCtrl(main, wxID_ANY, _("Frame1"));

	wxBoxSizer *slider2sizer = new wxBoxSizer(wxHORIZONTAL);
	wxCheckBox *slider2check = new wxCheckBox(main, ID_SLIDE2, "slider2");
	wxTextCtrl *TimeText2 = new wxTextCtrl(main, wxID_ANY, _("Time2"));
	wxTextCtrl *FrameText2 = new wxTextCtrl(main, wxID_ANY, _("Frame2"));

	wxBoxSizer *slider3sizer = new wxBoxSizer(wxHORIZONTAL);
	wxCheckBox *slider3check = new wxCheckBox(main, ID_SLIDE3, "slider3");
	wxTextCtrl *TimeText3 = new wxTextCtrl(main, wxID_ANY, _("Time3"));
	wxTextCtrl *FrameText3 = new wxTextCtrl(main, wxID_ANY, _("Frame3"));

	wxBoxSizer *slider4sizer = new wxBoxSizer(wxHORIZONTAL);
	wxCheckBox *slider4check = new wxCheckBox(main, ID_SLIDE4, "slider4");
	wxTextCtrl *TimeText4 = new wxTextCtrl(main, wxID_ANY, _("Time4"));
	wxTextCtrl *FrameText4 = new wxTextCtrl(main, wxID_ANY, _("Frame4"));

	slider1sizer->Add(slider1check, 1, wxLEFT);
	slider1sizer->Add(TimeText1, 1, wxRIGHT);
	slider1sizer->Add(FrameText1, 1, wxRIGHT);
	

	slider2sizer->Add(slider2check, 1, wxLEFT);
	slider2sizer->Add(TimeText2, 1, wxRIGHT);
	slider2sizer->Add(FrameText2, 1, wxRIGHT);
	
	slider3sizer->Add(slider3check, 1, wxLEFT);
	slider3sizer->Add(TimeText3, 1, wxRIGHT);
	slider3sizer->Add(FrameText3, 1, wxRIGHT);
	

	slider4sizer->Add(slider4check, 1, wxLEFT);
	slider4sizer->Add(TimeText4, 1, wxRIGHT);
	slider4sizer->Add(FrameText4, 1, wxRIGHT);
	


	mainVertical->Add(slider1sizer, 1, wxEXPAND);
	mainVertical->Add(slider2sizer, 1, wxEXPAND);
	mainVertical->Add(slider3sizer, 1, wxEXPAND);
	mainVertical->Add(slider4sizer, 1, wxEXPAND);

	main->SetSizer(mainVertical);

	SetBackgroundColour(wxString("LIGHT_GREY"));
	Centre();

	Bind(wxEVT_COMMAND_MENU_SELECTED, &slidercontrol::select1, main, ID_SLIDE1);
	Bind(wxEVT_COMMAND_MENU_SELECTED, &slidercontrol::select2, main, ID_SLIDE2);
	Bind(wxEVT_COMMAND_MENU_SELECTED, &slidercontrol::select3, main, ID_SLIDE3);
	Bind(wxEVT_COMMAND_MENU_SELECTED, &slidercontrol::select4, main, ID_SLIDE4);
}

//need to be able to label each slider (need slider name)
//need to have check boxes to pick which one to move or multiple ones to move
//2 text boxes one showing frame number and the other showing time
// box with time, box with frame, name with the colour of the slider, checkbox

//use these functions to set the value of selectslider to whichever one was clicked, then in the slider functions check the value of select slider

void slidercontrol::select1(wxCommandEvent & event)
{
	bool check = slider1check->GetValue();
	if (check = true) selected = 1;
	
}

void slidercontrol::select2(wxCommandEvent & event)
{
	bool check = slider2check->GetValue();
	if (check = true) selected = 2;

}

void slidercontrol::select3(wxCommandEvent & event)
{
	bool check = slider3check->GetValue();
	if (check = true) selected = 3;
}

void slidercontrol::select4(wxCommandEvent & event)
{
	bool check = slider4check->GetValue();
	if (check = true) selected = 4;
}

int slidercontrol::getselect() {
	return selected;
}