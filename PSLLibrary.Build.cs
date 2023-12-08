// Fill out your copyright notice in the Description page of Project Settings.

using System;
using System.IO;
using UnrealBuildTool;

public class PSLLibrary : ModuleRules {
  public PSLLibrary(ReadOnlyTargetRules Target) : base(Target) {
    Type = ModuleType.External;

    CppStandard = CppStandardVersion.Cpp20;
    
    // PublicSystemIncludePaths.Add("$(ModuleDir)/Public");
    PublicSystemIncludePaths.Add("$(ModuleDir)/external/include");
    PublicSystemIncludePaths.Add("$(ModuleDir)/PCG-Supplemental-Library/include");

    var external_lib_path = Path.Combine(ModuleDirectory, "external", "lib");

    if (Target.Platform == UnrealTargetPlatform.Win64) {
      PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "x64", "Release", "PCG-Supplemental-Library.lib"));

      PublicDelayLoadDLLs.Add("PCG-Supplemental-Library.dll");

      // RuntimeDependencies.Add("$(PluginDir)/Binaries/ThirdParty/PSLLibrary/Win64/ExampleLibrary.dll");
    }
    else {
      throw new NotImplementedException("This plugin is only implemented for Windows 64-bit.");
    }
  }
}