{
  inputs = {
    nixpkgs.url = "github:cachix/devenv-nixpkgs/rolling";
    systems.url = "github:nix-systems/default";
    devenv.url = "github:cachix/devenv";
    devenv.inputs.nixpkgs.follows = "nixpkgs";
    mach-nix.url = "mach-nix/3.5.0";
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

        mach-nix-pkgs = inputs.mach-nix.lib."${system}".mkPython {
          requirements = ''
            ue4cli
          '';
        };

        pwd = builtins.getEnv "PWD";
        projectName = "UPDATE_HERE";
        unrealVersion = "5.4.1"; # UPDATE_HERE if needed (Editor Path)
        projectPath = "${pwd}/${projectName}.uproject";
      in {
        default = devenv.lib.mkShell {
          inherit inputs pkgs;
          modules = [
            {
              packages = with pkgs; [
                clang-tools_16
                mach-nix-pkgs
              ];
              scripts = {
                de-openue.exec = ''
                  nvidia-offload openue ${unrealVersion} ${projectPath}
                '';

                de-uegen.exec = ''
                  uegen ${unrealVersion} ${projectName} ${projectPath}
                '';
              };
            }
          ];
        };
      });
  };
}
