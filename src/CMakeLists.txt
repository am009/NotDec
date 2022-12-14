
add_library(notdec STATIC
	# source files that are common to all frontend
)

# include直接在外部设置了src目录。

target_link_libraries(notdec
	PUBLIC
	LLVMCore LLVMIRReader LLVMSupport # LLVMPasses
)

if (NOTDEC_ENABLE_WASM)
	target_sources(notdec PRIVATE
		frontend/wasm/parser.cpp
		frontend/wasm/parser-block.cpp
	)

	target_link_libraries(notdec
		PUBLIC
		wabt::wabt
	)
	# add_dependencies(notdec wabt)
endif ()

set_target_properties(notdec
	PROPERTIES
		OUTPUT_NAME "notdec"
)

# 添加可执行文件

add_executable(notdec-decompile 
	notdec.cpp
	utils.cpp
)

# target_compile_features(bin2pat PUBLIC cxx_std_17)

target_link_libraries(notdec-decompile 
	notdec
)

set_target_properties(notdec-decompile
	PROPERTIES
		OUTPUT_NAME "notdec"
)

install(TARGETS notdec-decompile DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
