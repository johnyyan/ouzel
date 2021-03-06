// Copyright (C) 2018 Elviss Strazdins
// This file is part of the Ouzel engine.

#pragma once

#include "scene/Component.hpp"
#include "scene/ModelData.hpp"

namespace ouzel
{
    namespace scene
    {
        class ModelRenderer: public Component
        {
        public:
            static const uint32_t TYPE = Component::MODEL_RENDERER;

            ModelRenderer();
            explicit ModelRenderer(const ModelData& modelData);
            explicit ModelRenderer(const std::string& filename, bool mipmaps = true);

            bool init(const ModelData& modelData);
            bool init(const std::string& filename, bool mipmaps = true);

            virtual void draw(const Matrix4& transformMatrix,
                              float opacity,
                              const Matrix4& renderViewProjection,
                              const std::shared_ptr<graphics::Texture>& renderTarget,
                              const Rect& renderViewport,
                              bool depthWrite,
                              bool depthTest,
                              bool wireframe,
                              bool scissorTest,
                              const Rect& scissorRectangle) override;

            virtual const std::shared_ptr<graphics::Material>& getMaterial() const { return material; }
            virtual void setMaterial(const std::shared_ptr<graphics::Material>& newMaterial) { material = newMaterial; }

        protected:
            std::shared_ptr<graphics::Material> material;
            std::shared_ptr<graphics::MeshBuffer> meshBuffer;
            std::shared_ptr<graphics::Buffer> indexBuffer;
            std::shared_ptr<graphics::Buffer> vertexBuffer;

            std::shared_ptr<graphics::Texture> whitePixelTexture;
        };
    } // namespace scene
} // namespace ouzel
