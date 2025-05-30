/////////////////////////////////////////////////////////////////////////////
// Program:     wxWidgets Widgets Sample
// Name:        toggle.cpp
// Purpose:     Part of the widgets sample showing toggle control
// Author:      Dimitri Schoolwerth, Vadim Zeitlin
// Created:     27 Sep 2003
// Copyright:   (c) 2006 Wlodzmierz Skiba
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// ============================================================================
// declarations
// ============================================================================

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

// for compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"


#if wxUSE_TOGGLEBTN

#include "wx/tglbtn.h"

#include "widgets.h"

// for all others, include the necessary headers
#ifndef WX_PRECOMP
    #include "wx/button.h"
    #include "wx/checkbox.h"
    #include "wx/radiobox.h"
    #include "wx/statbox.h"
    #include "wx/textctrl.h"
#endif

#include "wx/artprov.h"
#include "wx/dcmemory.h"
#include "wx/log.h"
#include "wx/sizer.h"

#include "icons/toggle.xpm"

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

// control ids
enum
{
    TogglePage_Reset = wxID_HIGHEST,
    TogglePage_ChangeLabel,
    TogglePage_Picker
};

// radio boxes
enum
{
    ToggleImagePos_Left,
    ToggleImagePos_Right,
    ToggleImagePos_Top,
    ToggleImagePos_Bottom
};

enum
{
    ToggleHAlign_Left,
    ToggleHAlign_Centre,
    ToggleHAlign_Right
};

enum
{
    ToggleVAlign_Top,
    ToggleVAlign_Centre,
    ToggleVAlign_Bottom
};

// ----------------------------------------------------------------------------
// CheckBoxWidgetsPage
// ----------------------------------------------------------------------------

class ToggleWidgetsPage : public WidgetsPage
{
public:
    ToggleWidgetsPage(WidgetsBookCtrl *book, wxVector<wxBitmapBundle>& imaglist);

    virtual wxWindow *GetWidget() const override { return m_toggle; }
    virtual void RecreateWidget() override { CreateToggle(); }

    // lazy creation of the content
    virtual void CreateContent() override;

protected:
    // event handlers
    void OnCheckOrRadioBox(wxCommandEvent& event);

    // event handlers
    void OnButtonReset(wxCommandEvent& event);
    void OnButtonChangeLabel(wxCommandEvent& event);

    void OnToggled(wxCommandEvent& event);

    // reset the toggle parameters
    void Reset();

    // (re)create the toggle
    void CreateToggle();

    // add m_button to m_sizerButton using current value of m_chkFit
    void AddButtonToSizer();

    // helper function: create a bitmap for wxBitmapToggleButton
    wxBitmap CreateBitmap(const wxString& label, const wxArtID& type);

    // the controls
    // ------------

    wxCheckBox *m_chkFit,
               *m_chkDisable;

#if wxUSE_MARKUP
    wxCheckBox *m_chkUseMarkup;
#endif // wxUSE_MARKUP

#ifdef wxHAS_BITMAPTOGGLEBUTTON
    // the check/radio boxes for styles
    wxCheckBox *m_chkBitmapOnly,
               *m_chkTextAndBitmap,
               *m_chkUseBitmapClass;

    // more checkboxes for wxBitmapToggleButton only
    wxCheckBox *m_chkUsePressed,
               *m_chkUseFocused,
               *m_chkUseCurrent,
               *m_chkUseDisabled;

    // and an image position choice used if m_chkTextAndBitmap is on
    wxRadioBox *m_radioImagePos;

    wxRadioBox *m_radioHAlign,
               *m_radioVAlign;
#endif // wxHAS_BITMAPTOGGLEBUTTON

    // the checkbox itself and the sizer it is in
    wxToggleButton *m_toggle;
    wxSizer *m_sizerToggle;

    // the text entries for command parameters
    wxTextCtrl *m_textLabel;

private:
    wxDECLARE_EVENT_TABLE();
    DECLARE_WIDGETS_PAGE(ToggleWidgetsPage)
};

// ----------------------------------------------------------------------------
// event tables
// ----------------------------------------------------------------------------

