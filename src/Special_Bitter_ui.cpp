#include <SpecialBitter.hpp>

void SPECIAL_BITTER_MAIN::on_key_down(KEYID eKey_ID, unsigned char chScan_Code, unsigned int uiRepeat_Count, bool bExtended_Key, bool bPrevious_Key_State)
{
	// process a key that has been pressed
	switch (eKey_ID)
	{
	case KEY_ESCAPE:
		m_csEvent_Queue.Set();
		m_qEvent_List.push_back(QUIT_REQUEST);
		m_csEvent_Queue.Unset();
		break;
    case KEY_PGDN:
        m_ihmMap.Shift_Zoom(1.1);
        Request_Refresh();
        break;
    case KEY_PGUP:
        m_ihmMap.Shift_Zoom(1.0/1.1);
        Request_Refresh();
        break;
	}
}

void SPECIAL_BITTER_MAIN::on_key_up(KEYID eKey_ID, unsigned char chScan_Code, unsigned int uiRepeat_Count, bool bExtended_Key, bool bPrevious_Key_State)
{
}
void SPECIAL_BITTER_MAIN::on_mouse_button_double_click(MOUSEBUTTON i_eButton, const PAIR<unsigned int> &i_tMouse_Position)
{
}
void SPECIAL_BITTER_MAIN::on_mouse_button_down(MOUSEBUTTON i_eButton, const PAIR<unsigned int> &i_tMouse_Position)
{
	// process events when a mouse button is pressed.  Currently doesn't differentiate between left and right mouse click.
	PAIR<unsigned int> tMouse = i_tMouse_Position;
	pane_id idMouse_Pane = Find_Pane(tMouse);
	QUAD<unsigned int> qPane_Position = Get_Pane_Position(idMouse_Pane);
	PAIR<unsigned int> tMouse_TR = tMouse - qPane_Position.m_tTR;
	tMouse -= qPane_Position.m_tBL;
	double dPane_Scale = 1.0 / (double) qPane_Position.Get_Size().m_tY;
	PAIR<double> tMouse_Scaled = tMouse * dPane_Scale;
	m_pdMouse_Position = tMouse_Scaled;
	bool bProcessed = false;
	if (idMouse_Pane == m_idPane)
	{
		// a click has occurred in the main pain; iterate through the list of main pane buttons to see if the user has hit one
		for (std::map<button_id,BUTTON_INFO>::iterator cI = m_mMain_Pane_Buttons.begin(); cI != m_mMain_Pane_Buttons.end() && !bProcessed; cI++)
		{
			// check to see if current button has been hit
			if (cI->second.TestHit(tMouse_Scaled))
			{
				// button hit; set critical section (prevent thread problems) and add event to queue
				m_csEvent_Queue.Set();
				m_qEvent_List.push_back((button_id)(cI->second.GetID()));
				m_csEvent_Queue.Unset();
				// set flag to indicate that button has been processed in order to end for loop
				bProcessed = true;
			}
		}
	}
	// if no button has been processed and we are in a select mode, add an event to place the selected item
	if (!bProcessed && m_idSelected_Button == BLUE_CIRCLE_SELECT)
	{
		m_csEvent_Queue.Set();
		m_qEvent_List.push_back(SELECTED_OBJECT_PLACE);
		m_csEvent_Queue.Unset();
	}
}
void SPECIAL_BITTER_MAIN::on_mouse_button_up(MOUSEBUTTON i_eButton, const PAIR<unsigned int> &i_tMouse_Position)
{
}
void SPECIAL_BITTER_MAIN::on_mousemove(const PAIR<unsigned int> &i_tMouse_Position)
{
	// anytime the mouse moves, update the Mouse_position variable with the relative mouse position within a pane
	PAIR<unsigned int> tMouse = i_tMouse_Position;
	pane_id idMouse_Pane = Find_Pane(tMouse);
	QUAD<unsigned int> qPane_Position = Get_Pane_Position(idMouse_Pane);
	PAIR<unsigned int> tMouse_TR = tMouse - qPane_Position.m_tTR;
	tMouse -= qPane_Position.m_tBL;
	double dPane_Scale = 1.0 / (double) qPane_Position.Get_Size().m_tY;
	PAIR<double> tMouse_Scaled = tMouse * dPane_Scale;
	m_pdMouse_Position = tMouse_Scaled;

}
void SPECIAL_BITTER_MAIN::on_mouse_wheel(MOUSEBUTTON i_eWheel, int i_iWheel_Delta, const PAIR<unsigned int> &i_tMouse_Position)
{
}
void SPECIAL_BITTER_MAIN::on_timer(unsigned int i_uiTimer_ID, const double & i_dDelta_Time_s)
{
	// start with processing the event list
	// begin by setting the critical section to avoid race or thrash conditions while processing the list
	m_csEvent_Queue.Set();
	while (!m_qEvent_List.empty())
	{
		// take top of queue, then pop it from the list
		button_id eEvent = m_qEvent_List.front();
		m_qEvent_List.pop_front();
		// conditional processing of event
		switch(eEvent)
		{
		case QUIT_REQUEST:
			Request_Quit();
			break;
		case BLUE_CIRCLE_SELECT:
			m_idSelected_Button =  BLUE_CIRCLE_SELECT;
			break;
		case SELECTED_OBJECT_PLACE:
			// action to place a selected object; add it to the list of placed objects
			if (m_idSelected_Button ==  BLUE_CIRCLE_SELECT)
			{
				m_vPlaced_Objects.push_back(OBJECT(OBJECT::BLUE_CIRCLE,m_pdMouse_Position));
				m_idSelected_Button = NOOP;
			}
			break;
		}
	}
	m_csEvent_Queue.Unset();

	if (Get_Key_State(KEY_A))
		m_ihmMap.Shift_Map(PAIR<double>(-1.0 * i_dDelta_Time_s,0.0));
	if (Get_Key_State(KEY_D))
		m_ihmMap.Shift_Map(PAIR<double>(1.0 * i_dDelta_Time_s,0.0));
	if (Get_Key_State(KEY_W))
		m_ihmMap.Shift_Map(PAIR<double>(0.0,1.0 * i_dDelta_Time_s));
	if (Get_Key_State(KEY_S))
		m_ihmMap.Shift_Map(PAIR<double>(0.0,-1.0 * i_dDelta_Time_s));
//	if (Get_Key_State(KEY_UP)) // rotate camera
//		m_ihmMap.Change_Isometric_Angle(i_dDelta_Time_s * 90.0);
//	if (Get_Key_State(KEY_DOWN)) // rotate camera
//		m_ihmMap.Change_Isometric_Angle(i_dDelta_Time_s * -90.0);
//	if (Get_Key_State(KEY_LEFT)) // rotate camera
//		m_ihmMap.Change_Camera_Angle(i_dDelta_Time_s * 180.0);
//	if (Get_Key_State(KEY_RIGHT)) // rotate camera
//		m_ihmMap.Change_Camera_Angle(i_dDelta_Time_s * -180.0);

	// increment the timer
	m_dTimer += i_dDelta_Time_s;
	// set 1 Hz, 50% duty flasher
	bool bFlasher = fmod(m_dTimer,1.0) < 0.5;
	m_bFlasher_1s_50p = bFlasher;
	// always refresh the screen
	Request_Refresh();
}

