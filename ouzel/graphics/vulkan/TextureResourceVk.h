// Copyright (C) 2017 Elviss Strazdins
// This file is part of the Ouzel engine.

#pragma once

#include "core/CompileConfig.h"

#if OUZEL_SUPPORTS_VULKAN

#include "graphics/TextureResource.h"

namespace ouzel
{
    namespace graphics
    {
        class TextureResourceVk: public TextureResource
        {
        public:
            TextureResourceVk();
            virtual ~TextureResourceVk();

        protected:
            virtual bool upload() override;
        };
    } // namespace graphics
} // namespace ouzel

#endif
