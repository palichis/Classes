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
  
  schedule(schedule_selector(KariNivel1::stringSelection),1.0f);
  return true;
}

void KariNivel1::stringSelection(float dt){
  auto size = Director::getInstance()->getWinSize();
  tag = tag + 1;
  /* for (int i=0; i<csvFile->getRows(); ++i)
    {
      string strLine = "";
      for(int j=0; j<csvFile->getCols(); ++j)
        {
          strLine += csvFile->getData(i,j);
          strLine += "*";
        }
      CCLabelTTF* pLab = CCLabelTTF::create(strLine.c_str(),"fonts/ArchitectsDaughter.ttf",15);
      pLab->setPosition(ccp(size.width/2,size.height-90-i*30));
      this->addChild(pLab,2);
      }*/
  int coloruno = rand() % 255;
  int colordos = rand() % 255;
  int colortres = rand() % 255;
  //  CSVDocument doc;
  //  doc.Load("frases.csv");
  int positionWord = rand() % 3;
  auto screenSize = Director::getInstance()->getWinSize();
  //layer = Node::create();
  auto layer1 = Node::create();
  layer1->setContentSize(Size(screenSize.width/3, 80));
  layer1->setPosition(Vec2((screenSize.width/3)/2, 0));

  auto layer2 = Node::create();
  layer2->setContentSize(Size(screenSize.width/3, 80));
  layer2->setPosition(Vec2((screenSize.width-(screenSize.width/3))-(screenSize.width/3)/2, 0));

  auto layer3 = Node::create();
  layer3->setContentSize(Size(screenSize.width/3, 80));
  layer3->setPosition(Vec2(screenSize.width-(screenSize.width/3)/2, 0));
  //addChild(layer1);
  
  // Defines an array of title to create buttons dynamically                                                                                                                                    
  std::vector<std::string> vec;
  vec.push_back(std::to_string(positionWord));
  vec.push_back("Variable");
  vec.push_back("Size");
  vec.push_back("NONES");
  
  addChild(layer1, positionWord);
  addChild(layer2, positionWord);
  addChild(layer3, positionWord);
  
  double total_width = 0, height = 0;
  string text = "-";
  while (text == "-")
    {
      columna = rand() % csvFile->getCols();
      fila = rand() % csvFile->getRows();
      text = csvFile->getData(fila,columna);
    }
  button = standardButtonWithTitle(text.c_str());
  int i = 0;
  //button->setOpacity(500);
  button->setColor(Color3B(coloruno, colordos, colortres));
  /*for (auto& title : vec)
    {
    
    
    // Creates a button with this string as title                                                                                                                                             
    cocos2d::extension::ControlButton *button = standardButtonWithTitle(title.c_str());
    if (i == 0)
	{
    button->setOpacity(500);
    button->setColor(Color3B(positionWord1   , positionWord2, positionWord));
	}
    else if (i == 1)
	{
    button->setOpacity(200);
    button->setColor(Color3B(positionWord   , positionWord2, positionWord1));
	}
    else if (i == 2)
	{
    button->setOpacity(100);
    button->setColor(Color3B(positionWord2   , positionWord, positionWord1));
    }*/
  
  //button->setPosition(Vec2(screenSize.width/2,0));
  Sprite* parent = Sprite::create();
  parent->addChild(button);
  parent->setTag(tag);
  //CCLOGWARN("%d",parent->getTag());
  auto actionBy = MoveTo::create(10, Vec2(0,350));
  //auto actionByBack = actionBy->reverse();
  auto actionMoveDone = 
  CallFuncN::create( this, callfuncN_selector(KariNivel1::spriteMoveFinished));
  parent->runAction( Sequence::create(actionBy, actionMoveDone,NULL));
  /*switch(positionWord)
    {
    case 0: layer1->addChild(parent);break;
    case 1: layer2->addChild(parent);break;
    case 2: layer3->addChild(parent);break;
    }*/
  addChild(parent);
  //layer1->addChild(button);
  /*
  // Compute the size of the layer                                                                                                                                                          
  height = button->getContentSize().height;
  total_width += button->getContentSize().width;
  i++;
  }*/
  
  //layer1->setAnchorPoint(Vec2 (0.5, 0.5));
  //layer1->setContentSize(Size(total_width, height));
  //layer1->setPosition(Vec2(screenSize.width / 2.0f, 3.0f));//screenSize.height / 2.0f));
  //removeChild(layer);
  // Add the black background                                                                                                                                                                   
  /*auto background = cocos2d::extension::Scale9Sprite::create("extensions/buttonBackground.png");
    background->setContentSize(Size(total_width + 14, height + 14));
    background->setPosition(Vec2(screenSize.width / 2.0f, screenSize.height / 2.0f));
    addChild(background);    */
  //return true;  
  string fila1 = "algo";
  button->addTargetWithActionForControlEvents(this, cccontrol_selector(KariNivel1::touchDownAction), cocos2d::extension::Control::EventType::TOUCH_DOWN);
  //layer->removeChild(button);
}
  
  void KariNivel1::touchDownAction(Object *sender, cocos2d::extension::Control::EventType controlEvent)
{
  //_displayValueLabel->setString(String::createWithFormat("Touch Up Inside.")->getCString());
  //this->removeChild(layer,true);
  //CCLOGWARN("");
  
  Sprite *sprite = (Sprite *)sender;
  string *st = (string *)sender;
  this->removeChild(sprite, true);
  char buffer[1];
  sprintf (buffer, "%d", sprite->getTag());
  //int a = sprite->getTag();
  //char* b = a;
  CCLOGWARN("%d, %s",sprite->getTag(),st);
}

  
  // cpp with cocos2d-x
void KariNivel1::spriteMoveFinished(CCNode* sender)
{
  Sprite *sprite = (Sprite *)sender;
  this->removeChild(sprite, true);
  CCLOGWARN("%d",sprite->getTag());
}  

  cocos2d::extension::ControlButton *KariNivel1::standardButtonWithTitle(const char * title)
  {
  /** Creates and return a button with a default background and title color. */
  auto backgroundButton = cocos2d::extension::Scale9Sprite::create("extensions/button.png");
  auto backgroundHighlightedButton = cocos2d::extension::Scale9Sprite::create("extensions/buttonHighlighted.png");

  auto titleButton = Label::createWithTTF(title, "fonts/ArchitectsDaughter.ttf", 30);

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
