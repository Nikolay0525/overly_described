# Overly Described (Kyubu port)

> This is a **port to Kyubu** of the original mod [`ToufouMaster/OverlyDescribedCubeWorld`](https://github.com/ToufouMaster/OverlyDescribedCubeWorld).
> Original author: **ToufouMaster**. This port is not an official release by the author.

**What it does:** Descriptive texts for decorative objects instead of "There is nothing special".

**Original:** <https://github.com/ToufouMaster/OverlyDescribedCubeWorld>

**Release of the original this was ported from:** <https://github.com/ToufouMaster/OverlyDescribedCubeWorld/releases/tag/v1.2>

**Side:** client (`sides` in `mod.toml`).

## Installation

Requirements: **Cube World Alpha** (the 2013-07-20 `Cube.exe`, SHA-256 `84a7a132...30bf`, unpatched) and **Kyubu** (the mod loader, <https://github.com/kyubumods/kyubu>; this mod needs `kyubu = "^1.1"`, see `mod.toml`).

1. Install Kyubu with its own installer (`install\install.cmd`). The loader is not part of this mod.
2. Put **`overly_described.zip`** (do not unpack it) into the **`Mods\`** folder next to `Cube.exe`. If `overly_described.zip` is already there, replace it.
3. Start the game. `kyubu\logs\latest.log` should have a line saying `overly_described` loaded.
4. To turn the mod off or remove it, take `overly_described.zip` out of `Mods\` (or switch it off in the mod manager: **Mods** on the title screen).

The old Cube World Mod Launcher is **not needed** for this port and is not compatible with it: do not put the original mod's DLL next to it.


Mod id: `overly_described`. Source: `Mods\overly_described\src\main.cpp`.
