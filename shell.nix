{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell rec {
  name = "dwm-dev-shell";

  buildInputs = with pkgs; [
    pkg-config
    xorg.libX11
    xorg.libXft
    xorg.libXinerama
    xorg.xorgproto
    fontconfig
    freetype

    ghostty
    gcc
    gnumake
  ];

  shellHook = ''
          export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${pkgs.lib.makeLibraryPath buildInputs}
          export INCLUDE_PATH=$INCLUDE_PATH:${pkgs.lib.makeIncludePath buildInputs}
  '';
}
