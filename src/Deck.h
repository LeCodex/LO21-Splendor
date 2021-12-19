#pragma once
#include "BaseCard.h"
#include <vector>
#include <tinyxml.h>

namespace Splendor
{
	template <class T = BaseCard>
	class Deck
	{
	private:
		std::vector<const T *> cards;

		Deck(const Deck &) = delete;
		Deck &operator=(const Deck &) = delete;

	public:
		Deck() = default;

		int getNbCards() const
		{
			return cards.size();
		}
		std::vector<const T *> getAllCards() const { return cards; }
		const T &getCard(size_t i) const
		{
			if (i > cards.size())
				throw "Index out of bound\n";
			return *cards[i];
		}
		void loadXML(const std::string &filename);
	};

	template <>
	inline void Deck<ResourceCard>::loadXML(const std::string &filename)
	{
		std::cout << "Resources loading...\n";

		TiXmlDocument doc(filename);
		if (doc.LoadFile())
		{
			TiXmlElement *elem = doc.FirstChildElement("cards");
			if (elem)
			{
				TiXmlElement *child = elem->FirstChildElement("card");
				while (child)
				{
					// Now we iterate through cards
					int price[5];
					int prestige;
					Token resource;
					int level;

					// We load token price
					TiXmlElement *param = child->FirstChildElement("cost");

					if (param)
					{
						TiXmlElement *cost = param->FirstChildElement("token");

						size_t i = 0;
						while (cost)
						{
							price[i++] = std::stoi(cost->GetText());
							cost = cost->NextSiblingElement("token");
						}
					}

					// We load prestige
					param = param->NextSiblingElement("prestige");
					if (param)
						prestige = std::stoi(param->GetText());

					// We load resource
					param = param->NextSiblingElement("resource");
					if (param)
						resource = Token(std::stoi(param->GetText()));

					// We load level
					param = param->NextSiblingElement("level");
					if (param)
						level = std::stoi(param->GetText());

					const ResourceCard *c = new ResourceCard(price, prestige, resource, level);

					cards.push_back(c);

					child = child->NextSiblingElement("card");
				}
			}
			// Now our deck has been loaded
		}
		else
			throw "Could not load the specified file...\n";
	}

	template <>
	inline void Deck<NobleCard>::loadXML(const std::string &filename)
	{
		std::cout << "Nobles loading...\n";

		TiXmlDocument doc(filename);
		if (doc.LoadFile())
		{
			TiXmlElement *elem = doc.FirstChildElement("cards");
			if (elem)
			{
				TiXmlElement *child = elem->FirstChildElement("card");
				while (child)
				{
					// Now we iterate through cards
					int price[5];
					int prestige;

					// We load token price
					TiXmlElement *param = child->FirstChildElement("cost");

					if (param)
					{
						TiXmlElement *cost = param->FirstChildElement("token");

						size_t i = 0;
						while (cost)
						{
							price[i++] = std::stoi(cost->GetText());
							cost = cost->NextSiblingElement("token");
						}
					}

					// We load prestige
					param = param->NextSiblingElement("prestige");
					if (param)
						prestige = std::stoi(param->GetText());

					const NobleCard *c = new NobleCard(price, prestige);

					cards.push_back(c);

					child = child->NextSiblingElement("card");
				}
			}
		}
		else
			throw "Could not load the specified file...\n";
	}
}
