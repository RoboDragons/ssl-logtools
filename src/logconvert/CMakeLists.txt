# include_directories(${PROTOBUF_INCLUDE_DIR})
# include_directories(${Boost_INCLUDE_DIRS})

# set(SOURCES
#     logconvert.cpp
# )

# add_executable(logconvert ${SOURCES})
# # target_link_libraries(logconvert common Qt6::Core Qt6::Network ${ZLIB_LIBRARIES} z) # 修正: zlibをリンク
# target_link_libraries(logconvert ${PROTOBUF_LIBRARY}) # 修正: Protobufライブラリをリンク
# if(USE_Qt6)
#     target_link_libraries(logconvert Qt6::Core)
# else()
#     target_link_libraries(logconvert ${QT_QTCORE_LIBRARY})
#     include_directories(${QT_INCLUDE_DIR} ${QT_QTCORE_INCLUDE_DIR})
# endif()

include_directories(${PROTOBUF_INCLUDE_DIR})
include_directories(${Boost_INCLUDE_DIRS})

set(SOURCES
    logconvert.cpp
)

add_executable(logconvert ${SOURCES})
target_link_libraries(logconvert common Qt6::Core Qt6::Network Boost::program_options ${ZLIB_LIBRARIES}) # 修正: Boost::program_optionsを追加
target_link_libraries(logconvert ${PROTOBUF_LIBRARY}) # 修正: Protobufライブラリをリンク