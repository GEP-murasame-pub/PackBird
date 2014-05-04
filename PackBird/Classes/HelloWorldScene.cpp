#include "HelloWorldScene.h"
#include "murasame/Char.h"

USING_NS_CC;
using namespace std;

#define SAFE_DELETE(x) { if(x); delete x; x=0; }

//static cocos2d::Scene * m_scene;

//static Node *node;

// あとでマネージャー作ってaddでretainしよう・・
struct HelloWorld::Impl{
    bool                                enable;
    Texture2D                           *ptexAtlus;  // Manager作るべきだな STLで
    unique_ptr<ml::CharBase>            player;
    TMXTiledMap                         *map;
    
    Impl()
        : ptexAtlus(nullptr)
        , enable(false)
        , player(new ml::CharBase())
        , map(nullptr)
    {}
    
    ~Impl(){
        CC_SAFE_RELEASE_NULL(ptexAtlus);
        CC_SAFE_RELEASE_NULL(map);
    }
};

HelloWorld::HelloWorld() : pImpl(new Impl()) {};
HelloWorld::~HelloWorld(){ };




Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity( Point( 0.0f, -200.0f ));
    scene->getPhysicsWorld()->setSpeed( 2.0f );
    
   // scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
//layer->setPhyWorld(scene->getPhysicsWorld());
    
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
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
 
    
//    pImpl->texAtlus.reset(Director::getInstance()->getTextureCache()->addImage("atlus.png"));
    pImpl->ptexAtlus = Director::getInstance()->getTextureCache()->addImage("atlus.png");
    pImpl->ptexAtlus->retain();
    

    Vector<SpriteFrame*> v;
    v.pushBack( SpriteFrame::createWithTexture(pImpl->ptexAtlus, Rect(0,0,64,64)));
    v.pushBack( SpriteFrame::createWithTexture(pImpl->ptexAtlus, Rect(64,0,64,64)));
    
    
    Animate *animate = Animate::create(Animation::createWithSpriteFrames( v, 0.2f ));
    {
    auto sp = pImpl->player->addSprite(Sprite::create());
    sp->runAction( RepeatForever::create( animate ));

    auto w = ( sp->getContentSize().width - 10 ) * sp->getScaleX();
    auto h = ( sp->getContentSize().height -30 ) * sp->getScaleY();
    auto pb = PhysicsBody::createBox( Size(w, h));
    pb->setMass(1.0f);
    pb->setVelocity( Point(0,1));
    pb->setVelocityLimit(200.0f);
    pb->setRotationEnable(false);
    pb->setAngularVelocityLimit(150.0f);
    pb->setContactTestBitmask( 0xFFFF );
    sp->setPhysicsBody(pb);
  //      pb->setDynamic(true);
    pb->setEnable(true);
    
    }
    
    

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
 //   auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen:ZERO);
    //    pImpl->player->getSprite() ->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
 //   this->addChild(pImpl->player->getSprite(), 0);

    pImpl->map = TMXTiledMap::create("map/stg1.tmx");
    // Coliderつけたい
    // Layerとれ！
 //       node = Node::create();
    {
        
    auto map = pImpl->map;
    auto layer = map->getLayer("BG");
    auto s = map->getMapSize();
    auto st = map->getTileSize();

//    auto node = Layer::create();
//        node->setPhysicsBody(PhysicsBody::createBox(  map->getMapSize() * map->getTileSize()  ));
//    node->setContentSize( map->getMapSize() * map->getTileSize() );
//        this->setPhysicsBody(PhysicsBody::createBox(  map->getMapSize() * map->getTileSize()  ));
    
    uint32_t *t = layer->getTiles();
    for( int y=0; y < s.height; y++ ){
        for( int x=0; x < s.width; x++ ){
            auto n = *t++;
            if( n==5 ){
                CCLOG( "point(%d,%d)", x,y );
                auto tile = layer->getTileAt(Point(x,y));
                
                auto pb = PhysicsBody::createBox( Size( st.width, st.height));
//                auto pb = PhysicsBody::createBox( Size( st.width, st.height), PHYSICSBODY_MATERIAL_DEFAULT, Point(x*st.width,y*st.height) );
         //       auto pb = PhysicsBody::createBox( Size( st.width, st.height), PHYSICSBODY_MATERIAL_DEFAULT, getCorrectPoint(Point(x,y)) );
     //           pb->setPositionOffset(getCorrectPoint(Point(x,y)));
                tile->setAnchorPoint(Point::ANCHOR_MIDDLE);
                pb->setDynamic(false);
                pb->setEnable(true);
                pb->setContactTestBitmask( 0xFFFF );
       //         tile->setPhysicsBody(pb);
  //              map->setPhysicsBody(pb);
                tile->setPhysicsBody(pb);
                
            }
        }
    }
        
    }
//    this->setAnchorPoint(Point::ANCHOR_MIDDLE);
    
