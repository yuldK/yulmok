set(target omok)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

make_library(${target} "STATIC")

#add_sources(${target}
#	"Source Files"
#	"player.cpp"
#)

add_sources(${target}
	"player"
	"player.cpp"
	"player.h"
)

add_sources(${target}
	"Header Files"
	"hint.h"
	"rule.h"
	"board.h"
	"coord.h"
)
