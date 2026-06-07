////////////////////////////////////////////////////////////////////////////
//
// str.cpp
//
// CSTR class
// (Seven Tag Roster)
//
// Remi Coulom
//
// june 1996
//
////////////////////////////////////////////////////////////////////////////
#include <cstring>
#include <cstdio>

#include "debug.h"
#include "str.h"

////////////////////////////////////////////////////////////////////////////
// Safe copy of a string to another string with limited size
// snprintf always NUL-terminates and truncates cleanly (the truncation here
// is intentional, sized to the fixed STR fields).
////////////////////////////////////////////////////////////////////////////
static void SafeCopy(char *pszDest, const char *pszOrig, int Size)
{
 std::snprintf(pszDest, Size, "%s", pszOrig);
}

////////////////////////////////////////////////////////////////////////////
// Default constructor
////////////////////////////////////////////////////////////////////////////
CSTR::CSTR()
{
 Reset();
}

////////////////////////////////////////////////////////////////////////////
// Reset function
////////////////////////////////////////////////////////////////////////////
void CSTR::Reset()
{
 *szEvent = 0;
 *szSite  = 0;
 *szRound = 0;
 *szWhite = 0;
 *szBlack = 0;
 Result   = Unknown;
 date = CDate::Today();
}

////////////////////////////////////////////////////////////////////////////
// Functions to set strings
////////////////////////////////////////////////////////////////////////////
void CSTR::SetEvent(const char *psz)
{
 SafeCopy(szEvent, psz, sizeof szEvent);
}

void CSTR::SetSite(const char *psz)
{
 SafeCopy(szSite, psz, sizeof szSite);
}

void CSTR::SetRound(const char *psz)
{
 SafeCopy(szRound, psz, sizeof szRound);
}

void CSTR::SetWhite(const char *psz)
{
 SafeCopy(szWhite, psz, sizeof szWhite);
}

void CSTR::SetBlack(const char *psz)
{
 SafeCopy(szBlack, psz, sizeof szBlack);
}

void CSTR::SetResult(int i)
{
 ASSERT(i >= BlackWins && i <= Unknown);
 Result = i;
}
