#include <iostream>
#include <sstream>

#include "Player.h"

using std::vector, std::string, std::size_t;

Player::Player(bool isAI) : isAI(isAI), hand() /* TODO: initialize */ {}

void Player::addToHand(Card *c)
{
  // TODO: Add the card c to the player's hand
  hand.push_back(c);
}

size_t Player::getHandSize()
{
  // TODO: Implement getter
  return hand.size();
}

std::string Player::getHandString()
{
  // TODO: Implement getter
  string toReturn = "";
  for (size_t i = 0; i < hand.size(); i++)
  {
    toReturn += hand[i]->getRank() + " " + hand[i]->getSuit();

    if (i != hand.size() - 1)
    {
      toReturn += ", ";
    }
  }

  return toReturn;
}

Card *Player::playCard(vector<string> const &suits, string &currentRank, string &currentSuit)
{
  if (isAI)
  {
    for (size_t i = 0; i < hand.size(); i++)
    {
      if (hand[i]->canBePlayed(currentRank, currentSuit))
      {
        Card *toReturn = hand[i];
        toReturn->play();
        currentRank = toReturn->getRank();
        currentSuit = toReturn->getSuit();
        hand.erase(hand.begin() + i);
        return toReturn;
      }
    }

    return nullptr;
  }
  else
  {
    std::cout << "Your hand contains: " << getHandString() << std::endl;
    std::cout << "The next card played must be a " << currentRank << " or " << currentSuit << std::endl;
    std::cout << "What would you like to play? (enter \"draw card\" to draw a card)" << std::endl;
    while (true)
    {
      string input;
      std::getline(std::cin, input);

      if (input == "draw card")
      {
        return nullptr;
      }
      std::istringstream iss(input);
      string rank, suit;
      iss >> rank >> suit;
      bool inDeck = false;
      for (size_t i = 0; i < hand.size(); i++)
      {
        if (hand[i]->getRank() == rank && hand[i]->getSuit() == suit)
        {
          inDeck = true;
          if (hand[i]->canBePlayed(currentRank, currentSuit))
          {
            if (hand[i]->getRank() == "8")
            {
              std::cout << "What suit would you like to declare?" << std::endl;

              bool breakFlag = false;
              while (!breakFlag)
              {
                std::getline(std::cin, suit);
                for (size_t i = 0; i < suits.size(); i++)
                {
                  if (suits[i] == suit)
                  {
                    breakFlag = true;
                    break;
                  }
                }

                if (!breakFlag)
                {
                  std::cout << "That's not a suit in this deck. Try again." << std::endl;
                }
              }

              Card *toReturn = hand[i];
              toReturn->play();
              currentRank = "8";
              currentSuit = suit;
              hand.erase(hand.begin() + i);
              return toReturn;
            }

            Card *toReturn = hand[i];
            toReturn->play();
            currentRank = toReturn->getRank();
            currentSuit = toReturn->getSuit();
            hand.erase(hand.begin() + i);
            return toReturn;
          }
          else
          {
            std::cout << "You can't play that card. Try again." << std::endl;
          }
        }
      }
      if (!inDeck)
      {
        std::cout << "That's not a card you have. Try again." <<std::endl;
      }
    }
  }
}
