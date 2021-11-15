set(target main)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

make_executable(${target} "CONSOLE")

add_pch(${target} pch.cpp pch.h) 

add_sources(${target}
	"main"
	"main.cpp"
)

add_sources(${target}
	"Framework"
	"Framework.cpp"
	"Framework.h"
)

add_sources(${target}
	"Header Files"
)

add_and_link_dependency(${target} common)
add_and_link_dependency(${target} omok)

target_link_libraries(${target}
	PUBLIC
		${WINLIBS}
)
