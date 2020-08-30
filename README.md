# Shadowlight Engine
The Shadowlight Engine is a cross-platform game engine with Lua scripting, Bullet physics, and Vulkan graphics.

# Building

## Dependencies

- LuaJIT
- Vulkan
- OpenAL
- Bullet3
- Boost
- RapidJSON
- SDL2
- PhysFS
- FFMPEG

## Compiling

Built with meson:

```
mkdir builddir
cd builddir
meson ..
ninja
```
