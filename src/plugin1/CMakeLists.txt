include_directories(${install_dir} ../app/)
add_library (plugin1 SHARED plugin.c ../app/plugin.h)
install(TARGETS plugin1 DESTINATION bin)
