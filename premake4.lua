-------------------------------------------------------------------
-- Game of Life build script
-------------------------------------------------------------------

-- Windows specific settings
if os.get() == "windows" then

elseif os.get() == "linux" then

	-- where to export program
	appDir_debug = "bin/debug"
	appDir_release = "bin/release"

	-- header search directories
	headerSearchDirs = {
		"usr/local/include",
		"usr/include",
	}

	-- lib include directories
	libSearchDirs = {
		"usr/local/lib",
		"usr/lib",
	}

	-- link libraries
	linklibs_app_debug = {
		"sfml-system",
		"sfml-graphics",
	}
	linklibs_app_release = {
		"sfml-system",
		"sfml-graphics",
	}

-- MAAAC
elseif os.get() == "macosx" then

-- OS couldn't be determined
else
	printf( "FATAL: Unable to determine your operating system!" )
end

-------------------------------------------------------------------
-- Unilluminable Room Solution
-------------------------------------------------------------------

solution "Unilluminable Room"

	configurations { "Debug", "Release" }
	location "build"
	
	-------------------------------------------------------------------
	-- Global #defines
	-------------------------------------------------------------------
	
	-- Windows specific
	if os.get() == "windows" then
		defines {
			"WIN32",
			"_WINDOWS"
		}
	end

	-------------------------------------------------------------------
	-- Unilluminable Room project
	-------------------------------------------------------------------

	project "Unilluminable Room"
		kind "ConsoleApp"
		language "C++"
		files {
			"unilluminable-room/**.cpp",
			"unilluminable-room/**.hpp",
			"unilluminable-room/**.hxx"
		}

		includedirs {
			headerSearchDirs,
			"unilluminable-room"
		}

		configuration "Debug"
			targetdir (appDir_debug)
			defines {
				"DEBUG",
				"_DEBUG"
			}
			flags {
				"Symbols"
			}
			libdirs (libSearchDirs)
			links (linklibs_app_debug)

		configuration "Release"
			targetdir (appDir_release)
			defines {
				"NDEBUG"
			}
			flags {
				"Optimize"
			}
			libdirs (libSearchDirs)
			links (linklibs_app_release)

