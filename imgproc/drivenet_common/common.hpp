/////////////////////////////////////////////////////////////////////////////////////////
// This code contains NVIDIA Confidential Information and is disclosed
// under the Mutual Non-Disclosure Agreement.
//
// Notice
// ALL NVIDIA DESIGN SPECIFICATIONS AND CODE ("MATERIALS") ARE PROVIDED "AS IS" NVIDIA MAKES
// NO REPRESENTATIONS, WARRANTIES, EXPRESSED, IMPLIED, STATUTORY, OR OTHERWISE WITH RESPECT TO
// THE MATERIALS, AND EXPRESSLY DISCLAIMS ANY IMPLIED WARRANTIES OF NONINFRINGEMENT,
// MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE.
//
// NVIDIA Corporation assumes no responsibility for the consequences of use of such
// information or for any infringement of patents or other rights of third parties that may
// result from its use. No license is granted by implication or otherwise under any patent
// or patent rights of NVIDIA Corporation. No third party distribution is allowed unless
// expressly authorized by NVIDIA.  Details are subject to change without notice.
// This code supersedes and replaces all information previously supplied.
// NVIDIA Corporation products are not authorized for use as critical
// components in life support devices or systems without express written approval of
// NVIDIA Corporation.
//
// Copyright (c) 2017 NVIDIA Corporation. All rights reserved.
//
// NVIDIA Corporation and its licensors retain all intellectual property and proprietary
// rights in and to this software and related documentation and any modifications thereto.
// Any use, reproduction, disclosure or distribution of this software and related
// documentation without an express license agreement from NVIDIA Corporation is
// strictly prohibited.
//
/////////////////////////////////////////////////////////////////////////////////////////

#ifndef DRIVENET_COMNMON_METHODS_H_
#define DRIVENET_COMNMON_METHODS_H_
#include <GL/glew.h>

#include <signal.h>

#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <cmath>

#include <chrono>
#include <thread>

// SAMPLE COMMON
 #include "SampleFramework.hpp"
 #include "ConsoleColor.hpp"
 #include "DataPath.hpp.in"
 #include "ProgramArguments.hpp"

// CORE
#include <dw/core/Context.h>
#include <dw/core/Logger.h>

// HAL
#include <dw/sensors/Sensors.h>
#include <dw/sensors/camera/Camera.h>

// Renderer
#include <dw/renderer/Renderer.h>

// IMAGE
#include <dw/image/FormatConverter.h>
#include <dw/image/ImageStreamer.h>

// RCCB
#include <dw/raw/RawPipeline.h>

// opencv
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#ifndef DRIVENET_MACRO
#define DRIVENET_MACRO
//------------------------------------------------------------------------------
// Variables
//------------------------------------------------------------------------------
extern cudaStream_t g_cudaStream;

// Driveworks Handles
extern dwContextHandle_t gSdk;
extern dwRendererHandle_t gRenderer;
extern dwRenderBufferHandle_t gLineBuffer;
extern dwSALHandle_t gSal;
extern dwSensorHandle_t gCameraSensor;
extern dwRawPipelineHandle_t gRawPipeline;
//extern dwImageProperties gRCBProperties;

// Sample variables
extern std::string gInputType;

// Maximum number of colors for rendering bounding boxes
extern const uint32_t gMaxBoxColors;

// Colors for rendering bounding boxes
extern float32_t gBoxColors[][4];


extern dwImageCUDA gRCBImage;

extern dwImageCUDA gRGBAImage;
extern dwImageCUDA gRGGBImage;
extern dwImageProperties gRCBProperties;

extern dwImageStreamerHandle_t gCuda2gl;
extern dwImageStreamerHandle_t gInput2cuda;
extern dwImageFormatConverterHandle_t gConvert2RGBA;
extern dwImageFormatConverterHandle_t gConvertRGB2RAW;

// Sample variables
extern dwRect gScreenRectangle;
#endif

//------------------------------------------------------------------------------
// Methods
//------------------------------------------------------------------------------
void drawROI(dwRect roi, const float32_t color[4], dwRenderBufferHandle_t renderBuffer, dwRendererHandle_t renderer);
void resizeWindowCallback(int width, int height);
void initRenderer(const dwImageProperties& rcbProperties, dwRendererHandle_t *renderer, dwContextHandle_t context, WindowBase *window);
bool initPipeline(const dwImageProperties &rawImageProps, const dwCameraProperties &cameraProps, dwContextHandle_t ctx);
void initSdk(dwContextHandle_t *context, WindowBase *window);
bool initSensors(dwSALHandle_t *sal, dwSensorHandle_t *camera, dwImageProperties *cameraImageProperties,
                 dwCameraProperties* cameraProperties, dwContextHandle_t context);
void release();

bool getNextFrameImages(dwImageCUDA** rcbCudaImageOut, dwImageGL** rgbaGLImageOut, dwCameraFrameHandle_t frameHandle);

void returnNextFrameImages(dwImageCUDA* rcbCudaImageOut, dwImageGL* rgbaGLImage);

#endif
