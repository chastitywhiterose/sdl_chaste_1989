SET DEVKIT=C:\Users\chand\scoop\apps\gcc\current

gcc -Wall -ansi -pedantic main.c -o main -I%DEVKIT%\include\SDL2 -L%DEVKIT%\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

strip main.exe

main
