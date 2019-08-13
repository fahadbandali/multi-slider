#include "myDoubleSlider.h"
#include "thumb_up.xpm"
#include "thumb_down.xpm"
#include "play.h"
#include <wx/wx.h>
#include <wx/spinctrl.h>


static const int BORDER_THICKNESS = 1;

static const wxCoord SLIDER_MARGIN = 1; // margin around slider
static const wxCoord SLIDER_THUMB_LENGTH = 1;
static const wxCoord SLIDER_TICK_LENGTH = 1;
//create oninit (regular method), constructor calls it
//takes number of sensors 
//moves sldiers to the top, they can overlap too
myDoubleSlider::myDoubleSlider(wxPanel *parent,
	wxWindowID id,
	int leftValue, int rightValue, int minValue, int maxValue,
	const wxPoint& pos,
	const wxSize& size,
	long style,
	const wxValidator& val,
	const wxString& name) : wxPanel(parent, id, pos, size, wxBORDER_NONE)

{
	Connect(wxID_ANY, wxSizeEventHandler(myDoubleSlider::OnSize));
	m_parent = parent;
	SetBackgroundColour(parent->GetBackgroundColour());
	SetDoubleBuffered(true);
	leftval = leftValue; rightval = rightValue; minval = minValue; maxval = maxValue;
	upthumb = wxBitmap(thumb_up_xpm);
	downthumb = wxBitmap(thumb_down_xpm);
	selectedslider = 0;
	Bind(wxEVT_PAINT, &myDoubleSlider::OnPaint, this);
	Bind(wxEVT_LEFT_DOWN, &myDoubleSlider::OnLeftDown, this);
	Bind(wxEVT_SIZE, &myDoubleSlider::OnSize, this);
	Bind(wxEVT_MOTION, &myDoubleSlider::OnMotion, this);
	Bind(wxEVT_LEFT_UP, &myDoubleSlider::OnLeftUp, this);
	Bind(wxEVT_LEAVE_WINDOW, &myDoubleSlider::OnLeftUp, this);
	Bind(wxEVT_MOUSEWHEEL, &myDoubleSlider::OnWheel, this);

	Refresh();
	Update();
}


void myDoubleSlider::SetLeftValue(int lval)
{
	leftval = lval;
	Refresh();
	Update();
}

void myDoubleSlider::SetRightValue(int rval)
{
	rightval = rval;
	Refresh();
	Update();
}

int myDoubleSlider::GetLeftValue()
{
	return leftval;
}

int myDoubleSlider::GetRightValue()
{
	return rightval;
}

wxSize myDoubleSlider::DoGetBestSize()
{
	return (wxSize(300, 300));
}


void myDoubleSlider::OnPaint(wxPaintEvent&)
{
	wxPaintDC dc(this);
	render(dc);

}

void myDoubleSlider::paintNow()
{
	wxClientDC dc(this);
	render(dc);
}

void  myDoubleSlider::DrawUpThumb(wxDC& dc, wxCoord x, wxCoord y)
{

	dc.SetPen(wxColour("#447aee")); //for right pointer tip
	dc.DrawLine(x + 10, y + 16, x + 4, y + 22);
	dc.DrawLine(x + 10, y + 0, x + 10, y + 17);
	dc.DrawLine(x + 3, y + 17, x + 8, y + 17);

	dc.SetPen(wxColour("#447aee")); //for right pointer tip
	dc.DrawLine(x + 5, y + 20, x + 10, y + 15);
	dc.DrawLine(x + 9, y + 1, x + 9, y + 17);

	dc.SetPen(wxColour("#447aee")); //red right slider
	dc.DrawLine(x + 4, y + 21, x + 0, y + 17);
	dc.DrawLine(x + 5, y + 20, x + 0, y + 15);
	dc.DrawLine(x + 5, y + 19, x + 3, y + 17);
	dc.DrawLine(x + 5, y + 18, x + 7, y + 18);
	for (int i = 1; i <= 8; i++) dc.DrawLine(x + i - 5, y + 15, x + i - 5, y - 30);
	for (int i = 1; i <= 8; i++) dc.DrawLine(x + i + 3, y + 15, x + i + 3, y - 30);

}


