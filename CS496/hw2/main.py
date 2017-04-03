import ndbController as cntrl
import logging
from datetime import datetime
from flask import Flask, render_template, request, redirect, url_for
app = Flask(__name__)


@app.route('/')
def renderIndex():
	return render_template('index.html')


@app.route('/record', methods=['GET','POST'])
def renderRecordForm():
	recorded = False

	if request.method == 'POST':
		recorded = True

		#dream entity properties initialized with form data from record.html
		date = datetime.strptime(request.form['dreamDate'], '%Y-%m-%d')
		title = request.form['dreamTitle']
		desc = request.form['dreamDesc']
		dreamType = request.form['dreamType']
		dreamMoods = request.form.getlist('dreamMood')
		tags = request.form.get('dreamTags').split(',')

		#creates a dream entity and saves it into the data store
		dream = cntrl.createEntity(date,title,desc,dreamType,dreamMoods,tags)
		dreamKey = cntrl.saveEntity(dream)

		return render_template('record.html',moods=cntrl.moods,dreamTypes=cntrl.dreamTypes,recorded=recorded,title=title)
	else:
		return render_template('record.html',moods=cntrl.moods,dreamTypes=cntrl.dreamTypes,recorded=recorded)

@app.route('/review',methods=['GET','POST'])
def renderReviewForm():
	if request.method == 'GET':
		query = cntrl.fetchAllDreams()
		if len(query) > 0:
			results = cntrl.convertQueryToList(query)
			return render_template('review.html',hasResults=True,query=results)
		else:
			msg = 'You have no dreams recorded.'
			return render_template('review.html',msg=msg)
	else:
		dream = cntrl.getEntityByUrlKey(request.form['entityKey'])
		test = cntrl.deleteDream(dream)
		return redirect(url_for('.renderReviewForm'))


@app.route('/edit-dream',methods=['GET','POST'])
def renderEditForm():
	if request.method == 'GET':
		if 'key' in request.args:
			dream = cntrl.getEntityByUrlKey(request.args['key'])
			return render_template('edit-dream.html',key=request.args['key'],dreamTypes=cntrl.dreamTypes,dreamMoods=cntrl.moods,
				date=dream.date,title=dream.title,desc=dream.desc,type=dream.dreamType,moods=dream.moods,tags=dream.tags)
		else:
			return redirect(url_for('.renderReviewForm'))
	else:
		dream = cntrl.getEntityByUrlKey(request.args['key'])
		
		#dream entity properties initialized with form data from record.html
		date = datetime.strptime(request.form['dreamDate'], '%Y-%m-%d')
		title = request.form['dreamTitle']
		desc = request.form['dreamDesc']
		dreamType = request.form['dreamType']
		dreamMoods = request.form.getlist('dreamMood')
		tags = request.form.get('dreamTags').split(',')

		cntrl.updateDream(dream,date,title,desc,dreamType,dreamMoods,tags)
		return render_template('edit-dream-status.html')



#the following two routes will be used in future assigments
@app.route('/sign-up')
def renderSignUpForm():
	return render_template('sign-up.html')


@app.route('/login')
def renderLogInForm():
	return render_template('login.html')
#end routes for the future




@app.errorhandler(500)
def server_error(e):
    # Log the error and stacktrace.
    logging.exception('An error occurred during a request.')
    return 'An internal error occurred.', 500

if __name__ == "__main__":
    app.run()