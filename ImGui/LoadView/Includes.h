#include <MetalKit/MetalKit.h>
#include <Metal/Metal.h>
#include <iostream>
#include <UIKit/UIKit.h>
#include <vector>
#import "pthread.h"
#include <array>
#import <os/log.h>
#import "pthread.h"
#include <cmath>
#include <deque>
#include <vector>
#include <fstream>
#include <algorithm>

#import "ImGuiDrawView.h"
#import "LoadView.h"
#import "FTNotificationIndicator.h"
#import "../imgui/imgui.h"
#import "../imgui/imgui_internal.h"
#import "../imgui/imgui_impl_metal.h"
#include "Utils/hack/Vector3.h"
#include "Utils/hack/Vector2.h"
#include "Utils/hack/monoString.h"
#include "Security/Obfuscate.h"

#define kWidth  [UIScreen mainScreen].bounds.size.width
#define kHeight [UIScreen mainScreen].bounds.size.height
#define kScale [UIScreen mainScreen].scale

extern MenuInteraction* menuTouchView;
extern UIButton* InvisibleMenuButton;
extern UIButton* VisibleMenuButton;
extern UITextField* hideRecordTextfield;
extern UIView* hideRecordView;