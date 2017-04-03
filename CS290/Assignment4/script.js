/******************************************************************************************
 * Author: Conrad Lewin
 * Date: 2/13/2016
 * Description: This program tests asynchronous call functionality by gathering data from
 * openweathermap.org and posting data to httpbin.org. It then displays the response
 * recieved from each website.
 *******************************************************************************************/

var appID = ""; //your appid for openweathermap.org goes here

document.addEventListener("DOMContentLoaded", getWeather);
document.addEventListener("DOMContentLoaded", postPhilosopher);

/*
 * This function makes a request to openweathermap.org for weather data from a specific zipcode or city.
 * This information is then displayed in a list
 */
function getWeather(){
    document.getElementById("submitWeather").addEventListener("click", function(event){
        var req = new XMLHttpRequest();

        var location = document.getElementById("location").value; //get location data

        //check the location variable for a numeric value. a numeric value will get weather data based on a zipcode,
        //while a string of letters will get weather data based on a city name
        if(isNaN(location)){
            req.open("GET", "http://api.openweathermap.org/data/2.5/weather?q=" + location + "&units=imperial&appid=" + appID, true);
        }
        else{
            req.open("GET", "http://api.openweathermap.org/data/2.5/weather?zip=" + location +",us&units=imperial&appid=" + appID, true);
        }

        //waits for a response from openweathermap.org, parses the response to JSON,
        //creates a list if within the form if one does not already
        //exist and then populates it with the returned data
        req.addEventListener("load",function(){
            if(req.status >= 200 && req.status < 400) {
                var response = JSON.parse(req.responseText);

                if(document.getElementsByClassName("weatherList")[0] == null){
                    createList();
                }

                populateList(response);
            }
            else {
                console.log("Error in network request: " + req.statusText);
            }
        });

        req.send(null); //send request
        event.preventDefault(); //prevents submit button from refreshing the page
    });
}

/*
 * This function creates an unordered list in the get weather form that will be used to
 * display weather data recieved from openweathermap.org
 */
function createList(){

    const LST_ITEMS = 4; //number of data items that will be displayed

    var list = document.getElementById("weatherInfo"); //get the list

    //create list item tags and spans to append to the list
    for(var i = 0; i < LST_ITEMS; i++){
        var item = document.createElement("li");
        var label = document.createElement("span");
        var info = document.createElement("span");
        item.className = "weatherList";
        label.className = "infoLabel";
        list.appendChild(item);
        item.appendChild(label);
        item.appendChild(info);
    }

    //get the list items and assign text content to the first span element
    var lstItems = document.getElementsByClassName("weatherList");
    lstItems[0].firstElementChild.textContent = "City: ";
    lstItems[1].firstElementChild.textContent = "Temp: ";
    lstItems[2].firstElementChild.textContent = "Humidity: ";
    lstItems[3].firstElementChild.textContent = "Description: ";
}

/*
 * This function populates a list with weather data. Parameter reqResponse should be
 * JSON parsed data received from openweathermap.org
 */
function populateList(reqResponse){
    const DEGREE_SYM = 176; //the ASCII value for the degree symbol

    //get the list items and assign text content to the second span element
    var lstItems = document.getElementsByClassName("weatherList");
    lstItems[0].lastElementChild.textContent = reqResponse.name;
    lstItems[1].lastElementChild.textContent = reqResponse.main.temp + String.fromCharCode(DEGREE_SYM) + "F";
    lstItems[2].lastElementChild.textContent = reqResponse.main.humidity + "%";
    lstItems[3].lastElementChild.textContent = reqResponse.weather[0].description;
}

/*
 * This function sends a post request to httpbin.org and then displays the response in the
 * favorite philosopher form. This is a test request, so the data that is displayed will be the same
 * data that is being sent
 */
function postPhilosopher(){
    document.getElementById("submitPhil").addEventListener("click",function(event){
        var req = new XMLHttpRequest();
        var info = {name: null, book: null}; //object that stores the data input into the form

        //assign the form data to the appropriate object properties
        info.name = document.getElementById("philName").value;
        info.book = document.getElementById("book").value;

        //open an asynchronous post request and specify the header
        req.open("POST", "http://httpbin.org/post",true);
        req.setRequestHeader("Content-Type", "application/json");

        //waits for a response from httpbin.org/post, parses the response to JSON,
        //and assigns the response data to the appropriate element's text node
        req.addEventListener("load",function(){
            if(req.status >= 200 && req.status < 400){
                var response = JSON.parse(req.responseText);

                document.getElementById("thinker").textContent = response.json.name;
                document.getElementById("treatise").textContent = response.json.book;
            }
            else {
                console.log("Error in network request: " + request.statusText);
            }
        });

        req.send(JSON.stringify(info)); //send the object data
        event.preventDefault(); //prevent the submit button from refreshing the page
    });
}

