set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

set(SOURCES
    multicastsocket.cpp
    multicastsocket.h
    qtiocompressor.cpp
)

set(MOC_SOURCES
    qtiocompressor.h
)

# ライブラリを先に定義
add_library(qt ${SOURCES} ${MOC_SOURCES})
# add_library(common ${SOURCES})
# ライブラリにリンクを追加
target_link_libraries(qt Qt6::Core Qt6::Widgets)
target_link_libraries(qt ${ZLIB_LIBRARIES})

if(USE_Qt6)
    target_link_libraries(qt Qt6::Core Qt6::Network)
else()
    target_link_libraries(qt ${QT_QTCORE_LIBRARY} ${QT_QTNETWORK_LIBRARY})
    include_directories(${QT_INCLUDE_DIR} ${QT_QTCORE_INCLUDE_DIR} ${QT_QTNETWORK_INCLUDE_DIR})
endif()

if(WIN32)
    target_link_libraries(qt wsock32)
endif()