// Copyright (C) 2018 Elviss Strazdins
// This file is part of the Ouzel engine.

#include "RenderDeviceEmpty.hpp"
#include "BlendStateResourceEmpty.hpp"
#include "TextureResourceEmpty.hpp"
#include "ShaderResourceEmpty.hpp"
#include "MeshBufferResourceEmpty.hpp"
#include "BufferResourceEmpty.hpp"
#include "core/Engine.hpp"
#include "thread/Lock.hpp"
#include "assets/Cache.hpp"

namespace ouzel
{
    namespace graphics
    {
        RenderDeviceEmpty::RenderDeviceEmpty():
            RenderDevice(Renderer::Driver::EMPTY)
        {
        }

        bool RenderDeviceEmpty::init(Window* newWindow,
                                     const Size2& newSize,
                                     uint32_t newSampleCount,
                                     Texture::Filter newTextureFilter,
                                     uint32_t newMaxAnisotropy,
                                     bool newVerticalSync,
                                     bool newDepth,
                                     bool newDebugRenderer)
        {
            if (!RenderDevice::init(newWindow,
                                    newSize,
                                    newSampleCount,
                                    newTextureFilter,
                                    newMaxAnisotropy,
                                    newVerticalSync,
                                    newDepth,
                                    newDebugRenderer))
            {
                return false;
            }

            std::shared_ptr<Shader> textureShader = std::make_shared<Shader>();

            textureShader->init(std::vector<uint8_t>(),
                                std::vector<uint8_t>(),
                                {Vertex::Attribute::Usage::POSITION, Vertex::Attribute::Usage::COLOR, Vertex::Attribute::Usage::TEXTURE_COORDINATES0},
                                {{"color", DataType::FLOAT_VECTOR4}},
                                {{"modelViewProj", DataType::FLOAT_MATRIX4}});

            engine->getCache()->setShader(SHADER_TEXTURE, textureShader);

            std::shared_ptr<Shader> colorShader = std::make_shared<Shader>();

            colorShader->init(std::vector<uint8_t>(),
                              std::vector<uint8_t>(),
                              {Vertex::Attribute::Usage::POSITION, Vertex::Attribute::Usage::COLOR},
                              {{"color", DataType::FLOAT_VECTOR4}},
                              {{"modelViewProj", DataType::FLOAT_MATRIX4}});

            engine->getCache()->setShader(SHADER_COLOR, colorShader);

            return true;
        }

        bool RenderDeviceEmpty::processCommands(const std::vector<Command>&)
        {
            return true;
        }

        BlendStateResource* RenderDeviceEmpty::createBlendState()
        {
            Lock lock(resourceMutex);

            BlendStateResource* blendState = new BlendStateResourceEmpty();
            resources.push_back(std::unique_ptr<RenderResource>(blendState));
            return blendState;
        }

        TextureResource* RenderDeviceEmpty::createTexture()
        {
            Lock lock(resourceMutex);

            TextureResource* texture(new TextureResourceEmpty());
            resources.push_back(std::unique_ptr<RenderResource>(texture));
            return texture;
        }

        ShaderResource* RenderDeviceEmpty::createShader()
        {
            Lock lock(resourceMutex);

            ShaderResource* shader = new ShaderResourceEmpty();
            resources.push_back(std::unique_ptr<RenderResource>(shader));
            return shader;
        }

        MeshBufferResource* RenderDeviceEmpty::createMeshBuffer()
        {
            Lock lock(resourceMutex);

            MeshBufferResource* meshBuffer = new MeshBufferResourceEmpty();
            resources.push_back(std::unique_ptr<RenderResource>(meshBuffer));
            return meshBuffer;
        }

        BufferResource* RenderDeviceEmpty::createBuffer()
        {
            Lock lock(resourceMutex);

            BufferResource* buffer = new BufferResourceEmpty();
            resources.push_back(std::unique_ptr<RenderResource>(buffer));
            return buffer;
        }
    } // namespace graphics
} // namespace ouzel
