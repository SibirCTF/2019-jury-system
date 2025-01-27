cmake_minimum_required(VERSION 3.0)

project(fhq-jury-ad)

add_definitions(-DJURY_AD_VERSION="0.3.0")
add_definitions(-DJURY_AD_APP_NAME="fhq-jury-ad")

set(CMAKE_CXX_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH ${fhq-jury-ad_SOURCE_DIR})
# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set (JURY_AD_LIBRARIES "")
set (JURY_AD_INCLUDE_DIRS "")
set (JURY_AD_SOURCES "")

# Sources

# include header dirs
list (APPEND JURY_AD_INCLUDE_DIRS "src")
list (APPEND JURY_AD_INCLUDE_DIRS "src/checker")
list (APPEND JURY_AD_INCLUDE_DIRS "src/config")
list (APPEND JURY_AD_INCLUDE_DIRS "src/objects")
list (APPEND JURY_AD_INCLUDE_DIRS "src/resources")
list (APPEND JURY_AD_INCLUDE_DIRS "src/resources/files")
list (APPEND JURY_AD_INCLUDE_DIRS "src/scoreboard")
list (APPEND JURY_AD_INCLUDE_DIRS "src/utils")
list (APPEND JURY_AD_INCLUDE_DIRS "src/core")
list (APPEND JURY_AD_INCLUDE_DIRS "src/interfaces")
list (APPEND JURY_AD_INCLUDE_DIRS "src/storages")
list (APPEND JURY_AD_INCLUDE_DIRS "src/storages/file")
list (APPEND JURY_AD_INCLUDE_DIRS "src/web-server")
list (APPEND JURY_AD_INCLUDE_DIRS "src/web-server/core")
list (APPEND JURY_AD_INCLUDE_DIRS "src/3rd_party/nlohmann")
list (APPEND JURY_AD_INCLUDE_DIRS "src/3rd_party/HowardHinnant/date")

# nlohmann::json
list (APPEND JURY_AD_SOURCES "src/3rd_party/nlohmann/json.hpp")


# HowardHinnant/date
list (APPEND JURY_AD_SOURCES "src/3rd_party/HowardHinnant/date/date.h")

# config
list (APPEND JURY_AD_SOURCES "src/core/fallen.h")
list (APPEND JURY_AD_SOURCES "src/core/fallen.cpp")
list (APPEND JURY_AD_SOURCES "src/core/light_http_server.h")
list (APPEND JURY_AD_SOURCES "src/core/light_http_server.cpp")

# checker
list (APPEND JURY_AD_SOURCES "src/checker/dorunchecker.h")
list (APPEND JURY_AD_SOURCES "src/checker/dorunchecker.cpp")
list (APPEND JURY_AD_SOURCES "src/checker/service_checker_thread.h")
list (APPEND JURY_AD_SOURCES "src/checker/service_checker_thread.cpp")

# config
list (APPEND JURY_AD_SOURCES "src/config/conf_file_parser.h")
list (APPEND JURY_AD_SOURCES "src/config/conf_file_parser.cpp")
list (APPEND JURY_AD_SOURCES "src/config/config.h")
list (APPEND JURY_AD_SOURCES "src/config/config.cpp")
list (APPEND JURY_AD_SOURCES "src/config/read_teams_conf.h")
list (APPEND JURY_AD_SOURCES "src/config/read_teams_conf.cpp")
list (APPEND JURY_AD_SOURCES "src/config/service.h")
list (APPEND JURY_AD_SOURCES "src/config/service.cpp")
list (APPEND JURY_AD_SOURCES "src/config/team.h")
list (APPEND JURY_AD_SOURCES "src/config/team.cpp")


# web-server
list (APPEND JURY_AD_SOURCES "src/web-server/http_handler_api_v1.h")
list (APPEND JURY_AD_SOURCES "src/web-server/http_handler_api_v1.cpp")
list (APPEND JURY_AD_SOURCES "src/web-server/http_handler_web_folder.h")
list (APPEND JURY_AD_SOURCES "src/web-server/http_handler_web_folder.cpp")

# objects
list (APPEND JURY_AD_SOURCES "src/objects/flag.h")
list (APPEND JURY_AD_SOURCES "src/objects/flag.cpp")

# resources

#[begin-list-of-resources]

