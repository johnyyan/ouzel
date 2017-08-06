// Copyright (C) 2017 Elviss Strazdins
// This file is part of the Ouzel engine.

#pragma once

#include "core/CompileConfig.hpp"

#if OUZEL_PLATFORM_ANDROID && OUZEL_SUPPORTS_OPENGL

#include <thread>
#include <atomic>
#include "EGL/egl.h"
#include "EGL/eglext.h"
#include "graphics/opengl/RendererOGL.hpp"

namespace ouzel
{
    class Engine;

    namespace graphics
    {
        class RendererOGLAndroid: public RendererOGL
        {
            friend Engine;
        public:
            virtual ~RendererOGLAndroid();

        private:
            virtual bool init(Window* newWindow,
                              const Size2& newSize,
                              uint32_t newSampleCount,
                              Texture::Filter newTextureFilter,
                              uint32_t newMaxAnisotropy,
                              bool newVerticalSync,
                              bool newDepth,
                              bool newDebugRenderer) override;

            virtual bool lockContext() override;
            virtual bool swapBuffers() override;
            void main();

            EGLDisplay display = 0;
            EGLSurface surface = 0;
            EGLContext context = 0;

            std::atomic<bool> running;
            std::thread renderThread;
        };
    } // namespace graphics
} // namespace ouzel

#endif