//pImpl->map->retain();
//    auto nn  = Node::create();
//    this->addChild(node);
//    node->addChild( pImpl->map );
this->addChild( pImpl->map );
//    node->addChild( pImpl->map );
//    this->addChild( node );
    auto initPos = pImpl->map->getObjectGroup("point")->getObject("player");
 //   pImpl->map->setPosition(Point( -(int)initPos.at("x").asFloat() , -initPos.at("y").asFloat() ));
 
    
    pImpl->player->getSprite() ->setPosition(getCorrectPoint(Point(initPos["x"].asFloat(), initPos["y"].asFloat())));
  //  pImpl->player->getSprite() ->setAnchorPoint(Point::ZERO);
                                                
 //   this->addChild(pImpl->player->getSprite(), 0);
    pImpl->map->addChild(pImpl->player->getSprite(), 0);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    pImpl->enable = true;
    return true;
}



void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

Point HelloWorld::getMapPoint( const Point &point)
{
    int x = point.x / pImpl->map->getTileSize().width;
    int y = pImpl->map->getMapSize().height - (point.y + 0.1) / pImpl->map->getTileSize().height;
    return cocos2d::Point(x, y);
}

Point HelloWorld::getPoint(const Point &mapPoint)
{
    return Point(mapPoint.x * pImpl->map->getTileSize().width,
                 (pImpl->map->getMapSize().height - mapPoint.y - 1) * pImpl->map->getTileSize().height);
}

Point HelloWorld::getCorrectPoint(const Point &point)
{
    return getPoint(getMapPoint(point));
}


bool HelloWorld::onTouchBegan(Touch *touch, Event *unused_event)
{
    return true;
}

void HelloWorld::onTouchMoved(Touch *touch, Event *unused_event)
{
    pImpl->map->setPosition(pImpl->map->getPosition() + touch->getDelta());
  //　範囲チェックしよう
/*
    Vector<FiniteTimeAction*> actions;
    actions.pushBack(MoveTo::create( abs(touch->getDelta().x+touch->getDelta().y ) *0.01f, this->getPosition() + touch->getDelta() ));
    auto seq = Sequence::create(actions);
    if (seq)
        this->runAction(seq);
  */
    
    
}

void HelloWorld::onTouchEnded(Touch *touch, Event *unused_event)
{
    if (!pImpl->enable)
    return;
    
    auto start = getMapPoint(pImpl->map->convertToNodeSpace(touch->getStartLocation()));
    auto end = getMapPoint(pImpl->map->convertToNodeSpace(touch->getLocation()));
    
  //  CCLOG("%d, %d", end.x, end.y);
    
    if (start.x == end.x &&
        start.y == end.y
    //    && !getCollidable(end)
    )
    {
        // キャラ移動
        /*
        auto seq = getMoveAction(getMapPoint(pImpl->player->getSprite()->getPosition()), end, true);
        if (seq)
        pImpl->player->getSprite()->runAction(seq);
         */
        auto sp = pImpl->player->getSprite();
        float x = sp->getPosition().x;
        if( touch->getStartLocation().x < x ){
            x = -15;
        }else{
            x = 15;
        }
        
       sp->getPhysicsBody()->applyImpulse(Point(x, 180.0), Point( 0, sp->getContentSize().height*-1));
        
    }
}

void HelloWorld::onTouchCancelled(Touch *touch, Event *unused_event)
{
}

bool HelloWorld::getCollidable(const Point &mapPoint)
{
    auto metaLayer = pImpl->map->getLayer("BG");
    auto gid = metaLayer->getTileGIDAt(Point(mapPoint.x, mapPoint.y));
 //   auto properties = pImpl->map->getPropertiesForGID(gid).asValueMap();
//    CCLOG( "coli=%d\n", gid );
    return(gid == 5);
//    return properties["colider"].asString() == "True";
}

Sequence* HelloWorld::getMoveAction(const Point &startPoint, const Point &endPoint, bool movable)
{
    Vector<FiniteTimeAction*> actions;
    
    // 移動パスに移動不可のオブジェクトがないか確認
    if (endPoint.x != startPoint.x)
    {
        int xDirection = (endPoint.x - startPoint.x < 0)? -1 : 1;
        for (auto x = 0; x < abs(endPoint.x - startPoint.x); x++)
        {
            auto point = Point(startPoint.x + x * xDirection, startPoint.y);
            if (getCollidable(point))
            return nullptr;
        }
        actions.pushBack(MoveTo::create(abs(endPoint.x - startPoint.x) * 0.1, getPoint(Point(endPoint.x, startPoint.y))));
    }
    
    if (endPoint.y != startPoint.y)
    {
        int yDirection = (endPoint.y - startPoint.y < 0)? -1 : 1;
        for (auto y = 0; y < abs(endPoint.y - startPoint.y); y++)
        {
            auto point = Point(endPoint.x, startPoint.y + y * yDirection);
            if (getCollidable(point))
            return nullptr;
        }
        actions.pushBack(MoveTo::create(abs(endPoint.y - startPoint.y) * 0.1, getPoint(Point(endPoint.x, endPoint.y))));
    }
    
    // 移動アクションの作成
    if (movable)
    {
        pImpl->enable = false;
        actions.pushBack(CallFunc::create(CC_CALLBACK_0(HelloWorld::enableMovable, this)));
    }
    return Sequence::create(actions);
}

void HelloWorld::enableMovable()
{
    pImpl->enable = true;
}