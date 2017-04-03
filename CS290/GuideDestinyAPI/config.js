var expr = require("express");
var appE = expr();
var hndlBars = require("express-handlebars").create({defaultLayout: "main"});
var req = require("request");
var bdyParser = require("body-parser");
var creds = require("./credentials.js");
var pathE = require("path");
var data = require("./public/scripts/playerData");
var func = require("./public/scripts/functions");//test

module.exports = {
    express:expr,
    app:appE,
    handlebars:hndlBars,
    request:req,
    bodyParser:bdyParser,
    credentials:creds,
    path:pathE,
    playerData:data,
    functions:func,//test
    init:function(app){
        app.engine("handlebars", hndlBars.engine);
        app.set("view engine", "handlebars");
        app.use(bdyParser.urlencoded({extended: false}));
        app.use(bdyParser.json());
        app.use(expr.static(__dirname + "/public"));
        app.set("port", 3000);
    }
};