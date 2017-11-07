# quantum_afterburner

  Project for DevDays ( SPbAU hackathon). 
  
## Description 

It's a 2D game. The game uses a very simplistic idea of Heisenberg's uncertainty principle. 
A spaceship is created that flies through obstacles.
Obtacles are generated randomly and are geometric figures. The spaceship has two parameters: a coordinate and a velosity.
For these parameters, the concept of uncertainty is introduced. 
This means, that at regular intervals they will take random values within certain limits.
These limits are uncertainty in velosity and coordinate.
Limits can vary due to special bonuses, which are also generated randomly.
Limits are connected through a simple formula, their product must always be equal to some constant. 
Limits along the coordinate are displayed as a halo around the ship. 
In fact, when the velocity and coordinate changes, the ship can be anywhere in the halo. 

The ship has 5 lives. Also, the ship has fuel that helps to increase or decrease the speed. To increase the number of lives and fuel, there are also bonuses. In addition to the number of remaining lives, the screen displays the velocity, the fuel and the distance the ship was flying. 
A special timebar on the left shows how much time is left before the next recalculation of characteristics.
If a player crashes into an obstacle, then it disappears, and the number of lives of the player is decreased. 
When the number of lives becomes zero, the game ends.

Control

right arrow on keyboard - rotation of the vector of the ship's direction of travel clockwise

left arrow on keyboard - rotation of the vector of the ship's direction of travel counter-clockwise

up arrow on keyboard - fuel speed increase

down arrow on keyboard - fuel speed decrease

## Link to project page
[The info about project in Russian on the SE wiki ](http://mit.spbau.ru/sewiki/index.php/%D0%9A%D0%B2%D0%B0%D0%BD%D1%82%D0%BE%D0%B2%D1%8B%D0%B9_%D1%84%D0%BE%D1%80%D1%81%D0%B0%D0%B6)

## Build the project
In this project used the sfml library. First, you must download this library.

for Linux: 
sudo apt-get install libsfml-dev

for Windows: [Link for downloading the library](https://www.sfml-dev.org/download.php)

In case you installed SFML to a non-standard path, you'll need to tell the compiler where to find the SFML.
Add a path after the -I flag in the Makefile. For example: $(CXX) $(CXX_FLAGS) ./src/main.o -o qrace -I /usr/lib -lsfml-graphics -lsfml-window -lsfml-system
After assembly, you can run the executable from the same directory, for example ./qrace

For building you can use a make. 
