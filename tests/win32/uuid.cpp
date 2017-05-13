/* tests/win32/uuid.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include "tests/catch.hpp"

#include "win32/uuid.hpp"

TEST_CASE("UUID", "[Win32]")
{
  SECTION("generate")
  {
    Windows::Uuid u;

    REQUIRE(!u.value().empty());
  }
}

extern "C" int wmain(int argc, wchar_t **argv, wchar_t **)
{
  return run(argc,argv);
}

