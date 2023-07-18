project "Chess"
    kind "ConsoleApp"
    language "C++"
    targetdir "../Build/bin/%{prj.name}"
    objdir "../Build/bin-int/%{prj.name}"
    files { "src/**.h", "src/**.cpp" }
    includedirs{"lib/"}
    links{"lib"}
    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

project "lib"
    kind "StaticLib"
    language "C++"
    targetdir "../Build/bin/%{prj.name}"
    objdir "../Build/bin-int/%{prj.name}"
    files { "lib/**.h", "lib/**.cpp" }
    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

project "gTest"
    kind "StaticLib"
    targetdir "../Build/bin/%{prj.name}"
    objdir "../Build/bin-int/%{prj.name}"
    files { "../googletest/googletest/src/gtest-all.cc" }
    includedirs { "../googletest/googletest/include", "../googletest/googletest" }
    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
    
    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

project "Testing"
    kind "ConsoleApp"
    language "C++"
    targetdir "../Build/bin/%{prj.name}"
    objdir "../Build/bin-int/%{prj.name}"
    files {"unitTests/**.cpp", "unitTests/**.h"}
    includedirs{"lib/", "../googletest/googletest/include"}
    links{"lib", "gTest"}

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"