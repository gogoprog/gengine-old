solution "luasocket"
    configurations { "Release" }

    platforms { "x32", "x64" }

    project "luasocket"
        kind "StaticLib"
        language "C"
        files { "*.c" }
