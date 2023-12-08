// Fill out your copyright notice in the Description page of Project Settings.

using System;
using System.IO;
using EpicGames.Core;
using UnrealBuildTool;

public class PSLLibrary : ModuleRules {
  public PSLLibrary(ReadOnlyTargetRules Target) : base(Target) {
    Type = ModuleType.External;

    CppStandard = CppStandardVersion.Cpp20;

    // PublicSystemIncludePaths.Add("$(ModuleDir)/Public");
    PublicSystemIncludePaths.Add("$(ModuleDir)/external/include");
    PublicSystemIncludePaths.Add("$(ModuleDir)/PCG-Supplemental-Library/include");

    if (Target.Platform == UnrealTargetPlatform.Win64) {
      PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "x64", "Release", "PCG-Supplemental-Library.lib"));

      PublicDelayLoadDLLs.Add("PCG-Supplemental-Library.dll");

      var psl_compilation_config = Target.Configuration == UnrealTargetConfiguration.Development ? "Debug" : "Release";
      var psl_compilation_dir = Path.Combine(ModuleDirectory, "x64", psl_compilation_config);
      var plugin_binaries_dir = Path.Combine(PluginDirectory, "Binaries", "ThirdParty", "PSLLibrary", "Win64");

      // copy PSL dll to binaries 
      var psl_compile_result = Path.Combine(psl_compilation_dir, "PCG-Supplemental-Library.dll");
      var psl_binaries_path = Path.Combine(plugin_binaries_dir, "PCG-Supplemental-Library.dll");
      File.Copy(psl_compile_result, psl_binaries_path, true);

      RuntimeDependencies.Add(psl_binaries_path);
    }
    else {
      throw new NotImplementedException("This plugin is only implemented for Windows 64-bit.");
    }
  }
}