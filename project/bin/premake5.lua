workspace "Ephemeral"
  configurations { "Debug", "Release" }
  location ("../" .. _ACTION)
  platforms { "Shared64", "Static64", "Shared32", "Static32" }

project "Ephemeral"
  language "C"
  targetdir "../../build/"
  files { "../../src/UnityBuild.c" }

  filter "configurations:Debug"
    defines { "DEBUG", "EPHEMERAL_DEBUG" }
    flags { "Symbols" }
  filter "configurations:Release"
    defines { "NDEBUG", "EPHEMERAL_RELEASE" }
    optimize "Speed"

  filter "platforms:Static32"
    kind "StaticLib"
	defines "EPHEMERAL_STATIC"
    architecture "x32"
  filter "platforms:Static64"
    kind "StaticLib"
	defines "EPHEMERAL_STATIC"
    architecture "x64"
  filter "platforms:Shared32"
    kind "SharedLib"
	defines "EPHEMERAL_EXPORTS"
    architecture "x32"
  filter "platforms:Shared64"
    kind "SharedLib"
	defines "EPHEMERAL_EXPORTS"
    architecture "x64"