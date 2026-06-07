/////////////////////////////////////////////////////////////////////////////
//
// Rémi Coulom
//
// December, 2004
//
/////////////////////////////////////////////////////////////////////////////
#include "EloDataFromFile.h"
#include "pgnlex.h"
#include "pgn.h"
#include "str.h"
#include "CResultSet.h"

#include <map>
#include <string>
#include <iostream>



/////////////////////////////////////////////////////////////////////////////
// Read all data for Elo calculation
/////////////////////////////////////////////////////////////////////////////
void EloDataFromFile(CPGNLex &pgnlex,
                     CResultSet &rs,
                     std::vector<std::string> &vNames)
{
 int Players = 0;
 int Ignored = 0;

 //
 // Add current players to the name map
 //
 std::map<std::string, int> NameMap;
 for (int i = vNames.size(); --i >= 0;)
 {
  std::pair<const std::string, int> Pair(vNames[i], i);
  NameMap.insert(Pair);
  Players++;
 }

 //
 // Loop over games
 //
 while (1)
 {
  CSTR str;
  int fTheEnd = CPGN::ReadSTR(str, pgnlex);
  pgnlex.SkipGame();
  
  if (!fTheEnd)
  {
   //
   // Ignore unknown results
   //
   int r = str.GetResult();
   if (r < 0 || r > 2)
    Ignored++;
   else
   {
    std::string sWhite(str.GetWhite());
    std::string sBlack(str.GetBlack());

    int WhitePlayer;
    {
     std::pair<std::map<std::string, int>::iterator, bool> res = 
      NameMap.insert(std::pair<const std::string, int>(sWhite, Players));
     if (res.second)
     {
      Players++;
      vNames.push_back(sWhite);
     }
     WhitePlayer = res.first->second;
    }

    int BlackPlayer;
    {
     std::pair<std::map<std::string, int>::iterator, bool> res = 
      NameMap.insert(std::pair<const std::string, int>(sBlack, Players));
     if (res.second)
     {
      Players++;
      vNames.push_back(sBlack);
     }
     BlackPlayer = res.first->second;
    }

    rs.Append(WhitePlayer, BlackPlayer, r);
   }
  }

  if (rs.GetGames() % 1000 == 0 || fTheEnd)
  {
   std::cerr << rs.GetGames() << " game(s) loaded, ";
   std::cerr << Ignored << " game(s) with unknown result ignored.\r";
  }

  if (fTheEnd)
  {
   std::cerr << '\n';
   break;
  }
 }
}
