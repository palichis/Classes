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
  csvFile = new CCSVParse();
  csvFile->openFile("frases.csv");
  fila = rand() % csvFile->getRows();
  auto screenSize = Director::getInstance()->getWinSize();
  this->setTouchEnabled(true);
  schedule(schedule_selector(KariNivel1::stringSelection),1.0f);
  //  schedule(schedule_selector(KariNivel1::deleteWord),0.001f);
  return true;
}

void KariNivel1::stringSelection(float dt){
  auto size = Director::getInstance()->getWinSize();
  tag = tag + 1;
  //COLORES PARA RECUADROS DE TEXTO
  int coloruno = rand() % 255;
  int colordos = rand() % 255;
  int colortres = rand() % 255;
  //tamaño de pantalla
  auto screenSize = Director::getInstance()->getWinSize();

  /*auto layer1 = Node::create();
  layer1->setContentSize(Size(screenSize.width/3, 80));
  layer1->setPosition(Vec2((screenSize.width/3)/2, 0));

  auto layer2 = Node::create();
  layer2->setContentSize(Size(screenSize.width/3, 80));
  layer2->setPosition(Vec2((screenSize.width-(screenSize.width/3))-(screenSize.width/3)/2, 0));

  auto layer3 = Node::create();
  layer3->setContentSize(Size(screenSize.width/3, 80));
  layer3->setPosition(Vec2(screenSize.width-(screenSize.width/3)/2, 0));
  //addChild(layer1);
  
  addChild(layer1, positionWord);
  addChild(layer2, positionWord);
  addChild(layer3, positionWord);*/
  
  //lee de csv hasta que sea diferente de -, para no seleccionar vacios
  string text = "-";
  while (text == "-")
    {
      columna = rand() % csvFile->getCols();
      fila = rand() % csvFile->getRows();
      text = csvFile->getData(fila,columna);
    }
  button = standardButtonWithTitle(text.c_str());
  
  //  button->setOpacity(500);
  button->setColor(Color3B(coloruno, colordos, colortres));
  //  crea sprite con las dicenciones del boton
  Sprite* parent = Sprite::create("sprite.png",CCRectMake(0, 0, button->getContentSize().width, button->getContentSize().height));
  //  posiciona a boton y sprite en are derechade pantalla
  button->setPosition(Size(parent->getContentSize().width/2,parent->getContentSize().height/2));
  parent->setPosition(Vec2(((screenSize.width)/3)/2, 0));  
  //  agrego boton a sprint y pongo tag a sprint
  parent->addChild(button,-10);
  parent->setTag(tag);
  //  agrego sprint a vector
  target->pushBack(parent);
  
  //Create a "one by one" touch event listener (processes one touch at a time)
  auto listener1 = EventListenerTouchOneByOne::create();
  // Example of using a lambda expression to implement onTouchBegan event callback function
  listener1->onTouchBegan = [this](Touch* touch, Event* event){
    //llamo a evento para comparar posición de touch y eliminar sprite seleccionado
    onTouchBegan(touch, event);
    return true;
  };
  _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
  //creación de animación para desplazamiento de palabras
  auto actionBy = MoveTo::create(10, Vec2(((screenSize.width)/3)/2,850));
  //acción para cuando el Sprite culmine el movimiento
  auto actionMoveDone = 
  CallFuncN::create( this, callfuncN_selector(KariNivel1::spriteMoveFinished));
  //ejecución de acción
  parent->runAction( Sequence::create(actionBy, actionMoveDone,NULL));
  addChild(parent ,-100);
}

bool KariNivel1::onTouchBegan(Touch* touch, Event* event)
{
  for(auto sp : *target)
    {
      if (sp->boundingBox().containsPoint(Vec2(touch->getLocation().x,touch->getLocation().y)))
	{
	  this->removeChild(sp, true);
	  target->eraseObject(sp, true);
	}
    }
  return true;
}  

void KariNivel1::spriteMoveFinished(CCNode* sender)
{
  Sprite *sprite = (Sprite *)sender;
  this->removeChild(sprite, true);
  CCLOGWARN("%d",sprite->getTag());
  target->eraseObject(sprite, true);
}  

cocos2d::extension::ControlButton *KariNivel1::standardButtonWithTitle(const char * title)
  {
  /** Creates and return a button with a default background and title color. */
  auto backgroundButton = cocos2d::extension::Scale9Sprite::create("extensions/button.png");
  auto backgroundHighlightedButton = cocos2d::extension::Scale9Sprite::create("extensions/buttonHighlighted.png");

  auto titleButton = Label::createWithTTF(title, "fonts/ArchitectsDaughter.ttf", 35);

  titleButton->setColor(Color3B(159, 168, 176));

  cocos2d::extension::ControlButton *button = cocos2d::extension::ControlButton::create(titleButton, backgroundButton);
  button->setBackgroundSpriteForState(backgroundHighlightedButton, cocos2d::extension::Control::State::HIGH_LIGHTED);
  button->setTitleColorForState(Color3B::WHITE, cocos2d::extension::Control::State::HIGH_LIGHTED);

  return button;
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
