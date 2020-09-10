
# testing to see if ctriskseg target is defined. If it's not we will download 
# ctriskseg at configure time.
IF( NOT TARGET libctriskseg)
	include(FetchContent)
	## Adding CTRiskSeg package
	FetchContent_Declare(
		libctriskseg
		GIT_REPOSITORY https://github.com/medicalphysics/CTRiskSeg.git
		GIT_TAG master
		)
	FetchContent_MakeAvailable(libctriskseg)
ENDIF()


add_executable(example_seg example_seg.cpp)
target_link_libraries(example_seg PRIVATE libctriskseg)

install(TARGETS example_seg
	RUNTIME DESTINATION examples)
