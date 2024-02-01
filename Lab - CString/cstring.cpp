#include <iostream>
#include "cstring.h"

unsigned int length(char str[])
{
  unsigned int count = 0;
  while (str[count] != '\0')
  {
    count++;
  }
  return count;
}

unsigned int find(char str[], char character)
{
  unsigned int index = 0;
  while (str[index] != '\0')
  {
    if (str[index] == character)
    {
      return index;
    }
    index++;
  }
  return index;
}

bool equalStr(char str1[], char str2[])
{
  unsigned int index = 0;

  while (str1[index] != '\0' && str2[index] != '\0')
  {
    if (str1[index] != str2[index])
    {
      return false;
    }
    index++;
  }

  return (str1[index] == '\0' && str2[index] == '\0');
}