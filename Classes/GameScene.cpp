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
    
    auto bg_sprite = Sprite::create("MarioBg.png");
    bg_sprite->setAnchorPoint(Vec2(0,0));
    bg_sprite->setPosition(0,0);
    
    auto bg_width = bg_sprite->getBoundingBox().size.width;
    auto bg_height = bg_sprite->getBoundingBox().size.height;
    
    auto display_width = Director::getInstance()->getVisibleSize().width;
    auto display_height = Director::getInstance()->getVisibleSize().height;
    
    auto bg_scale_x = display_width/bg_width;
    auto bg_scale_y = display_height/bg_height;
    bg_sprite->setScale(bg_scale_x, bg_scale_y);
    
    touch_label = Label::createWithSystemFont("New scene opened!!!", "Roboto Mono Nerd Font", 30);
    
    touch_label->setPosition(Vec2(display_width/2,
                                 display_height/2));
    touch_label->setColor(ccBLACK);
    auto touch_listener = EventListenerTouchOneByOne::create();
    
    touch_listener->onTouchBegan = CC_CALLBACK_2(Game::onTouchBegan, this);
    touch_listener->onTouchEnded = CC_CALLBACK_2(Game::onTouchEnded, this);
    touch_listener->onTouchMoved = CC_CALLBACK_2(Game::onTouchMoved, this);
    touch_listener->onTouchCancelled = CC_CALLBACK_2(Game::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touch_listener, this);
    this->addChild(bg_sprite,0);
    this->addChild(touch_label);
    
    return true;
}

bool Game::onTouchBegan(Touch* touch, Event* event){
    touch_label->setPosition(touch->getLocation());
    touch_label->setString("Yes it works!!");
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
