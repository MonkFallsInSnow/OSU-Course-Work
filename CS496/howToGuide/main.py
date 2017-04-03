import logging
from flask import Flask, render_template
app = Flask(__name__)


@app.route('/')
def renderIndex():
	return render_template('index.html')

@app.route('/basic-chart-1')
def renderBasicChartSetup():
	return render_template('basic-chart-1.html')

@app.route('/basic-chart-2')
def renderBasicChartAssets():
	return render_template('basic-chart-2.html')

@app.route('/basic-chart-3')
def renderBasicChartDraw():
	return render_template('basic-chart-3.html')

@app.route('/chart-data-1')
def renderChartDataUserInput():
	return render_template('chart-data-1.html')

@app.route('/chart-data-2')
def renderChartDataHttpRequest():
	return render_template('chart-data-2.html')

@app.route('/chart-customization-1')
def renderChartCustomizationControls():
	return render_template('chart-customization-1.html')

@app.route('/resources')
def renderResources():
	return render_template('resources.html')

@app.errorhandler(500)
def server_error(e):
    # Log the error and stacktrace.
    logging.exception('An error occurred during a request.')
    return 'An internal error occurred.', 500

if __name__ == "__main__":
    app.run()