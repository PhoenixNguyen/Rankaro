
/**
 * Module dependencies.
 */

var express = require('express')
  , routes = require('./routes')
  , user = require('./routes/user')
  , http = require('http')
  , path = require('path')
  , iolib = require('socket.io');

var app = express();

app.configure(function(){
  app.set('port', process.env.PORT || 3000);
  app.set('views', 'E:/SERVER/ServerCocos2D/socket.io-testserver-master' + '/views');
  app.set('view engine', 'jade');
  app.use(express.favicon());
  app.use(express.logger('dev'));
  app.use(express.bodyParser());
  app.use(express.methodOverride());
  app.use(express.cookieParser('your secret here'));
  app.use(express.session());
  app.use(app.router);
  app.use(require('stylus').middleware('E:/SERVER/ServerCocos2D/socket.io-testserver-master' + '/public'));
  app.use(express.static(path.join('E:/SERVER/ServerCocos2D/socket.io-testserver-master', '/public')));
});

app.configure('development', function(){
  app.use(express.errorHandler());
});

app.get('/', routes.index);
app.get('/users', user.list);

var server = http.createServer(app).listen(app.get('port'), function(){
  console.log("Express server listening on port " + app.get('port'));
});

var io = iolib.listen(server);
io.set("log level", 3);
/////////////////////////////////////////////////////////////////////////////////////////////////
//------------------------------------- Khai bao ------------------------------------------------
var listUser = new Array(9);
var listState = new Array(9);
var playerList= new Array(9);

var mPlayerInRoom = new Array(9);
var mPlayerIsRunning = new Array(9);

for(var i= 0; i< 9; i++){
	listUser[i] = new Array();
	listState[i] = new Array();
	playerList[i] = new Array();

	mPlayerInRoom[i] = new Array();
	mPlayerIsRunning[i] = new Array();
}

/////
var countUser = new Array(9);
var countReady = new Array(9);
var countPosition = new Array(9);
var countEnd = new Array(9);
var mTurn = new Array(9);
var mCount = new Array(9);
var mRoomstatus = new Array(9);

for(var i= 0; i< 9; i++){
	countUser[i] = 0;
	countReady[i] = 0;
	countPosition[i] =  0;
	countEnd[i] = 0;
	mTurn[i] = 0;
	mCount[i] = 0;
	mRoomstatus[i] = false;
}

//mRoomstatus[0] = true;
//Define inject
Array.prototype.inject = function(element) {

    if (this.length >= 10) {
        this.shift()
    }
    this.push(element)
}

var mAllClients = [];
var mTimeoutList = [];


//--------------------------- Het khai bao ---------------------------------------------------

//myVar = setTimeout(function(){alert("Hello")},3000);
//clearTimeout(myVar);

///////////////////////// Function Define ////////////////////////////////////////
function resetTimeoutPlayer(socket){
	///////////////////// Clear timeout //////////////////////////////////////////
	for(var i= 0; i< mAllClients.length; i++){
		if(mAllClients[i].id == socket.id){
			//Khoi tao
			clearTimeout(mTimeoutList[i]);
			mTimeoutList[i] = setTimeout(function(){
				//alert("Hello")

				//disconnect client
				console.log("disconnect");
				socket.disconnect();
			},120000);

			//console.log("Set timout");
			break;
		}

	}
}

/////////////////// Delete client ///////////////////////////////////////
function deleteClient(socket){
	for(var i= 0; i< mAllClients.length; i++){
		if(mAllClients[i].id == socket.id){

			mAllClients.splice(i, 1);

			console.log("delete client");
			break;
		}

	}
}
/////////////// Out your Room  ////////////////////////////////////////
function outRoom(socket){
		console.log("OUT ROOM")
		//socket.roomStatus = null;
		//console.log("Room Status", socket.roomStatus);
		if(countUser[socket.room] == 1)
			mPlayerInRoom[socket.room].length = 0;

		if(countUser[socket.room] >= 1){
			
			countUser[socket.room] --;
			//Send user number to client
			io.sockets.emit('countuser', countUser);
		}
		if(socket.state && countReady[socket.room] >=1){
			countReady[socket.room] --;
			socket.state = false;
		}

		//Delete user from listUser
		//console.log("IDDDD: ", listUser[socket.room][0].id);
		for(var i= 0; i< listUser[socket.room].length; i++){
			if(listUser[socket.room][i].id == socket.id){
				listUser[socket.room].splice(i, 1);

				console.log("Xoa");
				break;
			}

		}
		
    	//Delete state from list state
		for(var i= 0; i< listState[socket.room].length; i++){
			if(listState[socket.room][i].id == socket.id){
				listState[socket.room].splice(i, 1);

				console.log("Xoa");
				break;
			}

		}
		
		// socket.broadcast.to(socket.room).emit('returnroom', socket.id);
		socket.broadcast.to(socket.room).emit("outroom", socket.id);
        socket.leave(socket.room);
        socket.emit("status", mRoomstatus);

        console.log("END OUT ROOM")
}

