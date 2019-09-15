#include "AuctionHouse.h"

AuctionHouse& AuctionHouse::getInstance()
{
	static AuctionHouse inst;
	return inst;
}

void AuctionHouse::AddListing(ListingType type, int amount, int item, int unitPrice)
{
	m_listings.push_back(Listing{type, amount, item, unitPrice});
}

AuctionHouse::AuctionHouse()
{
	AddListing(ListingType::BUY, 20, 0, 20);
	AddListing(ListingType::BUY, 30, 2, 40);
	AddListing(ListingType::SELL, 10, 2, 50);
	AddListing(ListingType::BUY, 12, 1, 30);
	AddListing(ListingType::SELL, 13, 1, 32);
	AddListing(ListingType::SELL, 13, 2, 49);
}