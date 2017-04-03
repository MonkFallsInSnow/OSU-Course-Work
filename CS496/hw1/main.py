from time import strftime
from flask import Flask
app = Flask(__name__)

@app.route('/')
def showTime():
	payload = {'q':'Raleigh'}
	date = strftime('%m/%d/%y')
	time = strftime('%I:%M:%S %p')
	
	htmlString = '''
		<html>
			<head>
				<title>CS 496 HW 1</title>
			</head>
			<body>
				<h1>Server Date & Time</h1>
				<p>{}</p>
				<p>{} UTC</p>
			</body>
		</html>
	'''.format(date,time)

	return htmlString

if __name__ == "__main__":
    app.run()