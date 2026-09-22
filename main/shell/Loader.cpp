/**
 * @file Loader.cpp
 * @brief Retour au loader.
 *
 * Sur AKA : bascule OTA sur la partition factory + redemarrage.
 * Sur PC (BUB_PC) : simple sortie du programme.
 */

#include "Loader.h"

#ifdef BUB_PC

#include <cstdlib>

namespace loader
{
    [[noreturn]] void returnToLoader() { std::exit(0); }
}

#else

#include "esp_system.h"        // esp_restart
#include "esp_ota_ops.h"       // esp_ota_set_boot_partition
#include "esp_partition.h"     // esp_partition_find_first
#include "esp_log.h"

namespace
{
    const char* TAG = "loader";
}

namespace loader
{
    [[noreturn]] void returnToLoader()
    {
        // Le loader AKA occupe la partition applicative "factory".
        const esp_partition_t* factory = esp_partition_find_first(
            ESP_PARTITION_TYPE_APP, ESP_PARTITION_SUBTYPE_APP_FACTORY, nullptr);

        if (factory != nullptr)
        {
            if (esp_ota_set_boot_partition(factory) != ESP_OK)
                ESP_LOGE(TAG, "set_boot_partition factory a echoue");
        }
        else
        {
            ESP_LOGW(TAG, "partition factory introuvable, simple restart");
        }

        esp_restart();
    }
}

#endif
