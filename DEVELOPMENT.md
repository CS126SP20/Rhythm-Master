# Development


4/21/20:
--
- Importned ImGui, but found out that it actually does not do anything significant. Start reading 
through all the cinder documentations for Gui.

4/22/20:
--
- Used logic for making textbox in snake, made 3 drawings for my three main UIs, and loaded the 
songs i wanted.

4/26/20:
--
- Finished drawing the frames for tiles to drop.

4/27/20:
--
- Adding the Choreograph Cincer Block, reading through the documentation and trying to understand
the basic logic.

4/28/20:
--
- Still reading through the documentation, found it confusing.

4/29/20:
--
- Finished implementing the basic code for 1 tile, the animation doesn't not because the update()
doesn't not take in any argument, however, on the Choreograph documentation, the update() seems
able to take 1 argument (ch:Time dt). Stuck and struggling to get the animation going.

4/30/20:
--
- Made the animation work, added 3 more tiles, made them drop at different speed. However, still
need to figure out how to repeat the animation. 

- Because Choreograph is way more difficult than I thought it would be, I HAVE to reduce the number 
of songs to 1, with (hopefully) 2 difficulties. Or I will be extremely difficult to take care of 
all three songs.

5/1/20:
--
- Made the  animations repeat, and drop randomly, also set a timer that ends the music  and stops
the animation after the song duration (33 sec).

5/2/20:
--
- Fixed some gamestate logic error with animation and music, made end game screen, started working
on tracking tile positions. (Planning on reducing the song to only 1 difficulty, since the setup
is somewhat complicated to organize)

5/3/20:
--
- Made the left arrow key reset both the animation and the song 

5/4/20:
--
- Adding the clicking sound when pressing keys, and created tile position detecting logic for losing 
game condition.
- Change the game to 1 song, the original plan is too delusional.

5/5/20:
--
- In the process of  organizing code.

5/6/20:
--
- Added comments, working on README file.
- Finished making the README file.
- There will not be any tests for this project, since it's heavy UI-based.
- The GameState and KeyState logic all depend upon the users (By clicking the keys).
- The two states are also relate to the draw() function, which is for the purpose of UI.