#pragma once
#include"Shop.h"
#include "Player.h"
class ShopGenerator
{
public:
	bool IsOut = false;
	shared_ptr<Player>m_player;
private:
	Shop* m_shop;
	GameEnums::Location mLocation;

public:
	ShopGenerator();
	~ShopGenerator();

	void UpdateShop();
	void PrintShopImage();

	void SetShopPage();
	void SetInventoryPage();
	void SetSellInventoryPage();
	void SetReSellShopPage();

	void DisplayShopItems(GameEnums::ItemType itemKind);
	void BuyItemFromShop(GameEnums::ItemType itemKind, int num);
	void EquipItemToPlayer(const int num);

	void SetLocation(GameEnums::Location location) { mLocation = location; }

};

