// Run And Gun Game. All Rights Received.

using UnrealBuildTool;

public class RunAndGun_git : ModuleRules
{
    public RunAndGun_git(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core",
            "CoreUObject",
            "Engine", 
            "InputCore",
            "UMG",
            "Niagara",
            "PhysicsCore",
            "GameplayTasks",
            "NavigationSystem" 
        });

        PrivateDependencyModuleNames.AddRange(new string[] { });

        PublicIncludePaths.AddRange(new string[] {
            "RunAndGun_git/Public/Player",
            "RunAndGun_git/Public/Components",
            "RunAndGun_git/Public/Dev",
            "RunAndGun_git/Public/UI",
            "RunAndGun_git/Public/Animation",
            "RunAndGun_git/Public/Pickups",
            "RunAndGun_git/Public/Weapon/Components",
            "RunAndGun_git/Public/AI",
            "RunAndGun_git/Public/AI/Tasks",
            "RunAndGun_git/Public/AI/Services"
        });
        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
