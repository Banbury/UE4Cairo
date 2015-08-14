// Some copyright should be here...

using UnrealBuildTool;
using System.IO;

public class CairoPlugin : ModuleRules
{
	public CairoPlugin(TargetInfo Target)
	{
		
		PublicIncludePaths.AddRange(
			new string[] {
				"CairoPlugin/Public"
				
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				"CairoPlugin/Private",
				
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core", "CoreUObject", "Engine", "InputCore"
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				
				// ... add any modules that your module loads dynamically here ...
			}
			);


        LoadCairo(Target);
	}

    public bool LoadCairo(TargetInfo Target)
    {
        bool isLibrarySupported = false;

        if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
        {
            isLibrarySupported = true;

            string PlatformString = (Target.Platform == UnrealTargetPlatform.Win64) ? "x64" : "x86";
            string LibrariesPath = Path.Combine(ThirdPartyPath, "Cairo", "Libraries");

            PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "x64", "cairo.lib"));
        }

        if (isLibrarySupported)
        {
            // Include path
            PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "Cairo", "Includes"));
        }

        Definitions.Add(string.Format("WITH_CAIRO_BINDING={0}", isLibrarySupported ? 1 : 0));

        return isLibrarySupported;
    }

    private string ModulePath
    {
        get { return Path.GetDirectoryName(RulesCompiler.GetModuleFilename(this.GetType().Name)); }
    }

    private string ThirdPartyPath
    {
        get { return Path.GetFullPath(Path.Combine(ModulePath, "../../../../ThirdParty/")); }
    }

}