void  myDoubleSlider::DrawDownThumb(wxDC& dc, wxCoord x, wxCoord y)
{
	dc.SetPen(wxColour("#696969")); //for right pointer tip
	dc.DrawLine(x + 10, y + 16, x + 4, y + 22);
	dc.DrawLine(x + 10, y + 0, x + 10, y + 17);
	dc.DrawLine(x + 3, y + 17, x + 8, y + 17);

	dc.SetPen(wxColour("#A0A0A0")); //for right pointer tip
	dc.DrawLine(x + 5, y + 20, x + 10, y + 15);
	dc.DrawLine(x + 9, y + 1, x + 9, y + 17);

	dc.SetPen(wxColour("#FF0000")); //red right slider
	dc.DrawLine(x + 4, y + 21, x + 0, y + 17);
	dc.DrawLine(x + 5, y + 20, x + 0, y + 15);
	dc.DrawLine(x + 5, y + 19, x + 3, y + 17);
	dc.DrawLine(x + 5, y + 18, x + 7, y + 18);
	for (int i = 1; i <= 8; i++) dc.DrawLine(x + i - 5, y + 15, x + i - 5, y - 30);
	for (int i = 1; i <= 8; i++) dc.DrawLine(x + i + 3, y + 15, x + i + 3, y - 30);


}


void myDoubleSlider::render(wxDC& dc)
{
	int w, h;
	GetSize(&w, &h);
	wxCoord tw, th;

	//media bar
	dc.SetPen(wxPen(wxColor(0, 0, 0), 7));
	dc.DrawLine(SLIDER_MARGIN, h / 2 - 1, w /1.3 + 15 , h / 2 - 1);
	dc.SetPen(wxPen(wxColor(0, 0, 0), 7));
	dc.DrawLine(SLIDER_MARGIN, h / 2, w / 1.3 + 15, h / 2);
	dc.SetPen(wxPen(wxColor(0, 0, 0), 7));
	dc.DrawLine(SLIDER_MARGIN, h / 2 + 1, w / 1.3 + 15, h / 2 + 1);
	dc.SetPen(wxPen(wxColor(0, 0, 0), 10));
	dc.DrawLine(SLIDER_MARGIN, h / 2 + 1, w / 1.3 + 15, h / 2 + 1);


	//left slider:
	double leftslidervalue = ((double)leftval / (double)maxval) * (double)w / 1.3;
	dc.GetTextExtent(wxString::Format("%d", leftval), &tw, &th);
	DrawUpThumb(dc, SLIDER_MARGIN + leftslidervalue + 2, h*0.5 - th + 10);
	if (leftval < maxval / 2)
		dc.DrawText(wxString::Format("%d", leftval), SLIDER_MARGIN + leftslidervalue + 20, h*0.5 + 5);
	else
		dc.DrawText(wxString::Format("%d", leftval), SLIDER_MARGIN + leftslidervalue - tw - 12, h*0.5 + 5);
	//right slider:
	double rightslidervalue = ((double)rightval / (double)maxval) * (double)w / 1.3;
	dc.GetTextExtent(wxString::Format("%d", rightval), &tw, &th);
	DrawDownThumb(dc, SLIDER_MARGIN + rightslidervalue + 4, h*0.5 - th + 10);
	if (rightval < maxval / 2)
		dc.DrawText(wxString::Format("%d", rightval), SLIDER_MARGIN + rightslidervalue + 20, h*0.5 - th - 4);
	else
		dc.DrawText(wxString::Format("%d", rightval), SLIDER_MARGIN + rightslidervalue - tw - 7, h*0.5 - th - 4);

}


