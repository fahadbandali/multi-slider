#include "mytripleslider.h"
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
mytripleslider::mytripleslider(wxPanel *parent,
	wxWindowID id,
	int leftValue, int rightValue, int middleValue, int minValue, int maxValue,
	const wxPoint& pos,
	const wxSize& size,
	long style,
	const wxValidator& val,
	const wxString& name) : wxPanel(parent, id, pos, size, wxBORDER_NONE)

{
	Connect(wxID_ANY, wxSizeEventHandler(mytripleslider::OnSize));
	m_parent = parent;
	SetBackgroundColour(parent->GetBackgroundColour());
	SetDoubleBuffered(true);
	leftval = leftValue; rightval = rightValue; middleval = middleValue; minval = minValue; maxval = maxValue;
	upthumb = wxBitmap(thumb_up_xpm);
	downthumb = wxBitmap(thumb_down_xpm);
	selectedslider = 0;
	Bind(wxEVT_PAINT, &mytripleslider::OnPaint, this);
	Bind(wxEVT_LEFT_DOWN, &mytripleslider::OnLeftDown, this);
	Bind(wxEVT_SIZE, &mytripleslider::OnSize, this);
	Bind(wxEVT_MOTION, &mytripleslider::OnMotion, this);
	Bind(wxEVT_LEFT_UP, &mytripleslider::OnLeftUp, this);
	Bind(wxEVT_LEAVE_WINDOW, &mytripleslider::OnLeftUp, this);
	Bind(wxEVT_MOUSEWHEEL, &mytripleslider::OnWheel, this);

	Refresh();
	Update();
}


void mytripleslider::SetLeftValue(int lval)
{
	leftval = lval;
	Refresh();
	Update();
}

void mytripleslider::SetRightValue(int rval)
{
	rightval = rval;
	Refresh();
	Update();
}

void mytripleslider::SetMiddleValue(int mval)
{
	middleval = mval;
	Refresh();
	Update();
}

int mytripleslider::GetLeftValue()
{
	return leftval;
}

int mytripleslider::GetRightValue()
{
	return rightval;
}

int mytripleslider::GetMiddleValue()
{
	return middleval;
}

wxSize mytripleslider::DoGetBestSize()
{
	return (wxSize(300, 300));
}


void mytripleslider::OnPaint(wxPaintEvent&)
{
	wxPaintDC dc(this);
	render(dc);

}

void mytripleslider::paintNow()
{
	wxClientDC dc(this);
	render(dc);
}

void  mytripleslider::DrawUpThumb(wxDC& dc, wxCoord x, wxCoord y)
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


