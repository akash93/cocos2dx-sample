#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto bgSprite = Sprite::create("MarioBg.png");
    bgSprite->setAnchorPoint(Vec2(0,0));
    bgSprite->setPosition(0,0);
    
    auto bgWidth = bgSprite->getBoundingBox().size.width;
    auto bgHeight = bgSprite->getBoundingBox().size.height;
    
    auto displayWidth = Director::getInstance()->getVisibleSize().width;
    auto displayHeight = Director::getInstance()->getVisibleSize().height;
    
    auto bgScaleX = displayWidth/bgWidth;
    auto bgScaleY = displayHeight/bgHeight;
    bgSprite->setScale(bgScaleX, bgScaleY);
    
    touchLabel = Label::createWithSystemFont("Touch anywhere to begin", "Roboto Mono Nerd Font", 30);
    
    touchLabel->setPosition(Vec2(displayWidth/2,
                                 displayHeight/2));
    touchLabel->setColor(ccBLACK);
    auto touchListener = EventListenerTouchOneByOne::create();
    
    touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    this->addChild(bgSprite,0);
    this->addChild(touchLabel);
    
    return true;
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event){
    touchLabel->setPosition(touch->getLocation());
    touchLabel->setString("Get Ready!!");
    return true;
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event){
    log("Touch ended");
}

void HelloWorld::onTouchMoved(Touch* touch, Event *event){
    log("Touch moved");
}

void HelloWorld::onTouchCancelled(Touch* touch, Event* event){
    log("Touch cancelled");
}
