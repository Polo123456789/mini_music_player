#include "music_player.hpp"

#if _WIN32 == 1
    #include <Windows.h>
    #pragma comment(lib, "winmm.lib")
#endif

void play_sounds(const std::vector<std::string> &play_list) {
#if _WIN32 == 1
    for (const std::string &song : play_list) {
        std::cout << "Reproduciendo: " << song << '\n';
        std::string mci_command =
            "open \"" + song + "\" type mpegvideo alias psg_song";

        MCIERROR error =
            mciSendString(mci_command.c_str(), nullptr, 0, nullptr);
        if (!error) {
            mciSendString("play psg_song wait", nullptr, 0, nullptr);
            mciSendString("close psg_song", nullptr, 0, nullptr);
        } else {
            throw std::exception("Error al reproducir cancion\n");
        }
    }
#else

    static_assert(false,
        "No se ha definido una forma de hacer sonar la musica en tu sistema. "
        "Puedes implementar una?");

#endif
}
