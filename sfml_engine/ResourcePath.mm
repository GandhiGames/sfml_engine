#include "ResourcePath.hpp"

//TODO: Make multiplatform  - beginning of chapter 6
//TODO: create "relative folder paths file" containing references to Characters/fonts folders etc so that any changes to resources file paths does not require code change.

#import <Foundation/Foundation.h>

std::string resourcePath(void)
{
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];

    std::string rpath;
    NSBundle* bundle = [NSBundle mainBundle];

    if (bundle == nil) {
#ifdef DEBUG
        NSLog(@"bundle is nil... thus no resources path can be found.");
#endif
    } else {
        NSString* path = [bundle resourcePath];
        rpath = [path UTF8String] + std::string("/");
    }

    [pool drain];

    return rpath;
}
