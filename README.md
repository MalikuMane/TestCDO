This is an awful project! So bad in fact, the class dependencies confuse UE4's linker causing it to load them in the wrong order.. or not! It depends on the order the plugins are reported by the filesystem weather it will fail or not. Use the Fix and Break script files to demonstrate this using symlinks to force the loading order. Tested on UE 4.25 and 4.26 Linux and Windows. Good luck!

Steps to reproduce this

1: Create a blank project

2: Close the editor

3: Copy the Plugin and PluginStore, .sh and .bat scripts to the project.

4: On Windows:
	Navigate to the project folder in an admin console and run fix.bat.
   On Linux:
	Navigate to the project folder as user and run fix.sh.

5: Reopen this project in the editor,
	Observe: the FirstPlugin opens before SecondPlugin.

6: Create these blueprints
	BP_ActorComponent (ActorComponent)
	BP_MyActor (SecondPlugin.BP_MyActor)
	BP_MyGameInstance (SecondPlugin.MyGameInstance)
	BP_MySaveGame (FirstPlugin.MySaveGame)
	S_Struct (Structure)

7: Set the following properties:
	S_Struct:
		MemberVar_0 Type: BP_MySaveGame
	BP_MySaveGame:
		Node: GetAIController
		Node: Get Component by Class
			Target: GetAIController
			Class BP_ActorComponent
	BP_MyActor:
		Component: AC (BP_ActorComponent)
	BP_ActorComponent
		Var: GI (GameInstance)
		Node: Break S_Struct
		
7: Set: Project Settings-> Plugins-Second -> Default Classes -> AMy Actor:BP_MyActor

8: Close the editor

9:  On Windows:
	Navigate to the project folder in an admin console and run break.bat.
    On Linux:
	Navigate to the project folder as user and run break.sh.

10: reopen the editor:
	Observe SecondPlugin opens before FirstPlugin.
	Observe the following log output:

FirstPlugin': Can't find file.
LogLinker: Warning: CreateExport: Failed to load Parent for BlueprintGeneratedClass /Game/Blueprints/BP_MySaveGame.BP_MySaveGame_C
LogLinker: [AssetLog] Content/Blueprints/BP_MySaveGame.uasset: Failed to load '/Script/FirstPlugin': Can't find file.
LogLinker: Warning: Unable to load Default__BP_MySaveGame_C with outer Package /Game/Blueprints/BP_MySaveGame because its class does not exist                                                                
LogUObjectGlobals: Warning: Failed to find object 'Object /Game/Blueprints/BP_MySaveGame.BP_MySaveGame_C'
LoadErrors: Warning: CreateExport: Failed to load Outer for resource 'ExecuteUbergraph_BP_MySaveGame': BlueprintGeneratedClass /Game/Blueprints/BP_MySaveGame.BP_MySaveGame_C

11: Do BP_MySaveGame -> Asset Actions -> reload.
	Observe: Crash with LogCore: Error: appError called: Assertion failed: OldClass && NewClass

12: Close the editor/crash reporter.

13: On Windows:
	Navigate to the project folder in an admin console and run fix.bat.
    On Linux:
	Navigate to the project folder as user and run fix.sh.

14: Reopen the project in the editor
	Observe: The errors no longer appear.
