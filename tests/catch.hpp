#pragma once
#ifndef XFSPP_CATCH_HPP
#define XFSPP_CATCH_HPP

#ifdef _MSC_VER
#pragma warning(push, 0)
#endif

#define CATCH_CONFIG_RUNNER
#include "catch/catch.hpp"

#include <functional>

#include <windows.h>

int run(int argc, wchar_t const* const* const argv, std::function< void (const std::wstring &) > initLibF = std::function< void (const std::wstring &) >())
{
  SetEnvironmentVariable(L"XFSPP_LOG_ON_CONSOLE",L"1");

  for (int i = 0; i < argc; ++i)
	if (std::wstring(argv[i]) == L"--lib")
    {
	  if (initLibF)
		initLibF(std::wstring(argv[i+1]));
      
      std::swap(argv[argc-2],argv[i]);
      std::swap(argv[argc-1],argv[i+1]);
      argc -= 2;
      break;
    }

  return Catch::Session().run(argc,argv);
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif
