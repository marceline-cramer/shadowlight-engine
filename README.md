# Shadowlight Engine
The Shadowlight Engine is a cross-platform game engine with Lua scripting, Bullet physics, and Vulkan graphics.

# Building

## Dependencies

- [LuaJIT](http://luajit.org/install.html)
- [Vulkan](https://www.lunarg.com/vulkan-sdk/)
- [OpenAL](https://www.openal.org/)
- [Bullet](https://github.com/bulletphysics/bullet3)
- [RapidJSON](https://rapidjson.org/)
- [SDL2](https://www.libsdl.org/)
- [PhysFS](https://www.icculus.org/physfs/)
- [FFMPEG](https://ffmpeg.org/)

All of these packages should be available through your package manager, but if not, links are provided for convenience.

## Compiling

Built with [meson](https://mesonbuild.com/):

```
mkdir builddir
cd builddir
meson ..
ninja
```
