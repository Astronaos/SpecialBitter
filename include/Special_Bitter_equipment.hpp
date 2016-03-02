#pragma once

class brew_equipment
{
public:
	unsigned int m_uiType;
	PAIR<int>	m_tpPosition; /// location in brewery
	double		m_dTime_Of_Last_Major_Maintenance;
	double		m_dTime_Of_Last_Minor_Maintenance;
	double		m_dCleanliness;

	brew_equipment(void)
	{
		m_uiType = 0;
		m_tpPosition =  PAIR<int>(-1,-1);
		m_dTime_Of_Last_Major_Maintenance = 0.0;
		m_dTime_Of_Last_Minor_Maintenance = 0.0;
		m_dCleanliness = 1.0; 
	}
};

class grain_storage : public brew_equipment
{
public:
	grain	m_grainContent;
};

class grain_mill : public brew_equipment
{
public:
	// input: grain storage
	// output: grain to mash tun
	grain	m_grainContent;

	
};

class mash_tun: public brew_equipment
{
public:
	// input: grain from grain_mill
	// input: water source
	// input: heating
	// output: wort to brew kettle
	// output: spent grain
	std::vector<grain>	m_vgrainGrains;
	beer_wort		m_wWort;
};

class brew_kettle: public brew_equipment
{
public:
	// input: wort from mash tun
	// input: heating
	// output: wort to chiller / fermenter

};

class tank: public brew_equipment
{
public:
	// input/output: wort or water
};

class kegging_system: public brew_equipment
{
public:
	// input: wort or water
	// input: empty kegs
	// output: filled kegs
};
class bottling_system: public brew_equipment
{
public:
	// input: wort or water
	// input: bottles and caps
	// output: filled bottes
};
class canning_system: public brew_equipment
{
public:
	// input: wort or water
	// input: empty cans
	// output: filled cans
};
