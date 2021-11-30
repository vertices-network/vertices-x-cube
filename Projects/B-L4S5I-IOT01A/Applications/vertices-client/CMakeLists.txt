set(PROJECT_NAME vertices-example)
project(${PROJECT_NAME} C ASM)


set(SDK_ROOT ${CMAKE_SOURCE_DIR})
set(SRC_FILES

        ${SDK_ROOT}/Middlewares/Third_Party/tinyhttp/chunk.c
        ${SDK_ROOT}/Middlewares/Third_Party/tinyhttp/header.c
        ${SDK_ROOT}/Middlewares/Third_Party/tinyhttp/http.c
        ${SDK_ROOT}/Middlewares/Third_Party/cJSON/cJSON.c
        ${SDK_ROOT}/Middlewares/Third_Party/Unity/unity.c

        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/aes.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/aesni.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/arc4.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/aria.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/asn1parse.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/asn1write.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/base64.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/bignum.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/blowfish.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/camellia.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/ccm.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/certs.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/chacha20.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/chachapoly.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/cipher.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/cipher_wrap.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/cmac.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/ctr_drbg.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/debug.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/des.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/dhm.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/ecdh.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/ecdsa.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/ecjpake.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/ecp.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/ecp_curves.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/entropy.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/entropy_poll.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/error.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/gcm.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/havege.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/hmac_drbg.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/md.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/md2.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/md4.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/md5.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/md_wrap.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/memory_buffer_alloc.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/nist_kw.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/oid.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/padlock.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/pem.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/pk.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/pk_wrap.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/pkcs11.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/pkcs12.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/pkcs5.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/pkparse.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/pkwrite.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/platform.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/platform_util.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/poly1305.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/ripemd160.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/rsa.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/rsa_internal.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/sha1.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/sha256.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/sha512.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/ssl_cache.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/ssl_ciphersuites.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/ssl_cli.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/ssl_cookie.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/ssl_srv.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/ssl_ticket.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/ssl_tls.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/threading.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/timing.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/version.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/version_features.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/x509.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/x509_create.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/x509_crl.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/x509_crt.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/x509_csr.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/x509write_crt.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/x509write_csr.c
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/library/xtea.c

        ${SDK_ROOT}/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.c
        ${SDK_ROOT}/Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c
        ${SDK_ROOT}/Middlewares/Third_Party/FreeRTOS/Source/list.c
        ${SDK_ROOT}/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c
        ${SDK_ROOT}/Middlewares/Third_Party/FreeRTOS/Source/queue.c
        ${SDK_ROOT}/Middlewares/Third_Party/FreeRTOS/Source/tasks.c
        ${SDK_ROOT}/Middlewares/Third_Party/FreeRTOS/Source/timers.c

        ${SDK_ROOT}/Middlewares/ST/STM32_Connect_Library/services/net_mbedtls.c
        ${SDK_ROOT}/Middlewares/ST/STM32_Connect_Library/netif/wifi_if/es_wifi/net_es_wifi.c
        ${SDK_ROOT}/Middlewares/ST/STM32_Connect_Library/core/net_address.c
        ${SDK_ROOT}/Middlewares/ST/STM32_Connect_Library/core/net_class_extension.c
        ${SDK_ROOT}/Middlewares/ST/STM32_Connect_Library/core/net_core.c
        ${SDK_ROOT}/Middlewares/ST/STM32_Connect_Library/core/net_os.c
        ${SDK_ROOT}/Middlewares/ST/STM32_Connect_Library/core/net_socket.c

        ${SDK_ROOT}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal.c
        ${SDK_ROOT}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_can.c
        ${SDK_ROOT}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_cortex.c
        ${SDK_ROOT}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_crc.c
        ${SDK_ROOT}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_crc_ex.c
        ${SDK_ROOT}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_cryp.c
        ${SDK_ROOT}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_cryp_ex.c
        ${SDK_ROOT}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dac.c
        ${SDK_ROOT}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dac_ex.c
        ${SDK_ROOT}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dfsdm.c
        ${SDK_ROOT}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dfsdm_ex.c
        ${SDK_ROOT}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dma.c
        ${SDK_ROOT}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dma_ex.c
        ${SDK_ROOT}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_exti.c
        ${SDK_ROOT}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash.c
        ${SDK_ROOT}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash_ex.c
        ${SDK_ROOT}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_gpio.c
        ${SDK_ROOT}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_hash.c
        ${SDK_ROOT}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_hash_ex.c
        ${SDK_ROOT}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_i2c.c
        ${SDK_ROOT}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_i2c_ex.c
        ${SDK_ROOT}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_iwdg.c
        ${SDK_ROOT}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_lptim.c
        ${SDK_ROOT}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_nand.c
        ${SDK_ROOT}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_nor.c
        ${SDK_ROOT}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr.c
        ${SDK_ROOT}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr_ex.c
        ${SDK_ROOT}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_qspi.c
        ${SDK_ROOT}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rcc.c
        ${SDK_ROOT}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rcc_ex.c
        ${SDK_ROOT}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rng.c
        ${SDK_ROOT}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rng_ex.c
        ${SDK_ROOT}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rtc.c
        ${SDK_ROOT}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rtc_ex.c
        ${SDK_ROOT}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_spi.c
        ${SDK_ROOT}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_spi_ex.c
        ${SDK_ROOT}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_sram.c
        ${SDK_ROOT}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_tim.c
        ${SDK_ROOT}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_tim_ex.c
        ${SDK_ROOT}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_uart.c
        ${SDK_ROOT}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_uart_ex.c
        ${SDK_ROOT}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_usart.c
        ${SDK_ROOT}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_usart_ex.c
        ${SDK_ROOT}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_wwdg.c
        ${SDK_ROOT}/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_fmc.c
        ${SDK_ROOT}/Drivers/BSP/Components/vl53l0x/vl53l0x_api.c
        ${SDK_ROOT}/Drivers/BSP/Components/vl53l0x/vl53l0x_api_calibration.c
        ${SDK_ROOT}/Drivers/BSP/Components/vl53l0x/vl53l0x_api_core.c
        ${SDK_ROOT}/Drivers/BSP/Components/vl53l0x/vl53l0x_api_ranging.c
        ${SDK_ROOT}/Drivers/BSP/Components/vl53l0x/vl53l0x_api_strings.c
        ${SDK_ROOT}/Drivers/BSP/Components/vl53l0x/vl53l0x_platform_log.c
        ${SDK_ROOT}/Drivers/BSP/Components/es_wifi/es_wifi.c
        ${SDK_ROOT}/Drivers/BSP/Components/lsm6dsl/lsm6dsl.c
        ${SDK_ROOT}/Drivers/BSP/Components/lsm6dsl/lsm6dsl_reg.c
        ${SDK_ROOT}/Drivers/BSP/Components/lps22hb/lps22hb.c
        ${SDK_ROOT}/Drivers/BSP/Components/lps22hb/lps22hb_reg.c
        ${SDK_ROOT}/Drivers/BSP/Components/lis3mdl/lis3mdl.c
        ${SDK_ROOT}/Drivers/BSP/Components/lis3mdl/lis3mdl_reg.c
        ${SDK_ROOT}/Drivers/BSP/Components/hts221/hts221.c
        ${SDK_ROOT}/Drivers/BSP/Components/hts221/hts221_reg.c
        ${SDK_ROOT}/Drivers/BSP/B-L475E-IOT01/stm32l475e_iot01.c
        ${SDK_ROOT}/Drivers/BSP/B-L475E-IOT01/stm32l475e_iot01_bus.c
        ${SDK_ROOT}/Drivers/BSP/B-L475E-IOT01/stm32l475e_iot01_env_sensors.c
        ${SDK_ROOT}/Drivers/BSP/B-L475E-IOT01/stm32l475e_iot01_motion_sensors.c

        Utils/cloud.c
        Utils/sensors_data.c
        Utils/credentials.c
        flash_l4.c
        main.c
        mbedtls_entropy.c
        net_conf.c
        stm32l4xx_hal_msp.c
        stm32l4xx_it.c
        vl53l0x_platform.c
        vl53l0x_proximity.c
        Time/STM32CubeRTCInterface.c
        Time/timedate.c
        Time/timingSystem.c

        vertices_client.c
        http_stm.c

        hardfault.c
        syscalls.c
        sysmem.c
        system_stm32l4xx.c
        startup_stm32l4s5aiix.s
        )

