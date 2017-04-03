from google.appengine.ext import ndb

class Model(ndb.Model):
	def to_dict(self):
		dictionary = super(Model,self).to_dict()
		dictionary['key'] = self.key.id()
		return dictionary

class Account(ndb.Model):
	pass

class User(ndb.Model):

	fname = ndb.StringProperty(required=True,indexed=True)
	lname = ndb.StringProperty(required=True,indexed=True)
	email = ndb.StringProperty(required=True,indexed=True)
	#password = ndb.StringProperty(required=True,indexed=False)
	username = ndb.StringProperty(required=True,indexed=True)
	gender = ndb.StringProperty(required=True,indexed=True,choices=['male','female','transgender','none'])
	age = ndb.IntegerProperty(required=True,indexed=True)
'''
class DreamDesc(ndb.Model):
	title = ndb.StringProperty(required=True,indexed=True)
	desc = ndb.TextProperty(required=True,indexed=False)
	tags = ndb.StringProperty(indexed=True,repeated=True)
	dreamType = ndb.StringProperty(required=True,indexed=True,choices=['Epic Dream','Lucid Dream','Nightmare','Recurring Dream','False Awakening Dream','Procognitive Dream'])
'''

class Dream(ndb.Model):
	summary = ndb.StringProperty(required=True,indexed=False,default="None")
	date = ndb.DateProperty(required=True,indexed=True,auto_now_add=True)
	mood = ndb.StringProperty(indexed=True,repeated=True)
	#longForm = ndb.StructuredProperty(DreamDesc)
	title = ndb.StringProperty(required=True,indexed=True,default="None")
	desc = ndb.TextProperty(required=True,indexed=False,default="None")
	tags = ndb.StringProperty(indexed=True,repeated=True)
	dreamType = ndb.StringProperty(required=True,indexed=True,choices=['Epic Dream','Lucid Dream','Nightmare','Recurring Dream','False Awakening Dream','Procognitive Dream','None'],default='None')

class Interpretation(ndb.Model):
	method = ndb.StringProperty(required=True,indexed=True,choices=['Psychoanalysis','Jungian Analysis','Gestalt Analysis'])
	content = ndb.TextProperty(required=True,indexed=False)

class Thread(ndb.Model):
	poster = ndb.StringProperty(required=True,indexed=True)
	title = ndb.StringProperty(required=True,indexed=True)
	content = ndb.TextProperty(required=True,indexed=False)
	date = ndb.DateProperty(required=True,indexed=True)
	tags = ndb.StringProperty(indexed=True,repeated=True)

class Comment(ndb.Model):
	commentor = ndb.StringProperty(required=True,indexed=False)
	content = ndb.TextProperty(required=True,indexed=False)
	date = ndb.DateTimeProperty(required=True,indexed=True,auto_now_add=True)
	userId = ndb.KeyProperty(kind=User,required=True,indexed=True)

#---------------------------------------------------------------------------------------------------------------------------------------------------
def createAccount():
	return Account()

def createUser(parentKey,fields):
	return User(parent=parentKey,fname=str(fields['fname']),lname=str(fields['lname']),email=str(fields['email']),
		username=str(fields['username']),gender=str(fields['gender']),age=int(fields['age']))

def createDream(parentKey,fields):
	dream = Dream(parent=parentKey)

	if 'summary' in fields:
		dream.summary = str(fields['summary'])

	if 'mood' in fields:
		dream.mood = fields['mood']

	if 'title' in fields:
		dream.title = str(fields['title'])

	if 'desc' in fields:
		dream.desc = str(fields['desc'])

	if 'tags' in fields:
		dream.tags = fields['tags']

	if 'type' in fields:
		dream.dreamType = fields['type']

	return dream

def saveEntity(entity):
	return entity.put()

