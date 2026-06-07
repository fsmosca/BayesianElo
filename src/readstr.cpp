////////////////////////////////////////////////////////////////////////////
//
// readstr.cpp
//
// ReadString function
//
// Remi Coulom
//
// june, 1998
//
////////////////////////////////////////////////////////////////////////////
#include <iostream>

using namespace std;

#include "readstr.h"

////////////////////////////////////////////////////////////////////////////
// Function : Reads a string from a stream
// Return   : Length of the string read, -1 if EOF
////////////////////////////////////////////////////////////////////////////
int ReadString(istream &is, char *pszBuffer, int Size)
{
 int i;

 if (is.eof())
  return -1;

 for(i = 0; i < Size; i++)
 {
  int c;
  c = is.peek();

  if (c == std::char_traits<char>::eof() || is.fail())
  {
   pszBuffer[i] = 0;
   return -1;
  }

  is.get();
  if (c == '\n')
  {
   pszBuffer[i] = 0;
   return i;
  }
  else
   pszBuffer[i] = c;
 }

 //
 // Buffer filled without reaching a newline: terminate to keep the result a
 // valid C-string (the caller treats it as one). The overlong line is
 // truncated rather than left unterminated, which would over-read.
 //
 pszBuffer[Size - 1] = 0;
 return i;
}
