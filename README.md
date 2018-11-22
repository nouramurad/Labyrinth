# Labyrinth
Game Designed by Jason Kemp, and Noura Murad
Section I:
“The Labyrinth is a survival puzzle/maze game”. The game is drawn with a two dimensional
bird’s eye view, and have rooms that are drawn with different colours and corridors that are
drawn with different shades of grey. Each room (except the first room) has an enemy in it.
The player must collect 5 keys and return to the first room to win the game. To collect the keys
the player must fight and defeat enemies (zombies) who have the key. Zombies can be holding
either a key(if they are in an unlocked room) or gear item which can be either a fuel tank or a
health pack (all with probability of 1/2 of being with the enemy).
Section II:
Our original plan/vision has not changed. However we had some struggles that made some of
the features hard to achieve due to lack of time or just because it didn't work because of how
the code was developed. Our plan/vision was to make a puzzle game in a generated dungeon
that would require the player to collect items to win and fight enemies to collect these items. And
our game The Labyrinth does exactly that.
In the game we wanted to add a damage points for the Motorcycle, but we did not do it because
having narrow corridors and sharp turns made it almost impossible to keep the motorcycle from
being damaged. Therefore we decided to just make the motorcycle decelerate when it collides
with the wall and slide along it until the player turns to a proper direction.
In the game we wanted to make some or maybe all of the rooms lock as soon as the player
enters them and not be able to leave until they defeat the enemy inside that room. We started
working on this feature but we were unable to finish it before the feature complete was due and
therefore we haven’t had enough time to do this feature. So instead we replaced it with having
the enemy always carrying the gear with them and having to fight the enemy to get health packs
and fuel.
In the game we wanted to add weapons that causes more damage, and explosions that would
create a cavern that can connect rooms and corridors together, allowing the player to bypass
undesirable areas. But we didn’t do them because we ran out of time before the feature
complete.
What we would have done differently is having more enemies in some rooms and maybe larger
enemies that require more hits to be defeated, just to make the game last longer and have
different difficulties. Also, add a big villain in the end that needs to be defeated in order to win
the game.
Section III:
The bugfixes that were made on the game are completely sprite related. The first big that was
fixed was that when the player is on the motorcycle and uses the brakes then the player’s
attacking sprite is drawn. The second bug is the player’s death sprite is not drawn if the player
died while attacking. And finally the health bar of the enemy is sometimes drawn on top of the
enemy’s head rather than above. All of the previous bugs happened because of the state
changes for both the player and the enemy.
Section IV:
The enemy has three different states (Patrol, Attack, Defeated). If the player is not their room
then the enemy moves randomly around in the room, this is done in a function that checks if the
player is in the room or not. If the player is in the room then the enemy’s state changes to attack
and starts to chase the player and attack if the are close enough to the player. And Finally
Defeated state is when the enemy’s health is reduced to 0 from the attacks done by the player.
To change the direction of the enemy as they move around we used the heading of the player
and rotated the sprites according to the heading. When patrolling the heading depends on which
wall the enemy bumps into and what was the previous heading, and if the enemy is attacking
then the heading depends on the player’s position.
