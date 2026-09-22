idf_component_register(
    SRCS
        app_main.cpp

        # Coquille : titre, menu, multilingue, config SD, retour loader
        shell/Shell.cpp
        shell/Menu.cpp
        shell/I18n.cpp
        shell/Config.cpp
        shell/Loader.cpp

        core/Game.cpp
        core/Input.cpp
        core/Renderer.cpp

        game/Level.cpp
        game/LevelManager.cpp
        game/Player.cpp
        game/Levels.cpp
        game/Sprites.cpp

    INCLUDE_DIRS
        . core game shell

    # Quand des assets seront convertis (title.bin, etc.), les lister ici :
    # EMBED_FILES
    #     assets/title.bin

    # RAPPEL : les composants vont dans REQUIRES, PAS dans INCLUDE_DIRS.
    REQUIRES
        gamebuino nvs_flash app_update esp_partition esp_system fatfs
)
