#pragma once
#include "BaseCard.h"
#include "ResourceCard.h"
#include "NobleCard.h"
#include <vector>
#include <QFile>
#include <QDomDocument>
#include <QDebug>

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

        QFile file(QString::fromStdString(filename));

        file.open(QFile::ReadOnly | QFile::Text);

        QDomDocument doc;

        doc.setContent(&file, false);

        // racine pointe sur cards
        QDomElement racine = doc.documentElement();

        if (!racine.isNull())
        {
                QDomElement child = racine.firstChildElement("card");
                while (!child.isNull())
				{

					// Now we iterate through cards
					int price[5];
					int prestige;
					Token resource;
					int level;

					// We load token price
                    QDomElement param = child.firstChildElement("cost");

                    if (!param.isNull())
					{
                        QDomElement cost = param.firstChildElement("token");

						size_t i = 0;
                        while (!cost.isNull())
						{
                            price[i++] = std::stoi(cost.text().toStdString());
                            cost = cost.nextSiblingElement("token");
						}
					}

					// We load prestige
                    param = param.nextSiblingElement("prestige");
                    if (!param.isNull())
                        prestige = std::stoi(param.text().toStdString());

					// We load resource
                    param = param.nextSiblingElement("resource");
                    if (!param.isNull())
                        resource = Token(std::stoi(param.text().toStdString()));

					// We load level
                    param = param.nextSiblingElement("level");
                    if (!param.isNull())
                        level = std::stoi(param.text().toStdString());

					const ResourceCard *c = new ResourceCard(price, prestige, resource, level);

					cards.push_back(c);

                    child = child.nextSiblingElement("card");
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

        QFile file(QString::fromStdString(filename));

        file.open(QFile::ReadOnly | QFile::Text);

        QDomDocument doc;

        doc.setContent(&file, false);

        // racine pointe sur cards
        QDomElement racine = doc.documentElement();

        if (!racine.isNull())
        {
                QDomElement child = racine.firstChildElement("card");
                while (!child.isNull())
                {

                    // Now we iterate through cards
                    int price[5];
                    int prestige;
                    Token resource;
                    int level;

                    // We load token price
                    QDomElement param = child.firstChildElement("cost");

                    if (!param.isNull())
                    {
                        QDomElement cost = param.firstChildElement("token");

                        size_t i = 0;
                        while (!cost.isNull())
                        {
                            price[i++] = std::stoi(cost.text().toStdString());
                            cost = cost.nextSiblingElement("token");
                        }
                    }

                    // We load prestige
                    param = param.nextSiblingElement("prestige");
                    if (!param.isNull())
                        prestige = std::stoi(param.text().toStdString());

                    const NobleCard *c = new NobleCard(price, prestige);

                    cards.push_back(c);

                    child = child.nextSiblingElement("card");
                }

            // Now our deck has been loaded
        }
        else
            throw "Could not load the specified file...\n";
    }
}
