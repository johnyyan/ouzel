// Copyright (C) 2017 Elviss Strazdins
// This file is part of the Ouzel engine.

#include "core/CompileConfig.h"

#if OUZEL_SUPPORTS_DIRECT3D12

#include <dxgi1_4.h>
#include "RendererD3D12.h"
#include "BlendStateResourceD3D12.h"
#include "TextureResourceD3D12.h"
#include "ShaderResourceD3D12.h"
#include "MeshBufferResourceD3D12.h"
#include "BufferResourceD3D12.h"
#include "TexturePSD3D12.h"
#include "TextureVSD3D12.h"
#include "ColorPSD3D12.h"
#include "ColorVSD3D12.h"
#include "core/Cache.h"
#include "core/Engine.h"
#include "utils/Log.h"
#include "core/windows/WindowWin.h"
#include "stb_image_write.h"

namespace ouzel
{
    namespace graphics
    {
        RendererD3D12::RendererD3D12():
            Renderer(Driver::DIRECT3D12)
        {
            apiMajorVersion = 12;
            apiMinorVersion = 0;
        }

        RendererD3D12::~RendererD3D12()
        {
            resourceDeleteSet.clear();
            resources.clear();

            if (device)
            {
                device->Release();
            }
        }

        bool RendererD3D12::init(Window* newWindow,
                                 const Size2& newSize,
                                 uint32_t newSampleCount,
                                 Texture::Filter newTextureFilter,
                                 uint32_t newMaxAnisotropy,
                                 bool newVerticalSync,
                                 bool newDepth,
                                 bool newDebugRenderer)
        {
            if (!Renderer::init(newWindow,
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

            IDXGIFactory4* factory;
            HRESULT hr = CreateDXGIFactory2(debugRenderer ? DXGI_CREATE_FACTORY_DEBUG : 0, IID_PPV_ARGS(&factory));

            if (FAILED(hr))
            {
                Log(Log::Level::ERR) << "Failed to create DXGI factory, error: " << hr;
                return false;
            }

            // TODO: initialize Direct3D 12
            


            std::shared_ptr<Shader> textureShader = std::make_shared<Shader>();
            textureShader->initFromBuffers(std::vector<uint8_t>(std::begin(TEXTURE_PIXEL_SHADER_D3D11), std::end(TEXTURE_PIXEL_SHADER_D3D11)),
                                           std::vector<uint8_t>(std::begin(TEXTURE_VERTEX_SHADER_D3D11), std::end(TEXTURE_VERTEX_SHADER_D3D11)),
                                           VertexPCT::ATTRIBUTES,
                                           {{"color", DataType::FLOAT_VECTOR4}},
                                           {{"modelViewProj", DataType::FLOAT_MATRIX4}});

            sharedEngine->getCache()->setShader(SHADER_TEXTURE, textureShader);

            std::shared_ptr<Shader> colorShader = std::make_shared<Shader>();
            colorShader->initFromBuffers(std::vector<uint8_t>(std::begin(COLOR_PIXEL_SHADER_D3D11), std::end(COLOR_PIXEL_SHADER_D3D11)),
                                         std::vector<uint8_t>(std::begin(COLOR_VERTEX_SHADER_D3D11), std::end(COLOR_VERTEX_SHADER_D3D11)),
                                         VertexPC::ATTRIBUTES,
                                         {{"color", DataType::FLOAT_VECTOR4}},
                                         {{"modelViewProj", DataType::FLOAT_MATRIX4}});

            sharedEngine->getCache()->setShader(SHADER_COLOR, colorShader);

            std::shared_ptr<BlendState> noBlendState = std::make_shared<BlendState>();

            noBlendState->init(false,
                               BlendState::BlendFactor::ONE, BlendState::BlendFactor::ZERO,
                               BlendState::BlendOperation::ADD,
                               BlendState::BlendFactor::ONE, BlendState::BlendFactor::ZERO,
                               BlendState::BlendOperation::ADD);

            sharedEngine->getCache()->setBlendState(BLEND_NO_BLEND, noBlendState);

            std::shared_ptr<BlendState> addBlendState = std::make_shared<BlendState>();

            addBlendState->init(true,
                                BlendState::BlendFactor::ONE, BlendState::BlendFactor::ONE,
                                BlendState::BlendOperation::ADD,
                                BlendState::BlendFactor::ONE, BlendState::BlendFactor::ONE,
                                BlendState::BlendOperation::ADD);

            sharedEngine->getCache()->setBlendState(BLEND_ADD, addBlendState);

            std::shared_ptr<BlendState> multiplyBlendState = std::make_shared<BlendState>();

            multiplyBlendState->init(true,
                                     BlendState::BlendFactor::DEST_COLOR, BlendState::BlendFactor::ZERO,
                                     BlendState::BlendOperation::ADD,
                                     BlendState::BlendFactor::ONE, BlendState::BlendFactor::ONE,
                                     BlendState::BlendOperation::ADD);

            sharedEngine->getCache()->setBlendState(BLEND_MULTIPLY, multiplyBlendState);

            std::shared_ptr<BlendState> alphaBlendState = std::make_shared<BlendState>();

            alphaBlendState->init(true,
                                  BlendState::BlendFactor::SRC_ALPHA, BlendState::BlendFactor::INV_SRC_ALPHA,
                                  BlendState::BlendOperation::ADD,
                                  BlendState::BlendFactor::ONE, BlendState::BlendFactor::ONE,
                                  BlendState::BlendOperation::ADD);

            sharedEngine->getCache()->setBlendState(BLEND_ALPHA, alphaBlendState);

            std::shared_ptr<Texture> whitePixelTexture = std::make_shared<Texture>();
            whitePixelTexture->initFromBuffer({255, 255, 255, 255}, Size2(1.0f, 1.0f), false, false);
            sharedEngine->getCache()->setTexture(TEXTURE_WHITE_PIXEL, whitePixelTexture);

            return true;
        }

        bool RendererD3D12::upload()
        {
            dirty = false;

            return true;
        }

        bool RendererD3D12::draw(const std::vector<DrawCommand>& drawCommands)
        {
            return true;
        }

        std::vector<Size2> RendererD3D12::getSupportedResolutions() const
        {
            std::vector<Size2> result;

            return result;
        }

        bool RendererD3D12::generateScreenshot(const std::string& filename)
        {
            return true;
        }

        BlendStateResource* RendererD3D12::createBlendState()
        {
            std::lock_guard<std::mutex> lock(resourceMutex);

            BlendStateResource* blendState = new BlendStateResourceD3D12();
            resources.push_back(std::unique_ptr<Resource>(blendState));
            return blendState;
        }

        TextureResource* RendererD3D12::createTexture()
        {
            std::lock_guard<std::mutex> lock(resourceMutex);

            TextureResource* texture = new TextureResourceD3D12();
            resources.push_back(std::unique_ptr<Resource>(texture));
            return texture;
        }

        ShaderResource* RendererD3D12::createShader()
        {
            std::lock_guard<std::mutex> lock(resourceMutex);

            ShaderResource* shader = new ShaderResourceD3D12();
            resources.push_back(std::unique_ptr<Resource>(shader));
            return shader;
        }

        MeshBufferResource* RendererD3D12::createMeshBuffer()
        {
            std::lock_guard<std::mutex> lock(resourceMutex);

            MeshBufferResource* meshBuffer = new MeshBufferResourceD3D12();
            resources.push_back(std::unique_ptr<Resource>(meshBuffer));
            return meshBuffer;
        }

        BufferResource* RendererD3D12::createBuffer()
        {
            std::lock_guard<std::mutex> lock(resourceMutex);

            BufferResource* buffer = new BufferResourceD3D12();
            resources.push_back(std::unique_ptr<Resource>(buffer));
            return buffer;
        }
    } // namespace graphics
} // namespace ouzel

#endif
