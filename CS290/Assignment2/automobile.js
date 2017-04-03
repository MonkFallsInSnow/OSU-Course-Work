/**************************************************************************
 * Author: Conrad Lewin
 * Date: 1/31/2016
 * Class: CS 290
 * Description: This program sorts an array of Automobile objects depending
 * on the results of a given comparator function and logs these objects
 * to the console in tabular format.
 * *************************************************************************/

function Automobile( year, make, model, type ){
    this.year = year; //integer (ex. 2001, 1995)
    this.make = make; //string (ex. Honda, Ford)
    this.model = model; //string (ex. Accord, Focus)
    this.type = type; //string (ex. Pickup, SUV)
}

var automobiles = [
    new Automobile(1995, "Honda", "Accord", "Sedan"),
    new Automobile(1990, "Ford", "F-150", "Pickup"),
    new Automobile(2000, "GMC", "Tahoe", "SUV"),
    new Automobile(2010, "Toyota", "Tacoma", "Pickup"),
    new Automobile(2005, "Lotus", "Elise", "Roadster"),
    new Automobile(2008, "Subaru", "Outback", "Wagon")
];

/* Automobile prototype function that outputs the property data of the calling object. This
 * function should be called in a loop that iterates through an array of Automobile objects in
 * order to create a data table.
 */
Automobile.prototype.logMe = function(fullReport){
    var info; //stores a string representation of the object

    //creates a string consisting of an automobile's property data,
    //separating each field with a padding of empty spaces
    if(fullReport){
        info = this.year + pad(this.year,8) + this.make + pad(this.make,10) + this.model + pad(this.model,10) + this.type;
        console.log(info);
    }
    else{
        info = this.year + pad(this.year,8) + this.make + pad(this.make,10) + this.model + pad(this.model,10);
        console.log(info);
    }
};

//---helper functions---------------------------------------------------

/* This function determines how much padding to include between each automobile
** property value when using the logMe() function
*/
function pad(element, colWidth){

    var padding = "";
    var prop;

    //make sure the property value is a string
    //and if not, convert it to one
    if(typeof element != "string"){
        prop = element.toString();
    }
    else{
        prop = element;
    }

    //determine the amount of column padding
    for(var i = 0; i < colWidth - prop.length; i++){
        padding += " ";
    }

    return padding;
}

/* This function iterates through the a sorted automobiles array calling logMe() on
 * each object in the array.
 */
function printAuto(comparator,reportType){
    sortArr(comparator,automobiles).forEach(function(currentValue){
        currentValue.logMe(reportType)
    });
}

//---end helper functions---------------------------------------------------

/* This function uses a simple insertion sort to order the given array */
function sortArr( comparator, array ){
    var sortedArr = array.slice(0); //get a copy of the array

    //insertion sort
    sortedArr.forEach(function(currentValue,index){
        var j = index;
        var prev = sortedArr[j-1];

        while (j > 0 && comparator(prev,currentValue)) {
            sortedArr[j] = sortedArr[j - 1];
            j--;
            prev = sortedArr[j-1];
        }

        sortedArr[j] = currentValue;
    });

    return sortedArr;
}

/* This function compares two Automobile year property values */
function yearComparator( auto1, auto2){
    return auto1.year <= auto2.year;
}

/* This function compares two Automobile make property values
 * (Alphabetic and case insensitive)
 */
function makeComparator( auto1, auto2){
    return auto1.make.toLowerCase() >= auto2.make.toLowerCase();
}

/* This function provides a schema by which to order Automobile objects
 * by type (case insensitive)
 */
function typeComparator(auto1, auto2) {
    //each index serves as a rank order, ie automobiles should be sorted in this
    //order (0 = highest rank, 3 = lowest known rank, array.length = lowest possible rank)
    var types = ["roadster", "pickup", "suv", "wagon"];

    //match the automobile type to an index/rank
    var id1 = types.indexOf(auto1.type.toLowerCase());
    var id2 = types.indexOf(auto2.type.toLowerCase());

    //if one or both of the given automobile types are not found in the array
    //then produce an index/rank that is equal to the length of the array - the lowest rank
    if (id1 == -1) {
        id1 *= -(types.length);
    }

    if (id2 == -1) {
        id2 *= -(types.length);
    }

    //similar types are compared by year, otherwise they are compared by rank
    if (id1 == id2) {
        return yearComparator(auto1, auto2);
    }
    else if (id1 < id2) {
        return false;
    }

    return true;
}

//output table data in various orders
var stars = "*****";
console.log("\n"+ stars);

console.log("The cars sorted by year are:" + "\n");
printAuto(yearComparator,false);

console.log("\nThe cars sorted by make are:" + "\n");
printAuto(makeComparator,false);

console.log("\nThe cars sorted by type are:" + "\n");
printAuto(typeComparator,true);

console.log(stars + "\n");


