#pragma once

class equipment_type
{
public:
	std::string m_szManufacturer;
	std::string m_szShort_Name;
	std::string m_szDescription;
	std::string m_szLong_Description;
	double	m_dCleaning_Efficiency;
	double	m_dMaintenance_Cost;
	double	m_dCleaning_Time_min;
	double	m_dCost; // dollars
	double	m_dWorkload_mph; // man-hours per hour of operation; may not be suitable for all equipment types
	std::vector<PAIR<int> > m_vpiMap_Usage; // list of spaces consumed by the object, with 0,0 as the location; effectively describes a area that the object occupies; -1,0 is one space to the left, 0,1 is one space "up", etc.
};

enum enum_keg_type {KT_UNDEF,BALL_LOCK,PIN_LOCK,SANKE};
enum enum_bottle_type {BT_UNDEF, GLASS, ALUMINUM};
enum enum_can_type {CT_UNDEF,CT_ALUMINUM,CT_STEEL_AL_ALLOY};
enum enum_can_opening_type {COT_STAY_TAB,COT_PULL_TAB,COT_PUSH_TAB,COT_NONE};
enum enum_bottle_closure_type {BCT_CAP,BCT_CORK};

class keg_type : equipment_type
{
public:
	enum_keg_type	m_eKeg_Tap_Type;
	double			m_dVolume_Liters;
};
class bottle_type : equipment_type
{
public:
	enum_bottle_type	m_eBottle_Material_Type;
	enum_bottle_closure_type	m_eBottle_Closure_Type;
	double			m_dVolume_Liters;
	TRIPLET<double>	m_tdColor; // green and brown plastics or glasses will do better with light protection; opaque = 0,0,0; clear = 1,1,1
};
class can_type : equipment_type
{
public:
	enum_can_type	m_eCan_Material_Type;
	double			m_dVolume_Liters;
	enum_can_opening_type	m_eCan_Opening_Type; // for marketing purposes only
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

class lauter_tun_type : public equipment_type
{
public:
	double	m_dSparging_Efficiency;
};
class mash_tun_type : public kettle_type
{
public:
	double	m_dBrewing_Efficiency;
};
class whirlpool_type : public equipment_type
{
public:
	double	m_dClarifying_Efficiency;
};

class tank_type : public equipment_type
{
public:
	double	m_dVolume_Liters;
};
class kegging_equipment_type : public equipment_type
{
public:
	enum_keg_type	m_eKeg_Type;
	double	m_dKegging_rate_lpm; // liters per minute
};
class bottling_equipment_type : public equipment_type
{
public:
	double	m_dSize_l; // size of cans/bottles handled by the equipment
	double	m_dRate_lpm; // liters per minute
};
/*
class two_tank_brewhouse_type : public kettle_type, mash_tun_type
{
};
class three_tank_brewhouse_type : public kettle_type, mash_tun_type, lauter_tun_type
{
};
class four_tank_brewhouse_type : public kettle_type, mash_tun_type, lauter_tun_type, whirlpool_type
{
};
*/
