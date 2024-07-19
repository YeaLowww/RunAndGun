// Run And Gun Game. All Rights Received.

using UnrealBuildTool;
using System.Collections.Generic;

public class RunAndGun_gitEditorTarget : TargetRules
{
	public RunAndGun_gitEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "RunAndGun_git" } );
	}
}
