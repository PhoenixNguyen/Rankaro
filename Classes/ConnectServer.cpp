//
//  SocketIOTest.cpp
//  TestCpp
//
//  Created by Chris Hannon on 6/26/13.
//
//

#include <algorithm>
#include "ConnectServer.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include <sstream>

using namespace rapidjson;

USING_NS_CC;
USING_NS_CC_EXT;

bool* ConnectionLayer::mListStatus = NULL;

ConnectionLayer::ConnectionLayer(void)
	: mClient(NULL)
	, _sioEndpoint(NULL)
{
	//set the clients to NULL until we are ready to connect
	newConnect(NULL);
  setTurn(0);
	

}


ConnectionLayer::~ConnectionLayer(void)
{
}

void ConnectionLayer::newConnect(cocos2d::Object *sender)
{
	//create a client by using this static method, url does not need to contain the protocol
	mClient = SocketIO::connect(*this, "http://localhost:8080"); //"ws://channon.us:3000"http://localhost:3000 //http://socketiodemo.nodejitsu.com:80
	//you may set a tag for the client for reference in callbacks
	mClient->setTag("Test Client");

	//Nhan nhung user khoi tao truoc
	mClient->on("init", CC_CALLBACK_2(ConnectionLayer::receiverUsername, this));
	//nhan user gan nhat
	mClient->on("username", CC_CALLBACK_2(ConnectionLayer::lastUsername, this));

  //trang thai room
	mClient->on("status", CC_CALLBACK_2(ConnectionLayer::roomStatus, this));
  //number in room
  mClient->on("countuser", CC_CALLBACK_2(ConnectionLayer::numberInRoom, this));

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

  //Receiver player disconnect
	mClient->on("returnroom", CC_CALLBACK_2(ConnectionLayer::receiverDisconnect, this));

  //Receiver player out room
	mClient->on("outroom", CC_CALLBACK_2(ConnectionLayer::receiverOutRoom, this));
	
}

void ConnectionLayer::sendEndGame()
{
  if(mClient != NULL) 
		mClient->emit("endgame","{\"name\":\"1\"}");
}
void ConnectionLayer::regUsername(std::string pName)
{
	//Send username to server
	if(mClient != NULL) 
		mClient->emit("username","{\"name\":\"" + pName + "\"}");
		//mClient->emit("username","[{\"ECHO\":\"Hello server\"}]");

	

}

void ConnectionLayer::regRoom(std::string pRoom)
{
	//Send username to server
	if(mClient != NULL) 
		mClient->emit("room","{\"room\":\"" + pRoom + "\"}");
		//mClient->emit("username","[{\"ECHO\":\"Hello server\"}]");

	

}

void ConnectionLayer::sendState(std::string pID)
{
	//Send username to server
	if(mClient != NULL) 
    //name: state, id: id
		mClient->emit("state","[{\"name\":\"1\",\"id\":\""+pID+"\"}]");
		
}

void ConnectionLayer::sendPosition(std::string pID, std::string pNumber, std::string pRow, std::string pCoLumn)
{
	//Send username to server
	if(mClient != NULL) 
    mClient->emit("position","[{\"id\":\""+pID+"\",\"number\":"+pNumber+",\"row\":"+pRow+",\"column\":"+pCoLumn+"}]");
		

}


//////// USER ///////////////////////////////////////////////////////////
void ConnectionLayer::receiverUsername(SIOClient *client, const std::string& data) {

	log("ALL USERNAME CONNECTED: %s", data.c_str());
  //Init lấy các user đăng ký trước nên phải khởi tạo đầu tiên đặt ở RoomLayer class!

  //Add rommdisplay
  if(!data.empty())
  {
    exportListData(data, mUsername);
    RoomLayer::setFirstUsername();
  }

}

void ConnectionLayer::lastUsername(SIOClient *client, const std::string& data) {

	//log("LAST USERNAME CONNECTED: %s", data.c_str());
  if(!data.empty())
  {
    //RoomDisplayLayer::createPlayer();
    //Add rommdisplay
    std::map<std::string, std::string> username;
    exportLastData(data, username);

    //CCLog("Name: %s",(*username.begin()).second.c_str());
    RoomLayer::setLastUsername((*username.begin()).second.c_str(), (*username.begin()).first.c_str());
  }
	
}

