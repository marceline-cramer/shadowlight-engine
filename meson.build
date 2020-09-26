project('shadowlight-engine', 'cpp')

src = [
    'src/global/main.cpp',
    'src/global/ShadowlightEngine.cpp',
    'src/global/Entity.cpp',
    'src/global/Scene.cpp',
    'src/global/Filesystem.cpp',
    'src/global/Window.cpp',

    'src/assets/ScriptAsset.cpp',
    'src/assets/AudioAsset.cpp',
    'src/assets/MeshAsset.cpp',
    'src/assets/MaterialAsset.cpp',
    'src/assets/TextureAsset.cpp',

    'src/bindings/BulletBinding.cpp',
    'src/bindings/LuaBinding.cpp',
    'src/bindings/OpenALBinding.cpp',
    'src/bindings/VulkanBinding.cpp',

    'src/bindings/vk/RenderAttachment.cpp',
    'src/bindings/vk/GBuffer.cpp',
    'src/bindings/vk/VulkanInstance.cpp',

    'src/components/ScriptComponent.cpp',
    'src/components/SceneComponent.cpp',
    'src/components/RigidBodyComponent.cpp',
    'src/components/AudioSourceComponent.cpp',
    'src/components/MeshRendererComponent.cpp',
    'src/components/CameraComponent.cpp',
    'src/components/FirstPersonControllerComponent.cpp',
    'src/components/PointLightComponent.cpp',

    'src/pipelines/MeshPipeline.cpp',
    'src/pipelines/PointLightPipeline.cpp',
    'src/pipelines/CompositePipeline.cpp',
    'src/pipelines/AmbientLightPipeline.cpp',

    'src/input/MouseAxis.cpp',
    'src/input/KeyboardAxis.cpp',

    'src/shaders/ShaderModule.cpp',
    'src/shaders/CompositeShader.cpp',
    'src/shaders/AmbientLightShader.cpp',
    'src/shaders/PointLightShader.cpp',
    'src/shaders/MaterialShader.cpp',

    'src/config/Config.cpp',
    'src/config/EngineConfig.cpp'
]

dependencies = [
    dependency('luajit', version: '>=2.0.5'),
    dependency('vulkan', version: '>=1.1.0'),
    dependency('openal', version: '>=1.19.1'),
    dependency('bullet', version: '>=2.87'),
    dependency('RapidJSON', version: '>=1.1.0'),
    dependency('sdl2', version: '>=2.0.9'),
    dependency('physfs', version: '>=3.0.2'),
    dependency('libavutil'),
    dependency('libavcodec'),
    dependency('libavformat'),
    dependency('libswresample'),
    dependency('shaderc')
]

incdir = include_directories(['src', 'lib'])

exe = executable('shadowlight', src,
    include_directories: incdir, dependencies: dependencies
)
