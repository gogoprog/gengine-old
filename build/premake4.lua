solution "gengine"
    configurations { "Debug", "Release", "DebugEmscripten", "ReleaseEmscripten" }

    platforms { "x32", "x64" }

    project "gengine"
        kind "ConsoleApp"
        language "C++"

        files { "../src/**.h", "../src/**.cpp" }

        includedirs {
            "../src/kernel",
            "../src/core",
            "../src/application",
            "../src/graphics",
            "../src/input",
            "../src/script",
            "../src/entity",
            "../src/gui"
            }

        links { "lua" }

        flags { "ExtraWarnings", "FatalWarnings", "FloatFast", "NoExceptions", "NoFramePointer", "NoNativeWChar" }
        buildoptions { "-std=c++11 -Wno-error=unused-variable -Wno-error=unused-parameter" }

        configuration "Debug*"
            defines { "DEBUG" }
            flags { "Symbols" }
            targetname "gengined"

        configuration "Release*"
            defines { "NDEBUG" }
            flags { "Optimize" }
            targetname "gengine"

        configuration "*Emscripten"
            defines { "EMSCRIPTEN" }
            libdirs { "../deps/emscripten/lib" }
            includedirs { "../deps/emscripten/include" }
            targetsuffix ".bc"
            postbuildcommands { "emcc $(TARGET) -o gengine.html --preload-file ../tests/basic@" }

        configuration "not *Emscripten"
            includedirs { "../deps/linux/include", "../deps/linux/include/cef" }
            links { "SDL2", "SDL2_image", "GL", "cef", "cef_dll_wrapper" }

        configuration { "not *Emscripten", "x32" }
            libdirs { "../deps/linux/lib32" }

        configuration { "not *Emscripten", "x64" }
            libdirs { "../deps/linux/lib64" }

