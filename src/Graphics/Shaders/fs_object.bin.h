#pragma once

// Generated compiled shaders using shaderc with the bin2c option
#include <generated/shaders/fs_object.sc.glsl.bin.h>
#include <generated/shaders/fs_object.sc.spv.bin.h>
#if defined(_WIN32)
#include <generated/shaders/fs_object.sc.dx9.bin.h>
#include <generated/shaders/fs_object.sc.dx11.bin.h>
#endif  //  defined(_WIN32)
#if __APPLE__
#include <generated/shaders/fs_object.sc.mtl.bin.h>
#endif // __APPLE__
