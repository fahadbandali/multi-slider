#ifndef MYSINGLESLIDER
#define MYSINGLESLIDER


#include "wx/wx.h"
#include <wx/slider.h>
#include <wx/spinctrl.h>



class mysingleslider : public wxPanel
{
public:

	mysingleslider(wxPanel *parent,
		wxWindowID id,
		int mainValue, int minValue, int maxValue,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxSL_HORIZONTAL,
		const wxValidator& val = wxDefaultValidator,
		const wxString& name = "mytripleslider");


	int GetMainValue();

	void SetMainValue(int lval);
	wxSize DoGetBestSize();
	void OnPaint(wxPaintEvent&);
	void OnLeftDown(wxMouseEvent& event);
	void OnMotion(wxMouseEvent& event);
	void OnLeftUp(wxMouseEvent& event);
	void OnWheel(wxMouseEvent& event);
	void OnSize(wxSizeEvent & event);
	wxPanel *m_parent;



protected:
	void paintNow();
	void render(wxDC& dc);
	void DrawThumb(wxDC& dc, wxCoord x, wxCoord y);


private:

	int mainval, minval, maxval, step;
	int selectedslider;
	int prevx, prevy;
	wxBitmap upthumb, downthumb;
	wxSpinCtrl* SpinCtrl1;

};


#endif
