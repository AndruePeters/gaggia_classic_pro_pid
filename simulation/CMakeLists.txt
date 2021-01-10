if (BUILD_LVGL_SIMULATION)
    set(SIMULATION_SOURCES
            ./lv_drivers/display/drm.c              ./lv_drivers/display/SHARP_MIP.c        ./lv_drivers/indev/evdev.c              ./lv_drivers/indev/XPT2046.c
            ./lv_drivers/display/fbdev.c            ./lv_drivers/display/SSD1963.c          ./lv_drivers/indev/FT5406EE8.c          ./lv_drivers/win_drv.c
            ./lv_drivers/display/GC9A01.c           ./lv_drivers/display/ST7565.c           ./lv_drivers/indev/keyboard.c           ./main/src/main.c
            ./lv_drivers/display/ILI9341.c          ./lv_drivers/display/UC1610.c           ./lv_drivers/indev/libinput.c           ./main/src/mouse_cursor_icon.c
            ./lv_drivers/display/monitor.c          ./lv_drivers/gtkdrv/gtkdrv.c            ./lv_drivers/indev/mouse.c
            ./lv_drivers/display/R61581.c           ./lv_drivers/indev/AD_touch.c           ./lv_drivers/indev/mousewheel.c
            main/src/main.c                         main/src/mouse_cursor_icon.c
            ${CMAKE_SOURCE_DIR}/src/ui/lv_demo_widgets.c
            )

    set(USE_SIMULATION_CONF TRUE)
    add_executable(gui_simulation ${SIMULATION_SOURCES})
    target_link_libraries(gui_simulation PRIVATE lvgl SDL2 m)
    target_include_directories(gui_simulation PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/include/)
    target_compile_definitions(gui_simulation PUBLIC  -DSIMULATOR=1)
endif()