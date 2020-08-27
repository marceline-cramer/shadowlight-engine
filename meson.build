project('shadowlight-engine', 'cpp')

src = [
    'src/global/main.cpp',
    'src/global/ShadowlightEngine.cpp',
    'src/global/Entity.cpp',
    'src/global/Scene.cpp',
    'src/global/Filesystem.cpp',

    'src/assets/ScriptAsset.cpp',
    'src/assets/AudioAsset.cpp',

    'src/bindings/BulletBinding.cpp',
    'src/bindings/LuaBinding.cpp',
    'src/bindings/OpenALBinding.cpp',
    'src/bindings/VulkanBinding.cpp',

    'src/components/ScriptComponent.cpp',
    'src/components/SceneComponent.cpp',
    'src/components/RigidBodyComponent.cpp',
    'src/components/AudioSourceComponent.cpp'
]

dependencies = [
    dependency('luajit', version: '>=2.0.5'),
    dependency('vulkan', version: '>=1.2.149'),
    dependency('openal', version: '>=1.20.1'),
    dependency('bullet', version: '>=2.89'),
    dependency('boost', version: '>=1.72.0'),
    dependency('RapidJSON', version: '>=1.1.0'),
    dependency('sdl2', version: '>=2.0.12'),
    dependency('physfs', version: '>=3.0.2'),
    dependency('libavutil'),
    dependency('libavcodec'),
    dependency('libavformat'),
    dependency('libswresample')
]

incdir = include_directories('src')

exe = executable('shadowlight', src,
    include_directories: incdir, dependencies: dependencies
)
