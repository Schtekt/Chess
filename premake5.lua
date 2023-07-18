require "vscode"
require "clean"

workspace "Chess"
    architecture "x86_64"
    cppdialect "C++17"
    configurations
    {
        "Debug",
        "Release"
    }
    filter "system:windows"
        platforms {"Win64"}

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

    include "Chess"