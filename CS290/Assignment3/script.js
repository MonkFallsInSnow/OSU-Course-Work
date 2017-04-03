/**************************************************************************
 * Author: Conrad Lewin
 * Date: 2/6/2016
 * Class: CS 290
 * Description: This program creates a web page consisting of a table and
 * several buttons that interact with that table. The user will be able to
 * select and mark a cell.
 * *************************************************************************/

/*
 * This functions creates an html table and fills it with content
 */
function createTable() {
    const NUM_ROWS = 4;
    const NUM_COLS = 4;

    //create an html table tag and append it to the body
    var body = document.getElementsByTagName("body");
    var table = document.createElement("table");
    body[0].appendChild(table);
    table.style.border = "1px solid";
    table.style.borderColor = "gray";

    //create table rows and columns and append them to the table
    //give each row an id and assign a class name to each cell in a column
    for (var i = 0; i < NUM_ROWS; i++) {
        var row = document.createElement("tr");
        table.appendChild(row);
        row.id = "row" + i;

        for (var j = 0; j < NUM_COLS; j++) {
            var colNum = j + 1;

            //create a table header and append it to the first row tag
            if (i == 0) {
                var col = document.createElement("th");
                row.appendChild(col);
                col.textContent = "Header " + colNum;
                col.style.border = "1.5px solid";
            }
            //create table cells and append them to the appropriate row
            else {
                col = document.createElement("td");
                row.appendChild(col);
                col.className = "data" + j;
                col.textContent = colNum + ", " + i;
                col.style.border = "1.5px dashed";
            }
        }
    }
}

/*
 * This function creates a button that will interact with the table.
 */
function createButton(label) {
    //create a button tag and append it to the body
    var body = document.getElementsByTagName("body");
    var button = document.createElement("button");
    body[0].appendChild(button);

    //set the button's id and text content
    button.id = label;
    button.textContent = label;

    //create the button's event listener
    button.addEventListener("click", function () {
        if (label != "Mark Cell") {
            return function () {
                moveCell(label)
            }();
        }
        //change the background color of the current cell to yellow
        //if the user clicks the Mark Cell button
        else {
            return function () {
                getCurrentCell().style.backgroundColor = "yellow"
            }();
        }
    });
}

/*
 * This function calls the createTable() and createButton() functions, initializing the starting
 * state of the webpage
 */
function createPage() {
    //create the table and set the cell in the upper left hand corner of the table
    //(not including the header row) to appear selected (gets a thicker border)
    createTable();
    var cells = document.getElementsByTagName("td");
    cells[0].style.border = "solid";

    //create table buttons
    createButton("up");
    createButton("down");
    createButton("left");
    createButton("right");
    createButton("Mark Cell");
}

/*
 * This function returns the currently "selected" cell (indicated by a thick border)
 */
function getCurrentCell(){
    var count = 0;
    var curCell = null;
    var cells = document.getElementsByTagName("td");

    //iterates through the table cells, performing a linear search for the cell
    //with a thick solid border
    while(curCell == null){
        if(cells[count].style.border == "solid"){
            curCell = cells[count];
        }
        count++;
    }

    return curCell;
}

/*
 * This function allows the user to select different cells in the table.
 * The parameter is a button id that indicates which button has been pushed
 */
function moveCell(id){
    //get the currently selected cell
    var curCell = getCurrentCell();

    switch(id){
        //move the selection border up one cell from its current position in a particular column
        //do not move up if the row above the current cell is the header row
        case "up":
            if(curCell.parentNode.id != "row1"){
                curCell.style.border = "1.5px dashed";

                //works, but kind of a hack...
                //get the children of the row that comes before the current row
                //remove all alpha characters from the current cell's class name -> data2 = 2
                //move the selection border to the cell above the current row whose index
                //matches the current cell's sliced class name
                var cols = curCell.parentNode.previousElementSibling.children;
                var index = Number(curCell.className.slice(4));
                cols[index].style.border = "solid";
            }
            break;
        //move the selection border down one cell from its current position in a particular column
        //do not move down if the the currently selected cell is in the last table row
        case "down":
            if(curCell.parentNode.id != "row3"){
                curCell.style.border = "1.5px dashed";

                //works, but kind of a hack...
                //see comment for case "up"
                cols = curCell.parentNode.nextElementSibling.children;
                index = Number(curCell.className.slice(4));
                cols[index].style.border = "solid";
            }
            break;
        //move the selection border to the left one cell from its current position in a particular row
        //do not move left if the the currently selected cell is in the first column
        case "left":
            if(curCell.previousElementSibling != null){
                curCell.style.border = "1.5px dashed";
                curCell.previousElementSibling.style.border = "solid";
            }
            break;
        //move the selection border to the right one cell from its current position in a particular row
        //do not move right if the the currently selected cell is in the last column
        case "right":
            if(curCell.nextElementSibling != null){
                curCell.style.border = "1.5px dashed";
                curCell.nextElementSibling.style.border = "solid";
            }
            break;
        default:
            break;
    }
}

//create the page
createPage();



