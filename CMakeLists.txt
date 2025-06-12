# --- Set LVGL Source Directory ---
set(LVGL_SOURCE_DIR "../lvgl_port/lvgl")

# --- Librarys ---
# Sources for LVGL core, widgets, themes, and extras
file(GLOB_RECURSE LVGLCPP_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

add_library(lvglcpp STATIC
    ${LVGLCPP_SOURCES}
)

target_include_directories(lvglcpp PUBLIC
    "${LVGL_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}" 
    "${CMAKE_CURRENT_SOURCE_DIR}/src"

)
message(STATUS "lvglcpp/CMakeLists.txt: Defined lvglcpp library.")