//
//  SocketIOTest.cpp
//  TestCpp
//
//  Created by Chris Hannon on 6/26/13.
//
//


#include "ConnectServer.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include <sstream>

using namespace rapidjson;

USING_NS_CC;
USING_NS_CC_EXT;

ConnectionLayer::ConnectionLayer(void)
	: mClient(NULL)
	, _sioEndpoint(NULL)
{
	//set the clients to NULL until we are ready to connect
	newConnect(NULL);
	

}


ConnectionLayer::~ConnectionLayer(void)
{
}

void ConnectionLayer::newConnect(cocos2d::Object *sender)
{
	//create a client by using this static method, url does not need to contain the protocol
	mClient = SocketIO::connect(*this, "http://localhost:3000"); //"ws://channon.us:3000"http://localhost:3000
	//you may set a tag for the client for reference in callbacks
	mClient->setTag("Test Client");

	//Nhan nhung user khoi tao truoc
	mClient->on("init", CC_CALLBACK_2(ConnectionLayer::receiverUsername, this));
	//nhan user gan nhat
	mClient->on("username", CC_CALLBACK_2(ConnectionLayer::lastUsername, this));

	//nhan trang thai cua nhung user khoi tao truoc
	mClient->on("initState", CC_CALLBACK_2(ConnectionLayer::receiverState, this));
	//nhan trang thai cua user vua khoi tao
	mClient->on("state", CC_CALLBACK_2(ConnectionLayer::lastState, this));

	//Start game and receiver random number
	mClient->on("randomNumber", CC_CALLBACK_2(ConnectionLayer::receiverNumber, this));

	//Receiver position
	mClient->on("position", CC_CALLBACK_2(ConnectionLayer::receiverPosition, this));

	//Receiver End game
	mClient->on("endGame", CC_CALLBACK_2(ConnectionLayer::endGame, this));
	
}

void ConnectionLayer::regUsername(std::string pName)
{
	//Send username to server
	if(mClient != NULL) 
		mClient->emit("username","{\"name\":\"" + pName + "\"}");
		//mClient->emit("username","[{\"ECHO\":\"Hello server\"}]");

	

}

void ConnectionLayer::sendState(std::string pID)
{
	//Send username to server
	if(mClient != NULL) 
    //name: state, id: id
		mClient->emit("state","[{\"name\":\"1\",\"id\":\""+pID+"\"}]");
		
}

void ConnectionLayer::sendPosition(cocos2d::Object *sender)
{
	//Send username to server
	if(mClient != NULL) 
		mClient->emit("position","[{\"id\":\"923\",\"pos\":\"654\"}]");
		

}


//////// USER ///////////////////////////////////////////////////////////
void ConnectionLayer::receiverUsername(SIOClient *client, const std::string& data) {

	//log("ALL USERNAME CONNECTED: %s", data.c_str());
  //Init lấy các user đăng ký trước nên phải khởi tạo đầu tiên đặt ở RoomLayer class!
  if(!data.empty())
  {
    exportListData(data, mUsername);
    
  }

}

void ConnectionLayer::lastUsername(SIOClient *client, const std::string& data) {

	//log("LAST USERNAME CONNECTED: %s", data.c_str());
  if(!data.empty())
  {
    std::map<std::string, std::string> username;
    exportLastData(data, username);

    //CCLog("Name: %s",(*username.begin()).second.c_str());
    RoomLayer::setLastUsername((*username.begin()).second.c_str(), (*username.begin()).first.c_str());
  }
	
}



///////  STATE ////////////////////////////////////////////////////////
void ConnectionLayer::receiverState(SIOClient *client, const std::string& data) {

	log("ALL STATE USERNAME: %s", data.c_str());
  //Init lấy các user đăng ký trước nên phải khởi tạo đầu tiên đặt ở RoomLayer class!
  if(!data.empty())
  {
    exportListData(data, mState);
    
  }
}

void ConnectionLayer::lastState(SIOClient *client, const std::string& data) {

	log("LAST STATE USERNAME: %s", data.c_str());
  if(!data.empty())
  {
    std::map<std::string, std::string> state;
    exportLastData(data, state);

    //CCLog("Name: %s",(*username.begin()).second.c_str());
    RoomLayer::setLastState((*state.begin()).first.c_str());
  }
}

////////  Receiver number ///////////////////////////////////////////////////////////
void ConnectionLayer::receiverNumber(SIOClient *client, const std::string& data) {

	log("START GAME AND RECEIVER NUMBER: %s", data.c_str());
	ConnectionLayer::setNumber(1);

}

