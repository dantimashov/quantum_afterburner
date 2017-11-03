# quantum_afterburner

  Project for DevDays ( SPbAU hackathon). 
  
## Description 

It's a 2D platformer. The game uses a very simplistic idea of Heisenberg's uncertainty principle. 
A spaceship is created that flies through obstacles.
Obtacles are generated randomly and are geometric figures. The spaceship has two parameters: a coordinate and a velosity.
For these parameters, the concept of uncertainty is introduced. 
This means, that at regular intervals they will take random values within certain limits.
These limits are uncertainty in velosity and coordinate.
Limits can vary due to special bonuses, which are also generated randomly.
Limits are connected through a simple formula, their product must always be equal to some constant. 
Limits along the coordinate are displayed as a halo around the ship. 
In fact, when the velocity and coordinate changes, the ship can be anywhere in the halo. 

The ship has 5 lives. In addition to the number of remaining lives, the screen displays the time elapsed since the beginning of the game. 
If a player crashes into an obstacle, then it disappears, and the number of lives of the player is decreased. 
When the number of lives becomes zero, the game ends.

## Link to project page
[The info about project in Russian on the SE wiki ](http://mit.spbau.ru/sewiki/index.php/%D0%9A%D0%B2%D0%B0%D0%BD%D1%82%D0%BE%D0%B2%D1%8B%D0%B9_%D1%84%D0%BE%D1%80%D1%81%D0%B0%D0%B6)

## Build the project
In this project used the sfml library. For building you can use a make.
