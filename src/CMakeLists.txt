set(srcs "esp_adapter/pin.cpp" "esp_adapter/interrupt.cpp" "esp_adapter/esp_timer.cpp" "esp_adapter/esp_timer_builder.cpp" "esp_adapter/logger.cpp")
set(includes "include")


idf_component_register(SRCS ${srcs}
                       INCLUDE_DIRS ${includes})