wxBEGIN_EVENT_TABLE(ToggleWidgetsPage, WidgetsPage)
    EVT_BUTTON(TogglePage_Reset, ToggleWidgetsPage::OnButtonReset)
    EVT_BUTTON(TogglePage_ChangeLabel, ToggleWidgetsPage::OnButtonChangeLabel)

    EVT_CHECKBOX(wxID_ANY, ToggleWidgetsPage::OnCheckOrRadioBox)
    EVT_RADIOBOX(wxID_ANY, ToggleWidgetsPage::OnCheckOrRadioBox)

    EVT_TOGGLEBUTTON(wxID_ANY, ToggleWidgetsPage::OnToggled)
wxEND_EVENT_TABLE()

// ============================================================================
// implementation
// ============================================================================

#if defined(__WXUNIVERSAL__)
    #define FAMILY_CTRLS UNIVERSAL_CTRLS
#else
    #define FAMILY_CTRLS NATIVE_CTRLS
#endif

IMPLEMENT_WIDGETS_PAGE(ToggleWidgetsPage, "ToggleButton",
                       FAMILY_CTRLS
                       );

ToggleWidgetsPage::ToggleWidgetsPage(WidgetsBookCtrl *book,
                                     wxVector<wxBitmapBundle>& imaglist)
                      :WidgetsPage(book, imaglist, toggle_xpm)
{
    m_chkFit =
    m_chkDisable = nullptr;

#if wxUSE_MARKUP
    m_chkUseMarkup = nullptr;
#endif // wxUSE_MARKUP

#ifdef wxHAS_BITMAPTOGGLEBUTTON
    // init everything
    m_chkBitmapOnly =
    m_chkTextAndBitmap =
    m_chkUseBitmapClass =
    m_chkUsePressed =
    m_chkUseFocused =
    m_chkUseCurrent =
    m_chkUseDisabled = nullptr;

    m_radioImagePos =
    m_radioHAlign =
    m_radioVAlign = nullptr;
#endif // wxHAS_BITMAPTOGGLEBUTTON

    m_textLabel = nullptr;

    m_toggle = nullptr;
    m_sizerToggle = nullptr;
}

