set(target common)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

make_library(${target} "STATIC")

add_sources(${target}
	"Source Files"
	"common.cpp"
)

add_sources(${target}
	"Header Files"
	"common.h"
	"group.h"
	"console_util.h"
	"dimension_coord.h"
)