/////////////////// Return room from gamelayer /////////////////////////////////
function returnRoom(socket){
	console.log("RETURN ROOM")
	//socket.running = null;
	//socket.running = false;
	//Send number - truong hop deadlock khong gui duoc number khi player disconnect
	//so player gui len = so player -1 va 1 trong so do khong phai bi disconnect
	//So player gui len trong 1 turn: (countPosition/3)/mTurn va countPosition%3=0
	console.log("mTurn ", mTurn[socket.room]);
	console.log("So player gui len: ", mCount[socket.room]);
	console.log("So player -1:  ", countUser[socket.room]-1);
	console.log("countPosition:  ", countPosition[socket.room]);
	if(mCount[socket.room] == (countUser[socket.room]-1) && countUser[socket.room] > 1){
		console.log("Thoa 1");
		var i;
		var tmp = 0;
		for(i =0; i< playerList[socket.room].length; i++){
			if(playerList[socket.room][i] == socket.id){
				tmp++;
			}
		}

		if(tmp == 0){
			console.log("Thoa 2");
			//Huy playerlist
			playerList[socket.room].length = 0;
			//Tang so turn
			mTurn[socket.room]++;
			//Reset mCount
			mCount[socket.room] = 0;
			var number = Math.floor((Math.random()*899)+100);

			//Khong gui cho thag out khoi room
			socket.broadcast.to(socket.room).emit("randomNumber",  number);
			console.log("SEND NUMBER 2: ", number);
		}
	}

	//reset mCount do giam so user
	if(mCount[socket.room] >= 1)
		mCount[socket.room]--;

	console.log('Return Room');
    socket.broadcast.to(socket.room).emit('returnroom', socket.id);
    socket.leave(socket.room);

    if(countUser[socket.room] == 0)
    	return;

	countUser[socket.room]--;
	//Send user number to client
	io.sockets.emit('countuser', countUser);
	//Send list status
	if(countUser[socket.room] >0)
    	io.sockets.emit("status", mRoomstatus);


	if(countUser[socket.room] == 0){
		resetValues(socket);
	}
}

/////////////////// Reset values ////////////////////////////////////////
function resetValues(socket){
	//RESET
	listUser[socket.room].length = 0;
	listState[socket.room].length = 0;
	playerList[socket.room].length = 0;
	countUser[socket.room] = 0;
	countReady[socket.room] = 0;
	countPosition[socket.room] =  0;
	countEnd[socket.room] = 0;
	mTurn[socket.room] = 0;
	mCount[socket.room] = 0;
	mRoomstatus[socket.room] = false;
	io.sockets.emit("status", mRoomstatus);
	mPlayerInRoom[socket.room].length = 0;
}


