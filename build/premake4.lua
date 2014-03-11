solution "gengine"
   configurations { "Debug", "Release" }

   project "gengine"
      kind "ConsoleApp"
      language "C++"
      files { "../src/**.h", "../src/**.cpp" }

      links { "SDL2", "lua" }
 
      configuration "Debug"
         defines { "DEBUG" }
         flags { "Symbols" }
 
      configuration "Release"
         defines { "NDEBUG" }
         flags { "Optimize" }
