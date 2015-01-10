#include "KariLevel1.h"
#include "extensions/cocos-ext.h"

USING_NS_CC;


Scene* KariNivel1::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = KariNivel1::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool KariNivel1::init()
{
    //////////////////////////////
    // 1. super init first
  if ( !Layer::init() )
    {
      return false;
    }
  auto screenSize = Director::getInstance()->getWinSize();
  //auto layer = Node::create();
  schedule(schedule_selector(KariNivel1::hola),0.5f);
  //removeChild(layer);
  
  return true;
}

void KariNivel1::hola(float dt){

  auto screenSize = Director::getInstance()->getWinSize();
  auto layer = Node::create();
  // Defines an array of title to create buttons dynamically                                                                                                                                    
  std::vector<std::string> vec;
  vec.push_back("Hola Mundo");
  vec.push_back("Variable");
  vec.push_back("Size");
  vec.push_back("NONES");

  
  addChild(layer, 1);

  double total_width = 0, height = 0;

  int i = 0;

  for (auto& title : vec)
    {

    
      // Creates a button with this string as title                                                                                                                                             
      cocos2d::extension::ControlButton *button = standardButtonWithTitle(title.c_str());
      if (i == 0)
	{
	  button->setOpacity(500);
	  button->setColor(Color3B(150, 255, 0));
	}
      else if (i == 1)
	{
	  button->setOpacity(200);
	  button->setColor(Color3B(0, 255, 0));
	}
      else if (i == 2)
	{
	  button->setOpacity(100);
	  button->setColor(Color3B(0, 0, 255));
	}
         
      button->setPosition(Vec2 (total_width + button->getContentSize().width / 2, 0));
    
      auto actionBy = MoveBy::create(1, Vec2(0,800));
      auto actionByBack = actionBy->reverse();
      button->runAction( Sequence::create(actionBy, actionByBack, nullptr));
      layer->addChild(button);

      // Compute the size of the layer                                                                                                                                                          
      height = button->getContentSize().height;
      total_width += button->getContentSize().width;
      i++;
    }

  layer->setAnchorPoint(Vec2 (0.5, 0.5));
  layer->setContentSize(Size(total_width, height));
  layer->setPosition(Vec2(screenSize.width / 2.0f, 3.0f));//screenSize.height / 2.0f));
  //removeChild(layer);
  // Add the black background                                                                                                                                                                   
  /*auto background = cocos2d::extension::Scale9Sprite::create("extensions/buttonBackground.png");
    background->setContentSize(Size(total_width + 14, height + 14));
    background->setPosition(Vec2(screenSize.width / 2.0f, screenSize.height / 2.0f));
    addChild(background);    */
  //return true;  
}


cocos2d::extension::ControlButton *KariNivel1::standardButtonWithTitle(const char * title)
{
  /** Creates and return a button with a default background and title color. */
  auto backgroundButton = cocos2d::extension::Scale9Sprite::create("extensions/button.png");
  auto backgroundHighlightedButton = cocos2d::extension::Scale9Sprite::create("extensions/buttonHighlighted.png");

  auto titleButton = Label::createWithTTF(title, "fonts/Marker Felt.ttf", 30);

  titleButton->setColor(Color3B(159, 168, 176));

  cocos2d::extension::ControlButton *button = cocos2d::extension::ControlButton::create(titleButton, backgroundButton);
  button->setBackgroundSpriteForState(backgroundHighlightedButton, cocos2d::extension::Control::State::HIGH_LIGHTED);
  button->setTitleColorForState(Color3B::WHITE, cocos2d::extension::Control::State::HIGH_LIGHTED);

  return button;
}


void KariNivel1::repeatForever(Node* sender)
{
  Size visibleSize = Director::getInstance()->getVisibleSize();
  Vec2 origin = Director::getInstance()->getVisibleOrigin();
  auto actionBy = MoveBy::create(2, Vec2(0,410));
  auto actionByBack = actionBy->reverse();
  
  //auto repeat = RepeatForever::create( RotateBy::create(1.0f, 360) );
  //closeItem->runAction( Sequence::create(actionBy, actionByBack, nullptr));
  auto repeat = RepeatForever::create(MoveTo::create(1, Vec2(40,40)));
  sender->runAction(repeat);
  sender->setPosition(Vec2(origin.x + visibleSize.width - sender->getContentSize().width/2 ,
                                origin.y + sender->getContentSize().height/2));
}

void KariNivel1::menuCloseCallback(Ref* pSender)
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
