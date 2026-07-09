#include "LoadView/Includes.h"
#import "LoadView/DTTJailbreakDetection.h"
#import "imgui/Il2cpp.h"
#import "LoadView/Icon.h"
#import "imgui/imgui_additional.h"
#import "imgui/stb_image.h"
#import "Utils/Macros.h"
#import "Utils/hack/Function.h"
#import "Utils/Mem.h"


using namespace IL2Cpp;
@interface ImGuiDrawView () <MTKViewDelegate>
@property (nonatomic, strong) id <MTLDevice> device;
@property (nonatomic, strong) id <MTLCommandQueue> commandQueue;
@end

UIView *view;
NSString *jail;
NSString *namedv;
NSString *deviceType;
NSString *bundle;
NSString *ver;

NSUserDefaults *saveSetting = [NSUserDefaults standardUserDefaults];
NSFileManager *fileManager = [NSFileManager defaultManager];
NSString *documentDir = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0];

@implementation ImGuiDrawView

ImFont* _espFont;
ImFont *_iconFont;

static bool MenDeal = false;
static bool StreamerMode = false;
static bool ESPEnable;
static bool ESPLine;
static bool ESPBox;
static bool ESPHealth;
static bool ESPName;
static bool ESPDistance;
static bool ESPAlert;
static bool ESPArrow;
static bool ESPCount;
float Dis = 1.0f;
int boxMode = 0;ImVec4 lineColor = ImVec4(1, 1, 1, 1);
ImVec4 boxColor = ImVec4(1, 1, 1, 1);
float ESPRounding = 0.0f;

- (instancetype)initWithNibName:(nullable NSString *)nibNameOrNil bundle:(nullable NSBundle *)nibBundleOrNil
{

    [self cc];

    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];

    _device = MTLCreateSystemDefaultDevice();
    _commandQueue = [_device newCommandQueue];

    if (!self.device) abort();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    ImFontConfig config;
    ImFontConfig icons_config;
    config.FontDataOwnedByAtlas = false;
    icons_config.MergeMode = true;
    icons_config.PixelSnapH = true;
    icons_config.OversampleH = 2;
    icons_config.OversampleV = 2;

    static const ImWchar icons_ranges[] = { 0xf000, 0xf3ff, 0 };

    NSString *fontPath = nssoxorany("/System/Library/Fonts/Core/AvenirNext.ttc");

    _espFont = io.Fonts->AddFontFromFileTTF(fontPath.UTF8String, 30.f, &config, io.Fonts->GetGlyphRangesVietnamese());

    _iconFont = io.Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 25.0f, &icons_config, icons_ranges);

    _iconFont->FontSize = 5;
    io.FontGlobalScale = 0.5f;

    ImGui_ImplMetal_Init(_device);

    return self;
}

+ (void)showChange:(BOOL)open
{
    MenDeal = open;
}

+ (BOOL)isMenuShowing {
    return MenDeal;
}

- (MTKView *)mtkView
{
    return (MTKView *)self.view;
}

-(void)cc
{

ver = [[[NSBundle mainBundle] infoDictionary] objectForKey:nssoxorany("CFBundleShortVersionString")];

bundle = [[NSBundle mainBundle] bundleIdentifier];

namedv = [[UIDevice currentDevice] name];
deviceType = [[UIDevice currentDevice] model];

if ([DTTJailbreakDetection isJailbroken]) {
jail = nssoxorany("Jailbroken");

}else{
jail = nssoxorany("Not Jailbroken Or Hidden Jailbreak");

}
}

- (void)loadView
{
    CGFloat w = [UIApplication sharedApplication].windows[0].rootViewController.view.frame.size.width;
    CGFloat h = [UIApplication sharedApplication].windows[0].rootViewController.view.frame.size.height;
    self.view = [[MTKView alloc] initWithFrame:CGRectMake(0, 0, w, h)];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.mtkView.device = self.device;
    if (!self.mtkView.device) {
        return;
    }
    self.mtkView.delegate = self;
    self.mtkView.clearColor = MTLClearColorMake(0, 0, 0, 0);
    self.mtkView.backgroundColor = [UIColor colorWithRed:0 green:0 blue:0 alpha:0];
    self.mtkView.clipsToBounds = YES;



}

