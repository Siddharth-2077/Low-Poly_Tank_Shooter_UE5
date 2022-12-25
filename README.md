
# Low Poly Tank-Shooter UE5 C++ 

- A low-poly game jam style shooter game
- Player controls a Tank that can shoot projectiles
- Goal to destroy enemy Tower-Turrets which can destroy the Player
- Player can destroy HealthBoxes to regain some health
- Created in ***Unreal Engine-5*** and developed in ***C++***

## Source Code
C++ source files for this project can be located under:  *Low-Poly_Tank_Shooter_UE5/Source/ToonTanks/*
<br />

### Core Classes

- **ABasePawn** *(Pawn class)* - Parent class that contains common functionality for the player-tank and enemy-towers.
Contains common functionality such as shooting projectiles, and the necessary class pointers stored to make it work. <br /><br />

  - **ATank** *(derived from ABasePawn)* - Implements the player-tank specific functionality such as movement for example. <br /><br />
  
  - **ATower** *(derived from ABasePawn)* - Implements the enemy-tower specific functionality such as facing the player and firing when the player is in range. <br /><br />
  
  - ![Pawn Classes](https://user-images.githubusercontent.com/67199656/209471592-a1bf1cb3-6305-42fb-bad5-94b4b3f4e481.png) <br />
  *The Tank and Tower Blueprints created from their respective C++ classes* <br /><br />

  
- **UHealthComponent** *(ActorComponent class)* - Contains health related functionality for any object in the world, such as max-health, current-health
and events to update the Health-UI as well as events to handle an object's destruction when it runs out of health. <br /><br />

- **AProjectile** *(Actor class)* - Is the projectile that will be spawned when the player/enemy fire projectiles. Works using Unreal's built-in 
ProjectileMovement Component, and is responsible for camera-shake effects when it hits other objects, as well as spawning the appropriate particle systems when hit. <br /><br />

  - ![Projectile](https://user-images.githubusercontent.com/67199656/209471825-36a2b60f-e7ad-4811-a566-38a51a19c75b.png) <br />
  *The Projectile Blueprint class* <br /><br />


- **AHealthBox** *(Actor class)* - Is the class that when destroyed by the player, awards a small amount of health to the player.
This can further be changed to award other perks to the player such as more-health, temporarily increased player movement speed, or things such as making
the player immune to any attack for a short period of time. <br /><br />

  - ![HealthBox](https://user-images.githubusercontent.com/67199656/209471910-48e7323a-b1f6-4350-be05-331a2761d5d1.png) <br />
  *The HealthBox Blueprint class* <br /><br />


### Class Diagram
![ToonTanks_Class_Diagram](https://user-images.githubusercontent.com/67199656/209470418-508c74de-085b-4cff-8cb0-0f3e18a0e37d.png)
The above UML diagram represents the class-diagram of the core classes in the project, as explained in the previous section

## Screenshots
![HighresScreenshot00000](https://user-images.githubusercontent.com/67199656/209472037-9f2c9b29-bde0-4b40-b3dc-fbb638843d10.png)

## Author
**Siddharth M** <br />
MIT Manipal, India <br />



