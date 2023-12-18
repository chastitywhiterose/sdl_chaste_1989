Chaste Tris 1989

This project is not even barely started but this is some important information.

Documentation I have referenced in the making of this program.

https://wiki.libsdl.org/SDL2/CategoryAPI
https://wiki.libsdl.org/SDL_image
https://wiki.libsdl.org/SDL_mixer
https://wiki.libsdl.org/SDL_ttf

Windows notes

For this project, I have not been able to get a static build made. This means that the executable depends on files which are located in this folder on my machine.

C:\Users\chand\scoop\apps\gcc\current\bin

So I copied the required DLL files into the executable directory.

SDL2.dll
SDL2_image.dll
SDL2_mixer.dll
SDL2_ttf.dll

This makes the archive bigger but it also should make the game work on any modern 64 bit Windows.

Linux notes

When running the game under Linux you only need to make sure all of the required SDL2 libraries are installed. This is easy to do when running Debian Linux through the apt or synaptic package managers. Because of this I don't include the libraries with my Linux archive for this game.



