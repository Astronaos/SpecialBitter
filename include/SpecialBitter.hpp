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


class wort_component_dictionary_entry
{
public:
	unsigned int m_uiType;
	unsigned int m_uiSub_Type;
};

class wort_component
{
public:
	double			m_dQuantity_Micrograms;
	double			m_dDensity_Gm_CC;
};
class adjunct
{
public:
	std::string 	m_szName;
	std::string		m_szManufacturer;
	double			m_dCost;

	double_uncert	m_duDensity_kg_cm; // kilograms per cubic meter
	std::map<unsigned int, wort_component> m_mSpecial_Components;
};
class grain : public adjunct
{
public:
	enum TYPE {UNDEF,BARLEY,WHEAT,RYE,CORN,RICE,OAT};

	TYPE			m_eType;
	double_uncert	m_duColor_SRM;
	double_uncert	m_duCaramelization_Pct;
	double_uncert	m_duMoisture_Pct;
	double_uncert	m_duExtract_CG_Pct;
	double_uncert	m_duProtein_Pct;
	double_uncert	m_duProtein_Soluble_Pct;
	double_uncert	m_duAlpha_Amylase;
	double_uncert	m_duDiastatic_Power_Deg_Lintner;

};

class wort
{
public:
	double		m_dQuantity_Kilograms;
	std::map<unsigned int, wort_component> m_mComponents;
};

class equipment_type
{
public:
	std::string m_szShort_Name;
	std::string m_szDescription;
	double	m_dCleaning_Efficiency;
	double	m_dMaintenance_Cost;
	double	m_dCleaning_Time_min;
	double	m_dCost; // dollars
};

class pump_type : public equipment_type
{
public:
	double	m_dPump_Flow_Rate_CLM; // (cubic liters per minute)
};
class kettle_type : public equipment_type
{
public:
	double	m_dVolume_Liters;
	double	m_dEnergy_Efficiency;
};

class mash_tun_type : public kettle_type
{
public:
	double	m_dBrewing_Efficiency;
};


class brew_equipment
{
public:
	unsigned int m_uiType;
	double		m_dTime_Of_Last_Major_Maintenance;
	double		m_dTime_Of_Last_Minor_Maintenance;
	double		m_dCleanliness;
};

class mash_tun: public brew_equipment
{
public:
	// object: grain hopper
	// object: water input
	// object: heating
	// object: ouput

	wort		m_wWort;
};

class brew_kettle: public brew_equipment
{
public:
	// object: heating
	// object: input from mash tun
	// object: output to chiller / fermenter
};


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
	std::vector<wort_component_dictionary_entry> 	m_mWort_Component_Dictionary;
	std::vector<mash_tun_type> 						m_mMash_Tun_Dictionary;
	std::vector<kettle_type> 						m_mBrew_Kettle_Dictionary;


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
