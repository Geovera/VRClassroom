// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class VRClassroomServerTarget : TargetRules
{
	public VRClassroomServerTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Server;
		BuildEnvironment = TargetBuildEnvironment.Shared;
        ExtraModuleNames.Add("VRClassroom");
	}
}
