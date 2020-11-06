#include <iostream>
#include <cstring>
#include <algorithm>
#include <random>
#include <fstream>

#include "music_player.hpp"
#include "directory_reader.hpp"

static bool generate_playlist = false;
const char* const version = "1.0";
const char* const help_message = R"(
Copyright 2020 Pablo Sanchez

Uso: player [-v, -h] directorio

Flags:
    -v      Imprime la version al ejecutar el programa
    -h      Imprimie este mensaje al ejecutar el programa
    -c      Crea un archivo playlist playlist.txt con las canciones mezcladas

Este programa toma todos los archivos mp3 de el "directorio", y los reproduce en
un  orden  aleatorio. Si no  se le  da  un directorio  hace  la  busqueda  en el
directorio actual.
)";

std::string parce_cmd_args(int argc, char **argv);

int main(int argc, char *argv[]) {
    std::string path;
    if (argc == 1) {
        path = std::filesystem::current_path().string();
        std::cout << "Path: " << path << '\n';
    } else {
        path = parce_cmd_args(argc, argv);
    }

    try {

        std::vector<std::string> songs = get_song_names(path);
        std::cout << "Mezclando las canciones ... \n";
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(songs.begin(), songs.end(), g);
        if (generate_playlist) {
            std::ofstream salida("playlist.txt");
            for (const auto& song : songs) {
                salida << song << '\n';
            }

        } else {
            std::cout << "Iniciando reproduccion\n";
            play_sounds(songs);
        }

    } catch (const std::exception &e) {
        std::cout << e.what() << '\n';
    }
    return 0;
}

//NOLINTNEXTLINE
std::string parce_cmd_args(int argc, char **argv) {
    std::string path{};
    for (int i=1; i<argc; i++) {
        if (std::strcmp("-h", argv[i]) == 0) { //NOLINT
            std::cout << help_message << '\n';
            
        } else if (std::strcmp("-v", argv[i]) == 0) { //NOLINT
            std::cout << version << '\n';

        } else if (std::strcmp("-c", argv[i])==0){ //NOLINT
            generate_playlist = true;

        } else {
            path = std::string(argv[i]); //NOLINT
        }
    }
    if (path.empty()) {
        path = std::filesystem::current_path().string();
    }
    std::cout << "Path: "<< path << '\n';
    return path;
}
