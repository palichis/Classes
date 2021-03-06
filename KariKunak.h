#ifndef __KARIKUNAK_SCENE_H__
#define __KARIKUNAK_SCENE_H__

#include "cocos2d.h"
#include "KariLevel1.h"

class KariKunak : public cocos2d::Layer
{

  cocos2d::CCSprite* sprite;
  cocos2d::CCSprite* frase;
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void Nivel1(cocos2d::Ref* pSender);
    void ocultCredits(float dt);
    // implement the "static create()" method manually
    CREATE_FUNC(KariKunak);
};

#endif // __KARIKUNAK_SCENE_H__