set(INC_DIRS
        include
        include/Time
        include/Utils
        ${SDK_ROOT}/Drivers/BSP/B-L475E-IOT01
        ${SDK_ROOT}/Drivers/BSP/Components/es_wifi
        ${SDK_ROOT}/Drivers/BSP/Components/vl53l0x
        ${SDK_ROOT}/Drivers/CMSIS/Device/ST/STM32L4xx/Include
        ${SDK_ROOT}/Drivers/CMSIS/Include
        ${SDK_ROOT}/Drivers/STM32L4xx_HAL_Driver/Inc
        ${SDK_ROOT}/Middlewares/ST/STM32_Connect_Library/Includes
        ${SDK_ROOT}/Middlewares/Third_Party/cJSON
        ${SDK_ROOT}/Middlewares/Third_Party/FreeRTOS/Source
        ${SDK_ROOT}/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS
        ${SDK_ROOT}/Middlewares/Third_Party/FreeRTOS/Source/include
        ${SDK_ROOT}/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F
        ${SDK_ROOT}/Middlewares/Third_Party/libsodium/include
        ${SDK_ROOT}/Middlewares/Third_Party/mbedTLS/include
        ${SDK_ROOT}/Middlewares/Third_Party/tinyhttp
        ${SDK_ROOT}/Middlewares/Third_Party/Unity
        ${SDK_ROOT}/Middlewares/Third_Party/uthash

        )

