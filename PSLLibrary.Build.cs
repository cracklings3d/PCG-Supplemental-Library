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

      string compile_config;
      switch (Target.Configuration) {
        case UnrealTargetConfiguration.Debug:
        case UnrealTargetConfiguration.DebugGame:
        case UnrealTargetConfiguration.Development:
          compile_config = "Debug";
          break;
        case UnrealTargetConfiguration.Test:
        case UnrealTargetConfiguration.Shipping:
          compile_config = "Release";
          break;
        default:
          throw new NotImplementedException("Unknown configuration: " + Target.Configuration.ToString());
      }

      var compile_result_dir = Path.Combine(ModuleDirectory, "x64", compile_config);
      var plugin_binaries_dir = Path.Combine(PluginDirectory, "Binaries", "ThirdParty", "PSLLibrary", "Win64");

      // copy PSL dll to binaries 
      var psl_compile_result = Path.Combine(compile_result_dir, "PCG-Supplemental-Library.dll");
      var psl_binaries_path = Path.Combine(plugin_binaries_dir, "PCG-Supplemental-Library.dll");
      File.Copy(psl_compile_result, psl_binaries_path, true);

      if (Target.Configuration == UnrealTargetConfiguration.Debug ||
          Target.Configuration == UnrealTargetConfiguration.DebugGame ||
          Target.Configuration == UnrealTargetConfiguration.Development
         ) {
        // copy PSL pdb to binaries 
        var psl_compile_result_pdb = Path.Combine(compile_result_dir, "PCG-Supplemental-Library.pdb");
        var psl_binaries_path_pdb = Path.Combine(plugin_binaries_dir, "PCG-Supplemental-Library.pdb");
        File.Copy(psl_compile_result_pdb, psl_binaries_path_pdb, true);
      }

      // Dependency packages
      switch (Target.Configuration) {
        case UnrealTargetConfiguration.Debug:
        case UnrealTargetConfiguration.DebugGame:
        case UnrealTargetConfiguration.Development:
          var dependency_lib_dir = Path.Combine(ModuleDirectory, "external", "debug", "lib");
          var dependency_libs = Directory.GetFiles(dependency_lib_dir, "*.lib");
          PublicAdditionalLibraries.AddRange(dependency_libs);

          var dependency_dll_dir = Path.Combine(ModuleDirectory, "external", "debug", "bin");
          var dependency_dlls = Directory.GetFiles(dependency_dll_dir, "*.dll");
          foreach (var dll in dependency_dlls) {
            PublicDelayLoadDLLs.Add(Path.GetFileName(dll));
          }

          break;
        case UnrealTargetConfiguration.Test:
        case UnrealTargetConfiguration.Shipping:
          var dependency_lib_dir_release = Path.Combine(ModuleDirectory, "external", "lib");
          var dependency_libs_release = Directory.GetFiles(dependency_lib_dir_release, "*.lib");
          PublicAdditionalLibraries.AddRange(dependency_libs_release);

          var dependency_dll_dir_release = Path.Combine(ModuleDirectory, "external", "bin");
          var dependency_dlls_release = Directory.GetFiles(dependency_dll_dir_release, "*.dll");
          foreach (var dll in dependency_dlls_release) {
            PublicDelayLoadDLLs.Add(Path.GetFileName(dll));
          }

          break;
      }

      RuntimeDependencies.Add(psl_binaries_path);
    }
    else {
      throw new NotImplementedException("This plugin is only implemented for Windows 64-bit.");
    }
  }
}