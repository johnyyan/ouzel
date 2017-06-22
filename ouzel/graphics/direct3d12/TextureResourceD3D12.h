// Copyright (C) 2017 Elviss Strazdins
// This file is part of the Ouzel engine.

#pragma once

#include "core/CompileConfig.h"

#if OUZEL_SUPPORTS_DIRECT3D12

#include <d3d12.h>
#include "graphics/TextureResource.h"

namespace ouzel
{
    namespace graphics
    {
        class TextureResourceD3D12: public TextureResource
        {
        public:
            TextureResourceD3D12();
            virtual ~TextureResourceD3D12();

        protected:
            virtual bool upload() override;
        };
    } // namespace graphics
} // namespace ouzel

#endif
