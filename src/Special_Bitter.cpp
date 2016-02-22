#include <SpecialBitter.hpp>
#include <string>
#include <vector>

special_bitter_main	g_cSpecial_Bitter_Main;

void special_bitter_main::init(void) // initialization routine; rendering context not created
{
	m_idPane = Register_Pane(true);

	m_dTimer = 0.0;
	m_bFlasher_1s_50p = true;

	m_ihmMap.Set_Map_Size(PAIR<unsigned int>(64,64),3);
	m_ihmMap.Set_Map_Zoom(2.0);
	for (unsigned int uiI = 0; uiI < 20; uiI++)
		m_ihmMap.Shift_Zoom(1.0/1.1);
	m_ihmMap.Center_Map(PAIR<int>(32,32));
//		printf("List init %i\n",m_ihmMap.Get_Map_List());

//	Set_Draw_Mode(PROJECTION);
}
void special_bitter_main::close(void) // program exiting; rendering context destroyed
{
}

