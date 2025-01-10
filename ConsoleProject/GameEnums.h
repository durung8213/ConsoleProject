#pragma once

namespace GameEnums
{
	enum class ItemType
	{
		ITEM_EMPTY,
		ITEM_ARMOR,
		ITEM_WEAPON,
		ITEM_RING,
		ITEM_POTION,
		ITEM_SOLDOUT
	};

	enum class Location
	{
		LOCATION_SHOP = 1,
		LOCATION_MAP,
		LOCATION_INVENTORY,
		LOCATION_SELL_INVENTORY,
		LOCATION_RESELL_SHOP
	};

	enum class Job
	{
		WARRIOR,
		WHITEMAGE,
		BLACKMAGE
	};

	enum class Skill
	{
		SWING = 40,
		CURE = 30,
		FIRE = 40,
		THORNS = 25
	};

	enum class Effect
	{
		ATK,
		DEF,
		CRT,
		HP,
		MP
	};

}