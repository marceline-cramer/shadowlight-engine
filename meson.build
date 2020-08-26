project('shadowlight-engine', 'cpp')

src = [
    'src/global/main.cpp',
    'src/global/ShadowlightEngine.cpp',
    'src/global/Entity.cpp',
    'src/global/Scene.cpp',

    'src/assets/Asset.cpp',
    'src/assets/ScriptAsset.cpp',

    'src/bindings/BulletBinding.cpp',
    'src/bindings/LuaBinding.cpp',
    'src/bindings/OpenALBinding.cpp',
    'src/bindings/VulkanBinding.cpp',

    'src/components/ScriptComponent.cpp'
]

dependencies = [
    dependency('luajit', version: '>=2.0.5'),
    dependency('vulkan', version: '>=1.2.149'),
    dependency('openal', version: '>=1.20.1'),
    dependency('bullet', version: '>=2.89'),
    dependency('boost', version: '>=1.72.0'),
    dependency('jsoncpp', version: '>=1.9.3'),
    dependency('sdl2', version: '>=2.0.12'),
    dependency('physfs', version: '>=3.0.2')
]

incdir = include_directories('src')

exe = executable('shadowlight', src,
    include_directories: incdir, dependencies: dependencies
)
