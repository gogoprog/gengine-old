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

        flags { "ExtraWarnings", "FloatFast", "NoExceptions", "NoFramePointer", "NoNativeWChar" }

        if not os.is("windows") then
            buildoptions { "-std=c++11 -Wno-error=unused-variable -Wno-error=unused-parameter" }
        end

        includedirs { "../deps/common/include" }

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
            targetsuffix ".bc"
            if not os.is("windows") then
                linkoptions { "-Wno-warn-absolute-paths" }
            end

        configuration "not *Emscripten"
            includedirs { "../deps/common/include/cef" }

            if os.is("linux") then
                includedirs { "../deps/linux/include" }
            elseif os.is("windows") then
                includedirs { "../deps/windows/include" }
            end

            links { "SDL2", "SDL2_image", "GL", "cef", "cef_dll_wrapper"}

        configuration { "not *Emscripten", "x32" }
            libdirs { "../deps/linux/lib32" }

        configuration { "not *Emscripten", "x64" }
            libdirs { "../deps/linux/lib64" }