////////  Receiver position ///////////////////////////////////////////////////////////
void ConnectionLayer::receiverPosition(SIOClient *client, const std::string& data) {

	log("RECEIVER POSITION: %s", data.c_str());
	
}

////////  Receiver end game ///////////////////////////////////////////////////////////
void ConnectionLayer::endGame(SIOClient *client, const std::string& data) {

	log("END GAME: %s", data.c_str());

}
void ConnectionLayer::echotest(SIOClient *client, const std::string& data) {

	log("SocketIOTestLayer::echotest called with data: %s", data.c_str());

	std::stringstream s;
	s << client->getTag() << " received event echotest with data: " << data.c_str();	

	//_sioClientStatus->setString(s.str().c_str());

}









void ConnectionLayer::onMenuTestClientDisconnectClicked(cocos2d::Object *sender)
{

	if(mClient != NULL) mClient->disconnect();

}



// Delegate methods

void ConnectionLayer::onConnect(cocos2d::extension::SIOClient* client)
{
	log("SocketIOTestLayer::onConnect called");

	std::stringstream s;
	s << client->getTag() << " connected!";	
	//_sioClientStatus->setString(s.str().c_str());

}

void ConnectionLayer::onMessage(cocos2d::extension::SIOClient* client, const std::string& data)
{
	log("SocketIOTestLayer::onMessage received: %s", data.c_str());
	
	std::stringstream s;
	s << client->getTag() << " received message with content: " << data.c_str();	
	//_sioClientStatus->setString(s.str().c_str());

}

void ConnectionLayer::onClose(cocos2d::extension::SIOClient* client)
{
	log("SocketIOTestLayer::onClose called");

	std::stringstream s;
	s << client->getTag() << " closed!";	
	//_sioClientStatus->setString(s.str().c_str());

	//set the local pointer to NULL or connect to another client
	//the client object will be released on its own after this method completes
	if(client == mClient) {
		
		mClient = NULL;
	} else if(client == _sioEndpoint) {
		
		_sioEndpoint = NULL;
	}
	
}

void ConnectionLayer::onError(cocos2d::extension::SIOClient* client, const std::string& data)
{
	log("SocketIOTestLayer::onError received: %s", data.c_str());

	std::stringstream s;
	s << client->getTag() << " received error with content: " << data.c_str();	
	//_sioClientStatus->setString(s.str().c_str());
}



void runSocketIOTest()
{
    auto scene = Scene::create();
    auto layer = new ConnectionLayer();
    scene->addChild(layer);
    
    Director::getInstance()->replaceScene(scene);
    layer->release();
}
/**
*
*
*Return list
**/
//void ConnectionLayer::exportList(std::string pData, std::map<std::string, std::string>& pList)
//{
//	std::map<std::string, std::string> username;
//	Document doc;
//	pData = " {\"name\":\"init\",\"args\":[[{\"name\":\"Duy Phuong\",\"id\":\"jDG33J_vilx5RHWvkLan\"},{\"name\":\"Hoang Phuong\",\"id\":\"TUd5gXsInDnxt_COkLao\"},{\"name\":\"Duy Phuong\",\"id\":\"_DYMTQjePZsAImTRkLap\"}]]} " ;
//	std::size_t n = std::count(pData.begin(), pData.end(), ':');
//	log("So lan lap nam la: %d", n/2 - 1);
//	
//	//std::count_if (s.begin(), s.end(), _1 == '_') 
//		//doc.Parse<0>(data.c_str()); //
//	doc.Parse<0>(pData.c_str() );
//	
//	SizeType j = 0;
//	for (SizeType i = 0; i < (n/2 - 1); i++){
//		//Gia tri 0 cua mang
//		Value& name = doc["args"][j][i]["name"];
//		log("NAME %d: %s", i + 1, name.GetString() );
//		Value& id = doc["args"][j][i]["id"];
//		log("ID %d: %s", i + 1, id.GetString() );
//
//		username.insert(std::pair<std::string,std::string>(id.GetString(), name.GetString() ));
//		
//	}
//
//	for( std::map<std::string, std::string>::iterator ii=username.begin(); ii!=username.end(); ++ii)
//	   {
//	       //cout << (*ii).first << ": " << (*ii).second << endl;
//		   log("MAPPPPPPPPPPPPPPP ID: %s NAME: %s", (*ii).first.c_str(), (*ii).second.c_str());
//	   }
//}

