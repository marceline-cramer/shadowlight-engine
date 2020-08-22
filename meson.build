project('shadowlight-engine', 'cpp')

src = [
    'src/main.cpp',

    'src/ShadowlightEngine.cpp'
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
