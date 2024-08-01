set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/test)

add_executable(test-card)
target_sources(test-card
        PUBLIC
        ${PROJECT_SOURCE_DIR}/test/test-card.cxx)
target_link_libraries(test-card
        PUBLIC
        card
        Catch2::Catch2WithMain)

include(CTest)
include(Catch)

add_test(NAME TestCard COMMAND test-card)
