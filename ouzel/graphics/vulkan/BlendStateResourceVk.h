// Copyright (C) 2017 Elviss Strazdins
// This file is part of the Ouzel engine.

#pragma once

#include "core/CompileConfig.h"

#if OUZEL_SUPPORTS_VULKAN

#include "graphics/BlendStateResource.h"

namespace ouzel
{
    namespace graphics
    {
        class BlendStateResourceVk: public BlendStateResource
        {
        public:
            BlendStateResourceVk();
            virtual ~BlendStateResourceVk();

        protected:
            virtual bool upload() override;
        };
    } // namespace graphics
} // namespace ouzel

#endif

