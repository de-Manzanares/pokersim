add_library(card)
target_sources(card
        PUBLIC
        PUBLIC
        FILE_SET CXX_MODULES
        BASE_DIRS ${PROJECT_SOURCE_DIR}/mod
        FILES
        ${PROJECT_SOURCE_DIR}/mod/Card.cppm)
