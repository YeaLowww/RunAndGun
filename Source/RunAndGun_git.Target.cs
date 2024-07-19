// Run And Gun Game. All Rights Received.

using UnrealBuildTool;
using System.Collections.Generic;

public class RunAndGun_gitTarget : TargetRules
{
	public RunAndGun_gitTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "RunAndGun_git" } );
	}
}
