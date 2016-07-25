--------------------------------------------------------------------------------
--- The Dungeon Throne modding API reference                                 ---
--------------------------------------------------------------------------------

This directory contains reference files for the modding API of the game
The Dungeon Throne in which we can find list of all functions in the API and
their descriptions.

The name of each file is in the form of <table>.txt and functions listed in it
can be accessed through the table <table>. E.g. if the file some-table.txt
contains function some-function we can call this function as
some-table.some-function().

Whenever we ask for an entity ID and such entity does not exist,
the function returns game.const.no_ent.

TODO: Add types to arguments.
Placeholder type info: distances, radii, position vectors, direction vectors,
etc are numbers, i.e. numbers with decimal parts. Others, like hp, mana,
damage, counts, IDs are unsigned integers, i.e. numbers without decimal parts.
Names of tables, blueprints, meshes, materials etc are strings.
