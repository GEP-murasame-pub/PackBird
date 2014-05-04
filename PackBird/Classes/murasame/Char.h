//
//  Char.h
//  PackBird
//
//  Created by Yuki miyatake on 2014/05/01.
//
//
#ifndef PackBird_Char_h
#define PackBird_Char_h

#include "cocos2d.h"
#include<memory>

namespace ml{

    
class CharBase
{
protected:
//    cocos2d::Texture2D                      *m_texture;
    cocos2d::Sprite                         *m_psprite;
    int                                     m_frameWidth;
    int                                     m_frameHeight;
    // Animation
    
public:
    CharBase()
  //      : m_texture(nullptr)
        : m_psprite(nullptr)
        , m_frameWidth(64)
        , m_frameHeight(64)
    {};
    
    virtual ~CharBase()
    {
        CC_SAFE_RELEASE_NULL( m_psprite );
 //       CC_SAFE_RELEASE_NULL( m_texture );
    };
    
    cocos2d::Sprite* addSprite( cocos2d::Sprite* spr)
    {
        CC_SAFE_RELEASE(m_psprite);
        m_psprite=spr;
        CC_SAFE_RETAIN(m_psprite);
        
        return(m_psprite);
    }
    void removeSprite()
    {
        CC_SAFE_RELEASE_NULL(m_psprite);
    }
    
    cocos2d::Sprite* getSprite()  {return(m_psprite);}

    
    /*
    void addTexture( cocos2d::Texture2D *tex ){
        CC_SAFE_RELEASE_NULL(m_texture);
        m_texture=tex;
        CC_SAFE_RETAIN(m_texture);
    }
    void removeTexture(){
        CC_SAFE_RELEASE_NULL(m_texture);
    }
    */
    
    
};


}
#endif


/*
 module("yy", package.seeall)
 
 
 Base = {}
 Base.new = function ( texAtlus )
 local obj={}
 obj.texAtlus = texAtlus
 obj.tag=0
 obj.frameWidth = 64
 obj.frameHeight = 64
 obj.sprite = nil
 obj.animations = {}
 
 ----------------------------------------
 --       Animation                    --
 ----------------------------------------
 obj.createAnimation = function( self, name, arect, ms )
 local frames = {}
 local i=1
 
 for key,value in pairs(arect) do
 value.x = value.x*self.frameWidth
 value.y = value.y*self.frameHeight
 value.width = value.width*self.frameWidth  -1
 value.height = value.height*self.frameWidth  -1
 frames[i] = cc.SpriteFrame:createWithTexture(self.texAtlus, value)
 i = i+1
 end
 
 if( self.sprite == nil) then
 self.sprite = cc.Sprite:createWithSpriteFrame(frames[1])
 end
 
 local animation = cc.Animation:createWithSpriteFrames( frames, ms)
 local animate = cc.Animate:create(animation);
 self.animations[name] = animate
 end
 
 obj.animationForever = function( self, name )
 print( "animationForever set :", name )
 self.sprite:runAction(cc.RepeatForever:create( cc.Animate:create(self.animations[name]) ))  -- これメンバにする
 end
 
 
 return obj;
 end
 
 
 Player = {}
 Player.new = function ( texAtlus )
 local obj = Base.new(texAtlus)
 --  setmetatable(obj,{__index=SpriteChar})
 obj.tag = 1
 
 return obj
 end
 ----
 
 */