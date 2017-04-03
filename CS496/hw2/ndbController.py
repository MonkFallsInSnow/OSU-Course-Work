from google.appengine.ext import ndb

dreamTypes = ['Epic Dream','Lucid Dream','Nightmare','Recurring Dream','False Awakening Dream','Procognitive Dream']
moods = ['Scared','Calm','Happy','Indifferent','Shocked','Enthusiastic','Sad','Disgusted','Ashamed','Confused',
'Encouraged','Amazed','Envious','Amused','Hopeful','Composed','Lustful','Worried']

class Dream(ndb.Model):
	date = ndb.DateProperty()
	title = ndb.StringProperty()
	desc = ndb.TextProperty()
	dreamType = ndb.StringProperty()
	moods = ndb.StringProperty(repeated=True)
	tags = ndb.StringProperty(repeated=True)

def createEntity(dateDream,titleDream,descDream,typeDream,moodsDream,tagsDream):
	dreamKey = ndb.Key(Dream,'dream-group')
	dream = Dream(parent=dreamKey,date=dateDream,title=titleDream,desc=descDream,dreamType=typeDream,moods=moodsDream,tags=tagsDream)
	return dream

def saveEntity(dreamEntity):
	dreamKey = dreamEntity.put()
	return dreamKey
	
def getEntity(dreamKey):
	dreamEntity = dreamKey.get()
	return dreamEntity

def getEntityByUrlKey(urlKey):
	dreamKey = ndb.Key(urlsafe=urlKey)
	dreamEntity = dreamKey.get()
	return dreamEntity

def fetchAllDreams():
	query = Dream.query(ancestor=ndb.Key(Dream,'dream-group')).order(Dream.date).fetch()
	return query

def convertQueryToList(query):
	lst = [{'key' : elem.key.urlsafe(),'date' : elem.date,'title' : elem.title,'desc' : elem.desc,'dreamType' : elem.dreamType,
	'moods' : elem.moods,'tags' : elem.tags} for elem in query]
  	return lst

def updateDream(dream,dateDream,titleDream,descDream,typeDream,moodsDream,tagsDream):
	dream.date = dateDream
	dream.title = titleDream
	dream.desc = descDream
	dream.type = typeDream
	dream.moods = moodsDream
	dream.tags = tagsDream
	dream.put()

def deleteDream(dreamEntity):
	dreamEntity.key.delete()

#you can add an interpt dream class later that allows the user to write comments interpreting their dreams
#these comments can be stored as children of the Dream entities in the ndb datastore
#add and interpet dream webpage and link in navbar