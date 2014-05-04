#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include<memory>

class HelloWorld : public cocos2d::Layer
{
private:
    struct Impl;
    std::unique_ptr<Impl> pImpl;
    cocos2d::PhysicsWorld* m_world;
    
    cocos2d::Sequence* getMoveAction( const cocos2d::Point &startPoint, const cocos2d::Point &endPoint, bool movable);
    cocos2d::Point getMapPoint( const cocos2d::Point &point);
    cocos2d::Point getPoint( const cocos2d::Point &mapPoint);
    cocos2d::Point getCorrectPoint(const cocos2d::Point &point);
    bool getCollidable( const cocos2d::Point &mapPoint);
    void enableMovable();

public:
    HelloWorld();
    virtual ~HelloWorld();
void setPhyWorld(cocos2d::PhysicsWorld* world){m_world = world;}
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event);
};

#endif // __HELLOWORLD_SCENE_H__
