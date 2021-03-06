/*
    MANGO Multimedia Development Platform
    Copyright (C) 2012-2017 Twilight Finland 3D Oy Ltd. All rights reserved.
*/
#pragma once

#include <string>
#include "../core/object.hpp"
#include "format.hpp"
#include "compression.hpp"
#include "header.hpp"
#include "exif.hpp"

namespace mango
{

    class ImageDecoderInterface : protected NonCopyable
    {
    public:
        ImageDecoderInterface() = default;
        virtual ~ImageDecoderInterface() = default;

        virtual ImageHeader header() = 0;
        virtual void decode(Surface& dest, Palette* palette, int level, int depth, int face) = 0;

        // optional interface
        virtual Exif exif();
        virtual Memory memory(int level, int depth, int face);
    };

    class ImageDecoder : protected NonCopyable
    {
    protected:
        ImageDecoderInterface* m_interface;

    public:
        typedef ImageDecoderInterface* (*CreateFunc)(Memory memory);

        ImageDecoder(Memory memory, const std::string& filename);
        ~ImageDecoder();

        bool isDecoder() const;

        ImageHeader header();
        Exif exif();
        Memory memory(int level, int depth, int face);
        void decode(Surface& dest, Palette* palette, int level, int depth, int face);
    };

    void registerImageDecoder(ImageDecoder::CreateFunc func, const std::string& extension);
    bool isImageDecoder(const std::string& extension);

} // namespace mango
