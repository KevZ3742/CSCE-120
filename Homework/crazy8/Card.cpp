#include <iostream>

#include "Card.h"

using std::string;

Card::Card(string rank, string suit) : rank(rank), suit(suit), timesPlayed(0) /* TODO: initialize */
{
  // TODO: implement constructor checks
  if (rank.empty() || suit.empty())
  {
    throw std::invalid_argument("Rank and suit must not be empty");
  }

  for (char c : rank)
  {
    if (!std::isalnum(c))
    {
      throw std::invalid_argument("Rank must be alphanumeric");
    }
  }

  for (char c : suit)
  {
    if (!std::isalnum(c))
    {
      throw std::invalid_argument("Suit must be alphanumeric");
    }
  }
}

string Card::getRank()
{
  // TODO: implement getter
  return rank;
}

string Card::getSuit()
{
  // TODO: implement getter
  return suit;
}

int Card::getTimesPlayed()
{
  // TODO: implement getter
  return timesPlayed;
}

bool Card::canBePlayed(string currentRank, string currentSuit)
{
  // TODO: return whether or not the card can legally be played
  if(rank == "8"){
    return true;
  }

  if (currentRank == rank || currentSuit == suit) {
    return true;
  }
  
  return false;
}

void Card::play()
{
  timesPlayed++;
}
