google.charts.load('current', {packages: ['corechart']});
google.charts.setOnLoadCallback(drawChart);

function drawChart(){
    var types = JSON.parse(ChartData.getData());

    var data = new google.visualization.DataTable();
    data.addColumn('string','Dream Types');
    data.addColumn('number','Type Count');

    for(var key in types){
        console.log("KEYS ----> " + key + " COUNT ----> " + types[key])
        data.addRow([key,parseInt(types[key])])
    }

    var chart = new google.visualization.PieChart(document.getElementById('chart'));

    var options = {title:'Dream Type Report',is3D:true};
    chart.draw(data, options);
}