/////////////////////////////////////////////////////////////////////////////
// Name:        src/xrc/xmlrsall.cpp
// Purpose:     wxXmlResource::InitAllHandlers
// Author:      Vaclav Slavik
// Created:     2000/03/05
// Copyright:   (c) 2000 Vaclav Slavik
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"


#if wxUSE_XRC

#include "wx/xrc/xmlres.h"
#include "wx/xrc/xh_all.h"

void wxXmlResource::InitAllHandlers()
{
    // these are the handlers, which we always have
    AddHandler(new wxUnknownWidgetXmlHandler);
    AddHandler(new wxBitmapXmlHandler);
    AddHandler(new wxIconXmlHandler);
    AddHandler(new wxDialogXmlHandler);
    AddHandler(new wxPanelXmlHandler);
    AddHandler(new wxSizerXmlHandler);
    AddHandler(new wxFrameXmlHandler);
    AddHandler(new wxScrolledWindowXmlHandler);

    // these are configurable handlers
    //
    // please keep them in alphabetical order of wxUSE_XXX guards
#if wxUSE_ACTIVITYINDICATOR
    AddHandler(new wxActivityIndicatorXmlHandler);
#endif
#if wxUSE_ANIMATIONCTRL
    AddHandler(new wxAnimationCtrlXmlHandler);
#endif
#if wxUSE_BANNERWINDOW
    AddHandler(new wxBannerWindowXmlHandler);
#endif
#if wxUSE_BITMAPCOMBOBOX
    AddHandler(new wxBitmapComboBoxXmlHandler);
#endif
#if wxUSE_BMPBUTTON
    AddHandler(new wxBitmapButtonXmlHandler);
#endif
#if wxUSE_BOOKCTRL
    AddHandler(new wxPropertySheetDialogXmlHandler);
#endif
#if wxUSE_BUTTON
    AddHandler(new wxStdDialogButtonSizerXmlHandler);
    AddHandler(new wxButtonXmlHandler);
#endif
#if wxUSE_CALENDARCTRL
    AddHandler(new wxCalendarCtrlXmlHandler);
#endif
#if wxUSE_CHECKBOX
    AddHandler(new wxCheckBoxXmlHandler);
#endif
#if wxUSE_CHECKLISTBOX
    AddHandler(new wxCheckListBoxXmlHandler);
#endif
#if wxUSE_CHOICE
    AddHandler(new wxChoiceXmlHandler);
#endif
#if wxUSE_CHOICEBOOK
    AddHandler(new wxChoicebookXmlHandler);
#endif
#if wxUSE_COLLPANE
    AddHandler(new wxCollapsiblePaneXmlHandler);
#endif
#if wxUSE_COLOURPICKERCTRL
    AddHandler(new wxColourPickerCtrlXmlHandler);
#endif
#if wxUSE_COMBOBOX
    AddHandler(new wxComboBoxXmlHandler);
#endif
#if wxUSE_COMBOCTRL
    AddHandler(new wxComboCtrlXmlHandler);
#endif
#if wxUSE_COMMANDLINKBUTTON
    AddHandler(new wxCommandLinkButtonXmlHandler);
#endif
#if wxUSE_DATAVIEWCTRL
    AddHandler(new wxDataViewXmlHandler);
#endif
#if wxUSE_DATEPICKCTRL
    AddHandler(new wxDateCtrlXmlHandler);
#endif
#if wxUSE_DIRDLG
    AddHandler(new wxGenericDirCtrlXmlHandler);
#endif
#if wxUSE_DIRPICKERCTRL
    AddHandler(new wxDirPickerCtrlXmlHandler);
#endif
#if wxUSE_EDITABLELISTBOX
    AddHandler(new wxEditableListBoxXmlHandler);
#endif
#if wxUSE_FILECTRL
    AddHandler(new wxFileCtrlXmlHandler);
#endif
#if wxUSE_FILEPICKERCTRL
    AddHandler(new wxFilePickerCtrlXmlHandler);
#endif
#if wxUSE_FONTPICKERCTRL
    AddHandler(new wxFontPickerCtrlXmlHandler);
#endif
#if wxUSE_GAUGE
    AddHandler(new wxGaugeXmlHandler);
#endif
#if wxUSE_GRID
    AddHandler( new wxGridXmlHandler);
#endif
#if wxUSE_HTML
    AddHandler(new wxHtmlWindowXmlHandler);
    AddHandler(new wxSimpleHtmlListBoxXmlHandler);
#endif
#if wxUSE_HYPERLINKCTRL
    AddHandler( new wxHyperlinkCtrlXmlHandler);
#endif
#if wxUSE_INFOBAR
    AddHandler(new wxInfoBarXmlHandler);
#endif
#if wxUSE_LISTBOOK
    AddHandler(new wxListbookXmlHandler);
#endif
#if wxUSE_LISTBOX
    AddHandler(new wxListBoxXmlHandler);
    AddHandler(new wxVListBoxXmlHandler);
#endif
#if wxUSE_LISTCTRL
    AddHandler(new wxListCtrlXmlHandler);
#endif
#if wxUSE_MDI
    AddHandler(new wxMdiXmlHandler);
#endif
#if wxUSE_MENUS
    AddHandler(new wxMenuXmlHandler);
#if wxUSE_MENUBAR
    AddHandler(new wxMenuBarXmlHandler);
#endif
#endif
#if wxUSE_NOTEBOOK
    AddHandler(new wxNotebookXmlHandler);
#endif
#if wxUSE_ODCOMBOBOX
    AddHandler(new wxOwnerDrawnComboBoxXmlHandler);
#endif
#if wxUSE_RADIOBOX
    AddHandler(new wxRadioBoxXmlHandler);
#endif
#if wxUSE_RADIOBTN
    AddHandler(new wxRadioButtonXmlHandler);
#endif
#if wxUSE_SCROLLBAR
    AddHandler(new wxScrollBarXmlHandler);
#endif
#if wxUSE_SEARCHCTRL
    AddHandler(new wxSearchCtrlXmlHandler);
#endif
#if wxUSE_BOOKCTRL
    AddHandler(new wxSimplebookXmlHandler);
#endif
#if wxUSE_SLIDER
    AddHandler(new wxSliderXmlHandler);
#endif
#if wxUSE_SPINBTN
    AddHandler(new wxSpinButtonXmlHandler);
#endif
#if wxUSE_SPINCTRL
    AddHandler(new wxSpinCtrlXmlHandler);
    AddHandler(new wxSpinCtrlDoubleXmlHandler);
#endif
#if wxUSE_SPLITTER
    AddHandler(new wxSplitterWindowXmlHandler);
#endif
#if wxUSE_STATBMP
    AddHandler(new wxStaticBitmapXmlHandler);
#endif
#if wxUSE_STATBOX
    AddHandler(new wxStaticBoxXmlHandler);
#endif
#if wxUSE_STATLINE
    AddHandler(new wxStaticLineXmlHandler);
#endif
#if wxUSE_STATTEXT
    AddHandler(new wxStaticTextXmlHandler);
#endif
#if wxUSE_STATUSBAR
    AddHandler(new wxStatusBarXmlHandler);
#endif
#if wxUSE_TEXTCTRL
    AddHandler(new wxTextCtrlXmlHandler);
#endif
#if wxUSE_TOGGLEBTN
    AddHandler(new wxToggleButtonXmlHandler);
#endif
#if wxUSE_TIMEPICKCTRL
    AddHandler(new wxTimeCtrlXmlHandler);
#endif
#if wxUSE_TOOLBAR
    AddHandler(new wxToolBarXmlHandler);
#endif
#if wxUSE_TOOLBOOK
    AddHandler(new wxToolbookXmlHandler);
#endif
#if wxUSE_TREEBOOK
    AddHandler(new wxTreebookXmlHandler);
#endif
#if wxUSE_TREECTRL
    AddHandler(new wxTreeCtrlXmlHandler);
#endif
#if wxUSE_WIZARDDLG
    AddHandler(new wxWizardXmlHandler);
#endif
}

#endif // wxUSE_XRC
