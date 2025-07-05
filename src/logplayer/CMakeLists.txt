include_directories(${PROTOBUF_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(SOURCES
    logplayer.cpp
    mainwindow.cpp
    player.cpp
)

set(MOC_SOURCES
    mainwindow.h
    player.h
)

set(UI_SOURCES
    mainwindow.ui
)

add_executable(logplayer ${SOURCES} ${MOC_SOURCES} ${UI_SOURCES})
# target_link_libraries(logplayer common)
target_link_libraries(logplayer common Qt6::Core Qt6::Network ${PROTOBUF_LIBRARY}) # 修正: Qt6::Networkを追加
if(USE_Qt6)
    target_link_libraries(logplayer Qt6::Widgets Qt6::Network)
else()
    target_link_libraries(logplayer ${QT_QTGUI_LIBRARY} ${QT_QTNETWORK_LIBRARY})
    include_directories(${QT_INCLUDE_DIR} ${QT_QTCORE_INCLUDE_DIR} ${QT_QTGUI_INCLUDE_DIR} ${QT_QTNETWORK_INCLUDE_DIR})
endif()

# include_directories(${PROTOBUF_INCLUDE_DIR})

# set(SOURCES
#     player.cpp
# )

# add_executable(logplayer ${SOURCES})
# target_link_libraries(logplayer common Qt6::Core Qt6::Network ${PROTOBUF_LIBRARY}) # 修正: Qt6::Networkを追加