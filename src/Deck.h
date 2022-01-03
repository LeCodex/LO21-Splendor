#ifndef DECK_H
#define DECK_H
#include "BaseCard.h"
#include "ResourceCard.h"
#include "NobleCard.h"
#include <vector>
#include <QFile>
#include <QDomDocument>
#include <QDebug>
#include "BaseCard.h"
#include <vector>
#include <algorithm>
#include <random>

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
        void shuffle(){
            srand(unsigned(time(NULL)));
            std::random_shuffle(std::begin(cards), std::end(cards));
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
            qInfo() << "Resources loaded";
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
            qInfo() << "Nobles loaded";
        }
        else
            throw "Could not load the specified file...\n";
    }

    template <>
    inline void Deck<CitiesCard>::loadXML(const std::string &filename)
    {
        std::cout << "Cities loading...\n";

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
                int price[6];
                int requiredPrestige;

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

                // We load other
                param = param.nextSiblingElement("other");
                if (!param.isNull())
                    price[5] = std::stoi(param.text().toStdString());

                // We load requiredPrestige
                param = param.nextSiblingElement("requiredPrestige");
                if (!param.isNull())
                    requiredPrestige = std::stoi(param.text().toStdString());

                const CitiesCard *c = new CitiesCard(price, requiredPrestige);

                cards.push_back(c);

                child = child.nextSiblingElement("card");
            }

            // Now our deck has been loaded
            qInfo() << "Cities loaded";
        }
        else
            throw "Could not load the specified file...\n";
    }
}
#endif
