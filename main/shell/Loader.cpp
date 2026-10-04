/**
 * @file Loader.cpp
 * @brief Retour au Launcher AKA.
 *
 * Organisation de la flash AKA : le Launcher est installe dans la partition
 * app1 (OTA_1), les jeux sont ecrits par le Launcher dans app0 (OTA_0).
 * Un jeu qui tourne depuis app0 revient donc au Launcher en selectionnant app1
 * comme partition de demarrage, puis en redemarrant. Les partitions sont
 * retrouvees par type/sous-type, aucun offset n'est ecrit en dur.
 *
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
#include "esp_ota_ops.h"       // esp_ota_set_boot_partition, esp_ota_get_running_partition
#include "esp_partition.h"     // esp_partition_find_first
#include "esp_log.h"

namespace
{
    const char* TAG = "loader";

    // Partition du Launcher : app1 (OTA_1) en priorite, sinon l'ancienne
    // organisation (partition factory).
    const esp_partition_t* findLauncher()
    {
        const esp_partition_t* p = esp_partition_find_first(
            ESP_PARTITION_TYPE_APP, ESP_PARTITION_SUBTYPE_APP_OTA_1, nullptr);
        if (p == nullptr)
            p = esp_partition_find_first(
                ESP_PARTITION_TYPE_APP, ESP_PARTITION_SUBTYPE_APP_FACTORY, nullptr);
        return p;
    }
}

namespace loader
{
    [[noreturn]] void returnToLoader()
    {
        const esp_partition_t* launcher = findLauncher();
        const esp_partition_t* running  = esp_ota_get_running_partition();

        if (launcher == nullptr)
        {
            ESP_LOGW(TAG, "partition du Launcher introuvable, simple restart");
        }
        else if (running != nullptr && launcher->address == running->address)
        {
            // On tourne deja depuis la partition du Launcher : rien a selectionner.
            ESP_LOGW(TAG, "deja dans la partition du Launcher, simple restart");
        }
        else
        {
            esp_err_t e = esp_ota_set_boot_partition(launcher);
            if (e != ESP_OK)
                ESP_LOGE(TAG, "set_boot_partition @0x%x a echoue (0x%x)",
                         (unsigned)launcher->address, (unsigned)e);
            else
                ESP_LOGI(TAG, "retour au Launcher @0x%x", (unsigned)launcher->address);
        }

        esp_restart();
    }
}

#endif
