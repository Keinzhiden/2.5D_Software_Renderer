# 2.5D Software Renderer

A Build-engine-style (Duke Nukem 3D) software renderer written from scratch in C++.
Every pixel is computed on the CPU into a framebuffer; SFML is only used to open the
window and display the final image.

![Walking through the sectors](docs/walk.gif)

## Download

**Windows 64-bit**: download [`2.5D_Software_Renderer-win64.zip`](https://github.com/Keinzhiden/2.5D_Software_Renderer/releases/latest/download/2.5D_Software_Renderer-win64.zip),
unzip it and run `2.5D_Renderer.exe`. Nothing else to install. It opens in fullscreen;
`Esc` quits.

## How it works

The world is a set of convex **sectors** (2D polygons with a floor and a ceiling height).
Each wall is either solid or a **portal** to a neighbouring sector.

![Portal rendering, step by step](docs/portals.gif)

*Debug mode: magenta is what has not been drawn yet. The view is filled sector by
sector, each portal restricting the screen window the next sector may draw into.*

- **Portal rendering**: start in the player's sector, draw its walls, and queue every
  visible portal with the screen-space window it covers. Neighbouring sectors are then
  drawn only inside that window.
- **Column renderer**: walls are projected and drawn as vertical spans into a CPU pixel
  buffer.
- **Near-plane clipping**: walls crossing behind the camera are clipped before projection.
- **Floor and ceiling heights per sector**: steps and lintels are drawn as the upper and
  lower parts of a portal.
- **Vertical look by y-shearing**, as in Duke Nukem 3D.
- **Per-column vertical occlusion**: each column keeps the top and bottom already drawn,
  which removes most of the overdraw.
- **Collision** with solid walls, and sector transitions that adjust the player height
  when stepping up or down.

## Controls

| Input | Action |
|---|---|
| Arrow keys | Move |
| Mouse | Look around |
| Left / right click | Move the camera down / up |
| `P` | Step-by-step debug render (`Space` = next wall, `P` = leave) |
| `Esc` | Quit |

## Build

Visual Studio 2019 or later, x64.

1. Download **SFML 2.5.1** (Visual C++ 15 (2017), 64-bit) and extract it into
   `2.5D_Engine/SFML-2.5.1/` (the project links the static libraries).
2. Open `2.5D_Engine/2.5D_Engine.sln` and build `Release | x64`.

The map is currently defined in code (`Map.cpp`). The renderer uses flat colours;
textures are not implemented yet.
