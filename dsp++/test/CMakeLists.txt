project(dsp++-test)

set(SOURCES
	execution_timer.h
	execution_timer.cpp
	utils.h

	adaptfilt_test.cpp
	fft_test.cpp
	filter_design_test.cpp
	filter_test.cpp
	intmath_test.cpp
	lattice_test.cpp
	levinson_test.cpp
	loudness_test.cpp
	lpc_test.cpp
	mean_test.cpp
	overlap_add_test.cpp
	pow2_test.cpp
	resample_test.cpp
	simd_test.cpp
	window_test.cpp
	xcorr_test.cpp

	main.cpp
)

add_executable(dsp++-test ${SOURCES})
target_include_directories(dsp++-test PRIVATE ${Boost_INCLUDE_DIRS})
target_compile_definitions(dsp++-test PRIVATE BOOST_TEST_DYN_LINK)
target_link_libraries(dsp++-test PRIVATE
	dsp++ ${Boost_UNIT_TEST_FRAMEWORK_LIBRARIES})
install(TARGETS dsp++-test DESTINATION bin)

if (MSVC)
	install(FILES $<TARGET_PDB_FILE:dsp++-test> DESTINATION lib OPTIONAL)
	include(CopyDlls)
	copy_dlls(dsp++-test ${Boost_UNIT_TEST_FRAMEWORK_LIBRARIES})
endif()


macro(dsp_test name)
	add_test(${name}
		${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/dsp++-test --run_test=${name})
endmacro()

dsp_test(adaptfilt)
dsp_test(fft)
dsp_test(filter_design)
dsp_test(filter)
dsp_test(intmath)
dsp_test(lattice)
dsp_test(levinson)
# dsp_test(loudness)
dsp_test(lpc)
dsp_test(mean)
# dsp_test(overlap)
dsp_test(pow2)
# dsp_test(resample)
# dsp_test(simd)
dsp_test(window)
dsp_test(xcorr)

