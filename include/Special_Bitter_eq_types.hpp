#pragma once

class equipment_type
{
public:
	std::string m_szShort_Name;
	std::string m_szDescription;
	double	m_dCleaning_Efficiency;
	double	m_dMaintenance_Cost;
	double	m_dCleaning_Time_min;
	double	m_dCost; // dollars
	std::vector<PAIR<int> > m_vpiMap_Usage; // list of spaces consumed by the object, with 0,0 as the location; effectively describes a area that the object occupies; -1,0 is one space to the left, 0,1 is one space "up", etc.
};

class grain_storage_type : public equipment_type
{
public:
	double	m_dVolume;
};
class grain_mill_type : public equipment_type
{
public:
	double	m_dMilling_Efficiency;
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
class tank_type : public equipment_type
{
public:
	double	m_dVolume_Liters;
};
class kegging_equipment_type : public equipment_type
{
public:
	enum KEG_TYPE {UNDEF,BALL_LOCK,PIN_LOCK,SANKE};
	KEG_TYPE	m_eKeg_Type;
	double	m_dKegging_rate_lpm; // liters per minute
};
class bottling_equipment_type : public equipment_type
{
public:
	double	m_dSize_l; // size of cans/bottles handled by the equipment
	double	m_dRate_lpm; // liters per minute
};

