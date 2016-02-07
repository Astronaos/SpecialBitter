#include <SpecialBitter.hpp>
#include <string>
#include <vector>

SPECIAL_BITTER_MAIN	g_cSPECIAL_BITTER_Main;

void SPECIAL_BITTER_MAIN::init(void) // initialization routine; rendering context not created
{
	m_idPane = Register_Pane(true);

	m_dTimer = 0.0;
	m_bFlasher_1s_50p = true;

}
void SPECIAL_BITTER_MAIN::close(void) // program exiting; rendering context destroyed
{
}

