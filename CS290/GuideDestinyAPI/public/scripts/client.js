var textbox = document.getElementById("playerId");
var accountRadio = document.getElementsByName("accountType");
var characterRadio = document.getElementsByName("characterNum");
var submitBtn = document.getElementById("submitBtn");

document.addEventListener("DOMContentLoaded", function(event) {
    submitBtn.disabled = true;
});

textbox.addEventListener("input",function(event){
    if(textbox.value != "" && (accountRadio[0].checked || accountRadio[1].checked) && (characterRadio[0].checked || characterRadio[1].checked || characterRadio[2].checked)){
        submitBtn.disabled = false;
    }

    if(accountRadio[2].checked) {
        submitBtn.disabled = false;
    }
});

for(var i = 0; i < accountRadio.length; i++) {
    if(accountRadio[i].value == "none"){
        accountRadio[i].addEventListener("click",function(event){
            submitBtn.disabled = false;
        });
    }
    else {
        accountRadio[i].addEventListener("click", function (event) {
            if (textbox.value != "" && (characterRadio[0].checked || characterRadio[1].checked || characterRadio[2].checked)) {
                submitBtn.disabled = false;
            }
        });
    }
}

for(var i = 0; i < accountRadio.length; i++){
    characterRadio[i].addEventListener("click",function(event){
        if(textbox.value != "" && (accountRadio[0].checked || accountRadio[1].checked)){
            submitBtn.disabled = false;
        }
    });
}

document.getElementById("submitBtn").addEventListener("click",function(event){
    var req = new XMLHttpRequest();
    var payload = {playerId:null,accountType:null,characterNum:null};
    payload.playerId = textbox.value;
    for(var i = 0; i < accountRadio.length; i++) {
        if(accountRadio[i].checked) {
            payload.accountType = accountRadio[i].value;
        }
    }
    for(var i = 0; i < characterRadio.length; i++) {
        if(characterRadio[i].checked) {
            payload.characterNum = characterRadio[i].value;
        }
    }
    req.open("POST", "/characterData",true);
    req.setRequestHeader("Content-Type", "application/json");
    req.send(JSON.stringify(payload));
});