list (APPEND JURY_AD_SOURCES "./src/resources/files/html_favicon_16x16_png.h")
list (APPEND JURY_AD_SOURCES "./src/resources/files/html_favicon_16x16_png.cpp")
list (APPEND JURY_AD_SOURCES "./src/resources/files/html_favicon_ico.h")
list (APPEND JURY_AD_SOURCES "./src/resources/files/html_favicon_ico.cpp")
list (APPEND JURY_AD_SOURCES "./src/resources/files/html_index_html.h")
list (APPEND JURY_AD_SOURCES "./src/resources/files/html_index_html.cpp")
list (APPEND JURY_AD_SOURCES "./src/resources/files/html_favicon_32x32_png.h")
list (APPEND JURY_AD_SOURCES "./src/resources/files/html_favicon_32x32_png.cpp")
list (APPEND JURY_AD_SOURCES "./src/resources/files/html_css_scoreboard_css.h")
list (APPEND JURY_AD_SOURCES "./src/resources/files/html_css_scoreboard_css.cpp")
list (APPEND JURY_AD_SOURCES "./src/resources/files/html_images_defence_svg.h")
list (APPEND JURY_AD_SOURCES "./src/resources/files/html_images_defence_svg.cpp")
list (APPEND JURY_AD_SOURCES "./src/resources/files/html_images_logo_png.h")
list (APPEND JURY_AD_SOURCES "./src/resources/files/html_images_logo_png.cpp")
list (APPEND JURY_AD_SOURCES "./src/resources/files/html_images_first_blood_svg.h")
list (APPEND JURY_AD_SOURCES "./src/resources/files/html_images_first_blood_svg.cpp")
list (APPEND JURY_AD_SOURCES "./src/resources/files/html_images_attack_svg.h")
list (APPEND JURY_AD_SOURCES "./src/resources/files/html_images_attack_svg.cpp")
list (APPEND JURY_AD_SOURCES "./src/resources/files/html_images_activity_svg.h")
list (APPEND JURY_AD_SOURCES "./src/resources/files/html_images_activity_svg.cpp")
list (APPEND JURY_AD_SOURCES "./src/resources/files/html_images_uptime_svg.h")
list (APPEND JURY_AD_SOURCES "./src/resources/files/html_images_uptime_svg.cpp")
list (APPEND JURY_AD_SOURCES "./src/resources/files/html_images_points_svg.h")
list (APPEND JURY_AD_SOURCES "./src/resources/files/html_images_points_svg.cpp")
list (APPEND JURY_AD_SOURCES "./src/resources/files/html_images_states_down_svg.h")
list (APPEND JURY_AD_SOURCES "./src/resources/files/html_images_states_down_svg.cpp")
list (APPEND JURY_AD_SOURCES "./src/resources/files/html_images_states_up_svg.h")
list (APPEND JURY_AD_SOURCES "./src/resources/files/html_images_states_up_svg.cpp")
list (APPEND JURY_AD_SOURCES "./src/resources/files/html_images_states_mumble_svg.h")
list (APPEND JURY_AD_SOURCES "./src/resources/files/html_images_states_mumble_svg.cpp")
list (APPEND JURY_AD_SOURCES "./src/resources/files/html_images_states_shit_svg.h")
list (APPEND JURY_AD_SOURCES "./src/resources/files/html_images_states_shit_svg.cpp")
list (APPEND JURY_AD_SOURCES "./src/resources/files/html_images_states_wait_svg.h")
list (APPEND JURY_AD_SOURCES "./src/resources/files/html_images_states_wait_svg.cpp")
list (APPEND JURY_AD_SOURCES "./src/resources/files/html_images_states_corrupt_svg.h")
list (APPEND JURY_AD_SOURCES "./src/resources/files/html_images_states_corrupt_svg.cpp")
list (APPEND JURY_AD_SOURCES "./src/resources/files/html_images_states_coffeebreak_svg.h")
list (APPEND JURY_AD_SOURCES "./src/resources/files/html_images_states_coffeebreak_svg.cpp")
list (APPEND JURY_AD_SOURCES "./src/resources/files/html_images_teams_unknown_svg.h")
list (APPEND JURY_AD_SOURCES "./src/resources/files/html_images_teams_unknown_svg.cpp")
list (APPEND JURY_AD_SOURCES "./src/resources/files/html_js_scoreboard_js.h")
list (APPEND JURY_AD_SOURCES "./src/resources/files/html_js_scoreboard_js.cpp")
list (APPEND JURY_AD_SOURCES "./src/resources/files/game_conf.h")
list (APPEND JURY_AD_SOURCES "./src/resources/files/game_conf.cpp")
list (APPEND JURY_AD_SOURCES "./src/resources/files/mysql_storage_conf.h")
list (APPEND JURY_AD_SOURCES "./src/resources/files/mysql_storage_conf.cpp")
list (APPEND JURY_AD_SOURCES "./src/resources/files/scoreboard_conf.h")
list (APPEND JURY_AD_SOURCES "./src/resources/files/scoreboard_conf.cpp")
list (APPEND JURY_AD_SOURCES "./src/resources/files/server_conf.h")
list (APPEND JURY_AD_SOURCES "./src/resources/files/server_conf.cpp")

#[end-list-of-resources]

list (APPEND JURY_AD_SOURCES "src/resources/resources_manager.h")
list (APPEND JURY_AD_SOURCES "src/resources/resources_manager.cpp")

