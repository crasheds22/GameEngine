workspace "GameEngine"
	architecture "x64"
	startproject "Sandbox"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	IncludeDir = {}
	IncludeDir["GLFW"]	= "Engine/Vendor/GLFW/include"
	IncludeDir["Glad"]	= "Engine/Vendor/glad/include"
	IncludeDir["ImGui"] = "Engine/Vendor/imgui"
	IncludeDir["glm"]	= "Engine/Vendor/glm"

	group "Dependencies"
		include "Engine/Vendor/GLFW"
		include "Engine/Vendor/GLAD"
		include "Engine/Vendor/imgui"

	group ""

project "Engine"
	location "Engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "ngpch.h"
	pchsource "Engine/src/ngpch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/Vendor/glm/glm/**.hpp",
		"%{prj.name}/Vendor/glm/glm/**.inl",
	}

	defines {
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links {
		"GLFW",
		"GLAD",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"NG_PLATFORM_WINDOWS",
			"NG_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "NG_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "NG_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "NG_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs {
		"Engine/Vendor/spdlog/include",
		"Engine/src",
		"Engine/Vendor",
		"Engine/Vendor/glm"
	}

	links {
		"Engine"
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"NG_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "NG_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "NG_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "NG_DIST"
		runtime "Release"
		optimize "on"
