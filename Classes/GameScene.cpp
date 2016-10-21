#include "GameScene.h"

USING_NS_CC;

Scene* Game::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Game::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Game::init()
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
    
    touchLabel = Label::createWithSystemFont("New scene opened!!!", "Roboto Mono Nerd Font", 30);
    
    touchLabel->setPosition(Vec2(displayWidth/2,
                                 displayHeight/2));
    touchLabel->setColor(ccBLACK);
    auto touchListener = EventListenerTouchOneByOne::create();
    
    touchListener->onTouchBegan = CC_CALLBACK_2(Game::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(Game::onTouchEnded, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(Game::onTouchMoved, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(Game::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    this->addChild(bgSprite,0);
    this->addChild(touchLabel);
    
    return true;
}

bool Game::onTouchBegan(Touch* touch, Event* event){
    touchLabel->setPosition(touch->getLocation());
    touchLabel->setString("Yes it works!!");
    return true;
}

void Game::onTouchEnded(Touch* touch, Event* event){
    log("Touch ended");
}

void Game::onTouchMoved(Touch* touch, Event *event){
    log("Touch moved");
}

void Game::onTouchCancelled(Touch* touch, Event* event){
    log("Touch cancelled");
}
