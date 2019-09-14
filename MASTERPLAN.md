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

## TECH

### The tick mechanic

Every set interval, the players will receive resources based on the tile that they are occupying, this update is called a tick. Since everything is decentralized, there is no server to send resources out to the players. As such, the tick will be calculated by the clients themselves based on how much time has passed, then add that data to the blockchain.