void ToggleWidgetsPage::CreateContent()
{
    wxSizer *sizerTop = new wxBoxSizer(wxHORIZONTAL);

    // left pane
    wxStaticBoxSizer *sizerLeft = new wxStaticBoxSizer(wxVERTICAL, this, "Styles");
    wxStaticBox* const sizerLeftBox = sizerLeft->GetStaticBox();

#ifdef wxHAS_BITMAPTOGGLEBUTTON
    m_chkBitmapOnly = CreateCheckBoxAndAddToSizer(sizerLeft, "&Bitmap only", wxID_ANY, sizerLeftBox);
    m_chkTextAndBitmap = CreateCheckBoxAndAddToSizer(sizerLeft, "Text &and bitmap", wxID_ANY, sizerLeftBox);
#endif // wxHAS_BITMAPTOGGLEBUTTON

#if wxUSE_MARKUP
    m_chkUseMarkup = CreateCheckBoxAndAddToSizer(sizerLeft, "Interpret &markup", wxID_ANY, sizerLeftBox);
#endif // wxUSE_MARKUP

    m_chkFit = CreateCheckBoxAndAddToSizer(sizerLeft, "&Fit exactly", wxID_ANY, sizerLeftBox);
    m_chkDisable = CreateCheckBoxAndAddToSizer(sizerLeft, "Disable", wxID_ANY, sizerLeftBox);

#ifdef wxHAS_BITMAPTOGGLEBUTTON
    m_chkUseBitmapClass = CreateCheckBoxAndAddToSizer(sizerLeft,
        "Use wxBitmapToggleButton", wxID_ANY, sizerLeftBox);
    m_chkUseBitmapClass->SetValue(true);


    sizerLeft->AddSpacer(5);

    wxStaticBoxSizer *sizerUseLabels =
        new wxStaticBoxSizer(wxVERTICAL, sizerLeftBox,
                "&Use the following bitmaps in addition to the normal one?");
    wxStaticBox* const sizerUseLabelsBox = sizerUseLabels->GetStaticBox();

    m_chkUsePressed = CreateCheckBoxAndAddToSizer(sizerUseLabels,
        "&Pressed (small help icon)", wxID_ANY, sizerUseLabelsBox);
    m_chkUseFocused = CreateCheckBoxAndAddToSizer(sizerUseLabels,
        "&Focused (small error icon)", wxID_ANY, sizerUseLabelsBox);
    m_chkUseCurrent = CreateCheckBoxAndAddToSizer(sizerUseLabels,
        "&Current (small warning icon)", wxID_ANY, sizerUseLabelsBox);
    m_chkUseDisabled = CreateCheckBoxAndAddToSizer(sizerUseLabels,
        "&Disabled (broken image icon)", wxID_ANY, sizerUseLabelsBox);
    sizerLeft->Add(sizerUseLabels, wxSizerFlags().Expand().Border());

    sizerLeft->AddSpacer(10);

    static const wxString dirs[] =
    {
        "left", "right", "top", "bottom",
    };
    m_radioImagePos = new wxRadioBox(sizerLeftBox, wxID_ANY, "Image &position",
                                     wxDefaultPosition, wxDefaultSize,
                                     WXSIZEOF(dirs), dirs);
    sizerLeft->Add(m_radioImagePos, wxSizerFlags().Expand().Border());
    sizerLeft->AddSpacer(15);

    // should be in sync with enums Toggle[HV]Align!
    static const wxString halign[] =
    {
        "left",
        "centre",
        "right",
    };

    static const wxString valign[] =
    {
        "top",
        "centre",
        "bottom",
    };

    m_radioHAlign = new wxRadioBox(sizerLeftBox, wxID_ANY, "&Horz alignment",
                                   wxDefaultPosition, wxDefaultSize,
                                   WXSIZEOF(halign), halign);
    m_radioVAlign = new wxRadioBox(sizerLeftBox, wxID_ANY, "&Vert alignment",
                                   wxDefaultPosition, wxDefaultSize,
                                   WXSIZEOF(valign), valign);

    sizerLeft->Add(m_radioHAlign, wxSizerFlags().Expand().Border());
    sizerLeft->Add(m_radioVAlign, wxSizerFlags().Expand().Border());
#endif // wxHAS_BITMAPTOGGLEBUTTON

    sizerLeft->AddSpacer(5);

    wxButton *btn = new wxButton(sizerLeftBox, TogglePage_Reset, "&Reset");
    sizerLeft->Add(btn, wxSizerFlags().CentreHorizontal().Border(wxALL, FromDIP(15)));

    // middle pane
    wxStaticBoxSizer *sizerMiddle = new wxStaticBoxSizer(wxVERTICAL, this, "&Operations");

    wxSizer *sizerRow = CreateSizerWithTextAndButton(TogglePage_ChangeLabel,
                                                     "Change label",
                                                     wxID_ANY,
                                                     &m_textLabel,
                                                     sizerMiddle->GetStaticBox());
    m_textLabel->SetValue("&Toggle me!");

    sizerMiddle->Add(sizerRow, wxSizerFlags().Expand().Border());

    // right pane
    m_sizerToggle = new wxBoxSizer(wxHORIZONTAL);
    m_sizerToggle->SetMinSize(FromDIP(150), 0);

    // the 3 panes panes compose the window
    sizerTop->Add(sizerLeft,
                  wxSizerFlags(0).Expand().DoubleBorder((wxALL & ~wxLEFT)));
    sizerTop->Add(sizerMiddle,
                  wxSizerFlags(1).Expand().DoubleBorder(wxALL));
    sizerTop->Add(m_sizerToggle,
                  wxSizerFlags(1).Expand().DoubleBorder((wxALL & ~wxRIGHT)));

    // do create the main control
    Reset();
    CreateToggle();

    SetSizer(sizerTop);
}

void ToggleWidgetsPage::Reset()
{

    m_chkFit->SetValue(true);
    m_chkDisable->SetValue(false);

#if wxUSE_MARKUP
    m_chkUseMarkup->SetValue(false);
#endif // wxUSE_MARKUP

#ifdef wxHAS_BITMAPTOGGLEBUTTON
    m_chkBitmapOnly->SetValue(false);
    m_chkTextAndBitmap->SetValue(false);
    m_chkUseBitmapClass->SetValue(true);

    m_chkUsePressed->SetValue(true);
    m_chkUseFocused->SetValue(true);
    m_chkUseCurrent->SetValue(true);
    m_chkUseDisabled->SetValue(true);

    m_radioImagePos->SetSelection(ToggleImagePos_Left);
    m_radioHAlign->SetSelection(ToggleHAlign_Centre);
    m_radioVAlign->SetSelection(ToggleVAlign_Centre);
#endif // wxHAS_BITMAPTOGGLEBUTTON

    if ( m_toggle )
    {
        m_toggle->SetValue(false);
    }
}

