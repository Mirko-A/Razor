workspace "Razor"
    architecture "x64"
    
	configurations
    {
        "Debug",
        "Release",
        "Dist"
    }
	
    startproject "Prototype"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution dir) 
-- Currently not used, refer to the Game Engine series Ep. 11
-- IncludeDir = {}
-- IncludeDir["spdlog"] = "Engine/vendor/spdlog/include"
-- IncludeDir["GLFW"] = "Engine/vendor/GLFW/include"
-- IncludeDir["Glad"] = "Engine/vendor/Glad/include"
-- IncludeDir["ImGui"] = "Engine/vendor/imgui/include"
-- IncludeDir["ImGui"] = "Engine/vendor/glm/glm"

group "Dependencies"
    include "Razor/vendor/GLFW"
    include "Razor/vendor/Glad"
    include "Razor/vendor/imgui"
    include "Razor/vendor/glm"

group ""

project "Razor"
    location "Razor"
    kind "staticlib"
    language "C++"
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "rzr_pch.h"
	pchsource "Razor/src/rzr_pch.cpp"

    files
    {
        "%{prj.name}/include/**.h",
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs
    {
        "%{prj.name}/include",
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{prj.name}/vendor/GLFW/include",
        "%{prj.name}/vendor/Glad/include",
		"%{prj.name}/vendor/imgui",
		"%{prj.name}/vendor/glm",
    }

    links
	{
	    "GLFW",
	    "Glad",
		"ImGui",
		"opengl32.lib"
	}
	
	defines
	{
	    "_CRT_SECURE_NO_WARNINGS"
	}

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"
		staticruntime "on"
        
        defines
        {
            "RZR_PLATFORM_WINDOWS",
            "RENDERER_API=OPENGL_RENDERER_API",
			"GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug"
        defines "RZR_DEBUG"
		runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "RZR_RELEASE"
		runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "RZR_DIST"
		runtime "Release"
        optimize "On"


project "Prototype"
    location "Prototype"
    kind "ConsoleApp"
    language "C++"
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/include/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs
    {
        "Razor/include",
        "Razor/src",
        "Razor/vendor/spdlog/include",
        "Razor/vendor/GLFW/include",
        "Razor/vendor/Glad/include",
		"Razor/vendor/imgui",
		"Razor/vendor/glm",
    }

    links
	{
	    "Razor",
	}

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"
		staticruntime "on"
        
        defines
        {
            "RZR_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug"
        defines "RZR_DEBUG"
		runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "RZR_RELEASE"
		runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "RZR_DIST"
		runtime "Release"
        optimize "On"
