{ pkgs }: {
    deps = [
      pkgs.cdrkit
      pkgs.grub2_light
      pkgs.nixos-rebuild
      pkgs.gdb
      pkgs.busybox
      pkgs.xorriso
      pkgs.llvmPackages.bintools-unwrapped
      pkgs.qemu
      pkgs.nasm
      pkgs.llvmPackages.clang
      pkgs.ccls
    ];
}