void  mytripleslider::DrawDownThumb(wxDC& dc, wxCoord x, wxCoord y)
{
	dc.SetPen(wxColour("#FF0000")); //for right pointer tip
	dc.DrawLine(x + 10, y + 16, x + 4, y + 22);
	dc.DrawLine(x + 10, y + 0, x + 10, y + 17);
	dc.DrawLine(x + 3, y + 17, x + 8, y + 17);

	dc.SetPen(wxColour("#FF0000")); //for right pointer tip
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

void  mytripleslider::DrawMiddleThumb(wxDC& dc, wxCoord x, wxCoord y)
{

	dc.SetPen(wxColour("#39FF14")); //for middle pointer tip
	dc.DrawLine(x + 10, y + 16, x + 4, y + 22);
	dc.DrawLine(x + 10, y + 0, x + 10, y + 17);
	dc.DrawLine(x + 3, y + 17, x + 8, y + 17);

	dc.SetPen(wxColour("#39FF14")); //for middle pointer tip
	dc.DrawLine(x + 5, y + 20, x + 10, y + 15);
	dc.DrawLine(x + 9, y + 1, x + 9, y + 17);

	dc.SetPen(wxColour("#39FF14")); //green middle slider
	dc.DrawLine(x + 4, y + 21, x + 0, y + 17);
	dc.DrawLine(x + 5, y + 20, x + 0, y + 15);
	dc.DrawLine(x + 5, y + 19, x + 3, y + 17);
	dc.DrawLine(x + 5, y + 18, x + 7, y + 18);
	for (int i = 1; i <= 8; i++) dc.DrawLine(x + i - 5, y + 15, x + i - 5, y - 30);
	for (int i = 1; i <= 8; i++) dc.DrawLine(x + i + 3, y + 15, x + i + 3, y - 30);

}


void mytripleslider::render(wxDC& dc)
{
	int w, h;
	GetSize(&w, &h);
	wxCoord tw, th;

	//media bar
	dc.SetPen(wxPen(wxColor(0, 0, 0), 7));
	dc.DrawLine(SLIDER_MARGIN, h / 2 - 1, w / 1.3 + 15, h / 2 - 1);
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
	//middle slider:
	double middleslidervalue = ((double)middleval / (double)maxval) * (double)w / 1.3;
	dc.GetTextExtent(wxString::Format("%d", middleval), &tw, &th);
	DrawMiddleThumb(dc, SLIDER_MARGIN + middleslidervalue + 4, h*0.5 - th + 10);
	if (middleval < maxval / 2)
		dc.DrawText(wxString::Format("%d", middleval), SLIDER_MARGIN + middleslidervalue + 20, h*0.5 - th - 4);
	else
		dc.DrawText(wxString::Format("%d", middleval), SLIDER_MARGIN + middleslidervalue - tw - 7, h*0.5 - th - 4);

}


void mytripleslider::OnLeftDown(wxMouseEvent& event)
{
	int w, h;
	wxClientDC dc(this);
	dc.GetSize(&w, &h);
	double leftslidervalue = ((double)leftval / (double)maxval) * (double)w / 1.3;
	double rightslidervalue = ((double)rightval / (double)maxval) * (double)w / 1.3;
	double middleslidervalue = ((double)middleval / (double)maxval) * (double)w / 1.3;
	wxPoint pos = event.GetLogicalPosition(dc);
	pos.x = pos.x - SLIDER_MARGIN;
	pos.y = h - SLIDER_MARGIN - pos.y;
	
	if (rightslidervalue > middleslidervalue && middleslidervalue > leftslidervalue) {
		if (pos.x <= leftslidervalue) selectedslider = 1;
		if (leftslidervalue <= pos.x ) selectedslider = 3;
		if (middleslidervalue <= pos.x ) selectedslider = 2;
	}
	
	else if (leftslidervalue > middleslidervalue && middleslidervalue > rightslidervalue) {
		if (pos.x <= rightslidervalue) selectedslider = 2; 
		if (rightslidervalue <= pos.x) selectedslider = 3; 
		if (middleslidervalue <= pos.x) selectedslider = 1;
	}
	
	else if (rightslidervalue > leftslidervalue && leftslidervalue > middleslidervalue) {
		if (pos.x <= middleslidervalue) selectedslider = 3;
		if (middleslidervalue <= pos.x) selectedslider = 1; 
		if (leftslidervalue <= pos.x) selectedslider = 2;
	}
	
	else if (leftslidervalue > rightslidervalue && rightslidervalue > middleslidervalue) {
		if (pos.x <= middleslidervalue) selectedslider = 3;
		if (middleslidervalue <= pos.x) selectedslider = 2; 
		if (rightslidervalue <= pos.x) selectedslider = 1;
	}
	
	else if (middleslidervalue > rightslidervalue && rightslidervalue > leftslidervalue) {
		if (pos.x <= leftslidervalue) selectedslider = 1; 
		if (leftslidervalue <= pos.x) selectedslider = 2; 
		if (rightslidervalue <= pos.x) selectedslider = 3;
	}
	
	else if (middleslidervalue > leftslidervalue && leftslidervalue > rightslidervalue) {
		if (pos.x <= rightslidervalue) selectedslider = 2; 
		if (rightslidervalue <= pos.x) selectedslider = 1; 
		if (leftslidervalue <= pos.x) selectedslider = 3;
	}

	//if (pos.x = leftslidervalue) {
	//	selectedslider = 1;
	//}
	//if (pos.x = rightslidervalue) {
	//	selectedslider = 2;
	//}
	//if (pos.x = middleslidervalue) {
	//	selectedslider = 3;
	//}

	prevx = pos.x;
	prevy = pos.y;
	event.Skip();

	//left is 1 Middle is 3 and right is 2
	
	//left middle right YES
	//right middle left YES
	//middle left right YES
	//middle right left YES
	//left right middle YES
	//right left middle YES
}

void mytripleslider::OnMotion(wxMouseEvent& event)
{
	int w, h;
	play* spinctrl = (play*)m_parent->GetParent();
	int test = spinctrl->Getstep();
	int m = test;
	if (selectedslider != 0) {
		wxClientDC dc(this);
		dc.GetSize(&w, &h);
		wxPoint pos = event.GetLogicalPosition(dc);
		pos.x = pos.x - SLIDER_MARGIN;
		pos.y = h - SLIDER_MARGIN - pos.y;

		if (prevx - pos.x > 0)
			m = -m; //THESE CHANGE THE STEP SIZE
		if (test == 1) m = pos.x - prevx;

		if (selectedslider == 1) {
			leftval += m;
			if (leftval < minval)  leftval = minval;
			if (leftval > maxval) leftval = maxval;
		}
		else if (selectedslider == 2) {
			rightval += m;
			if (rightval < minval)  rightval = minval;
			if (rightval > maxval) rightval = maxval;
		}
		else if (selectedslider == 3) {
			middleval += m;
			if (middleval < minval)  middleval = minval;
			if (middleval > maxval) middleval = maxval;
		}
		prevx = pos.x;
		prevy = pos.y;
		Refresh();
		Update();
	}
	event.Skip();
}

void mytripleslider::OnLeftUp(wxMouseEvent& event)
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

void mytripleslider::OnWheel(wxMouseEvent& event)
{
	int w, h;
	play* spinctrl = (play*)m_parent->GetParent();
	int test = spinctrl->Getstep();
	int m = test;
	//int m = step;
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


void mytripleslider::OnSize(wxSizeEvent& event)
{
	Refresh();
	Update();
}

