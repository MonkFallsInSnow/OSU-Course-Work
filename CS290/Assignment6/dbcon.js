var mysql = require('mysql');
var pool = mysql.createPool({
    host  : 'localhost',
    user  : 'student', //needs to be changed?
    password: 'default', //needs to be changed?
    database: 'student' //needs to be changed?
});

module.exports = pool;
