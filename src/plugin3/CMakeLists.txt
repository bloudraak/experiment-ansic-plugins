include_directories(${install_dir} ../app/)
add_library (plugin3 SHARED plugin.c ../app/plugin.h)
install(TARGETS plugin3 DESTINATION bin)
