
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
var listUser = new Array();
var listState = new Array();
var playerList = new Array();

Array.prototype.inject = function(element) {

    if (this.length >= 10) {
        this.shift()
    }
    this.push(element)
}

/////
var countUser = 0;
var countReady = 0;
var countPosition =  0;
var countEnd = 0;
var mTurn = 0;
var mCount = 0;

io.sockets.on('connection', function (socket) {
	countUser ++;
	if(countUser >= 5)
		return;
	
    console.log('connection', socket.id);

    //testing simple message
    socket.send('welcome!');
   
   //1. USERNAME
   //send username and id for last client
   socket.emit("init", listUser);
	
    socket.on("username", function(data) {

		console.log('USERNAME: ');
        console.log(data);
		//socket.json.send(data);
		
		var user = new Object();
		user.name = data.name;
		user.id = socket.id;
		
		//add into array
		listUser.inject(user);
		//Console
		console.log('LIST USERNAME: ' + listUser);
        io.sockets.emit("username", user);

    });
	
	//2. STATE
	socket.emit("initState", listState);
	
	socket.on("state", function(data) {
		console.log("STATE: ");
		console.log(data);
		
		countReady ++;
		listState.inject(data);
		io.sockets.emit("state", data);
		
		console.log('countReady: ', countReady);
		console.log('countUser: ', countUser);
		
		//start game
		if(countUser > 1 && countReady == countUser){
			//Tang so turn
			mTurn++;
			//countReady = 0;
			var number = Math.floor((Math.random()*899)+100);
			
			io.sockets.emit("randomNumber",  number);
		}
	
	});

	//3. POSITION
	socket.on('position', function(data) {
		countPosition ++;
		
		//Set player da gui position trong 1 turn
		if(countPosition%3 ==0){

			console.log("mTurn ", mTurn);
			playerList[mCount++] = data.id;
			console.log("player: ", mCount-1);
			console.log("ID: ", data.id);
		}

		// console.log("POSITION:");
		// console.log(data.pos);
		
		socket.broadcast.emit("position",data);
		
		//Send number next turn
		if(mCount == countUser){
			//Huy playerlist
			playerList.length = 0;
			//Tang so turn
			mTurn++;
			//Reset mCount
			mCount = 0;
			var number = Math.floor((Math.random()*899)+100);
			io.sockets.emit("randomNumber",  number);
		}
		
	});

	console.log("countEnd: ");
	//4. End Game
	socket.on('endgame', function(data) {
		countEnd ++;
		console.log("countEnd: ", countEnd);
		if (countEnd == countUser){
			console.log("countEnd: END");
			//console.log("End game POSITION:", countPosition);
			var end = 1;
			io.sockets.emit("endGame", end);

			//RESET
			listUser.length = 0;
			listState.length = 0;
			playerList.length = 0;
			countUser = 0;
			countReady = 0;
			countPosition =  0;
			countEnd = 0;
			mTurn = 0;
			mCount = 0;
		}
	});
	//Receiver disconnected command
	socket.on('discn', function(data) {
		console.log('discn', data);
		io.sockets.emit("discn", data);
	});

    socket.on('disconnect', function () {
    	//Send number - truong hop deadlock khong gui duoc number khi player disconnect
    	//so player gui len = so player -1 va 1 trong so do khong phai bi disconnect
    	//So player gui len trong 1 turn: (countPosition/3)/mTurn va countPosition%3=0
    	console.log("mTurn ", mTurn);
    	console.log("So player gui len: ", mCount);
    	console.log("So player -1:  ", countUser-1);
    	console.log("countPosition:  ", countPosition);
    	if(mCount == countUser-1){
    		console.log("Thoa 1");
    		var i;
    		var tmp = 0;
    		for(i =0; i< playerList.length; i++){
    			if(playerList[i] == socket.id){
    				tmp++;
    			}
    		}

    		if(tmp == 0){
    			console.log("Thoa 2");
    			//Huy playerlist
				playerList.length = 0;
				//Tang so turn
				mTurn++;
				//Reset mCount
				mCount = 0;
				var number = Math.floor((Math.random()*899)+100);
				io.sockets.emit("randomNumber",  number);
    		}
    	}

    	console.log('disconnect socket');
        socket.broadcast.emit('disconnect', socket.id);

        if(countUser == 0)
        	return;

    	countUser--;

    	if(countUser == 0){
    		//RESET
			listUser.length = 0;
			listState.length = 0;
			playerList.length = 0;
			countUser = 0;
			countReady = 0;
			countPosition =  0;
			countEnd = 0;
			mTurn = 0;
			mCount = 0;

    	}
        
    });
});