void myDoubleSlider::OnLeftDown(wxMouseEvent& event)
{
	int w, h;
	wxClientDC dc(this);
	dc.GetSize(&w, &h);
	double leftslidervalue = ((double)leftval / (double)maxval) * (double)w / 1.3;
	double rightslidervalue = ((double)rightval / (double)maxval) * (double)w / 1.3;
	wxPoint pos = event.GetLogicalPosition(dc);
	pos.x = pos.x - SLIDER_MARGIN;
	pos.y = h - SLIDER_MARGIN - pos.y;
	if(leftslidervalue < rightslidervalue){
		if (pos.x <= leftslidervalue) selectedslider = 1; //pos.y < h / 2
		if (pos.x >= rightslidervalue) selectedslider = 2; //pos.y > h / 2
	}

	if (leftslidervalue > rightslidervalue) {
		if (pos.x >= leftslidervalue) selectedslider = 1; //pos.y < h / 2
		if (pos.x <= rightslidervalue) selectedslider = 2; //pos.y > h / 2
	}

	//if (pos.x = leftslidervalue) {
	//	selectedslider = 1;
	//}
	//if (pos.x = rightslidervalue) {
	//	selectedslider = 2;
	//}
	prevx = pos.x;
	prevy = pos.y;
	event.Skip();
}

void myDoubleSlider::OnMotion(wxMouseEvent& event)
{
	int w, h;
	play* spinctrl = (play*)m_parent->GetParent();
	int test = spinctrl->Getstep();
	int m = test;
	//int m = step;
	if (selectedslider != 0) {
		wxClientDC dc(this);
		dc.GetSize(&w, &h);
		wxPoint pos = event.GetLogicalPosition(dc);
		pos.x = pos.x - SLIDER_MARGIN;
		pos.y = h - SLIDER_MARGIN - pos.y;

		if (prevx-pos.x > 0)
			m = -m; //THESE CHANGE THE STEP SIZE
		if (test == 1) m = pos.x-prevx;

		if (selectedslider == 1) {
			leftval += m;
			if (leftval < minval)  leftval = minval;
			//if (leftval >= rightval) leftval = rightval;
		}
		else if (selectedslider == 2) {
			rightval += m;
			if (rightval > maxval) rightval = maxval;
			//if (rightval <= leftval) rightval = leftval + 1;
		}
		prevx = pos.x;
		prevy = pos.y;
		Refresh();
		Update();
	}
	event.Skip();
}

void myDoubleSlider::OnLeftUp(wxMouseEvent& event)
{
	event.Skip();
	if (selectedslider != 0) {
		selectedslider = 0;
		wxCommandEvent e(wxEVT_SCROLL_CHANGED);
		e.SetEventObject(this);
		e.SetString("update");
		ProcessWindowEvent(e);
	}
}

void myDoubleSlider::OnWheel(wxMouseEvent& event)
{
	int w, h;
	play* spinctrl = (play*)m_parent->GetParent();
	int test = spinctrl->Getstep();
	int m = test;
	wxClientDC dc(this);
	dc.GetSize(&w, &h);
	wxPoint pos = event.GetLogicalPosition(dc);
	pos.x = pos.x - SLIDER_MARGIN;
	pos.y = h - SLIDER_MARGIN - pos.y;
	if (event.GetWheelRotation() > 0)
		m = m; //THESE CHANGE THE STEP SIZE
	else
		m = -m;
	if (pos.y < h / 2) {
		leftval -= m;
		if (leftval < minval)  leftval = minval;
		if (leftval >= rightval) leftval = rightval;
	}
	else if (pos.y > h / 2) {
		rightval -= m;
		if (rightval > maxval) rightval = maxval;
		if (rightval <= leftval) rightval = leftval + 1;
	}
	Refresh();
	Update();
	wxCommandEvent e(wxEVT_SCROLL_CHANGED);
	e.SetEventObject(this);
	e.SetString("update");
	ProcessWindowEvent(e);
	event.Skip();
}


void myDoubleSlider::OnSize(wxSizeEvent& event)
{
	Refresh();
	Update();
}

