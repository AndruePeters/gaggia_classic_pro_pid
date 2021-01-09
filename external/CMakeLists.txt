# This CMakeLists.txt is responsible for setting up external libraries

# Set up LVGL
set(LVGL_SOURCES
    lvgl/src/lv_core/lv_disp.c                              lvgl/src/lv_font/lv_font_montserrat_12_subpx.c          lvgl/src/lv_font/lv_font_unscii_8.c                     lvgl/src/lv_misc/lv_txt.c                               lvgl/src/lv_widgets/lv_label.c
    lvgl/src/lv_core/lv_group.c                             lvgl/src/lv_font/lv_font_montserrat_14.c                lvgl/src/lv_gpu/lv_gpu_nxp_pxp.c                        lvgl/src/lv_misc/lv_txt_ap.c                            lvgl/src/lv_widgets/lv_led.c
    lvgl/src/lv_core/lv_indev.c                             lvgl/src/lv_font/lv_font_montserrat_16.c                lvgl/src/lv_gpu/lv_gpu_nxp_pxp_osa.c                    lvgl/src/lv_misc/lv_utils.c                             lvgl/src/lv_widgets/lv_line.c
    lvgl/src/lv_core/lv_obj.c                               lvgl/src/lv_font/lv_font_montserrat_18.c                lvgl/src/lv_gpu/lv_gpu_nxp_vglite.c                     lvgl/src/lv_themes/lv_theme.c                           lvgl/src/lv_widgets/lv_linemeter.c
    lvgl/src/lv_core/lv_refr.c                              lvgl/src/lv_font/lv_font_montserrat_20.c                lvgl/src/lv_gpu/lv_gpu_stm32_dma2d.c                    lvgl/src/lv_themes/lv_theme_empty.c                     lvgl/src/lv_widgets/lv_list.c
    lvgl/src/lv_core/lv_style.c                             lvgl/src/lv_font/lv_font_montserrat_22.c                lvgl/src/lv_hal/lv_hal_disp.c                           lvgl/src/lv_themes/lv_theme_material.c                  lvgl/src/lv_widgets/lv_msgbox.c
    lvgl/src/lv_draw/lv_draw_arc.c                          lvgl/src/lv_font/lv_font_montserrat_24.c                lvgl/src/lv_hal/lv_hal_indev.c                          lvgl/src/lv_themes/lv_theme_mono.c                      lvgl/src/lv_widgets/lv_objmask.c
    lvgl/src/lv_draw/lv_draw_blend.c                        lvgl/src/lv_font/lv_font_montserrat_26.c                lvgl/src/lv_hal/lv_hal_tick.c                           lvgl/src/lv_themes/lv_theme_template.c                  lvgl/src/lv_widgets/lv_objx_templ.c
    lvgl/src/lv_draw/lv_draw_img.c                          lvgl/src/lv_font/lv_font_montserrat_28.c                lvgl/src/lv_misc/lv_anim.c                              lvgl/src/lv_widgets/lv_arc.c                            lvgl/src/lv_widgets/lv_page.c
    lvgl/src/lv_draw/lv_draw_label.c                        lvgl/src/lv_font/lv_font_montserrat_28_compressed.c     lvgl/src/lv_misc/lv_area.c                              lvgl/src/lv_widgets/lv_bar.c                            lvgl/src/lv_widgets/lv_roller.c
    lvgl/src/lv_draw/lv_draw_line.c                         lvgl/src/lv_font/lv_font_montserrat_30.c                lvgl/src/lv_misc/lv_async.c                             lvgl/src/lv_widgets/lv_btn.c                            lvgl/src/lv_widgets/lv_slider.c
    lvgl/src/lv_draw/lv_draw_mask.c                         lvgl/src/lv_font/lv_font_montserrat_32.c                lvgl/src/lv_misc/lv_bidi.c                              lvgl/src/lv_widgets/lv_btnmatrix.c                      lvgl/src/lv_widgets/lv_spinbox.c
    lvgl/src/lv_draw/lv_draw_rect.c                         lvgl/src/lv_font/lv_font_montserrat_34.c                lvgl/src/lv_misc/lv_color.c                             lvgl/src/lv_widgets/lv_calendar.c                       lvgl/src/lv_widgets/lv_spinner.c
    lvgl/src/lv_draw/lv_draw_triangle.c                     lvgl/src/lv_font/lv_font_montserrat_36.c                lvgl/src/lv_misc/lv_debug.c                             lvgl/src/lv_widgets/lv_canvas.c                         lvgl/src/lv_widgets/lv_switch.c
    lvgl/src/lv_draw/lv_img_buf.c                           lvgl/src/lv_font/lv_font_montserrat_38.c                lvgl/src/lv_misc/lv_fs.c                                lvgl/src/lv_widgets/lv_chart.c                          lvgl/src/lv_widgets/lv_table.c
    lvgl/src/lv_draw/lv_img_cache.c                         lvgl/src/lv_font/lv_font_montserrat_40.c                lvgl/src/lv_misc/lv_gc.c                                lvgl/src/lv_widgets/lv_checkbox.c                       lvgl/src/lv_widgets/lv_tabview.c
    lvgl/src/lv_draw/lv_img_decoder.c                       lvgl/src/lv_font/lv_font_montserrat_42.c                lvgl/src/lv_misc/lv_ll.c                                lvgl/src/lv_widgets/lv_cont.c                           lvgl/src/lv_widgets/lv_textarea.c
    lvgl/src/lv_font/lv_font.c                              lvgl/src/lv_font/lv_font_montserrat_44.c                lvgl/src/lv_misc/lv_log.c                               lvgl/src/lv_widgets/lv_cpicker.c                        lvgl/src/lv_widgets/lv_tileview.c
    lvgl/src/lv_font/lv_font_dejavu_16_persian_hebrew.c     lvgl/src/lv_font/lv_font_montserrat_46.c                lvgl/src/lv_misc/lv_math.c                              lvgl/src/lv_widgets/lv_dropdown.c                       lvgl/src/lv_widgets/lv_win.c
    lvgl/src/lv_font/lv_font_fmt_txt.c                      lvgl/src/lv_font/lv_font_montserrat_48.c                lvgl/src/lv_misc/lv_mem.c                               lvgl/src/lv_widgets/lv_gauge.c
    lvgl/src/lv_font/lv_font_loader.c                       lvgl/src/lv_font/lv_font_montserrat_8.c                 lvgl/src/lv_misc/lv_printf.c                            lvgl/src/lv_widgets/lv_img.c
    lvgl/src/lv_font/lv_font_montserrat_10.c                lvgl/src/lv_font/lv_font_simsun_16_cjk.c                lvgl/src/lv_misc/lv_task.c                              lvgl/src/lv_widgets/lv_imgbtn.c
    lvgl/src/lv_font/lv_font_montserrat_12.c                lvgl/src/lv_font/lv_font_unscii_16.c                    lvgl/src/lv_misc/lv_templ.c                             lvgl/src/lv_widgets/lv_keyboard.c
)

