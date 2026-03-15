#pragma once


#define module godot, API

moduleValues(InitLvl,
       CORE,,
       SERVERS,,
       SCENE,,
       EDITOR,,
       MAX,,
)


export(
SUBMODULE(Core, Object, Script, String, Type),
VALUES(InitLvl),
	load
)

#undef module
