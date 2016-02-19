if os.is("linux") then
    local getcxxflags = premake.gcc.getcxxflags;
    function premake.gcc.getcxxflags(cfg)
        local cxxflags = { Cxx11 = "-std=c++11" }
        local r = getcxxflags(cfg);
        local r2 = table.translate(cfg.flags, cxxflags);
        for _,v in ipairs(r2) do table.insert(r, v) end
        return r;
    end
    table.insert(premake.fields.flags.allowed, "Cxx11");
end

solution "gengine"
    configurations { "Debug", "Release", "DebugEmscripten", "ReleaseEmscripten" }

    platforms { "x32", "x64" }

    project "gengine"
        kind "ConsoleApp"
        language "C++"

        files {
            "../src/**.h",
            "../src/**.cpp"
            }

        includedirs {
            "../src/kernel",
            "../src/core",
            "../src/math",
            "../src/application",
            "../src/graphics",
            "../src/graphics/spriter",
            "../src/graphics/spine",
            "../src/audio",
            "../src/input",
            "../src/script",
            "../src/entity",
            "../src/gui",
            "../src/physics",
            "../src/navigation",
            "../src/tiled"
            }

        links {
            "Urho3D",
            "Box2D"
            }

        flags {
            "ExtraWarnings",
            "FloatFast",
            "NoExceptions",
            "NoFramePointer",
            "NoNativeWChar"
            }

        if os.is("linux") then
            defines { "_LINUX" }
            flags { "Cxx11" }
            buildoptions { "-Wno-error=unused-variable -Wno-error=unused-parameter" }
        elseif os.is("windows") then
            defines { "_WINDOWS", "NOMINMAX" }
            flags { "StaticRuntime" }
        end

        includedirs {
            "../deps/common/include",
            "../deps/common/tilemover2d/src/",
            "../deps/common/jsonxx/",
            "../deps/common/spine/include/",
            "../deps/common/include/Urho3D/ThirdParty/"
            }

        files {
            "../deps/common/tilemover2d/src/micropather.*",
            "../deps/common/tilemover2d/src/tilemover2d.*",
            "../deps/common/jsonxx/*.*",
            "../deps/common/spine/src/spine/*.*"
            }

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
            if os.is("linux") then
                includedirs { "../deps/linux/include" }
                includedirs { "../deps/linux/include/cef" }
                links {
                    "SDL2",
                    "SDL2_image",
                    "SDL2_mixer",
                    "SDL2_ttf",
                    "GL",
                    "cef",
                    "cef_dll_wrapper",
                    "pthread",
                    "dl"
                    }

            elseif os.is("windows") then
                includedirs { "../deps/windows/include" }
                includedirs { "../deps/windows/include/cef" }
                libdirs { "../deps/windows/lib" }
                links {
                    "SDL2",
                    "SDL2_image",
                    "SDL2_mixer",
                    "SDL2_ttf",
                    "OpenGL32",
                    "libcef",
                    "libcef_dll_wrapper",
                    "glew32"
                    }
            end

        configuration { "not *Emscripten", "x32" }
            libdirs { "../deps/linux/lib32" }

        configuration { "not *Emscripten", "x64" }
            libdirs { "../deps/linux/lib64" }
