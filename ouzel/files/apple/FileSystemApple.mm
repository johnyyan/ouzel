// Copyright (C) 2018 Elviss Strazdins
// This file is part of the Ouzel engine.

#include "core/Setup.h"

#include <Foundation/Foundation.h>
#include "FileSystemApple.hpp"
#include "utils/Log.hpp"

#if OUZEL_PLATFORM_MACOS
extern std::string DEVELOPER_NAME;
extern std::string APPLICATION_NAME;
#endif

namespace ouzel
{
    std::string getStorageDirectoryApple(bool user)
    {
#if OUZEL_PLATFORM_MACOS
        NSFileManager* fileManager = [NSFileManager defaultManager];

        NSError* error;
        NSURL* applicationSupportDirectory = [fileManager URLForDirectory:NSApplicationSupportDirectory inDomain:user ? NSUserDomainMask : NSLocalDomainMask appropriateForURL:nil create:YES error:&error];

        if (!applicationSupportDirectory)
        {
            Log(Log::Level::ERR) << "Failed to get application support directory";
            return "";
        }

        NSString* identifier = [[NSBundle mainBundle] bundleIdentifier];

        if (!identifier)
        {
            identifier = [NSString stringWithFormat:@"%s.%s", DEVELOPER_NAME.c_str(), APPLICATION_NAME.c_str()];
        }

        NSURL* path = [applicationSupportDirectory URLByAppendingPathComponent:identifier];

        [fileManager createDirectoryAtURL:path withIntermediateDirectories:YES attributes:nil error:nil];

        return [[path path] UTF8String];
#else
        NSFileManager* fileManager = [NSFileManager defaultManager];

        NSError* error;
        NSURL* documentDirectory = [fileManager URLForDirectory:NSDocumentDirectory inDomain:user ? NSUserDomainMask : NSLocalDomainMask appropriateForURL:nil create:YES error:&error];

        if (!documentDirectory)
        {
            Log(Log::Level::ERR) << "Failed to get document directory";
            return "";
        }

        return [[documentDirectory path] UTF8String];
#endif
    }
}
