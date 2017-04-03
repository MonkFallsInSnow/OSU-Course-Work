//get DOM elements
var exercise = document.getElementById('name');
var reps = document.getElementById('reps');
var weight = document.getElementById('weight');
var date = document.getElementById('date');
var lbs = document.getElementById('lbs');
var submitBtn = document.getElementById('submitBtn');

//sends a post request to the server to update the database table
//id - primary key of the row to update
function postEdit(id){
    //form an AJAX request and its contents
    var request = new XMLHttpRequest();
    var payload = {
        id: id,
        name: document.getElementById('name' + id).value,
        reps: document.getElementById('reps' + id).value,
        weight: document.getElementById('weight' + id).value,
        date: document.getElementById('date' + id).value,
        lbs: document.getElementById('lbs' + id).value,
        btnType: 'edit'
    };

    request.open('POST','/',true); //open a post request

    //gets a status update from the server on the state of the database
    request.addEventListener('load',function() {
        if (request.status >= 200 && request.status < 400) {
            document.getElementById('status').textContent = request.responseText;
        }
    });

    //send the request
    request.setRequestHeader("Content-Type", "application/json");
    request.send(JSON.stringify(payload));

    event.preventDefault();
}

//sends a post request to the server to delete a row from the database table
//id - primary key of the row to update
function postDel(id){
    //form an AJAX request and its content
    var request = new XMLHttpRequest();
    var payload = {
        id: id,
        btnType: 'delete'
    };

    request.open('POST','/',true); //open a post request

    //gets a status update from the server on the state of the database
    request.addEventListener('load',function() {
        if (request.status >= 200 && request.status < 400) {
            document.getElementById('status').textContent = request.responseText;
        }
    });

    //send request
    request.setRequestHeader("Content-Type", "application/json");
    request.send(JSON.stringify(payload));

    deleteRow(payload.id); //delete the row from the html table

    //hide the header row if all html table rows have been removed
    var rows = document.getElementsByClassName('hiddenInput');
    if(rows.length == 0){
        document.getElementById('workoutTable').hidden = true;
    }

    event.preventDefault();
}

/* creates a button to edit/delete a row in the database table
** row - which row the edit/delete button should be added to, id - primary key of the row
** eventFunc - onclick event function, btnType - requires a string 'edit' for an edit button. anything else
** will produce a delete button
*/
function createBtn(row,id,eventFunc,btnType){
    //create cell and button
    var cell = document.createElement('td');
    var btn = document.createElement('input');

    //define button attributes
    if(btnType == 'edit'){
        btn.value = 'Edit';
    }
    else{
        btn.value = 'Delete';
    }
    btn.type = 'submit';
    btn.className = 'buttons';
    btn.onclick = function(){
        eventFunc(id);
    };

    //add the button to the html table/form
    row.appendChild(cell);
    cell.appendChild(btn);
}

//creates an html table within a form to store workout data
//content - server response from a sequel query
function makeTable(content){
    //get table elements and create row
    var table = document.getElementById('workoutTable');
    var header = document.getElementById('header');
    var row = document.createElement('tr');

    table.hidden = false; //hide the table

    //if there is no header row, then create one
    if(header == null){
        var headerRow = document.createElement('tr');
        headerRow.id = 'header';
        table.appendChild(headerRow);

        for(prop in content[0]){
            if(prop != 'id') {
                var newHeader = document.createElement('th');
                headerRow.appendChild(newHeader);
                newHeader.textContent = prop.toString().toUpperCase();
            }
        }
    }

    //create a hidden input and append it to the latest row
    table.appendChild(row);
    var hiddenField = document.createElement('input');
    hiddenField.type = 'hidden';
    hiddenField.id = content[0].id;
    hiddenField.className = 'hiddenInput';
    row.appendChild(hiddenField);

    //create table cells and fill them with textboxes occupied by the submitted form data
    for (prop in content[0]) {
        if (prop != 'id') {
            var data = document.createElement('td');
            var field = document.createElement('input');
            row.appendChild(data);
            data.appendChild(field);
            field.type = 'text';
            field.value = content[0][prop];
            field.id = prop.toString() + hiddenField.id;
        }
    }

    //print a status message and return an object containing the current row and id
    document.getElementById('status').textContent = 'Status: Row successfully inserted into database.';
    return {row: row, hidden: hiddenField.id};
}

//deletes an row from the html table
//id - id of the row to delete
function deleteRow(id){
    //get all hidden inputs and initialize an index
    var rows = document.getElementsByClassName('hiddenInput');
    var index = 0;

    //iterate through the collection of hidden inputs searching for a particular id,
    //then delete the row that matches that id
    Array.prototype.forEach.call(rows, function(row){
        index++;
        if(row.id == id){
            document.getElementById('workoutTable').deleteRow(index);
            return;
        }
    });
}

//inserts a row into html table
//content - server response from a sequel query
function insertRow(content){
    var rowData = makeTable(content); //add a row to the html table
    createBtn(rowData.row,rowData.hidden,postEdit,'edit'); //create edit button
    createBtn(rowData.row,rowData.hidden,postDel,'delete'); //create delete button
}

//form submit button event listener
submitBtn.addEventListener('click',function(event){
    var btnType = document.getElementById('insert'); //get form submit button
    var valid = true; //boolean flag indicating whether or not all form fields are filled

    //form a AJAX request and its content
    var request = new XMLHttpRequest();
    var payload = {
        name: exercise.value,
        reps: reps.value,
        weight: weight.value,
        date: date.value,
        lbs: lbs.value,
        btnType: btnType.name
    };

    //ensure all form fields have data
    for(prop in payload){
        if(payload[prop] == ""){
            valid = false;
            document.getElementById('status').textContent = 'Status: Unable to insert row. Make sure all form fields have data.'
        }
    }

    //send the request if all form fields have data, then insert the row into the html and database table
    if(valid) {

        request.open('POST', '/', true);

        request.addEventListener('load', function () {
            if (request.status >= 200 && request.status < 400) {
                var response = JSON.parse(request.responseText);
                insertRow(response);
            }
        });

        //send the request
        request.setRequestHeader("Content-Type", "application/json");
        request.send(JSON.stringify(payload));
    }

    event.preventDefault();
});