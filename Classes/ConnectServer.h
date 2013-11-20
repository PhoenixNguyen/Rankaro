//
//  SocketIOTest.h
//  TestCpp
//
//  Created by Chris Hannon on 6/26/13.
//
//
#ifndef __connectserver__
#define __connectserver__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "network/SocketIO.h"
#include "RoomLayer.h"

class ConnectionLayer
	: public cocos2d::Layer
	, public cocos2d::extension::SocketIO::SIODelegate
{

  CC_SYNTHESIZE(std::string, mLastUsername, LastUsername);
  CC_SYNTHESIZE(int, mNumber, Number);
  static int mTurn;
public:
  std::map<std::string, std::string> mUsername;
  std::map<std::string, std::string> mState;
  //static std::string mLastUsername;
	ConnectionLayer(void);
	virtual ~ConnectionLayer(void);

	virtual void onConnect(cocos2d::extension::SIOClient* client);
    virtual void onMessage(cocos2d::extension::SIOClient* client, const std::string& data);
    virtual void onClose(cocos2d::extension::SIOClient* client);
    virtual void onError(cocos2d::extension::SIOClient* client, const std::string& data);

	void toExtensionsMainLayer(cocos2d::Object *sender);
	
	void newConnect(cocos2d::Object *sender);
	void onMenuTestMessageClicked(cocos2d::Object *sender);
	void onMenuTestEventClicked(cocos2d::Object *sender);
	void onMenuTestClientDisconnectClicked(cocos2d::Object *sender);

	void onMenuSIOEndpointClicked(cocos2d::Object *sender);
	void onMenuTestMessageEndpointClicked(cocos2d::Object *sender);
	void onMenuTestEventEndpointClicked(cocos2d::Object *sender);
	void onMenuTestEndpointDisconnectClicked(cocos2d::Object *sender);


	
	void echotest(cocos2d::extension::SIOClient *client, const std::string& data);

	cocos2d::extension::SIOClient *mClient, *_sioEndpoint;
	
	//Send and receiver username
	void regUsername(std::string pName);
	void receiverUsername(cocos2d::extension::SIOClient *client, const std::string& data);
	void lastUsername(cocos2d::extension::SIOClient *client, const std::string& data);

	//state
	void sendState(std::string pName);
	void receiverState(cocos2d::extension::SIOClient *client, const std::string& data);
	void lastState(cocos2d::extension::SIOClient *client, const std::string& data);

	//receiver number
	void receiverNumber(cocos2d::extension::SIOClient *client, const std::string& data);


	//receiver position
	void sendPosition(std::string pID, std::string pNumber, std::string pRow, std::string pCoLumn);
	void receiverPosition(cocos2d::extension::SIOClient *client, const std::string& data);

	//receiver End game
	void endGame(cocos2d::extension::SIOClient *client, const std::string& data);

	//return List data
  void exportListData(std::string pData, std::map<std::string, std::string>& pList);
	//void exportList(std::string pData, std::map<std::string, std::string>& pList);

	//return last data
  void exportLastData(std::string pData, std::map<std::string, std::string>& pList);
	//void exportLast(std::string pData, std::map<std::string, std::string>& pList);

	//return last data - Number
  void exportLastData(std::string pData, int& pReturn);

  //return last data - position
  void exportLastData(std::string pData, std::string& pID, std::string& pNumber, std::string& pRow, std::string& pColumn);

};

void runSocketIOTest();

#endif /* defined(__TestCpp__SocketIOTest__) */