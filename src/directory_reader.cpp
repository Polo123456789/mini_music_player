#include "directory_reader.hpp"

std::vector<std::string> get_song_names(const std::string &path) {
    std::vector<std::string> songs;
    std::regex mp3_filter(".*\\.mp3");
    try {
        for (const auto &file : std::filesystem::directory_iterator(path)) {
            std::string file_name;
            file_name = file.path().string();
            if (std::regex_match(file_name, mp3_filter)) {
                std::cout << "Incluyendo [" << file_name << "] en la lista\n";
                songs.push_back(file_name);
            }
        }
    } catch (const std::exception &e) {
        std::cout << e.what() << '\n';
    }
    return songs;
}
