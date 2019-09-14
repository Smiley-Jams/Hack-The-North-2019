# Eternity

The main pillars that make up *Eternity* are progression, collaboration, and decentralization.

- To achieve progression, players can level up certain skills like gathering or crafting
- To achieve collaboration, players will have to trade resources with other players to craft better items.
- To achieve decentralization, the game's data will all be stored by blockchain

The game world is grid based, with each tile of the grid containing information about the quantity of different types of resources it contains. The *tick* of the game will run every certain time interval, and all each tick does is give the players resources based on the tile that they are occupying.

## Core Game Loop

- The player will gather resources at every tick
- By gathering resources, the player can level up their *gathering professions*
- With the gathered resources, players can either sell it or craft items

The items will be the goal of the game, these items could be cosmetic so it could be shown off to other players.

## Auction House

The *auction house* facilitates the buying and selling of resources and items. This is the part of the game that encourages collaboration between players; The specialization of different professions will require players to work with each other to craft better items.

## TECH / MECHANICS

### The tick mechanic

Every set interval, the players will receive resources based on the tile that they are occupying, this update is called a tick. Since everything is decentralized, there is no server to send resources out to the players. As such, the tick will be calculated by the clients themselves based on how much time has passed, then add that data to the blockchain.

### Movement

Since player movement doesn't affect gameplay at all, it will all be handled on the client side. The only data that matters is the position of the player when a 'tick' occurs, which can simply be stored at the end of a players game session and then uploaded to the blockchain.

### Resources

For now, there will be three basic resources:

- Wood
- Ore
- Leather

Each resource can have different tiers, and higher tier resources have to be obtained either by buying on the auction house or by leveling up the respective gathering profession.

Gathering levels can be handled by a simple XP bar. The system can work similar to DnD multiclassing, where the XP required for the next level is based on total level instead of specific profession levels. This prevents players from just maxing out everything and completing the whole game solo.
