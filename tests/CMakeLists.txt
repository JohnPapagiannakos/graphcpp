Project(examples)

SET(TEST_SRC_FILE_NAMES test_matrix
                        test_adjmatrix
                        test_BFS
                        test_DFS
                        test_weighted_graph
                        test_shortest_path
                        test_btree
                        test_bst
                        )

INCLUDE_DIRECTORIES(${INCLUDE_DIR})
FOREACH(TEST IN LISTS TEST_SRC_FILE_NAMES)

    MESSAGE(STATUS "Creating executable for ${TEST}.cpp")

    ADD_EXECUTABLE(${TEST} ${CMAKE_CURRENT_LIST_DIR}/${TEST}.cpp)
    TARGET_INCLUDE_DIRECTORIES(${TEST} PUBLIC ${INCLUDE_DIR})
    TARGET_LINK_LIBRARIES(${TEST} ${LIBRARIES_TO_LINK})

    SET_TARGET_PROPERTIES(
        ${TEST}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${BIN_DIR}"
    )
ENDFOREACH()