# Dungeons and Dragons
A text-based game written in C++ where the player has to get from the upper left corner of a randomly generated maze to the lower right one without getting killed by the dragons.
# About the game
## The start
Initially, the game will ask you to choose a class. Currently, only Warrior and Mage are available. The only difference is the stats they receive:
* The mage starts with:
  * 10 Strength
  * 40 Intellect
  * 50 Health 
* The warrior starts with:
  * 40 strength
  * 10 intellect
  * 50 health
## The stats
The stats modify the damage your attacks deal.
* Strength makes your basic attacks stronger
* Intellect makes your spells stronger
## The map
On every step the game prints out the maze. The symbols used are:
* \# - a wall
* . - an empty cell
* P - the current position of the player
* D - a dragon
* T - a treasure
## Moving your character
The player can use the following commands:
* 'u' - move up
* 'd' - move down
* 'l' - move to the left
* 'r' - move to the right
## Items
You have three item slots:
* Armor - reduces the damage you receive
* Weapon - increases the damage you deal with basic attacks
* Spell - increases the damage you deal with spells\
## Treasures
The treasures are randomly placed on the map and contain items that can be better than the ones you have equipped, but they can also be absolutely useless. If you reach a place with a treasure, you can choose to discard it or equip it.
## Dragons
The dragons are also randomly placed on the map. Once you reach a cell with a dragon you **have to** defeat it. If you manage to defeat a dragon, 50% of your max health is restored.

# Compiling
After compiling, ensure that the executable and the level files (level1.txt and level2.txt) are in the same directory!
