# cub3d

The "cub3d" project at 42 is an exciting endeavor that introduces us to the world of raycasting and 3D graphics programming using the C language. It challenges us to create a simple first-person 3D maze game reminiscent of the classic game Wolfenstein 3D. Below is a detailed description of the "cub3d" project:

Project Name: cub3d

Objective:
The main objective of the "cub3d" project is to familiarize us with the fundamentals of raycasting, a technique used to render 3D graphics from a 2D map. Through this project, we gain hands-on experience in graphics programming, including techniques for rendering walls, floors, ceilings, and objects in a simulated 3D environment.

Key Components:

Map Parsing:
We are required to read and parse a map file that defines the layout of the game environment. The map file typically contains information about walls, player starting position, texture identifiers, and other elements crucial for rendering the game world.

Raycasting Engine:
The core of the project involves implementing a raycasting engine, which simulates the behavior of light rays to render a 3D perspective view of the game world. We must understand the mathematics behind raycasting, including concepts such as ray-plane intersection and distance calculation.

Graphics Rendering:
Using a graphic library (such as MiniLibX), We render the game environment based on the information parsed from the map file and the results of the raycasting calculations. This includes drawing walls, floors, ceilings, and other objects using textures provided in the project resources.

Player Movement and Controls:
We implement player movement controls, allowing the player to navigate through the 3D environment using keyboard input. This involves handling user input for moving forward, backward, turning left and right, and possibly other actions such as strafing.

Bonus Features:
The "cub3d" project could be included the use of Textures and Sprites to enhance the visual quality of the game. For instance, we could implement texture mapping techniques to apply textures to walls and other surfaces in the game world. Additionally, rendering of sprites (2D images) to represent objects such as items or enemies.
