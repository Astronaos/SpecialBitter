#pragma once

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

