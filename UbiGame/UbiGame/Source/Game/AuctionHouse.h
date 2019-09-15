#pragma once

#include <vector>

enum class ListingType
{
	BUY,
	SELL
};

struct Listing
{
	ListingType m_type;
	int m_amount;
	int m_itemId;
	int m_unitPrice;
};

class AuctionHouse
{
public:
	static AuctionHouse& getInstance();

	void AddListing(ListingType type, int amount, int item, int unitPrice);
	const std::vector<Listing>& GetListings() const { return m_listings; }

private:
	AuctionHouse();

	std::vector<Listing> m_listings;
};