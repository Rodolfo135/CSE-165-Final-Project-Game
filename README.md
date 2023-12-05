# CSE-165-Final-Project-Game
Final project for CSE 165: Object Oriented Programming at UC Merced.

Example Gameplay:

![ezgif com-crop (1)](https://github.com/Rodolfo135/CSE-165-Final-Project-Game/assets/81655461/36235076-795b-49cb-bf1f-e73b77d38c00)

We used the Raylib library for C++ in this project: 
- https://www.raylib.com/

Instructions for how to get the code working (Windows 10):
- Make sure you have a compiler like MINGW installed on your system. https://www.mingw-w64.org/
- Make sure you have CMake installed on your system. https://cmake.org/
- Click on the link above. Then, click download now, and follow the simple installation provided by the raylib developers.
- From there you can clone the repository, and open it in a text editor such as Visual Studio Code (This will require the C/C++ extensions, and CMake extensions).
- Once you do this if you must then build the CMake file. This will allow you to actually include raylib in your header and source files.
- If you were able to successfully build, then you can now alter and compile the code however you like.

NOTE:
- Once you build and compile, the executable that launches the game can be found in the build folder that CMake will generate.

NOTE:
- For some reason we were having issues when using the relative paths for the sprite sheets. Therefore, if one decides to clone this repository to alter and compile the code then they should (in main.cpp) change the texture paths to the paths unique to their system.
