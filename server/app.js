
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
var countDis = 0;

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
			//countReady = 0;
			var number = Math.floor((Math.random()*899)+100);
			
			io.sockets.emit("randomNumber",  number);
		}
	
	});

	//3. POSITION
	socket.on('position', function(data) {
		countPosition ++;
		
		// console.log("POSITION:");
		// console.log(data.pos);
		
		socket.broadcast.emit("position",data);
		
		//Send number next turn
		if(((countPosition/3)%countUser == 0) && (countPosition%3 == 0) ){
			var number = Math.floor((Math.random()*899)+100);
			io.sockets.emit("randomNumber",  number);
		}
		//End game
		//console.log("POSITION:", countPosition);
		if (countPosition == (27*3*countUser) ){
			//console.log("End game POSITION:", countPosition);
			var end = 1;
			io.sockets.emit("endGame", end);

			//RESET
			listUser.length = 0;
			listState.length = 0;
			countUser = 0;
			countReady = 0;
			countPosition =  0;
		}
	});
	
    socket.on('disconnect', function () {
    	countDis++;
    	if(countDis == countUser){
    		//RESET
			listUser.length = 0;
			listState.length = 0;
			countUser = 0;
			countReady = 0;
			countPosition =  0;
			countDis = 0;
    	}
        console.log('disconnect socket');
        socket.broadcast.emit('announcement', 'disconnect');
    });
});
