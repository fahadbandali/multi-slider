#ifndef MYTRIPLESLIDER
#define MYTRIPLESLIDER


#include "wx/wx.h"
#include <wx/slider.h>
#include <wx/spinctrl.h>



class mytripleslider : public wxPanel
{
public:

	mytripleslider(wxPanel *parent,
		wxWindowID id,
		int leftValue, int rightValue, int middleValue, int minValue, int maxValue,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxSL_HORIZONTAL,
		const wxValidator& val = wxDefaultValidator,
		const wxString& name = "mytripleslider");


	int GetLeftValue();
	int GetRightValue();
	int GetMiddleValue();

	void SetLeftValue(int lval);
	void SetRightValue(int rval);
	void SetMiddleValue(int mval);
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
	void  DrawUpThumb(wxDC& dc, wxCoord x, wxCoord y);
	void  DrawDownThumb(wxDC& dc, wxCoord x, wxCoord y);
	void  DrawMiddleThumb(wxDC& dc, wxCoord x, wxCoord y);


private:

	int leftval, rightval, middleval, minval, maxval, step;
	int selectedslider;
	int prevx, prevy;
	wxBitmap upthumb, downthumb;
	wxSpinCtrl* SpinCtrl1;

};


#endif
