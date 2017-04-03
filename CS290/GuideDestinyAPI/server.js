var config = require('./config.js');
config.init(config.app);

var app = config.app;
var request = config.request;
var credentials = config.credentials;
var playerData = config.playerData;
var path = config.path;
var functions = config.functions;

const HOST = 'http://www.bungie.net/Platform/Destiny/';
var baseRequest = request.defaults({headers: {'X-API-Key':credentials.destinyKey}});

//debug -> used to test various requests
app.get('/test',function(req,res) {
    baseRequest('http://www.bungie.net/Platform/Destiny/Explorer/Items/?name=Obsidian&definitions=true', function (err, response, body) {
        if (!err && response.statusCode < 400) {
            var context = {};
            context.test = JSON.stringify(JSON.parse(body), null, 4);
            res.render('test', context);
        }
    });
});

//end tests

app.get('/',function(req,res){
    res.sendFile(path.join(__dirname + '/public/html/index.html'));
});

app.get('/index',function(req,res){
    res.sendFile(path.join(__dirname + '/public/html/index.html'));
});

app.get('/characterData',function(req,res) {
    res.render('characterData');
});

app.get('/invalid',function(req,res){
    res.sendFile(path.join(__dirname + '/public/html/invalid.html'));
});

app.get('/getKey',function(req,res){
    res.sendFile(path.join(__dirname + '/public/html/getKey.html'));
});

app.get('/firstRequest',function(req,res) {
    var context = {};
    request(HOST + '2/Stats/GetMembershipIdByDisplayName/' + credentials.defaultUserName +'/', function (err, response, body) {
        context.error = JSON.stringify(JSON.parse(body), null, 4);

        baseRequest(HOST + credentials.defaultMemberType + '/Stats/GetMembershipIdByDisplayName/' + credentials.defaultUserName + '/', function (err, response, body) {
            context.expression = "<code>{{test}}</code>";
            context.memId = JSON.stringify(JSON.parse(body), null, 4);
            res.render('firstRequest', context);
        });
    });
});

app.get('/moreRequests',function(req,res){
    baseRequest('http://www.bungie.net/Platform/Destiny/' + credentials.defaultMemberType + '/Account/' + credentials.defaultMemberID + '/Summary/', function (err, response, body) {
        if (!err && response.statusCode < 400) {
            var context = {};
            context.summary = JSON.stringify(JSON.parse(body).Response.data.characters[0].characterBase, null, 4);
            //res.render('moreRequests', context);
        }
        functions.getActivities(baseRequest,res,HOST,credentials.defaultMemberType,credentials.defaultMemberID,credentials.defaultCharacterID,'moreRequests',context,90);

    });
});

app.get('/summary',function(req,res) {
    baseRequest(HOST + credentials.defaultMemberType + '/Account/' + credentials.defaultMemberID + '/Summary/', function (err, response, body) {
        if (!err && response.statusCode < 400) {
            var context = {};
            context.summary = JSON.stringify(JSON.parse(body), null, 4);
            res.render('summary', context);
        }
    });
});

app.get('/resources',function(req,res){
    res.sendFile(path.join(__dirname + '/public/html/resources.html'));
});

app.post('/characterData',function(req,res) {
    playerData.characterNum = req.body.characterNum;

    if(req.body.accountType == 'none')
    {
        playerData.userName = credentials.defaultUserName;
        playerData.characterNum = 0;
    }
    else
    {
        playerData.userName = req.body.playerId;
    }

    switch (req.body.accountType) {
        case 'xbox':
            playerData.memberType = '1';
            break;
        case 'psn':
        case 'none':
            playerData.memberType = '2';
            break;
        default:
            return;
            break;
    }

    baseRequest(HOST + playerData.memberType + '/Stats/GetMembershipIdByDisplayName/' + playerData.userName + '/', function (err, response, body) {
        if (!err && response.statusCode < 400) {
            playerData.memberId = JSON.parse(body).Response;
            if (JSON.parse(body).ErrorCode > 1) {
                res.redirect('/html/invalid.html');
            }
            else {
                functions.getEquipment(baseRequest,res,HOST,playerData.memberType,playerData.memberId,playerData.characterNum,'characterData');
            }
        }
    });
});

//error handling
app.use(function(req,res){
    res.status(404);
    res.send('404 - Not Found');
});

app.use(function(err,req,res,next)
{
    console.log(err.stack); //debug
    res.status(500);
    res.send('500 - Server Error');
});

//server start
app.listen(app.get('port'), function(){
    console.log('Express started on http://localhost:' + app.get('port') + '; press Ctrl-C to terminate.');
});