# scoreboard
list (APPEND JURY_AD_SOURCES "src/scoreboard/scoreboard.cpp")
list (APPEND JURY_AD_SOURCES "src/scoreboard/scoreboard.h")
list (APPEND JURY_AD_SOURCES "src/scoreboard/service_costs_and_statistics.h")
list (APPEND JURY_AD_SOURCES "src/scoreboard/service_costs_and_statistics.cpp")
list (APPEND JURY_AD_SOURCES "src/scoreboard/service_status_cell.h")
list (APPEND JURY_AD_SOURCES "src/scoreboard/service_status_cell.cpp")
list (APPEND JURY_AD_SOURCES "src/scoreboard/team_status_row.h")
list (APPEND JURY_AD_SOURCES "src/scoreboard/team_status_row.cpp")

# utils
list (APPEND JURY_AD_SOURCES "src/utils/colormod.h")
list (APPEND JURY_AD_SOURCES "src/utils/fs.h")
list (APPEND JURY_AD_SOURCES "src/utils/fs.cpp")
list (APPEND JURY_AD_SOURCES "src/utils/ts.h")
list (APPEND JURY_AD_SOURCES "src/utils/ts.cpp")
list (APPEND JURY_AD_SOURCES "src/utils/str.h")
list (APPEND JURY_AD_SOURCES "src/utils/str.cpp")
list (APPEND JURY_AD_SOURCES "src/utils/utils_help_parse_args.h")
list (APPEND JURY_AD_SOURCES "src/utils/utils_help_parse_args.cpp")
list (APPEND JURY_AD_SOURCES "src/utils/utils_logger.h")
list (APPEND JURY_AD_SOURCES "src/utils/utils_logger.cpp")

# storages
list (APPEND JURY_AD_SOURCES "src/storages/storages.h")
list (APPEND JURY_AD_SOURCES "src/storages/storages.cpp")

# file storage
# list (APPEND JURY_AD_SOURCES "src/storages/file/file_storage.h")
# list (APPEND JURY_AD_SOURCES "src/storages/file/file_storage.cpp")

# main
list (APPEND JURY_AD_SOURCES "src/main.cpp")


############################
##### mysql storage
list (APPEND JURY_AD_INCLUDE_DIRS "src/storages/mysql")
list (APPEND JURY_AD_SOURCES "src/storages/mysql/mysql_storage.h")
list (APPEND JURY_AD_SOURCES "src/storages/mysql/mysql_storage.cpp")

# Find and make sure the system have the header file
find_path(MYSQL_HEADER mysql/mysql.h)
if(MYSQL_HEADER STREQUAL "MYSQL_HEADER-NOTFOUND")
    message(FATAL_ERROR "Could not find the mysql/mysql.h header file: apt install libmysqlclient-dev")
endif()

include(FindPkgConfig)
pkg_check_modules(LIBMYSQLCLIENT REQUIRED mysqlclient)

foreach(FLAG ${LIBMYSQLCLIENT_CFLAGS_OTHER})
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${FLAG}")
endforeach()

list (APPEND JURY_AD_INCLUDE_DIRS ${LIBMYSQLCLIENT_LIBRARY_DIRS})
list (APPEND JURY_AD_LIBRARIES ${LIBMYSQLCLIENT_LIBRARIES})

#####
############################

# ZLIB
find_package( ZLIB REQUIRED )
if ( ZLIB_FOUND )
    list (APPEND JURY_AD_INCLUDE_DIRS ${ZLIB_INCLUDE_DIRS})
    include_directories( ${ZLIB_INCLUDE_DIRS} )
    list (APPEND JURY_AD_LIBRARIES ${ZLIB_LIBRARIES})
endif( ZLIB_FOUND )

# LIBPNG
find_package(PNG REQUIRED)
if (NOT PNG_FOUND)
    message(FATAL_ERROR "You don't seem to have libpng development libraries installed (apt isntall libpng-dev)")
else ()
    list (APPEND JURY_AD_INCLUDE_DIRS ${PNG_INCLUDE_DIR})
    list (APPEND JURY_AD_LIBRARIES ${PNG_LIBRARY})
endif ()

# CURL
FIND_PACKAGE(CURL)
IF(CURL_FOUND)
  list (APPEND JURY_AD_INCLUDE_DIRS ${CURL_INCLUDE_DIR})
  list (APPEND JURY_AD_LIBRARIES ${CURL_LIBRARIES})
ELSE(CURL_FOUND)
  MESSAGE(FATAL_ERROR "Could not find the CURL library and development files.")
ENDIF(CURL_FOUND)

include_directories(${JURY_AD_INCLUDE_DIRS})

add_executable (fhq-jury-ad ${JURY_AD_SOURCES})

target_link_libraries(fhq-jury-ad -lpthread ${JURY_AD_LIBRARIES} )

install(
    TARGETS
        fhq-jury-ad
    RUNTIME DESTINATION
        ${CMAKE_INSTALL_PREFIX}/bin
)
