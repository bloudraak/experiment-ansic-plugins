include_directories(${install_dir} ../app/)
add_library (plugin2 SHARED plugin.c ../app/plugin.h)
install(TARGETS plugin2 DESTINATION bin)
