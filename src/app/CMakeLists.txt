include_directories(${install_dir})
add_executable (app main.c plugin.c)

install(TARGETS app DESTINATION bin)
install(FILES app.conf DESTINATION etc COMPONENT config)
