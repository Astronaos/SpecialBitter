#pragma once

#include <core.hpp>
#include <thread>

enum button_id
{
	NOOP,
	QUIT_REQUEST,
	BLUE_CIRCLE_SELECT,
	SELECTED_OBJECT_PLACE

};
class OBJECT
{
public:
	PAIR<double> m_piPosition;
	enum OBJECT_TYPE	{BLUE_CIRCLE};
	OBJECT_TYPE m_eObject_Type;
	OBJECT(OBJECT_TYPE i_eType, PAIR<double> i_piPosition)
	{
		m_eObject_Type = i_eType;
		m_piPosition = i_piPosition;
	}
};

class double_uncert
{
public:
	double	m_dValue;
	double	m_dSigma;
	double	Get_Rand_Value(void)
	{
		double	dRand = 0.0; //@@TODO generate random variate in (-\infty,\infty)
		double dZ = dRand / m_dSigma;
		double dSign = dRand < 0.0 ? -1.0 : 1.0;
		return m_dValue * (1.0 + dSign *  exp(-dZ* dZ));
	}
};

#include <Special_Bitter_wort.hpp>
#include <Special_Bitter_grains.hpp>
#include <Special_Bitter_eq_types.hpp>
#include <Special_Bitter_equipment.hpp>



class	space : public MAPSPACE
{
public:

	void	Draw_Layer(unsigned int i_uiLayer,void *) const;
};

class special_bitter_main : public MAIN
{
private:
	pane_id	m_idPane;

	std::map<button_id, BUTTON_INFO> m_mMain_Pane_Buttons;

	button_id	m_idSelected_Button;
	PAIR<double>	m_pdMouse_Position;
	std::vector<OBJECT> m_vPlaced_Objects;

	double		m_dTimer;
	bool		m_bFlasher_1s_50p;
	criticalsection	m_csEvent_Queue;
	std::deque<button_id> m_qEvent_List;

	ISOMETRIC_HEXMAP<space>							m_ihmMap;
	std::vector<wort_component_dictionary_entry> 	m_vWort_Component_Dictionary;
	std::vector<mash_tun_type> 						m_vMash_Tun_Dictionary;
	std::vector<kettle_type> 						m_vBrew_Kettle_Dictionary;
	std::vector<grain_storage_type>					m_vGrain_Storage_Dictionary;


public:
	special_bitter_main(void) {;}
private:
	void on_key_down(KEYID eKey_ID, unsigned char chScan_Code, unsigned int uiRepeat_Count, bool bExtended_Key, bool bPrevious_Key_State);
	void on_key_up(KEYID eKey_ID, unsigned char chScan_Code, unsigned int uiRepeat_Count, bool bExtended_Key, bool bPrevious_Key_State);
	void on_mouse_button_double_click(MOUSEBUTTON i_eButton, const PAIR<unsigned int> &i_tMouse_Position);
	void on_mouse_button_down(MOUSEBUTTON i_eButton, const PAIR<unsigned int> &i_tMouse_Position);
	void on_mouse_button_up(MOUSEBUTTON i_eButton, const PAIR<unsigned int> &i_tMouse_Position);
	void on_mousemove(const PAIR<unsigned int> &i_tMouse_Position);
	void on_mouse_wheel(MOUSEBUTTON i_eWheel, int i_iWheel_Delta, const PAIR<unsigned int> &i_tMouse_Position);
	void on_timer(unsigned int i_uiTimer_ID, const double & i_dDelta_Time_s);

	void init(void); // initialization routine; rendering context not created
	void gfx_display(pane_id i_idPane); // primary display routine
	void gfx_init(void); // initialization routine; rendering context already created
	void gfx_reshape(const PAIR<unsigned int> & i_tNew_Size); // window size change
	void gfx_close(void); // graphics exiting; rendering context still active
	void close(void); // program exiting; rendering context destroyed
};
