Music Player
============

Es una micro app. Dado un directorio, reproduce en orden aleatorio todos los
mp3 que se encuentren en el mismo.

De momento solo soporta Windows. Ya algun dia cuando tenga ganas le metere una
interfaz asi chilera a lo cmus, pero de momento solo queria hacer esto.

Compilacion
===========

Puede compilarlo con el sigiente comando:
~~~

clang -Wall -Werror -std=c++17 src/main.cpp src/music_player.cpp src/directory_reader.cpp -o bin/player.exe
~~~

Limitaciones
============

Si no se puede colocar el nombre usando caracteres unicode se va a lanzar una
excepcion y no se van a añadir las demas canciones.
