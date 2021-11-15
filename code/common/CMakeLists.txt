set(target common)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

make_library(${target} "STATIC")

add_sources(${target}
	"Common"
	"common.cpp"
	"common.h"
)

add_sources(${target}
	"Header Files"
	"bit_op.h"
	"group.h"
	"console_util.h"
	"dimension_coord.h"
)
