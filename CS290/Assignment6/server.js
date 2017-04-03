//get and initialize necessary modules
var express = require("express");
var app = express();
var handlebars = require("express-handlebars").create({defaultLayout:"main"});
var bodyParser = require("body-parser");
var mysql = require('./dbcon.js');
var path = require('path');

app.engine("handlebars", handlebars.engine);
app.set("view engine", "handlebars");
app.use(bodyParser.urlencoded({extended: false}));
app.use(bodyParser.json());
app.use(express.static(__dirname + "/public"));
app.set("port", 2000);

app.get('/',function(req,res,next){
    //creates a table called workouts if none exists
    var createString = "CREATE TABLE IF NOT EXISTS workouts("+
        "id INT PRIMARY KEY AUTO_INCREMENT,"+
        "name VARCHAR(255) NOT NULL,"+
        "reps INT,"+
        "weight INT,"+
        "date DATE,"+
        "lbs BOOLEAN)";

    mysql.query(createString, function(err){
        if(err){
            next(err);
            return;
        }

        res.sendFile(path.join(__dirname + '/public/home.html')); //load the homepage
    });
});

app.post('/',function(req,res,next) {
    //handles insert post requests
    if (req.body.btnType == 'insert') {
        //insert a row into the table
        mysql.query('INSERT INTO workouts (`name`,`reps`,`weight`,`date`,`lbs`) VALUES(?,?,?,?,?)',
            [req.body.name, req.body.reps, req.body.weight, req.body.date, req.body.lbs],
            function (err, result) {
                if (err) {
                    next(err);
                    return;
                }

                //select the newly inserted row
                mysql.query('SELECT * FROM workouts WHERE id=?', [result.insertId], function (err, rows, fields) {
                    if (err) {
                        next(err);
                        return;
                    }

                    //respond to client with the data in the row that was just inserted
                    var table = JSON.stringify(rows);
                    res.type('text/plain');
                    res.send(table);
                });
            });
    }
    //handles updates to the table
    else if (req.body.btnType == 'edit') {
        //select the row to be updated
        mysql.query('SELECT * FROM workouts WHERE id=?', [req.body.id], function (err, result) {
            if (err) {
                next(err);
                return;
            }
            //if a valid row was selected...
            if (result.length == 1) {
                var curVal = result[0];

                //update that row with the data sent from the client
                mysql.query('UPDATE workouts SET name=?, reps=?, weight=?, date=?, lbs=? WHERE id=?',
                    [req.body.name || curVal.name, req.body.reps || curVal.reps, req.body.weight || curVal.weight, req.body.date || curVal.date,
                        req.body.lbs || curVal.lbs, req.body.id], function (err, result) {
                        if (err) {
                            next(err);
                            return;
                        }

                        //inform the client the table was updated
                        res.type('text/plain');
                        res.send('Status: Row successfully updated in database.');
                    });
            }
        });
    }
    //handles row deletion
    else if (req.body.btnType == 'delete') {
        //deletes a row from the table
        mysql.query('DELETE FROM workouts WHERE id=?', [req.body.id], function (err, result) {
            if (err) {
                next(err);
                return;
            }

            //inform the client the row was deleted
            res.type('text/plain');
            res.send('Status: Row successfully deleted from database.');
        });
    }
});

app.get('/reset-table',function(req,res,next){
    mysql.query("DROP TABLE IF EXISTS workouts", function(err){
        var createString = "CREATE TABLE workouts("+
            "id INT PRIMARY KEY AUTO_INCREMENT,"+
            "name VARCHAR(255) NOT NULL,"+
            "reps INT,"+
            "weight INT,"+
            "date DATE,"+
            "lbs BOOLEAN)";
        mysql.query(createString, function(err){
            res.redirect('/');
        })
    });
});

//error handling
app.use(function(req,res){
    res.status(404);
    res.send('404 - Not Found');
});

app.use(function(err,req,res,next) {
    console.log(err.stack); //debug
    res.status(500);
    res.send('500 - Server Error');
});

//server start
app.listen(app.get('port'), function(){
    console.log('Express started on http://localhost:' + app.get('port') + '; press Ctrl-C to terminate.');
});
