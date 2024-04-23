#include "Game.h"

#include <iostream>
#include <fstream>
#include <sstream>

using std::string, std::vector, std::ifstream, std::invalid_argument;

Game::Game() : players({}), suits({}), ranks({}), deck({}), drawPile({}), discardPile({}) {}

string *splitString(const string &str, char delimiter, int &count)
{
  count = 1;
  size_t pos = 0;
  size_t found;
  while ((found = str.find(delimiter, pos)) != string::npos)
  {
    ++count;
    pos = found + 1;
  }
  string *substrings = new string[count];
  std::stringstream ss(str);
  string token;
  int i = 0;
  while (getline(ss, token, delimiter))
  {
    substrings[i++] = token;
  }
  return substrings;
}

void Game::loadDeckFromFile(string filename)
{
  // TODO: initialize suits, ranks, deck, and drawPile from the given file
  ifstream file(filename);
  if (!file.is_open())
  {
    throw invalid_argument("File not found");
  }
  string line;
  getline(file, line);
  int count1;
  string *substrings = splitString(line, ' ', count1);

  for (int i = 0; i < count1; i++)
  {
    suits.push_back(substrings[i]);
  }
  delete[] substrings;

  getline(file, line);
  int count2;
  substrings = splitString(line, ' ', count2);

  for (int i = 0; i < count2; i++)
  {
    ranks.push_back(substrings[i]);
  }
  delete[] substrings;

  while (getline(file, line))
  {
    int count;
    substrings = splitString(line, ' ', count);
    if (count != 2)
    {
      delete[] substrings;
      throw std::runtime_error("Invalid card format");
    }
    bool validRank = false;
    for (string r : ranks)
    {
      if (substrings[0] == r)
      {
        validRank = true;
      }
    }
    if (validRank == false)
    {
      delete[] substrings;
      throw std::runtime_error("Invalid card format");
    }

    bool validSuit = false;
    for (string s : suits)
    {
      if (substrings[1] == s)
      {
        validSuit = true;
      }
    }
    if (validSuit == false)
    {
      delete[] substrings;
      throw std::runtime_error("Invalid card format");
    }

    try
    {
      Card *c = new Card(substrings[0], substrings[1]);
      deck.push_back(c);
      drawPile.insert(drawPile.begin(), c);
      delete[] substrings;
    }
    catch (invalid_argument const &)
    {
      delete[] substrings;
      throw std::runtime_error("Invalid card format");
    }
  }
}

void Game::addPlayer(bool isAI)
{
  // TODO: add a new player to the game
  Player *p = new Player(isAI);
  players.push_back(p);
}

void Game::drawCard(Player *p)
{
  // TODO: Move the top card of the draw pile to Player p's hand
  // If the draw pile is empty, flip the discard pile to create a new one
  if (drawPile.size() == 0 && discardPile.size() == 0)
  {
    throw std::runtime_error("Both draw and discard piles are empty");
  }

  if (drawPile.size() == 0)
  {
    std::cout << "Draw pile, empty, flipping the discard pile." << std::endl;

    int initialSize = discardPile.size();
    for (size_t i = 0; i < initialSize; i++)
    {
      drawPile.push_back(discardPile.back());
      discardPile.pop_back();
    }
  }

  p->addToHand(drawPile.back());
  drawPile.pop_back();
}

Card *Game::deal(int numCards)
{
  discardPile.push_back(drawPile.back());
  Card *initiallyDiscardedCard = drawPile.back();
  drawPile.pop_back();

  for (int i = 0; i < numCards; i++)
  {
    for (Player *p : players)
    {
      drawCard(p);
    }
  }

  return initiallyDiscardedCard;
}

string Game::mostPlayedSuit()
{
  vector<int> suitCounts(suits.size(), 0);
  int index;
  for (Card *c : deck)
  {
    for (string s : suits)
    {
      if (c->getSuit() == s)
      {
        for (size_t i = 0; i < suits.size(); ++i)
        {
          if (suits[i] == s)
          {
            index = i;
          }
        }
        suitCounts[index] += c->getTimesPlayed();
      }
    }
  }

  int max_index = 0;
  int max_value = suitCounts[0];

  for (int i = 1; i < suitCounts.size(); ++i)
  {
    if (suitCounts[i] > max_value)
    {
      max_value = suitCounts[i];
      max_index = i;
    }
  }

  return suits[max_index];
}

int Game::runGame()
{
  int currentPlayer = 0;

  while (true)
  {
    std::cout << "Player " << currentPlayer << "'s turn!" << std::endl;
    Player *p = players[currentPlayer];
    string currentRank = discardPile.back()->getRank();
    string currentSuit = discardPile.back()->getSuit();
    Card *c = p->playCard(suits, currentRank, currentSuit);
    
    if (c == nullptr)
    {
      std::cout << "Player " << currentPlayer << " draws a card." <<std::endl;
      try {
        drawCard(p);
      } catch (...) {
        std::cout << "Player " << currentPlayer << " cannot draw a card." << std::endl;
        return -1;
      }
    }
    else
    {
      if (c->getRank() == "8")
      {
        std::cout << "Player " << currentPlayer << " plays " << c->getRank() << " " << c->getSuit() << " and changes the suit to " << currentSuit << "." <<std::endl;
      } else {
        std::cout << "Player " << currentPlayer << " plays " << c->getRank() << " " << c->getSuit() << "." <<std::endl;
      }

      discardPile.push_back(c);
      if (p->getHandSize() == 0)
      {
        break;
      }
    }

    currentPlayer = (currentPlayer + 1) % players.size();
  }

  return currentPlayer;
}


// Destructor--Deallocates all the dynamic memory we allocated
Game::~Game()
{
  for (unsigned int i = 0; i < deck.size(); i++)
  {
    delete deck.at(i);
  }
  for (unsigned int i = 0; i < players.size(); i++)
  {
    delete players.at(i);
  }
}
