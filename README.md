# Cnake

Cnake is a "classic" snake game written in C. Only exception is, you can't lose this game.
Yep! You can not eat yourself, you can not toss a wall. The only limit is boredom!

## Compiling Source Code

You'll need SDL2, SDL_ttf and SDL_image libraries in order to compile this project.
After that, it's just a simple gcc command. Here is mine:

```bash
gcc src\*.c -o snakegame -ID:\sources\include -Iheaders -LD:\sources\lib -lmingw32 -lSDL2_ttf -lSDL2_image -lSDL2main -lSDL2 -Wall -Werror
```

I've used windows for building this project, so yours can be a little bit different than mine.
After compilation, just run the executable **snakegame**.

## Gameplay

1. Use arrow keys (↑, ↓, ←, →) for moving around
2. Use P key for pausing the game

That's all!