- (void)drawInMTKView:(MTKView*)view
{

    hideRecordTextfield.secureTextEntry = StreamerMode;

    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize.x = view.bounds.size.width;
    io.DisplaySize.y = view.bounds.size.height;

    CGFloat framebufferScale = view.window.screen.nativeScale ?: UIScreen.mainScreen.nativeScale;
    io.DisplayFramebufferScale = ImVec2(framebufferScale, framebufferScale);
    io.DeltaTime = 1 / float(view.preferredFramesPerSecond ?: 60);
    
    id<MTLCommandBuffer> commandBuffer = [self.commandQueue commandBuffer];
        
        if (MenDeal == true) 
        {
            [self.view setUserInteractionEnabled:YES];
            [self.view.superview setUserInteractionEnabled:YES];
            [menuTouchView setUserInteractionEnabled:YES];
        } 
        else if (MenDeal == false) 
        {
           
            [self.view setUserInteractionEnabled:NO];
            [self.view.superview setUserInteractionEnabled:NO];
            [menuTouchView setUserInteractionEnabled:NO];

        }

Attach();

        MTLRenderPassDescriptor* renderPassDescriptor = view.currentRenderPassDescriptor;
        if (renderPassDescriptor != nil)
        {
            id <MTLRenderCommandEncoder> renderEncoder = [commandBuffer renderCommandEncoderWithDescriptor:renderPassDescriptor];
            [renderEncoder pushDebugGroup:nssoxorany("ImGui Jane")];

            ImGui_ImplMetal_NewFrame(renderPassDescriptor);
            ImGui::NewFrame();

            CGFloat width = 400;
            CGFloat height = 260;
            ImGui::SetNextWindowPos(ImVec2((kWidth - width) / 2, (kHeight - height) / 2), ImGuiCond_FirstUseEver);
            ImGui::SetNextWindowSize(ImVec2(width, height), ImGuiCond_FirstUseEver);



            
   if (MenDeal == true) {

   char* Gnam = (char*) [[NSString stringWithFormat:nssoxorany("Free Fire - Version: %@ "), ver] cStringUsingEncoding:NSUTF8StringEncoding];
ImGui::Begin(Gnam, &MenDeal, ImGuiWindowFlags_NoResize);

    ImGui::BeginTabBar(oxorany("Bar"), ImGuiTabBarFlags_NoTooltip);

if (ImGui::BeginTabItem(oxorany(ICON_FA_EYE " Esp")))
{
ImGui::Checkbox("Start Draw ESP", &ESPEnable);
        ImGui::Checkbox("Line", &ESPLine);
        ImGui::SameLine();  
        ImGui::Checkbox("Box", &ESPBox);
ImGui::SameLine();  
        ImGui::Checkbox("Info", &ESPHealth);
ImGui::SameLine();  
        ImGui::Checkbox("Arrow", &ESPArrow);
ImGui::SameLine();  
        ImGui::Checkbox("Count", &ESPCount);

ImGui::SliderFloat("Distance esp", &Dis, 0.0f, 200.0f, "%.0f m");

ImGui::EndTabItem();
}

        ImGui::EndTabBar();
    
bundle = [NSString stringWithFormat:nssoxorany("%@"),bundle];


                    char* showbundle = (char*) [bundle cStringUsingEncoding:NSUTF8StringEncoding];


ver = [NSString stringWithFormat:nssoxorany("%@"),ver];


                    char* showver = (char*) [ver cStringUsingEncoding:NSUTF8StringEncoding];


ImGui::Text(oxorany("%s"), oxorany("\n"));

ImGui::Separator();

ImGui::Text(oxorany("Bundle: %s"), showbundle);

ImGui::Text(oxorany("Version: %s"), showver);

    ImGui::End();
}
DrawEsp();
            
            ImGui::Render();
            ImDrawData* draw_data = ImGui::GetDrawData();
            ImGui_ImplMetal_RenderDrawData(draw_data, commandBuffer, renderEncoder);

            [renderEncoder popDebugGroup];
            [renderEncoder endEncoding];

            [commandBuffer presentDrawable:view.currentDrawable];
            
        }
        [commandBuffer commit];
}

- (void)mtkView:(MTKView*)view drawableSizeWillChange:(CGSize)size
{
    
}

- (void)updateIOWithTouchEvent:(UIEvent *)event
{
    UITouch *anyTouch = event.allTouches.anyObject;
    CGPoint touchLocation = [anyTouch locationInView:self.view];
    ImGuiIO &io = ImGui::GetIO();
    io.MousePos = ImVec2(touchLocation.x, touchLocation.y);

    BOOL hasActiveTouch = NO;
    for (UITouch *touch in event.allTouches)
    {
        if (touch.phase != UITouchPhaseEnded && touch.phase != UITouchPhaseCancelled)
        {
            hasActiveTouch = YES;
            break;
        }
    }
    io.MouseDown[0] = hasActiveTouch;
}

ImDrawList* getDrawList(){
    ImDrawList *drawList;
    drawList = ImGui::GetBackgroundDrawList();
    return drawList;
};
// #import "ESP.h"

void *hack_thread(void *) {

    sleep(5);
    hooking();
    pthread_exit(nullptr);
    return nullptr;
}

void __attribute__((constructor)) initialize() {
    pthread_t hacks;
    pthread_create(&hacks, NULL, hack_thread, NULL); 
}

@end