add_library(lvgl STATIC ${LVGL_SOURCES} lv_conf.h)
target_include_directories(lvgl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/)
#target_compile_definitions(lvgl PUBLIC "-DLV_CONF_INCLUDE_SIMPLE")

if (CONFIG_LV_MEM_CUSTOM)
    if (CONFIG_LV_MEM_CUSTOM_ALLOC)
    target_compile_definitions(lvgl PUBLIC "-DLV_MEM_CUSTOM_ALLOC=${CONFIG_LV_MEM_CUSTOM_ALLOC}")
    endif()

    if (CONFIG_LV_MEM_CUSTOM_FREE)
    target_compile_definitions(lvgl PUBLIC "-DLV_MEM_CUSTOM_FREE=${CONFIG_LV_MEM_CUSTOM_FREE}")
    endif()
endif()

if (CONFIG_LV_TICK_CUSTOM)
    if (CONFIG_LV_TICK_CUSTOM_SYS_TIME_EXPR)
    target_compile_definitions(lvgl PUBLIC "-DLV_TICK_CUSTOM_SYS_TIME_EXPR=${CONFIG_LV_TICK_CUSTOM_SYS_TIME_EXPR}")
    endif()
endif()

if (CONFIG_LV_USER_DATA_FREE)
    target_compile_definitions(lvgl PUBLIC "-DLV_USER_DATA_FREE=${CONFIG_LV_USER_DATA_FREE}")
endif()

if (CONFIG_LV_ATTRIBUTE_FAST_MEM_USE_IRAM)
    target_compile_definitions(lvgl PUBLIC "-DLV_ATTRIBUTE_FAST_MEM=IRAM_ATTR")
endif()



# Now do TFT drivers
set(lvgl_tft_driver_sources
        lvgl_esp32_drivers/lvgl_helpers.c          lvgl_esp32_drivers/lvgl_tft/disp_spi.c
        lvgl_esp32_drivers/lvgl_tft/disp_driver.c  lvgl_esp32_drivers/lvgl_tft/ili9341.c)
add_library(lvgl_tft_driver STATIC ${lvgl_tft_driver_sources})
target_include_directories(lvgl_tft_driver PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(lvgl_tft_driver PRIVATE idf::esp32)
target_compile_definitions(lvgl_tft_driver PUBLIC
        -DCONFIG_LV_TFT_DISPLAY_CONTROLLER_ILI9341
        -DCONFIG_LV_DISP_PIN_DC=2
        -DCONFIG_LV_DISP_PIN_RST=4
        -DCONFIG_LV_DISP_PIN_BCKL=12
        -DCONFIG_LV_BACKLIGHT_ACTIVE_LVL=1
        -DCONFIG_LV_DISPLAY_ORIENTATION=0
        -DCONFIG_LV_PREDEFINED_DISPLAY_NONE
        -DCONFIG_LV_DISP_SPI_MOSI=13
        -DCONFIG_LV_DISP_SPI_CLK=14
        -DCONFIG_LV_DISP_SPI_CS=15
        -DCONFIG_LV_ENABLE_BACKLIGHT_CONTROL=y
        -DCONFIG_LV_TFT_DISPLAY_PROTOCOL_SPI
        -DCONFIG_LV_TFT_DISPLAY_SPI_HSPI=y
        )