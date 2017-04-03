var express = require("express");
var app = express();
var handlebars = require("express-handlebars").create({defaultLayout:"main"});

app.engine("handlebars", handlebars.engine);
app.set("view engine", "handlebars");
app.set("port", 3000);

function genContext()
{
	var num = {};
	num.randNum = Math.floor(Math.random() * 100);
	return num;
}

app.get('/', function(req,res){
	
	res.render("randNum", genContext());
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