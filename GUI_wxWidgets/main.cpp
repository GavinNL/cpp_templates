#include <wx/wx.h>

class MyFrame : public wxFrame
{
public:
    MyFrame() : wxFrame(NULL, wxID_ANY, "Test")
    {
        wxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
        sizer->Add(new wxStaticText(this, wxID_ANY, "Press to enlarge"), wxSizerFlags().Border().Centre());

        wxButton* btn = new wxButton(this, wxID_OK);
        btn->Bind(wxEVT_BUTTON, &MyFrame::OnButton, this),

        sizer->Add(btn, wxSizerFlags().Border().Centre());
        SetSizerAndFit(sizer);
        Show(true);
    }

private:
    void OnButton(wxCommandEvent& event)
    {
        for ( wxWindowList::iterator it = GetChildren().begin(); it != GetChildren().end(); ++it )
            (*it)->SetFont((*it)->GetFont().Larger());

        Fit();
    }
};

class MyApp : public wxApp
{
public:
    virtual bool OnInit()
    {
        new MyFrame; return true;
    }
};

wxIMPLEMENT_APP(MyApp);
