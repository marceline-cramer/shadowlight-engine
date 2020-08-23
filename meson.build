project('shadowlight-engine', 'cpp')

src = [
    'src/main.cpp',

    'src/ShadowlightEngine.cpp',
    'src/LuaBinding.cpp',
    'src/BulletBinding.cpp',
    'src/OpenALBinding.cpp',
    'src/VulkanBinding.cpp',
    'src/Scene.cpp',

    'src/Entity.cpp',

    'src/ComponentScript.cpp'
]

dependencies = [
    dependency('luajit', version: '>=2.0.0'),
    dependency('vulkan'),
    dependency('openal'),
    dependency('bullet')
]

incdir = include_directories('include')

exe = executable('shadowlight', src,
    include_directories: incdir, dependencies: dependencies
)
