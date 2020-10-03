# Shadowlight Engine
The Shadowlight Engine is a future-proof VR engine for creating multiplayer virtual reality experiences.

## Future-proof?
Virtual reality is a rapidly expanding field of research, encompassing many topics, including optics, computer vision, machine learning, and embedded programming. As such, any development platform targeting VR needs to be ready to adapt to advances in VR technology, to provide a reliable and cross-platform user experience. Shadowlight will natively support new VR features such as full-body tracking, haptic feedback, eye tracking, and omnidirectional treadmills, as long as new VR tech is being created.

## VR engine?
The Shadowlight Engine is structured very similarly to a traditional game engine, but VR can be used for far more than just games. Large-scale virtual reality will revolutionize internet communication,
allowing employees, teachers, artists, and performers to engage with their peers over the internet in a far more natural way than with what is currently possible.

## Multiplayer?
Shadowlight is strictly designed around a client-server architecture, allowing multiple users to exist in the same virtual environment. Servers can be built to host virtual classrooms, professional meeting spaces, casual hangout areas, and of course, games. Your imagination is the only limit.

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
- [GLM](https://github.com/g-truc/glm)
- [shaderc](https://github.com/google/shaderc)

All of these packages should be available through your package manager, but if not, links are provided for convenience.

## Compiling

Built with [meson](https://mesonbuild.com/):

```
mkdir builddir
cd builddir
meson ..
ninja
```