//void ConnectionLayer::exportLast(std::string pData, std::map<std::string, std::string>& pList)
//{
//	std::map<std::string, std::string> username;
//	Document doc;
//	pData = " {\"name\":\"username\",\"args\":[{\"name\":\"Duy Phuong\",\"id\":\"nOJqkJ2_c75tgP6Zlvyh\"}]} " ;
//	//std::size_t n = std::count(pData.begin(), pData.end(), ':');
//	//log("So lan lap nam la: %d", n/2 - 1);
//	
//	//std::count_if (s.begin(), s.end(), _1 == '_') 
//		//doc.Parse<0>(data.c_str()); //
//	doc.Parse<0>(pData.c_str() );
//	
//	SizeType j = 0;
//	//for (SizeType i = 0; i < (n/2 - 1); i++){
//		//Gia tri 0 cua mang
//		Value& name = doc["args"][j]["name"];
//		log("LAST THE NAME %s", name.GetString() );
//		Value& id = doc["args"][j]["id"];
//		log("LAST THE ID %s", id.GetString() );
//
//		username.insert(std::pair<std::string,std::string>(id.GetString(), name.GetString() ));
//		
//	//}
//
//	for( std::map<std::string, std::string>::iterator ii=username.begin(); ii!=username.end(); ++ii)
//	   {
//	       //cout << (*ii).first << ": " << (*ii).second << endl;
//		   log("MAPPPPPPPPPPPPPPP ID: %s NAME: %s", (*ii).first.c_str(), (*ii).second.c_str());
//	   }
//}


/**
*
*
*Return list
**/

void ConnectionLayer::exportListData(std::string pData, std::map<std::string, std::string>& pList)
{
	//std::map<std::string, std::string> username;
	Document doc;
	//pData = " {\"name\":\"init\",\"args\":[[{\"name\":\"Duy Phuong\",\"id\":\"jDG33J_vilx5RHWvkLan\"},{\"name\":\"Hoang Phuong\",\"id\":\"TUd5gXsInDnxt_COkLao\"},{\"name\":\"Duy Phuong\",\"id\":\"_DYMTQjePZsAImTRkLap\"}]]} " ;
	std::size_t n = std::count(pData.begin(), pData.end(), ':');
	//log("So lan lap name la: %d", n/2 - 1);
	
	doc.Parse<0>(pData.c_str() );
	
	int j = 0;
	for (int i = (n/2 - 1)-1; i > -1 ; i--){
		//Gia tri 0 cua mang
		Value& name = doc["args"][j][i]["name"];
		log("NAME %d: %s", i + 1, name.GetString() );
		Value& id = doc["args"][j][i]["id"];
		log("ID %d: %s", i + 1, id.GetString() );

		pList.insert(std::pair<std::string,std::string>(id.GetString(), name.GetString() ));
		
	}

	//for( std::map<std::string, std::string>::iterator ii=pList.begin(); ii!=pList.end(); ++ii)
	//   {
	//       //cout << (*ii).first << ": " << (*ii).second << endl;
	//	   log("MAPPPPPPPPPPPPPPP ID: %s NAME: %s", (*ii).first.c_str(), (*ii).second.c_str());
	//   }
}


void ConnectionLayer::exportLastData(std::string pData, std::map<std::string, std::string>& pList)
{
	Document doc;
	//pData = " {\"name\":\"username\",\"args\":[{\"name\":\"Duy Phuong\",\"id\":\"nOJqkJ2_c75tgP6Zlvyh\"}]} " ;
	
	doc.Parse<0>(pData.c_str() );
	
	SizeType j = 0;
	//for (SizeType i = 0; i < (n/2 - 1); i++){
		//Gia tri 0 cua mang
		Value& name = doc["args"][j]["name"];
		log("LAST THE NAME %s", name.GetString() );
		Value& id = doc["args"][j]["id"];
		log("LAST THE ID %s", id.GetString() );

		pList.insert(std::pair<std::string,std::string>(id.GetString(), name.GetString() ));
    
	//}

	//for( std::map<std::string, std::string>::iterator ii=pList.begin(); ii!=pList.end(); ++ii)
	//   {
	//       //cout << (*ii).first << ": " << (*ii).second << endl;
	//	   log("MAPPPPPPPPPPPPPPP ID: %s NAME: %s", (*ii).first.c_str(), (*ii).second.c_str());
	//   }
}