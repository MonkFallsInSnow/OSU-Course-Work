module.exports = {
    getEquipment: function(httpReq,res,host,memberType,memberId,characterNum,page){
        httpReq(host + memberType + '/Account/' + memberId + '/Summary/', function (err, response, body) {
        var context = {};
        if (!err && response.statusCode < 400) {

            if (JSON.parse(body).ErrorCode > 1) {
                res.redirect('/invalid');
                return;
            }

            var result = [];

            var items = JSON.parse(body).Response.data.characters[characterNum].characterBase.peerView.equipment;
            var itemHashes = items.map(function (currentValue) {
                return currentValue.itemHash.toString();
            });

            var keys = Object.keys(itemHashes);
            var callsLeft = keys.length;

            var callback = function () {
                context.header = true;
                context.data = result;
                res.render(page, context);
            };

            if (callsLeft === 0) {
                callback();
            }
            else {
                for (var i = 0; i < itemHashes.length; i++) {
                    httpReq(host + '/Manifest/6/' + itemHashes[i] + '/', function (err, response, body) {
                        if (!err && response.statusCode < 400) {
                            result.push({
                                name: JSON.parse(body).Response.data.inventoryItem.itemName,
                                desc: JSON.parse(body).Response.data.inventoryItem.itemDescription,
                                icon: 'http://bungie.net' + JSON.parse(body).Response.data.inventoryItem.icon,
                                type: JSON.parse(body).Response.data.inventoryItem.itemTypeName
                            });

                            if (--callsLeft === 0) {
                                callback();
                            }
                        }
                    });
                }
            }
        }
    });
},

    getActivities: function(httpReq,res,host,memberType,memberId,characterId, page, context,limit){
            httpReq(host + memberType + '/Account/' + memberId + '/Character/' + characterId + '/Activities/', function (err, response, body) {
            if (!err && response.statusCode < 400) {
                var activities = [];
                var result = [];

                var len = JSON.parse(body).Response.data.available.length;

                for(var i = 0; i < len; i++)
                {
                    if(JSON.parse(body).Response.data.available[i].isCompleted == true)
                    {
                        activities.push(JSON.parse(body).Response.data.available[i].activityHash);
                    }
                }

                var callback = function () {
                    context.activity = result;
                    res.render(page, context);
                };

                len = activities.length - limit;
                var callsLeft = len;

                if (callsLeft === 0) {
                    callback();
                }
                else {
                    for (var i = 0; i < len; i++) {
                        httpReq(host + '/Manifest/1/' + activities[i] + '/', function (err, response, body) {
                            if (!err && response.statusCode < 400) {
                                result.push({
                                    name: JSON.parse(body).Response.data.activity.activityName,
                                    desc: JSON.parse(body).Response.data.activity.activityDescription
                                });

                                if (--callsLeft === 0) {
                                    callback();
                                }
                            }
                        });
                    }
                }
            }
        });
    }

}