set_source_files_properties(startup_stm32l4s5aiix.s PROPERTIES COMPILE_FLAGS "-x assembler-with-cpp -mthumb")

include_directories(${INC_DIRS})
set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/STM32L4S5VITX_FLASH.ld)

# Use custom .config.cmake to set application-specific variables
# such as Wi-Fi credentials
if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/.config.cmake)
    include(${CMAKE_CURRENT_SOURCE_DIR}/.config.cmake)
endif ()

# Create object file from keys so that we can link them into the final binary
set(KEYS_OBJ keys.o)
add_custom_target(load_secret
        COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/private_key.bin ${CMAKE_CURRENT_BINARY_DIR}/private_key.bin
        COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/public_b32.txt ${CMAKE_CURRENT_BINARY_DIR}/public_b32.txt
        COMMAND ${TOOLCHAIN_PREFIX}ld -r -b binary -o ${KEYS_OBJ} private_key.bin public_b32.txt
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/private_key.bin ${CMAKE_CURRENT_SOURCE_DIR}/public_b32.txt
        BYPRODUCTS ${KEYS_OBJ}
        COMMENT "Encapsulating keys")

# get full path to root CMake so that it can be removed from the log
string(LENGTH "${CMAKE_SOURCE_DIR}/" SOURCE_PATH_SIZE)
add_definitions("-DSOURCE_PATH_SIZE=${SOURCE_PATH_SIZE}")

add_compile_options(-DUSE_HAL_DRIVER -DUSE_WIFI -D__BYTE_ORDER__=__ORDER_LITTLE_ENDIAN__ -DMBEDTLS_CONFIG_FILE=<mbedtls_config.h> -DSTM32L4S5xx -DCRYPTO_USE_SODIUM -D__FPU_PRESENT=1)
add_compile_options(-mfloat-abi=hard -mfpu=fpv4-sp-d16)
add_compile_options(-mcpu=cortex-m4 -mthumb)
add_compile_options(-ffunction-sections)
add_compile_options(-Os -Wall -Wno-strict-aliasing -Wno-format -fstack-usage)

add_link_options(-mcpu=cortex-m4 -mthumb -mfloat-abi=hard)
add_link_options(-Wl,-gc-sections,--print-memory-usage,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map)
add_link_options(-static -Xlinker)
add_link_options(-T ${LINKER_SCRIPT})
link_directories(${CMAKE_CURRENT_SOURCE_DIR} ${SDK_ROOT}/Middlewares/Third_Party/libsodium/library/STM32CubeIDE/)

link_libraries(
        c
        m
        sodium
)

add_executable(${PROJECT_NAME} ${SRC_FILES} ${LINKER_SCRIPT} ${KEYS_OBJ})
add_dependencies(${PROJECT_NAME} vertices load_secret)

target_compile_options(vertices PRIVATE -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSOURCE_PATH_SIZE=${SOURCE_PATH_SIZE})
target_link_options(vertices PRIVATE -mcpu=cortex-m4 -mthumb -mfloat-abi=hard)
target_link_libraries(${PROJECT_NAME} PRIVATE vertices)

set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX .elf)
