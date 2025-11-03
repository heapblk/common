{ pkgs ? import (fetchTarball "https://github.com/NixOS/nixpkgs/archive/3de8f8d73e35724bf9abef41f1bdbedda1e14a31.tar.gz") {} }:

pkgs.mkShell {
	name = "common-dev";
	packages = with pkgs; [
		gcc15
		gnumake
		ninja
	];
}
