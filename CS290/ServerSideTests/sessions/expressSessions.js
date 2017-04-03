var express = require('express');
var app = express();
var session = require('express-session');
var handlebars = require("express-handlebars").create({defaultLayout:"main"});

app.engine("handlebars", handlebars.engine);
app.set("view engine", "handlebars");
app.set("port", 3000);

function genPassword(){
	const MIN = 33;
	const MAX = 126;
	const LEN = 30;
	var password = "";

	for(var i = 0; i < LEN; i++)
	{
		password += String.fromCharCode(Math.floor(Math.random() * (MAX - MIN + 1)) + MIN);
	}

	return password;
}

app.use(session({secret: genPassword()}));

app.get('/', function(req,res){
	var context = {};
	context.count = req.session.count || 0;
	req.session.count = context.count + 1;
	res.render('counter', context);
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