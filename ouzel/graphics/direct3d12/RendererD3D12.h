// Copyright (C) 2017 Elviss Strazdins
// This file is part of the Ouzel engine.

#pragma once

#include <atomic>
#include <map>
#include <d3d12.h>
#include "graphics/Renderer.h"
#include "graphics/Texture.h"

namespace ouzel
{
    namespace graphics
    {
        class RendererD3D12: public Renderer
        {
            friend Engine;
        public:
            virtual ~RendererD3D12();

            virtual std::vector<Size2> getSupportedResolutions() const override;
        protected:
            RendererD3D12();

            virtual bool init(Window* newWindow,
                              const Size2& newSize,
                              uint32_t newSampleCount,
                              Texture::Filter newTextureFilter,
                              uint32_t newMaxAnisotropy,
                              bool newVerticalSync,
                              bool newDepth,
                              bool newDebugRenderer) override;
            virtual bool upload() override;
            virtual bool draw(const std::vector<DrawCommand>& drawCommands) override;
            virtual bool generateScreenshot(const std::string& filename) override;

            virtual BlendStateResource* createBlendState() override;
            virtual TextureResource* createTexture() override;
            virtual ShaderResource* createShader() override;
            virtual MeshBufferResource* createMeshBuffer() override;
            virtual BufferResource* createBuffer() override;
        };
    } // namespace graphics
} // namespace ouzel
