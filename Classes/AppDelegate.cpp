#include "AppDelegate.h"
#include "GameScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {
    
}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("Hello World");
        auto screen_size = glview->getFrameSize();
        auto design_size = Size(768,1024);
        glview->setDesignResolutionSize(design_size.width,design_size.height, ResolutionPolicy::EXACT_FIT);
        director->setOpenGLView(glview);
    }
    
    auto scene = Game::createScene();
    director->runWithScene(scene);
    
    return true;
}

void AppDelegate::applicationDidEnterBackground() {
}

void AppDelegate::applicationWillEnterForeground() {
}

void AppDelegate::initGLContextAttrs(){
    GLContextAttrs gl_context_attrs = {8,8,8,8,24,8};
    GLView::setGLContextAttrs(gl_context_attrs);
}
