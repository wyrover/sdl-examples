BOOK_CODE_PATH = "E:/book-code"
THIRD_PARTY = "E:/book-code/3rdparty"
WORK_PATH = os.getcwd()
includeexternal (BOOK_CODE_PATH .. "/premake-vs-include.lua")




workspace(path.getname(os.realpath(".")))
    language "C++"
    location "build/%{_ACTION}/%{wks.name}"    
    if _ACTION == "vs2015" then
        toolset "v140_xp"
    elseif _ACTION == "vs2013" then
        toolset "v120_xp"
    end

    --include (BOOK_CODE_PATH .. "/common.lua")    
    

    function create_sdl_project(name, dir)        
        create_console_project(name, dir)
            includedirs
            {
                "3rdparty/SDL2-2.0.5/include",
                "3rdparty/SDL2_image-2.0.1/include",
                "3rdparty/SDL2_ttf-2.0.14/include",
                "3rdparty/SDL2_mixer-2.0.1/include",
                "3rdparty/SDL2_net-2.0.1/include",
                "%{THIRD_PARTY}/zlib"

            }
            links
            {
                "3rdparty/SDL2-2.0.5/lib/x86/SDL2.lib",
                "3rdparty/SDL2_ttf-2.0.14/lib/x86/SDL2_ttf.lib",
                "3rdparty/SDL2_image-2.0.1/lib/x86/SDL2_image.lib",
                "3rdparty/SDL2_mixer-2.0.1/lib/x86/SDL2_mixer.lib",
                "3rdparty/SDL2_net-2.0.1/lib/x86/SDL2_net.lib",                
            }
            link_libs
            {
                "zlib1.lib"
            }
    end

    group "sdl-examples"    

        matches = os.matchdirs("src/sdl2*")
        for i = #matches, 1, -1 do           
            create_sdl_project(path.getname(matches[i]), "src")
        end


        project "AlienAttack"          
            kind "ConsoleApp"                                             
            files
            {                                  
                "src/%{prj.name}/**.h",
                "src/%{prj.name}/**.cpp", 
                "src/%{prj.name}/**.c", 
                "src/%{prj.name}/**.rc",
                "src/tinyxml/**.h",
                "src/tinyxml/**.cpp"
            }
            removefiles
            {               
            }
            includedirs
            {               
                "3rdparty",  
                "src/tinyxml"
            }         
            includedirs
            {
                "3rdparty/SDL2-2.0.5/include",
                "3rdparty/SDL2_image-2.0.1/include",
                "3rdparty/SDL2_ttf-2.0.14/include",
                "3rdparty/SDL2_mixer-2.0.1/include",
                "3rdparty/SDL2_net-2.0.1/include",
                "%{THIRD_PARTY}/zlib"

            }
            links
            {
                "3rdparty/SDL2-2.0.5/lib/x86/SDL2.lib",
                "3rdparty/SDL2_ttf-2.0.14/lib/x86/SDL2_ttf.lib",
                "3rdparty/SDL2_image-2.0.1/lib/x86/SDL2_image.lib",
                "3rdparty/SDL2_mixer-2.0.1/lib/x86/SDL2_mixer.lib",
                "3rdparty/SDL2_net-2.0.1/lib/x86/SDL2_net.lib",                
            }
            link_libs
            {
                "zlib1.lib"
            }
            has_stdafx("AlienAttack", "src")          

        
    

        create_sdl_project("Breakout", "src")
        create_sdl_project("Pong", "src")

--        create_console_project("sdl2-init", "src")
--            includedirs
--            {
--                "SDL2-2.0.5/include"
--            }
--            links
--            {
--                "SDL2-2.0.5/lib/x86/SDL2.lib"
--            }
--
--        create_console_project("sdl2-01", "src")
--            includedirs
--            {
--                "SDL2-2.0.5/include"
--            }
--            links
--            {
--                "SDL2-2.0.5/lib/x86/SDL2.lib"
--            }
--
--        create_console_project("sdl2-02", "src")
--            includedirs
--            {
--                "SDL2-2.0.5/include"
--            }
--            links
--            {
--                "SDL2-2.0.5/lib/x86/SDL2.lib"
--            }
--
--        create_console_project("sdl2-03", "src")
--            includedirs
--            {
--                "SDL2-2.0.5/include",
--                "SDL2_image-2.0.1/include",
--            }
--            links
--            {
--                "SDL2-2.0.5/lib/x86/SDL2.lib",
--                "SDL2_image-2.0.1/lib/x86/SDL2_image.lib"
--            }
--
--            
--        create_console_project("sdl2-hello", "src")
--            includedirs
--            {
--                "SDL2-2.0.5/include"
--            }
--            links
--            {
--                "SDL2-2.0.5/lib/x86/SDL2.lib"
--            }
--
--
--        create_console_project("gui", "src")
--            includedirs
--            {
--                "SDL2-2.0.5/include",
--                "SDL2_image-2.0.1/include",
--                "SDL2_ttf-2.0.14/include",
--                --"SDL2_mixer-2.0.1/include"
--
--            }
--            links
--            {
--                "SDL2-2.0.5/lib/x86/SDL2.lib",
--                "SDL2_ttf-2.0.14/lib/x86/SDL2_ttf.lib",
--                "SDL2_image-2.0.1/lib/x86/SDL2_image.lib",
--                --"SDL2_mixer-2.0.1/lib/x86/SDL2_mixer.lib"
--
--            }
--
--
--        create_console_project("sdl2-ttf", "src")
--            includedirs
--            {
--                "SDL2-2.0.5/include",
--                --"SDL2_image-2.0.1/include",
--                "SDL2_ttf-2.0.14/include",
--                --"SDL2_mixer-2.0.1/include"
--
--            }
--            links
--            {
--                "SDL2-2.0.5/lib/x86/SDL2.lib",
--                "SDL2_ttf-2.0.14/lib/x86/SDL2_ttf.lib",
--                --"SDL2_image-2.0.1/lib/x86/SDL2_image.lib",
--                --"SDL2_mixer-2.0.1/lib/x86/SDL2_mixer.lib"
--
--            }
--
--        create_console_project("sdl2-draw-a-circle", "src")
--            includedirs
--            {
--                "SDL2-2.0.5/include",
--                "SDL2_image-2.0.1/include",
--                "SDL2_ttf-2.0.14/include",
--                --"SDL2_mixer-2.0.1/include"
--
--            }
--            links
--            {
--                "SDL2-2.0.5/lib/x86/SDL2.lib",
--                "SDL2_ttf-2.0.14/lib/x86/SDL2_ttf.lib",
--                "SDL2_image-2.0.1/lib/x86/SDL2_image.lib",
--                --"SDL2_mixer-2.0.1/lib/x86/SDL2_mixer.lib"
--
--            }


            