void ToggleWidgetsPage::CreateToggle()
{
    wxString label;
    bool value = false;

    if ( m_toggle )
    {
        label = m_toggle->GetLabel();
        value = m_toggle->GetValue();
        size_t count = m_sizerToggle->GetChildren().GetCount();
        for ( size_t n = 0; n < count; n++ )
        {
            m_sizerToggle->Remove(0);
        }

        delete m_toggle;
    }

    if ( label.empty() )
    {
        // creating for the first time or recreating a toggle button after bitmap
        // button
        label = m_textLabel->GetValue();
    }

    int flags = GetAttrs().m_defaultFlags;

#ifdef wxHAS_BITMAPTOGGLEBUTTON
    switch ( m_radioHAlign->GetSelection() )
    {
        case ToggleHAlign_Left:
            flags |= wxBU_LEFT;
            break;

        default:
            wxFAIL_MSG("unexpected radiobox selection");
            wxFALLTHROUGH;

        case ToggleHAlign_Centre:
            break;

        case ToggleHAlign_Right:
            flags |= wxBU_RIGHT;
            break;
    }

    switch ( m_radioVAlign->GetSelection() )
    {
        case ToggleVAlign_Top:
            flags |= wxBU_TOP;
            break;

        default:
            wxFAIL_MSG("unexpected radiobox selection");
            wxFALLTHROUGH;

        case ToggleVAlign_Centre:
            // centre vertical alignment is the default (no style)
            break;

        case ToggleVAlign_Bottom:
            flags |= wxBU_BOTTOM;
            break;
    }

    bool showsBitmap = false;
    if ( m_chkBitmapOnly->GetValue() )
    {
        showsBitmap = true;

        wxToggleButton *btgl;
        if ( m_chkUseBitmapClass->GetValue() )
        {
          btgl = new wxBitmapToggleButton(this, TogglePage_Picker,
                                          CreateBitmap("normal", wxART_INFORMATION));
        }
        else
        {
          btgl = new wxToggleButton(this, TogglePage_Picker, "");
          btgl->SetBitmapLabel(CreateBitmap("normal", wxART_INFORMATION));
        }
        if ( m_chkUsePressed->GetValue() )
            btgl->SetBitmapPressed(CreateBitmap("pushed", wxART_HELP));
        if ( m_chkUseFocused->GetValue() )
            btgl->SetBitmapFocus(CreateBitmap("focused", wxART_ERROR));
        if ( m_chkUseCurrent->GetValue() )
            btgl->SetBitmapCurrent(CreateBitmap("hover", wxART_WARNING));
        if ( m_chkUseDisabled->GetValue() )
            btgl->SetBitmapDisabled(CreateBitmap("disabled", wxART_MISSING_IMAGE));
        m_toggle = btgl;
    }
    else // normal button
#endif // wxHAS_BITMAPTOGGLEBUTTON
    {
        m_toggle = new wxToggleButton(this, TogglePage_Picker, label,
                                      wxDefaultPosition, wxDefaultSize,
                                      flags);
    }

    NotifyWidgetRecreation(m_toggle);

    m_toggle->SetValue(value);

#ifdef wxHAS_BITMAPTOGGLEBUTTON
    if ( !showsBitmap && m_chkTextAndBitmap->GetValue() )
    {
        showsBitmap = true;

        static const wxDirection positions[] =
        {
            wxLEFT, wxRIGHT, wxTOP, wxBOTTOM
        };

        m_toggle->SetBitmap(wxArtProvider::GetIcon(wxART_INFORMATION, wxART_BUTTON),
                            positions[m_radioImagePos->GetSelection()]);

        if ( m_chkUsePressed->GetValue() )
            m_toggle->SetBitmapPressed(wxArtProvider::GetIcon(wxART_HELP, wxART_BUTTON));
        if ( m_chkUseFocused->GetValue() )
            m_toggle->SetBitmapFocus(wxArtProvider::GetIcon(wxART_ERROR, wxART_BUTTON));
        if ( m_chkUseCurrent->GetValue() )
            m_toggle->SetBitmapCurrent(wxArtProvider::GetIcon(wxART_WARNING, wxART_BUTTON));
        if ( m_chkUseDisabled->GetValue() )
            m_toggle->SetBitmapDisabled(wxArtProvider::GetIcon(wxART_MISSING_IMAGE, wxART_BUTTON));
    }

    m_chkUseBitmapClass->Enable(showsBitmap);
    m_chkTextAndBitmap->Enable(!m_chkBitmapOnly->IsChecked());

    m_chkUsePressed->Enable(showsBitmap);
    m_chkUseFocused->Enable(showsBitmap);
    m_chkUseCurrent->Enable(showsBitmap);
    m_chkUseDisabled->Enable(showsBitmap);
#endif // wxHAS_BITMAPTOGGLEBUTTON

    m_toggle->Enable(!m_chkDisable->IsChecked());

    AddButtonToSizer();

    m_sizerToggle->Layout();
}

