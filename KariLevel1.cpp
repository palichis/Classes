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
  //carga de archivo CSV
  csvFile = new CCSVParse();
  csvFile->openFile("frases.csv");
  auto screenSize = Director::getInstance()->getWinSize();
  auto fondo = Sprite::create("sprites/fondo.png");
  fondo->setContentSize(Size(screenSize.width,screenSize.height));
  fondo->setPosition(Vec2(screenSize.width/2,screenSize.height/2));
  //sprint barra superior
  auto barrasuperior = Sprite::create("sprites/barra1.png");
  //fondo->setContentSize(Size(screenSize.width,screenSize.height));
  barrasuperior->setPosition(Vec2(screenSize.width/2,screenSize.height));
  puntaje = 0;
  scoreLabel = CCLabelTTF::create(" ", "fonts/ArchitectsDaughter.ttf", 30, 
                                  CCSizeMake(250, 50), kCCTextAlignmentRight);
  char text[256];
  sprintf(text,"Puntaje %d",puntaje);
  scoreLabel->setString(text);
  scoreLabel->setColor(ccc3(0,0,0));
  scoreLabel->setPosition(Vec2(screenSize.width-130,screenSize.height-20));
  //selección de fila para completar la frase
  fila = rand() % csvFile->getRows();
  //add texto frace a seleccionar
  frase = Node::create(); 
  //frase->setPosition(Vec2 (-100,-100));
  int height = 0,total_width = 0;
  string word = "-";
  fila = 0;
  int pos;
  if (csvFile->getCols() > 14)
    {
      pos = 20;
    }
  for (int j=0; j<csvFile->getCols(); ++j)
    { 
      // Creates a button with this string as title
      word = csvFile->getData(fila,j);    
      if (word != "-")
        {
          cocos2d::extension::ControlButton *button1 = fraseButtonWithTitle(word.c_str());
          //CCLOGWARN("%s", word);
          //button1->setOpacity(50);
          button1->setColor(Color3B(255, 255, 255));
          button1->setPosition(Vec2 ((total_width + button1->getContentSize().width / 2), button1->getContentSize().height+pos));
          frase->addChild(button1);
          // Compute the size of the layer                                                                                                                                                                       
          height = button1->getContentSize().height;
          total_width += button1->getContentSize().width-12;
          if (j == 13)
            {
              pos = pos - 25;
              total_width = 0;
            }
        }
    }
  frase->setAnchorPoint(Vec2 (0.5, 0.5));
  frase->setContentSize(Size(0, height));
  //frase->setPosition(Vec2(100,1000));
  this->addChild(fondo);
  this->addChild(scoreLabel,10);
  this->addChild(barrasuperior,9);
  this->setTouchEnabled(true);
  this->addChild(frase, 100);
  schedule(schedule_selector(KariNivel1::stringSelection),1.0f);
  //  schedule(schedule_selector(KariNivel1::deleteWord),0.001f);
  return true;
}

void KariNivel1::stringSelection(float dt)
{
  auto screenSize = Director::getInstance()->getWinSize();
  words((screenSize.width/3)/2,0);
  words((screenSize.width-(screenSize.width/3))-(screenSize.width/3)/2,0);
  words(screenSize.width-(screenSize.width/3)/2,0);
}

void KariNivel1::words(int w, int h)
{
  auto size = Director::getInstance()->getWinSize();
  tag = tag + 1;
  //COLORES PARA RECUADROS DE TEXTO
  int coloruno = rand() % 255;
  int colordos = rand() % 255;
  int colortres = rand() % 255;
  //tamaño de pantalla
  auto screenSize = Director::getInstance()->getWinSize();
  //lee de csv hasta que sea diferente de -, para no seleccionar vacios
  string text = "-";
  int col, fil;
  while (text == "-")
    {
      col = rand() % csvFile->getCols();
      fil = rand() % csvFile->getRows();
      if (tag%3 == 0)
        text = csvFile->getData(fila,col);
      else
        text = csvFile->getData(fil,col);
    }
  button = standardButtonWithTitle(text.c_str());
  
  //  button->setOpacity(500);
  button->setColor(Color3B(coloruno, colordos, colortres));
  //  crea sprite con las dicenciones del boton
  Sprite* parent = Sprite::create("sprite.png",CCRectMake(0, 0, button->getContentSize().width, button->getContentSize().height));
  //  posiciona a boton y sprite en are derechade pantalla
  button->setPosition(Size(parent->getContentSize().width/2,parent->getContentSize().height/2));
  parent->setPosition(Vec2(w, h));  
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
  auto actionBy = MoveTo::create(10, Vec2(w,850));
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
          CCSprite *buton = static_cast<CCSprite*>(sp);
          buton->setColor(Color3B(0, 0, 0));
          //sp->addChild(buton);
          CCLOGWARN("%d",sp->getTag());
          auto actionBy = MoveTo::create(0.5f, Vec2(touch->getLocation().x,-20));
          //acción para cuando el Sprite culmine el movimiento
          auto actionMoveDone = 
            CallFuncN::create( this, callfuncN_selector(KariNivel1::spriteMoveFinished));
          //ejecución de acción
          //sp->runAction( Sequence::create(actionBy, actionMoveDone,NULL));
          //this->removeChild(sp, true);
          target->eraseObject(sp, true);
          puntaje = puntaje + 10;
          char text[256];
          sprintf(text,"Puntaje %d",puntaje);
          scoreLabel->setString(text);
        }
    }
  return true;
}  

void KariNivel1::spriteMoveFinished(Node* sender)
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

cocos2d::extension::ControlButton *KariNivel1::fraseButtonWithTitle(const char * title)
  {
  /** Creates and return a button with a default background and title color. */
  auto backgroundButton = cocos2d::extension::Scale9Sprite::create("sprite.png");
  //auto backgroundHighlightedButton = cocos2d::extension::Scale9Sprite::create("extensions/buttonHighlighted.png");

  auto titleButton = Label::createWithTTF(title, "fonts/ArchitectsDaughter.ttf", 19);

  //titleButton->setColor(Color3B(159, 168, 176));

  cocos2d::extension::ControlButton *button = cocos2d::extension::ControlButton::create(titleButton, backgroundButton);
  //button->setBackgroundSpriteForState(backgroundHighlightedButton, cocos2d::extension::Control::State::HIGH_LIGHTED);
  //button->setTitleColorForState(Color3B::WHITE, cocos2d::extension::Control::State::HIGH_LIGHTED);
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
