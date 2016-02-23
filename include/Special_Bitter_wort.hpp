#pragma once

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

class beer_wort // used for both beer and wort
{
public:
	double		m_dQuantity_Kilograms;
	std::map<unsigned int, wort_component> m_mComponents;
};

