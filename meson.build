project('shadowlight-engine', 'cpp')

src = [
    'src/main.cpp',

    'src/ShadowlightEngine.cpp',
    'src/LuaBinding.cpp',
    'src/BulletBinding.cpp',
    'src/OpenALBinding.cpp',
    'src/VulkanBinding.cpp',
    'src/Scene.cpp',

    'src/AssetPool.cpp',
    'src/Asset.cpp',
    'src/AssetHandle.cpp',

    'src/Entity.cpp',

    'src/ComponentScript.cpp'
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

incdir = include_directories('include')

exe = executable('shadowlight', src,
    include_directories: incdir, dependencies: dependencies
)
