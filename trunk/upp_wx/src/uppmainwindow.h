/***************************************************************************
*   Copyright (C) 2008 by Frans Schreuder                                 *
*   usbpicprog.sourceforge.net                                            *
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
*   This program is distributed in the hope that it will be useful,       *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
*   GNU General Public License for more details.                          *
*                                                                         *
*   You should have received a copy of the GNU General Public License     *
*   along with this program; if not, write to the                         *
*   Free Software Foundation, Inc.,                                       *
*   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
***************************************************************************/

#ifndef UPPMAINWINDOW_CALLBACK_H
#define UPPMAINWINDOW_CALLBACK_H

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <wx/config.h>
#include <wx/confbase.h>
#include <wx/docview.h>
#include <wx/thread.h>
#include <wx/progdlg.h>
#include <wx/log.h>

#if wxCHECK_VERSION(2,7,1) //about dialog only implemented from wxWidgets v2.7.1
#include <wx/aboutdlg.h>
#else
#warning About dialog not implemented, use a newer wxWidgets version!
#endif

#include <iostream>

using namespace std;

#include "uppmainwindow_base.h"
#include "hardware.h"
#include "pictype.h"
#include "hexfile.h"
#include "preferences.h"

#ifdef __WXMAC__
#define EVENT_FIX
#else //__WXMAC__
#define EVENT_FIX event.Skip();
#endif //__WXMAC__


// more readable names for the various fields of the status bar
enum UppMainWindowStatusBar
{
    STATUS_FIELD_MENU,
    STATUS_FIELD_OTHER = STATUS_FIELD_MENU,
    STATUS_FIELD_HARDWARE
};

// defines the order in which the pages related to the loaded HEX file are shown
enum UppMainWindowNotebookPages
{
    PAGE_CODE,
    PAGE_CONFIG,
    PAGE_DATA
};

// we use a single thread's Entry() function to do all kind of long tasks:
enum UppMainWindowThreadMode
{
    THREAD_PROGRAM,
    THREAD_READ,
    THREAD_VERIFY,
    THREAD_ERASE,
    THREAD_BLANKCHECK
};

typedef std::vector<time_t> wxArrayTime;


/*
    This class derives from the UppMainWindowBase which is the class automatically
    generated by wxFormBuilder, upon which the entire application is built.
*/
class UppMainWindow : public UppMainWindowBase, public wxThreadHelper
{
public:

    UppMainWindow(wxWindow* parent, wxWindowID id = wxID_ANY);
    ~UppMainWindow();


    bool upp_open_file(const wxString& path);
    void upp_new();
    void updateProgress(int value);

protected:      // internal helpers

    void UpdateGrids();
    void UpdateTitle();
    void Reset();

    wxBitmap GetMenuBitmap(const char* xpm_data[]);
    void CompleteGUICreation();

    UppHexViewGrid* GetCurrentGrid() const;

    bool ShouldContinueIfUnsaved();


protected:      // internal thread-related functions

    // functions which are executed in the secondary thread context:
    wxThread::ExitCode Entry();
    void LogFromThread(wxLogLevel level, const wxString& str);
    bool upp_thread_program();
    bool upp_thread_read();
    bool upp_thread_verify();
    bool upp_thread_erase();
    bool upp_thread_blankcheck();

    // functions which are executed in the primary thread context:
    bool RunThread(UppMainWindowThreadMode mode);
#if wxCHECK_VERSION(2,9,0)
    void OnThreadUpdate(wxThreadEvent& evt);
    void OnThreadCompleted(wxThreadEvent& evt);
#else
    void OnThreadUpdate(wxCommandEvent& evt);
    void OnThreadCompleted(wxCommandEvent& evt);
#endif

public:     // event handlers

    void on_mru( wxCommandEvent& event );
    void on_close( wxCloseEvent& event );
    void on_new( wxCommandEvent& event ){upp_new(); EVENT_FIX}
    void on_open( wxCommandEvent& event ){upp_open(); EVENT_FIX}
    void on_refresh( wxCommandEvent& event ){upp_refresh(); EVENT_FIX}
    void on_save( wxCommandEvent& event ){upp_save(); EVENT_FIX}
    void on_save_as( wxCommandEvent& event ){upp_save_as(); EVENT_FIX}
    void on_exit( wxCommandEvent& event ){upp_exit(); EVENT_FIX}
    void on_copy( wxCommandEvent& event ){upp_copy(); EVENT_FIX}
    void on_selectall( wxCommandEvent& event ){upp_selectall(); EVENT_FIX}
    void on_program( wxCommandEvent& event ){upp_program(); EVENT_FIX}
    void on_read( wxCommandEvent& event ){upp_read(); EVENT_FIX}
    void on_verify( wxCommandEvent& event ){upp_verify(); EVENT_FIX}
    void on_erase( wxCommandEvent& event ){upp_erase(); EVENT_FIX}
    void on_blankcheck( wxCommandEvent& event ){upp_blankcheck(); EVENT_FIX}
    void on_autodetect( wxCommandEvent& event ){upp_autodetect(); EVENT_FIX}
    void on_connect( wxCommandEvent& event){upp_connect(); EVENT_FIX}
    void on_disconnect( wxCommandEvent& event ){upp_disconnect(); EVENT_FIX}
    void on_preferences( wxCommandEvent& event ){upp_preferences(); EVENT_FIX}
    void on_help( wxCommandEvent& event ){upp_help(); EVENT_FIX}
    void on_about( wxCommandEvent& event ){upp_about(); EVENT_FIX}
    void on_cell_changed( wxGridEvent& event ){upp_cell_changed(); EVENT_FIX}
    void on_pic_choice_changed( wxCommandEvent& event ){upp_pic_choice_changed(); EVENT_FIX}
    void on_pic_choice_changed_bymenu( wxCommandEvent& event )
        {upp_pic_choice_changed_bymenu(event.GetId()-wxID_PIC_CHOICE_MENU); EVENT_FIX}

private:
    void upp_open();
    void upp_refresh();
    void upp_save();
    void upp_save_as();
    void upp_cell_changed();
    void upp_exit();
    void upp_copy();
    void upp_selectall();
    void upp_program();
    void upp_read();
    void upp_verify();
    void upp_erase();
    void upp_blankcheck();
    bool upp_autodetect();
    bool upp_connect();
    void upp_disconnect();
    void upp_preferences();
    void upp_help();
    void upp_about();
    void upp_pic_choice_changed();
    void upp_pic_choice_changed_bymenu(int id);

private:    // member variables

    HexFile m_hexFile;
    PicType m_picType;
    Hardware* m_hardware;

    vector<string> m_arrPICName;

    ConfigFields m_cfg;
    wxString m_defaultPath;

    wxChoice* m_pPICChoice;
    wxFileHistory m_history;


private:   // variables related to the threaded operations:

    // accessed only by the main/primary thread
    wxProgressDialog* m_dlgProgress;

    // the messages recorded during the thread activity
    wxCriticalSection m_arrLogCS;
    wxArrayString m_arrLog;
    wxArrayInt m_arrLogLevel;
    wxArrayTime m_arrLogTimes;

    // tells the thread which operation should be performed
    // NOTE: since the main thread reads/writes this var only when the
    //       secondary thread has ended, there's no need for critical section
    UppMainWindowThreadMode m_mode;
};

#endif