void ToggleWidgetsPage::AddButtonToSizer()
{
    if ( m_chkFit->GetValue() )
    {
        m_sizerToggle->AddStretchSpacer(1);
        m_sizerToggle->Add(m_toggle, wxSizerFlags(0).Centre().Border());
        m_sizerToggle->AddStretchSpacer(1);
    }
    else // take up the entire space
    {
        m_sizerToggle->Add(m_toggle, wxSizerFlags(1).Expand().Border());
    }
}

// ----------------------------------------------------------------------------
// event handlers
// ----------------------------------------------------------------------------

void ToggleWidgetsPage::OnButtonReset(wxCommandEvent& WXUNUSED(event))
{
    Reset();

    CreateToggle();
}

void ToggleWidgetsPage::OnCheckOrRadioBox(wxCommandEvent& WXUNUSED(event))
{
    CreateToggle();
}

void ToggleWidgetsPage::OnButtonChangeLabel(wxCommandEvent& WXUNUSED(event))
{
    const wxString labelText = m_textLabel->GetValue();

#if wxUSE_MARKUP
    if ( m_chkUseMarkup->GetValue() )
        m_toggle->SetLabelMarkup(labelText);
    else
#endif // wxUSE_MARKUP
        m_toggle->SetLabel(labelText);

#ifdef wxHAS_BITMAPTOGGLEBUTTON
    if ( m_chkBitmapOnly->IsChecked() )
        CreateToggle();
#endif // wxHAS_BITMAPTOGGLEBUTTON
}

void ToggleWidgetsPage::OnToggled(wxCommandEvent& event)
{
    wxLogMessage("Button toggled, currently %s (event) or %s (control)",
                 event.IsChecked() ? "on" : "off",
                 m_toggle->GetValue() ? "on" : "off");
}

#ifdef wxHAS_BITMAPTOGGLEBUTTON
// ----------------------------------------------------------------------------
// bitmap toggle button stuff
// ----------------------------------------------------------------------------

wxBitmap ToggleWidgetsPage::CreateBitmap(const wxString& label, const wxArtID& type)
{
    wxBitmap bmp(FromDIP(wxSize(180, 70))); // shouldn't hardcode but it's simpler like this
    wxMemoryDC dc;
    dc.SelectObject(bmp);
    dc.SetFont(GetFont());
    dc.SetBackground(*wxCYAN_BRUSH);
    dc.Clear();
    dc.SetTextForeground(*wxBLACK);
    dc.DrawLabel(wxStripMenuCodes(m_textLabel->GetValue()) + "\n"
                    "(" + label + " state)",
                 wxArtProvider::GetBitmap(type),
                 wxRect(10, 10, bmp.GetWidth() - 20, bmp.GetHeight() - 20),
                 wxALIGN_CENTRE);

    return bmp;
}
#endif // wxHAS_BITMAPTOGGLEBUTTON

#endif // wxUSE_TOGGLEBTN