///////////////////////// Receiver request from client //////////////////
io.sockets.on('connection', function (socket) {

	//console.log('SOCKET', socket);
	//Add client to array
	mAllClients.push(socket);
	
	//Set timeout
	resetTimeoutPlayer(socket);

    console.log('connection', socket.id);

    //testing simple message
    socket.send('welcome!');
   
   //1. USERNAME
   //send username and id for last client
    socket.on("username", function(data) {
	    	
		//Set timeout
		resetTimeoutPlayer(socket);


		console.log('USERNAME: ');
        console.log(data);
		//socket.json.send(data);
		
		//set name for client
		socket.name = data.name;

		
		//Send user number to client
		socket.emit('countuser', countUser);
		socket.emit("status", mRoomstatus);
    });
	
	
	socket.on("room", function(data) {
			
		//Set timeout
		resetTimeoutPlayer(socket);

		//Neu so player nhieu hon 4 hoac room full thi return
		if(countUser[data.room] >= 4 || mRoomstatus[data.room]){
			return;
		}
		countUser[data.room] ++;
		//Send user number to client
		io.sockets.emit('countuser', countUser);
		socket.emit("status", mRoomstatus);

		console.log('ROOM: ');
        console.log(data.room);
		//socket.json.send(data);
		
		//set name for client
		socket.room = data.room;
		socket.join(data.room);

		socket.roomStatus = true;
		socket.isRunning = false;
		//add player into room array
		mPlayerInRoom[data.room].inject(socket);
		console.log("LENGTH: ", mPlayerInRoom[socket.room].length);
		//console.log("SOCKET: ", );mPlayerInRoom[socket.room][0]

		console.log("Room Status", socket.roomStatus);
		//Send list user init
		if(listUser[data.room].length != 0){
			socket.emit("init", listUser[data.room]);
			console.log("INIT LIST USER ", listUser[data.room]);
			//Send state init
			socket.emit("initState", listState[socket.room]);
		}
		
		//Get new player
		var user = new Object();
		user.name = socket.name;
		user.id = socket.id;
		//add into array
		listUser[data.room].inject(user);
		console.log("ADD LIST USER ", listUser[data.room]);
		//send new player
		io.sockets.in(data.room).emit("username", user)

    });

	//2. STATE
	
	socket.on("state", function(data) {
			
		//Set timeout
		resetTimeoutPlayer(socket);

		console.log("STATE: ");
		console.log(data);
		
		//Gan socket state
		socket.state = true;

		countReady[socket.room] ++;
		listState[socket.room].inject(data);
		io.sockets.in(socket.room).emit("state", data);
		
		console.log('countReady: ', countReady[socket.room]);
		console.log('countUser: ', countUser[socket.room]);
		
		//start game
		if(countUser[socket.room] > 1 && countReady[socket.room] == countUser[socket.room]){
			//Tang so turn
			mTurn[socket.room]++;
			//countReady = 0;
			var number = Math.floor((Math.random()*899)+100);
			
			io.sockets.in(socket.room).emit("randomNumber",  number);
			mRoomstatus[socket.room] = true;

			for(var i= 0; i< mPlayerInRoom[socket.room].length; i++){
				mPlayerInRoom[socket.room][i].roomStatus = false;
				mPlayerInRoom[socket.room][i].isRunning = true;

			}
			// for(var i= 0; i< socket.length; i++){
			// 	console.log("Socket in Room: ", i);
			// 	if(socket[i].room == socket.room){

			// 		socket[i].running = true;
			// 		socket[i].roomStatus = false;
			// 		console.log("Socket in Room: ", i);
			// 	}

			// }
			
			console.log("Room Status", socket.roomStatus);

			io.sockets.emit('countuser', countUser);
			io.sockets.emit("status", mRoomstatus);
		}
	
	});

	//3. POSITION
	socket.on('position', function(data) {
			
		//Set timeout
		resetTimeoutPlayer(socket);

		countPosition[socket.room] ++;
		
		socket.broadcast.to(socket.room).emit("position",data);

		//Set player da gui position trong 1 turn
		if(countPosition[socket.room]%3 ==0){

			console.log("mTurn ", mTurn[socket.room]);
			playerList[socket.room][mCount[socket.room]++] = data.id;
			console.log("player: ", mCount[socket.room]-1);
			console.log("ID: ", data.id);
		
			//Send number next turn
			if(mCount[socket.room] == countUser[socket.room]){
				//Huy playerlist
				playerList[socket.room].length = 0;
				//Tang so turn
				mTurn[socket.room]++;
				//Reset mCount
				mCount[socket.room] = 0;
				var number = Math.floor((Math.random()*899)+100);
				io.sockets.in(socket.room).emit("randomNumber",  number);
				console.log("SEND NUMBER 1: ", number);
			}
		}
	});

	console.log("countEnd: ");
	//4. End Game
	socket.on('endgame', function(data) {
			
		//Set timeout
		resetTimeoutPlayer(socket);

		countEnd[socket.room] ++;
		console.log("countEnd: ", countEnd[socket.room]);
		if (countEnd[socket.room] == countUser[socket.room]){
			console.log("countEnd: END");
			//console.log("End game POSITION:", countPosition);
			var end = 1;
			io.sockets.in(socket.room).emit("endGame", end);

			//RESET
			resetValues(socket);
		}
	});
	//Receiver disconnected command
	socket.on('discn', function(data) {
		console.log('discn', data);
		io.sockets.in(socket.room).emit("discn", data);
	});


	socket.on('outroom', function(){
			
		//Set timeout
		resetTimeoutPlayer(socket);

		//outroom
		outRoom(socket);
		
	});

	socket.on('returnroom', function(){
			
		//Set timeout
		resetTimeoutPlayer(socket);

		//Return room
		returnRoom(socket);
	});

    socket.on('disconnect', function () {
    	console.log('disconnect socket');
    	//Khong the delete user - xem xet chuyen tao connection khi create user
    	//- Moi user la 1 connection
	    //deleteClient(socket);

	    if(!mPlayerInRoom[socket.room])
	    	return;

	    for(var i= 0; i< mPlayerInRoom[socket.room].length; i++){

	    		if(mPlayerInRoom[socket.room][i].id = socket.id){

	    			//Neu dang trong room thi out room
	    			if(mPlayerInRoom[socket.room][i].roomStatus){
	    				console.log("OUT : ", i);
	    				//Reset
	    				//mPlayerInRoom[socket.room][i].roomStatus = false;
	    				outRoom(socket);
	    				
	    			}
	    			else
	    				if(mPlayerInRoom[socket.room][i].isRunning){
	    					console.log("OUT : ", i);
	    					//Reset
	    					//mPlayerInRoom[socket.room][i].isRunning = false;
	    					returnRoom(socket);
	    					
	    				}

	    			break;			
	    		}
		}

    });
});

