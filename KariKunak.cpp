#include "KariKunak.h"

enum
  {
    background = -10,
    Conf = -5,
    aux_anim = -6,
    info = -1,
    s_info = 1001
  };

USING_NS_CC;

Scene* KariKunak::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = KariKunak::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool KariKunak::init()
{
  //////////////////////////////
  // 1. super init first
  if ( !Layer::init() )
    {
      return false;
    }
    
  Size size = Director::getInstance()->getVisibleSize();

  sprite = CCSprite::create("KariKunak.png");
  CCSprite* back = CCSprite::create("splash_ini.jpg");

  // position the sprite on the center of the screen
  sprite->setPosition(CCPointMake((size.width/2.0f), (size.height/2.0f)));
  back->setPosition(CCPointMake((size.width/2.0f), (size.height/2.0f)));
  //sprite->setPosition(Vec2(0,0));
  // add the sprite as a child to this layer
  //this->addChild(sprite, 100);
  //this->addChild(back, background);
  //auto action1 = FadeOut::create(5.0f);
  //sprite->runAction( Sequence::create( action1, nullptr));
  //schedule( schedule_selector(KariKunak::ocultCredits),0.1f);

  //return true;
  //}

  //void KariKunak::ocultCredits(float dt){
  //Size size = Director::getInstance()->getVisibleSize();
    
  auto action1 = FadeOut::create(1.0f);

  //sprite->runAction( Sequence::create( action1, nullptr));
 

  auto s = Director::getInstance()->getWinSize();

  // IMPORTANT:
  // The sprite frames will be cached AND RETAINED, and they won't be released unless you call
  //     SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
  //
  // SpriteFrameCache is a cache of SpriteFrames
  // SpriteFrames each contain a texture id and a rect (frame).

  auto cache = SpriteFrameCache::getInstance();
  cache->addSpriteFramesWithFile("SD/intro_ini01.plist", "SD/intro_ini01.png");
  //auto spriteBatch = SpriteBatchNode::create("SD/intro_ini01.png");
  //
  // Animation using Sprite batch
  //
  // A SpriteBatchNode can reference one and only one texture (one .png file)
  // Sprites that are contained in that texture can be instantiatied as Sprites and then added to the SpriteBatchNode
  // All Sprites added to a SpriteBatchNode are drawn in one OpenGL ES draw call
  // If the Sprites are not added to a SpriteBatchNode then an OpenGL ES draw call will be needed for each one, which is less efficient
  //
  // When you animate a sprite, Animation changes the frame of the sprite using setDisplayFrame: (this is why the animation must be in the same texture)
  // When setDisplayFrame: is used in the Animation it changes the frame to one specified by the SpriteFrames that were added to the animation,
  // but texture id is still the same and so the sprite is still a child of the SpriteBatchNode, 
  // and therefore all the animation sprites are also drawn as part of the SpriteBatchNode
  //
  //ANIMATION LOGO KARIKUNAK
  auto sprite = Sprite::createWithSpriteFrameName("INTRO_INI_V20001.png");
  sprite->setPosition(CCPointMake((size.width/2.0f), (size.height/2.0f)));
  //sprite->setPosition(Vec2(s.width * 0.5f, s.height * 0.5f));
  auto spriteBatch = SpriteBatchNode::create("SD/intro_ini01.png");
  spriteBatch->addChild(sprite);
  addChild(spriteBatch);

  Vector<SpriteFrame*> animFrames(52);
  char str[100] = {0};
  for(int i = 3; i < 53; i++)
    {
      // Obtain frames by alias name
      if (i<10)
	{
	  sprintf(str, "INTRO_INI_V2000%d.png", i);
	}	  
      if ((i>9)and(i<100))
	{
	  sprintf(str, "INTRO_INI_V200%d.png", i);
	}
      auto frame = cache->getSpriteFrameByName(str);
      animFrames.pushBack(frame);
    }

  auto animation = Animation::createWithSpriteFrames(animFrames, 0.02f);
  // 14 frames * 1sec = 14 seconds
  sprite->runAction(Repeat::create(Animate::create(animation),1));

  //ANIMATION TEXT 

  auto cache1 = SpriteFrameCache::getInstance();
  cache1->addSpriteFramesWithFile("SD/frase01.plist", "SD/frase01.png");

  auto frase = Sprite::createWithSpriteFrameName("INTRO_FRASE0001.png");
  frase->setPosition(CCPointMake((size.width/2.0f), (size.height/2.0f)));
  //sprite->setPosition(Vec2(s.width * 0.5f, s.height * 0.5f));
  auto spriteBatch1 = SpriteBatchNode::create("SD/frase01.png");
  spriteBatch1->addChild(frase);
  addChild(spriteBatch1);

  Vector<SpriteFrame*> animFrames1(53);
  char str1[100] = {0};
  for(int i = 1; i < 64; i++)
    {
      // Obtain frames by alias name
      if (i<10)
	{
	  sprintf(str1, "INTRO_FRASE000%d.png", i);
	}	  
      if ((i>9)and(i<100))
	{
	  sprintf(str1, "INTRO_FRASE00%d.png", i);
	}
      auto frame1 = cache1->getSpriteFrameByName(str1);
      animFrames1.pushBack(frame1);
    }

  auto animation1 = Animation::createWithSpriteFrames(animFrames1, 0.02f);
  // 14 frames * 1sec = 14 seconds
  frase->runAction(Repeat::create(Animate::create(animation1),1));

  //ANIMATION BRILLO DERECHA 

  auto cache2 = SpriteFrameCache::getInstance();
  cache2->addSpriteFramesWithFile("SD/brilloder01.plist", "SD/brilloder01.png");

  auto brilloder = Sprite::createWithSpriteFrameName("INTRO_INI_brillo_der0001.png");
  brilloder->setPosition(CCPointMake((size.width/2.0f), (size.height/2.0f)));
  //sprite->setPosition(Vec2(s.width * 0.5f, s.height * 0.5f));
  auto spriteBatch2 = SpriteBatchNode::create("SD/brilloder01.png");
  spriteBatch2->addChild(brilloder);
  addChild(spriteBatch2);

  Vector<SpriteFrame*> animFrames2(80);
  char str2[100] = {0};
  for(int i = 1; i < 81; i++) 
   {
      // Obtain frames by alias name
      if (i<10)
	{
	  sprintf(str2, "INTRO_INI_brillo_der000%d.png", i);
	}	  
      if ((i>9)and(i<100))
	{
	  sprintf(str2, "INTRO_INI_brillo_der00%d.png", i);
	}
      auto frame2 = cache2->getSpriteFrameByName(str2);
      animFrames2.pushBack(frame2);
    }

  auto animation2 = Animation::createWithSpriteFrames(animFrames2, 0.02f);
  // 14 frames * 1sec = 14 seconds
  brilloder->runAction(Repeat::create(Animate::create(animation2),1));


//ANIMATION BRILLO izquierda

  auto cache3 = SpriteFrameCache::getInstance();
  cache3->addSpriteFramesWithFile("SD/brilloizq01.plist", "SD/brilloizq01.png");

  auto brilloizq = Sprite::createWithSpriteFrameName("INTRO_brillo_izq0080.png");
  brilloizq->setPosition(CCPointMake((size.width/2.0f), (size.height/2.0f)));
  //sprite->setPosition(Vec2(s.width * 0.5f, s.height * 0.5f));
  auto spriteBatch3 = SpriteBatchNode::create("SD/brilloizq01.png");
  spriteBatch3->addChild(brilloizq);
  addChild(spriteBatch3);

  Vector<SpriteFrame*> animFrames3(80);
  char str3[100] = {0};
  for(int i = 1; i < 81; i++)
    {
      // Obtain frames by alias name
      if (i<10)
	{
	  sprintf(str3, "INTRO_brillo_izq000%d.png", i);
	}	  
      if ((i>9)and(i<100))
	{
	  sprintf(str3, "INTRO_brillo_izq00%d.png", i);
	}
      auto frame3 = cache3->getSpriteFrameByName(str3);
      animFrames3.pushBack(frame3);
    }

  auto animation3 = Animation::createWithSpriteFrames(animFrames3, 0.02f);
  // 14 frames * 1sec = 14 seconds
  brilloizq->runAction(Repeat::create(Animate::create(animation3),1));


  schedule( schedule_selector(KariKunak::ocultCredits),2.0f);
  
  return true;
}

void KariKunak::ocultCredits(float dt){
  Size size = Director::getInstance()->getVisibleSize();
  auto Nivel1 = MenuItemImage::create(
					 "SD/intro.png",
					 "SD/intro1.png",
					 CC_CALLBACK_1(KariKunak::Nivel1, this));

  Nivel1->setPosition(CCPointMake((size.width/2.0f), (size.height/6.0f)));
  
  auto menu = Menu::create(Nivel1, nullptr);
  menu->setPosition(Vec2::ZERO);
  this->addChild(menu, 1);

  //auto sprite = Sprite::create("splash_ini.jpg");
  //addChild(sprite);
  //sprite->setPosition(CCPointMake((size.width/2.0f), (size.height/2.0f)));
  //auto action1 = FadeOut::create(1.0f);
  //sprite->runAction( Sequence::create( action1, nullptr));

}

void KariKunak::Nivel1(Ref* pSender)
{
  CCScene *Nivel1;
  Nivel1 = KariNivel1::createScene();
  CCDirector::sharedDirector()->replaceScene(Nivel1);
}