void ConnectionLayer::roomStatus(SIOClient *client, const std::string& data)
{
  log("ALL Status: %s", data.c_str());
  if(!data.empty())
  {
    //Lay ve list room status
    exportListData(data, mListStatus);

    //Neu la this player thi return neu khong se loi vi dang choi==
    if(RoomDisplayLayer::getRoomStatus())
      return;
    RoomDisplayLayer::roomStatus(mListStatus);

    //RoomLayer::roomFull();
  }
}

void ConnectionLayer::numberInRoom(SIOClient *client, const std::string& data)
{
  log("Number in room: %s", data.c_str());
  if(!data.empty())
  {
    //Lay ve list room status
    exportListData(data, mListNumberInRoom);

    //Neu la this player thi return neu khong se loi vi dang choi==
    if(RoomDisplayLayer::getRoomStatus())
      return;
    RoomDisplayLayer::addNumberInRoom(mListNumberInRoom);

    //RoomLayer::roomFull();
  }
}
///////  STATE ////////////////////////////////////////////////////////
void ConnectionLayer::receiverState(SIOClient *client, const std::string& data) {


	log("ALL STATE USERNAME: %s", data.c_str());
  //Init lấy các user đăng ký trước nên phải khởi tạo đầu tiên đặt ở RoomLayer class!
  if(!data.empty())
  {
    exportListData(data, mState);
    RoomLayer::setFirstState();
    
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
  if(!data.empty())
  {
    //Neu khong dang choi thi return - khong set number
    if(!RoomDisplayLayer::getRoomStatus())
      return;

    int number;
    exportLastData(data, number);

    CCLog("TURN: %d", getTurn());
    if(getTurn() == 0)
      RoomLayer::startGame();
	   
    GameLayer::setNumber(number);

    //Tang so turn. turn hien tai = mTurn -1
    CCLog("TURN2: %d", getTurn());
    setTurn(getTurn()+1);
    CCLog("TURN3: %d", getTurn());
  }
}

////////  Receiver position ///////////////////////////////////////////////////////////
void ConnectionLayer::receiverPosition(SIOClient *client, const std::string& data) {

	log("RECEIVER POSITION: %s", data.c_str());
  if(!data.empty())
  {
    std::string id;
    int number;
    int row;
    int column;

    exportLastData(data, id, number, row, column);
    GameLayer::setPositionPlayer(id, number, row, column);

  }
	
}

////////  Receiver end game ///////////////////////////////////////////////////////////
void ConnectionLayer::endGame(SIOClient *client, const std::string& data) {

	log("END GAME: %s", data.c_str());
  if(!data.empty())
  {
    GameLayer::setEndGame();
  }

}
void ConnectionLayer::echotest(SIOClient *client, const std::string& data) {

	log("SocketIOTestLayer::echotest called with data: %s", data.c_str());

	std::stringstream s;
	s << client->getTag() << " received event echotest with data: " << data.c_str();	

	//_sioClientStatus->setString(s.str().c_str());

}


void ConnectionLayer::onMenuTestClientDisconnectClicked(cocos2d::Object *sender)
{

	if(mClient != NULL){
    mClient->emit("disconnect","[{\"id\":\"1\"}]");
    mClient->disconnect();
  }
}
//Disconnect to server
void ConnectionLayer::sendDisconnect(std::string pName)
{

	if(mClient != NULL){
    mClient->disconnect();
  }
}

//Return room
void ConnectionLayer::disconnectPlayer(std::string pName, std::string pID)
{

	if(mClient != NULL){
    mClient->emit("returnroom","[{\"id\":\"1\"}]");
    //mClient->disconnect();
  }
}

void ConnectionLayer::receiverDisconnect(cocos2d::extension::SIOClient *client, const std::string& data)
{
  log("----------Receiver Disconnect: %s", data.c_str());
  if(!data.empty())
  {
    std::string id;
    exportLastData(data, id);

    GameLayer::setPlayerDisconnect(id);

  }
}

//Send out room
void ConnectionLayer::sendOutRoom(std::string pname)
{

	if(mClient != NULL){
    mClient->emit("outroom","[{\"id\":\"1\"}]");
    //mClient->disconnect();
  }
}

void ConnectionLayer::receiverOutRoom(cocos2d::extension::SIOClient *client, const std::string& data)
{
  if(!data.empty())
  {
    std::string id;
    exportLastData(data, id);

    RoomLayer::removePlayer(id);

  }
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

void ConnectionLayer::exportLastData(std::string pData, int& pReturn)
{
  Document doc;
	//pData = " {\"name\":\"username\",\"args\":[123]} " ;
	//{"name":"randomNumber","args":[510]}
	doc.Parse<0>(pData.c_str() );
	
	SizeType j = 0;
	//for (SizeType i = 0; i < (n/2 - 1); i++){
		//Gia tri 0 cua mang
		Value& data = doc["args"][j];
    CCLog("Number-- %d", data.GetInt() );

    pReturn = data.GetInt();
}

void ConnectionLayer::exportLastData(std::string pData, std::string& pReturn)
{
  Document doc;
	//pData = " {\"name\":\"username\",\"args\":[123]} " ;
	//{"name":"randomNumber","args":[510]}
	doc.Parse<0>(pData.c_str() );
	
	SizeType j = 0;
	//for (SizeType i = 0; i < (n/2 - 1); i++){
		//Gia tri 0 cua mang
		Value& data = doc["args"][j];
    CCLog("ID dis %s", data.GetString() );

    pReturn = data.GetString();
}

void ConnectionLayer::exportLastData(std::string pData, std::string& pID, int& pNumber, 
                                     int& pRow, int& pColumn)
{
	Document doc;
	//pData = " {\"name\":\"username\",\"args\":[{\"name\":\"Duy Phuong\",\"id\":\"nOJqkJ2_c75tgP6Zlvyh\"}]} " ;
	
	doc.Parse<0>(pData.c_str() );
	
	SizeType j = 0;

	//Gia tri 0 cua mang
	Value& id = doc["args"][j]["id"];
	log("LAST THE ID %s", id.GetString() );
	Value& number = doc["args"][j]["number"];
	log("LAST THE NUMBER %d", number.GetInt() );
  Value& row = doc["args"][j]["row"];
	log("LAST THE Row %d", row.GetInt() );
	Value& column = doc["args"][j]["column"];
	log("LAST THE column %d", column.GetInt() );

  pID = id.GetString();
  pNumber = number.GetInt();
  pRow = row.GetInt();
  pColumn = column.GetInt();
}

void ConnectionLayer::exportListData(std::string pData, bool* &pReturn)
{
  pReturn = new bool[9];
  Document doc;
	//pData = " {\"name\":\"username\",\"args\":[123]} " ;
	//{"name":"status","args":[[false,false,false,false,false,false,false,false,false]]}
	doc.Parse<0>(pData.c_str() );
	
	SizeType j = 0;
	for (int i = 0; i < MAX_ROOM; i++){
		//Gia tri 0 cua mang
		Value& data = doc["args"][j][i];
    CCLog("Status list %s", data.GetBool() == true? "true":"false" );

    pReturn[i] = data.GetBool();
  }
}

void ConnectionLayer::exportListData(std::string pData, int* &pReturn)
{
  pReturn = new int[9];
  Document doc;
	//pData = " {\"name\":\"username\",\"args\":[123]} " ;
	//{"name":"status","args":[[false,false,false,false,false,false,false,false,false]]}
	doc.Parse<0>(pData.c_str() );
	
	SizeType j = 0;
	for (int i = 0; i < MAX_ROOM; i++){
		//Gia tri 0 cua mang
		Value& data = doc["args"][j][i];
    CCLog("Status list %d", data.GetInt());

    pReturn[i] = data.GetInt();
  }
}