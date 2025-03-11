{
  inputs = {
    nixpkgs.url = "github:cachix/devenv-nixpkgs/rolling";
    systems.url = "github:nix-systems/default";
    devenv.url = "github:cachix/devenv";
    devenv.inputs.nixpkgs.follows = "nixpkgs";
  };

  nixConfig = {
    extra-trusted-public-keys = "devenv.cachix.org-1:w1cLUi8dv3hnoSPGAuibQv+f9TZLr6cv/Hm9XgU50cw=";
    extra-substituters = "https://devenv.cachix.org";
  };

  outputs = {
    self,
    nixpkgs,
    devenv,
    systems,
    ...
  } @ inputs: let
    forEachSystem = nixpkgs.lib.genAttrs (import systems);
  in {
    packages = forEachSystem (system: {
      devenv-up = self.devShells.${system}.default.config.procfileScript;
    });

    devShells =
      forEachSystem
      (system: let
        pkgs = import nixpkgs {
          inherit system;
          config.allowUnfree = true;
        };

        projectDirPath = builtins.getEnv "PWD";
        projectName = "DoorQuest";
        unrealEditorBaseDirPath = "/mnt/storage/unreal_editors/5.4.1";
        uprojectFilePath = "${projectDirPath}/${projectName}.uproject";
      in {
        default = devenv.lib.mkShell {
          inherit inputs pkgs;
          modules = [
            {
              packages = with pkgs; [
                clang-tools_16
              ];

              scripts = {
                ueg.exec = ''
                  ${unrealEditorBaseDirPath}/Engine/Build/BatchFiles/Linux/Build.sh \
                  -mode=GenerateClangDatabase \
                  -project=${uprojectFilePath} \
                  -game -engine ${projectName}Editor Linux Development

                  mv ${unrealEditorBaseDirPath}/compile_commands.json ${projectDirPath}
                '';

                uehr.exec = ''
                  randomNumber=$(echo $(( ( RANDOM % 1000 ) + 1000 )))

                  ${unrealEditorBaseDirPath}/Engine/Build/BatchFiles/Linux/Build.sh \
                  -ModuleWithSuffix=${projectName},''${randomNumber} \
                  ${projectName}Editor \
                  Linux Development \
                  -Project="${uprojectFilePath}" \
                  "${uprojectFilePath}"  \
                  -IgnoreJunk \
                  -progress \
                  -waitmutex
                '';
              };
            }
          ];
        };
      });
  };
}
