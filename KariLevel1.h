#ifndef __KariNivel1_SCENE_H__
#define __KariNivel1_SCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "CCSVParse.h"


class KariNivel1 : public cocos2d::Layer
{

public:
  // there's no 'id' in cpp, so we recommend returning the class instance pointer
static cocos2d::CCScene* createScene();
  cocos2d::extension::ControlButton *standardButtonWithTitle(const char * title);
  
  // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
  virtual bool init();  
  CCSVParse* csvFile;
  int columna;
  int fila;
  int tag;
  cocos2d::extension::ControlButton *button;
  cocos2d::Node *layer;
 // a selector callback
  void menuCloseCallback(cocos2d::Ref* pSender);
  void spriteMoveFinished(Node* sender);
  void touchDownAction(cocos2d::Object *sender, cocos2d::extension::Control::EventType controlEvent);
  void repeatForever(Node* sender);
  void stringSelection(float dt);
  
  
    // implement the "static create()" method manually
  CREATE_FUNC(KariNivel1);
};

#endif // __KariNivel1_SCENE_H__