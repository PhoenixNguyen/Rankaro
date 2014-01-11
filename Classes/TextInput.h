//============================================================================
// Name        : TextInput.h
// Author      : HP
// Version     :
// Copyright   : Your copyright notice
// Description : TextInput in Cocos2d x C++, Ansi-style
//============================================================================

#ifndef __TEXT_INPUT_H__
#define __TEXT_INPUT_H__


#include "cocos2d.h"
#include "text_input_node\CCIMEDelegate.h"
#include "CheckinLayer.h"

class KeyboardNotificationLayer;

/**
@brief    TextInputTest for retain prev, reset, next, main menu buttons.
*/
class TextInputTest : public cocos2d::Layer
{
    KeyboardNotificationLayer * _notificationLayer;
public:
    TextInputTest();

    void restartCallback(cocos2d::Object* sender);
    void nextCallback(cocos2d::Object* sender);
    void backCallback(cocos2d::Object* sender);

    std::string title();
    void addKeyboardNotificationLayer(KeyboardNotificationLayer * layer);
    
    virtual void onEnter();
		std::string subtitle();

};

//////////////////////////////////////////////////////////////////////////
// KeyboardNotificationLayer for test IME keyboard notification.
//////////////////////////////////////////////////////////////////////////

class KeyboardNotificationLayer : public cocos2d::Layer, public cocos2d::IMEDelegate
{
public:
    KeyboardNotificationLayer();

    virtual std::string subtitle() = 0;
    virtual void onClickTrackNode(bool bClicked) = 0;

    virtual void registerWithTouchDispatcher();
    virtual void keyboardWillShow(cocos2d::IMEKeyboardNotificationInfo& info);

    // Layer
    virtual bool ccTouchBegan(cocos2d::Touch  *touch, cocos2d::Event  *event);
    virtual void ccTouchEnded(cocos2d::Touch  *touch, cocos2d::Event  *event);
		static cocos2d::Node * _trackNode;
protected:
    
    cocos2d::Point  _beginPos;
};

//////////////////////////////////////////////////////////////////////////
// TextFieldTTFDefaultTest for test TextFieldTTF default behavior.
//////////////////////////////////////////////////////////////////////////

class TextFieldTTFDefaultTest : public KeyboardNotificationLayer
{
public:
    // KeyboardNotificationLayer
    virtual std::string subtitle();
    virtual void onClickTrackNode(bool bClicked);

    // Layer
    virtual void onEnter();
};

//////////////////////////////////////////////////////////////////////////
// TextFieldTTFActionTest
//////////////////////////////////////////////////////////////////////////

class TextFieldTTFActionTest : public KeyboardNotificationLayer, public cocos2d::TextFieldDelegate
{
    cocos2d::TextFieldTTF *    _textField;
    cocos2d::Action *          _textFieldAction;
    bool                _action;
    int                 _charLimit;       // the textfield max char limit

public:
    void callbackRemoveNodeWhenDidAction(Node * node);

    // KeyboardNotificationLayer
    virtual std::string subtitle();
    virtual void onClickTrackNode(bool bClicked);

    // Layer
    virtual void onEnter();
    virtual void onExit();

    // TextFieldDelegate
    virtual bool onTextFieldAttachWithIME(cocos2d::TextFieldTTF * sender);
    virtual bool onTextFieldDetachWithIME(cocos2d::TextFieldTTF * sender);
    virtual bool onTextFieldInsertText(cocos2d::TextFieldTTF * sender, const char * text, int nLen);
    virtual bool onTextFieldDeleteBackward(cocos2d::TextFieldTTF * sender, const char * delText, int nLen);
    virtual bool onDraw(cocos2d::TextFieldTTF * sender);
};

class TextInputTestScene : public cocos2d::Scene
{
public:
    cocos2d::Layer* runThisTest();
		const char* getText();
};

#endif    // __TEXT_INPUT_TEST_H__
