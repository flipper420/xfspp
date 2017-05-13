/* tests/win32/library.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include "tests/catch.hpp"

#include "win32/library.hpp"

TEST_CASE("Libraries", "[Win32]")
{
  SECTION("not-existing library")
  {
    REQUIRE(!Windows::Library(L"not_existing_library.dll"));
  }

  SECTION("existing library")
  {
    Windows::Library l(L"kernel32.dll");

    REQUIRE(l);
    REQUIRE_THROWS_AS(l.call< DWORD >("No_GetTickCount64"),std::invalid_argument);
    REQUIRE_NOTHROW(l.call< DWORD >("GetTickCount64"));
  }
}

extern "C" int wmain(int argc, wchar_t **argv, wchar_t **)
{
  return run(argc,argv);
}
