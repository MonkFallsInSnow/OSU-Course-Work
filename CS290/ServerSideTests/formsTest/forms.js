var express = require("express");
var app = express();
var handlebars = require("express-handlebars").create({defaultLayout:"main"});
var bodyParser = require("body-parser");

app.engine("handlebars", handlebars.engine);
app.set("view engine", "handlebars");
app.use(bodyParser.urlencoded({extended: false}));
app.use(bodyParser.json());
app.set("port", 3000);

app.get('/', function(req,res){
	var queryItems = [];
	for(var prop in req.query){
		queryItems.push({"name": prop, "value": req.query[prop]})
	}
	var context = {};
	context.item = queryItems;
	context.getReq = true;
	res.render('data',context);
});

app.post('/', function(req,res){
	var queryItems = [];
	for(var prop in req.body){
		queryItems.push({"name": prop, "value": req.body[prop]})
	}
	var context = {};
	context.item = queryItems;
	context.getReq = false;
	res.render('data',context);
});

app.use(function(req,res){
	res.status(404);
	res.send("404 - Not Found");
});

app.use(function(err,req,res,next)
{
	console.log(err.stack); //debug
	res.status(500);
	res.send('500 - Server Error');
});

app.listen(app.get("port"), function(){
	console.log("Express started on http://localhost:" + app.get("port") + "; press Ctrl-C to terminate.");
});