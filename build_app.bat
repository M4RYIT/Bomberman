clang.exe -o .\bin\bomberman.exe -I .\core\inc -I .\SDL2-2.0.20\include\ -L .\SDL2-2.0.20\lib\x64\ .\app\src\*.c .\core\src\*.c -Xlinker /subsystem:console -lSDL2main -lSDL2 -lshell32