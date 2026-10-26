message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(
        ${PROJECT_NAME} 
        PRIVATE 
            -g
            -O0
            #-fno-omit-frame-pointer
            #-fsanitize=address
            #-fsanitize=undefined
            #-fno-optimize-sibling-calls
            #-fsanitize=thread
        )
    target_link_options(${PROJECT_NAME} PRIVATE 
        -DEBUG
        -Wall
        #-fsanitize=address
        #-fsanitize=undefined
        #-fsanitize=thread

    )
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    include(CheckIPOSupported)
    check_ipo_supported(RESULT result OUTPUT output)
    if(result)
        set_target_properties(${PROJECT_NAME} PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
    else()
        message(WARNING "IPO is not supported: ${output}")
    endif()

    target_compile_options(${PROJECT_NAME} 
        PRIVATE 
        -O3  
        -DNDEBUG
        -march=native
    )
    
    #TODO: Add msvc
endif()