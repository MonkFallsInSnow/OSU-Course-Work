import sys
import json
import requests

def setHost():
	if len(sys.argv) == 2:
		url = str(sys.argv[1])
	else:
		url = 'http://localhost:8080'

	return url

def queryAccounts(url):
	r = requests.get(url + '/dream-catcher/v1/accounts')
	return r.text,r.headers

def queryUsers(url):
	r = requests.get(url + '/dream-catcher/v1/users')
	return r.text,r.headers

def queryDreams(url):
	r = requests.get(url + '/dream-catcher/v1/dreams')
	return r.text,r.headers

def queryUserWithParams(url,params):
	r = requests.get(url + '/dream-catcher/v1/users',params=params)
	return r.text,r.headers

def queryDreamsWithParams(url,params):
	r = requests.get(url + '/dream-catcher/v1/dreams',params=params)
	return r.text,r.headers 

def queryUserByAccount(url,accId):
	r = requests.get(url + '/dream-catcher/v1/accounts/' + accId + '/users')
	return r.text,r.headers 

def queryDreamByUser(url,accId,userId):
	r = requests.get(url + '/dream-catcher/v1/accounts/' + accId + '/users/' + userId + '/dreams')
	return r.text,r.headers

def queryInvalidKind(url):
	r = requests.get(url + '/dream-catcher/v1/invalid')
	return r.text,r.headers 

def postUser(url,payload):
	r = requests.post(url + '/dream-catcher/v1/accounts/users/queries/1',json=payload)
	return r.text,r.headers  

def postDream(url,accounts,users,payload):
	r = requests.post(url + '/dream-catcher/v1/accounts/users/dreams/queries/1',json=payload)
	return r.text,r.headers

def updateUser(url,accounts,users,payload):
	r = requests.put(url + '/dream-catcher/v1/accounts/users/queries/2',json=payload)
	return r.text,r.headers

def updateDream(url,payload,accounts,users,dreams):
	r = requests.put(url + '/dream-catcher/v1/accounts/users/dreams/queries/2',json=payload)
	return r.text,r.headers

def deleteUser(url,accId,userId):
	r = requests.delete(url + '/dream-catcher/v1/accounts/' + accId + '/users/' + userId)
	return r.text,r.headers

def deleteDream(url,accId,userId,dreamId):
	r = requests.delete(url + '/dream-catcher/v1/accounts/' + accId + '/users/' + userId +'/dreams/' + dreamId)
	return r.text,r.headers

def printResults(text,headers,testId):
	print testId
	print '-------------------------------------------------------------------'
	print 'Response:'
	#print json.dumps(dict(text),indent=4, sort_keys=True)
	print json.dumps(json.loads(text),indent=4, sort_keys=True)
	print '\n'
	print 'Headers:'
	print json.dumps(dict(headers),indent=4, sort_keys=True)
	print '-------------------------------------------------------------------'
	print '\n'

def runPhase1(url):
	'''show the datastore is empty'''

	text,headers = queryAccounts(url)
	printResults(text,headers,'Get All Accounts - eventual consistency only')

	text,headers = queryUsers(url)
	printResults(text,headers,'Get All Users - eventual consistency only')

	text,headers = queryDreams(url)
	printResults(text,headers,'Get All Dreams - eventual consistency only')

	text,headers = queryInvalidKind(url)
	printResults(text,headers,'Get Invalid')

def runPhase2A(url):
	'''add users to the datastore'''

	text,headers = postUser(url,
	{
		'email':'bad@foo.com',
		'username':'badTest',
		'gender':'none',
		'age':'0'
	})
	printResults(text,headers,'Invalid User Post - Missing Keys')

	text,headers = postUser(url,
	{
		'fname':'bart',
		'lname':'lewin',
		'email':'bart@foo.com',
		'username':'blewin',
		'gender':'male',
		'age':'bad val'
	})
	printResults(text,headers,'Invalid User Post - Bad Age Value')

	text,headers = postUser(url,
	{
		'fname':'bart',
		'lname':'lewin',
		'email':'bart@foo.com',
		'username':'blewin',
		'gender':'bad val',
		'age':'65'
	})
	printResults(text,headers,'Invalid User Post - Bad Gender Value')

	text,headers = postUser(url,
	{
		'fname':'conrad',
		'lname':'lewin',
		'email':'conrad@foo.com',
		'username':'clewin',
		'gender':'male',
		'age':'32'
	})
	printResults(text,headers,'Post User 1')
	account1 = json.loads(text)['account']
	user1 = json.loads(text)['user']

	text,headers = postUser(url,
	{
		'fname':'sam',
		'lname':'toman',
		'email':'sam@foo.com',
		'username':'stoman',
		'gender':'female',
		'age':'31'
	})
	printResults(text,headers,'Post User 2')
	account2 = json.loads(text)['account']
	user2 = json.loads(text)['user']

	text,headers = postUser(url,
	{
		'fname':'bart',
		'lname':'lewin',
		'email':'bart@foo.com',
		'username':'blewin',
		'gender':'male',
		'age':'65'
	})
	printResults(text,headers,'Post User 3')
	account3 = json.loads(text)['account']
	user3 = json.loads(text)['user']

	accounts = {'account1':account1,'account2':account2,'account3':account3,'invalid':1}
	users = {'user1':user1,'user2':user2,'user3':user3,'invalid':1}

	return accounts,users

def runPhase2B(url,accounts,users):
	'''get specific users'''

	text,headers = queryUserByAccount(url,str(accounts['invalid']))
	printResults(text,headers,'Get User With Invalid Account ID')

	text,headers = queryUserByAccount(url,str(accounts['account1']))
	printResults(text,headers,'Get User 1 By Account ID')

	text,headers = queryUserByAccount(url,str(accounts['account2']))
	printResults(text,headers,'Get User 2 By Account ID')

	text,headers = queryUserWithParams(url,
	{
		'lnames' : 'lewin',
	})
	printResults(text,headers,'Invalid Query String')

	text,headers = queryUserWithParams(url,
	{
		'lname' : 'lewin' 

	})
	printResults(text,headers,'Find User By Last Name (lewin) - Case Sensitive')

	text,headers = queryUserWithParams(url,
	{
		'lname' : 'lewin',
		'limit' : '1',
		'fields': 'username,gender,age'

	})
	printResults(text,headers,'Find User By Last Name  (lewin); Limit 1 Result; Filter Result Columns - Case Sensitive')

	text,headers = queryUserWithParams(url,
	{
		'lname' : 'Lewin',
		'limit' : '1',
		'fields': 'username,gender,age'

	})
	printResults(text,headers,'Find User By Last Name  (Lewin); Limit 1 Result; Filter Result Columns - Case Sensitive')

def runPhase2C(url,accounts,users):
	'''update a specific user (and show that it has been updated)'''

	text,headers = queryUserByAccount(url,str(accounts['account1']))
	printResults(text,headers,'User 1 - Original')

	text,headers = updateUser(url,accounts,users,
	{
		'account': accounts['invalid'],
		'user': users['user1'],
		'fname':'wrong fname',
		'lname':'wrong lname',

	})
	printResults(text,headers,'Invalid Update of User 1')

	text,headers = queryUserByAccount(url,str(accounts['account1']))
	printResults(text,headers,'User 1 - Update')

	text,headers = queryUserByAccount(url,str(accounts['account3']))
	printResults(text,headers,'User 3 - Original')

	text,headers = updateUser(url,accounts,users,
	{
		'account': accounts['account3'],
		'user': users['user3'],
		'fname':'foo',
		'lname':'bar',
		'gender':'transgender'

	})
	printResults(text,headers,'Update Name and Gender of User 3')

	text,headers = queryUserByAccount(url,str(accounts['account3']))
	printResults(text,headers,'User 3 - Update')

def runPhase3A(url,accounts,users):
	'''post dreams to the datastore'''

	text,headers = postDream(url,accounts,users,
	{
		'summary':'test summary',
		'mood':['scared','calm','happy'],
		'title':'test dream',
		'desc':'test description',
		'tags':['tag1','tag2'],
		'type':'Recurring Dream'
	})
	printResults(text,headers,'Invalid Dream Post - Missing Required Keys')

	text,headers = postDream(url,accounts,users,
	{
		'account': accounts['account1'],
		'user': users['user1'],
		'summary':'test summary',
		'mood':['annoyed','calm','scared'],
		'title':'test dream 2',
		'desc':'test description 2',
		'tags':['tag1','tag2'],
		'type':'Recurring Dream'
	})
	printResults(text,headers,'Post Dream With All Fields - User 1')
	dream1 = json.loads(text)['dream']

	text,headers = postDream(url,accounts,users,
	{
		'account': accounts['account1'],
		'user': users['user1'],
		'summary':'foo bar baz',
		'tags':['tag3'],
		'type':'Epic Dream'
	})
	printResults(text,headers,'Post Dream With Fewer Fields - User 1')
	dream2 = json.loads(text)['dream']

	text,headers = postDream(url,accounts,users,
	{
		'account': accounts['account2'],
		'user': users['user2'],
		'summary':'nightmare dream summary',
		'mood':['worried','disgusted'],
		'title':'nightmare dream title',
		'desc':'nightmare test description',
		'tags':['tag1','tag2','tag3'],
		'type':'Nightmare'
	})
	printResults(text,headers,'Post Dream With All Fields - User 2')
	dream3 = json.loads(text)['dream']

	return {'dream1':dream1,'dream2':dream2,'dream3':dream3,'invalid':1}

def runPhase3B(url,accounts,users):
	'''find specific dreams'''

	text,headers = queryDreamByUser(url,str(accounts['invalid']),str(users['invalid']))
	printResults(text,headers,'Get Dreams From Invalid User')

	text,headers = queryDreamByUser(url,str(accounts['account1']),str(users['user1']))
	printResults(text,headers,'Get Dreams From User 1')

	text,headers = queryDreamByUser(url,str(accounts['account2']),str(users['user2']))
	printResults(text,headers,'Get Dreams From User 2')

	text,headers = queryDreamByUser(url,str(accounts['account3']),str(users['user3']))
	printResults(text,headers,'Get Dreams From User 3')

	text,headers = queryDreamsWithParams(url,
	{
		'type':'Recurring Dream'
	})
	printResults(text,headers,'Search Using Invalid Key')

	text,headers = queryDreamsWithParams(url,
	{
		'dreamType':'Recurring Dream'
	})
	printResults(text,headers,'Find All Recurring Dreams - Case Sensitive')

	text,headers = queryDreamsWithParams(url,
	{
		'dreamType':'Recurring Dream',
		'limit':'1',
		'fields':'title,mood'
	})
	printResults(text,headers,'Find All Recurring Dreams; Limit is 1; Fewer Fields - Case Sensitive')

	text,headers = queryDreamsWithParams(url,
	{
		'dreamType':'Recurring Dream',
		'limit':'1',
		'fields':'title,mood.desc'
	})
	printResults(text,headers,'Find All Recurring Dreams - Invalid Query String')

def runPhase3C(url,accounts,users,dreams):
	'''update a dream (and show that it has been updated)'''

	text,headers = queryDreamByUser(url,str(accounts['account1']),str(users['user1']))
	printResults(text,headers,'User 1 Dream 1- Original')

	text,headers = updateDream(url,accounts,users,dreams,
	{
		'account': accounts['account1'],
		'user': users['user1'],
		'dream': dreams['dream1'],
		'title':'updated dream title',
		'desc':'updated dream description',
		'mood':['update','my','mood']

	})
	printResults(text,headers,'Update User 1 Dream 1')

	text,headers = queryDreamByUser(url,str(accounts['account1']),str(users['user1']))
	printResults(text,headers,'User 1 Dream 1 - Update')

	text,headers = queryDreamByUser(url,str(accounts['account1']),str(users['user1']))
	printResults(text,headers,'User 2 Dream 1 - Original')

	text,headers = updateDream(url,accounts,users,dreams,
	{
		'user': users['user2'],
		'dream': dreams['dream3'],
		'title':'bad',

	})
	printResults(text,headers,'Update User 2 Dream 1 - Invalid Request')

	text,headers = queryDreamByUser(url,str(accounts['account1']),str(users['user1']))
	printResults(text,headers,'User 2 Dream 1 - Update')

def runPhase4A(url,accounts,users,dreams):
	'''delete users and dreams'''
	text,headers = deleteDream(url,str(accounts['account2']),str(users['user2']),str(dreams['dream3']))
	printResults(text,headers,'Removing Dream 1 From User 2')

	text,headers = queryDreamByUser(url,str(accounts['account2']),str(users['user2']))
	printResults(text,headers,'Get Dreams From User 2')

	text,headers = deleteDream(url,str(accounts['account2']),str(users['user2']),str(dreams['dream3']))
	printResults(text,headers,'Remove Non-Existant Dream')

	text,headers = deleteUser(url,str(accounts['account1']),str(users['user1']))
	printResults(text,headers,'Removing User 1')

	text,headers = deleteUser(url,str(accounts['account2']),str(users['user2']))
	printResults(text,headers,'Removing User 2')

	text,headers = deleteUser(url,str(accounts['account3']),str(users['user3']))
	printResults(text,headers,'Removing User 3')

def runPhase4B(url,accounts,users):
	'''prove datastore is empty'''

	text,headers = queryUserByAccount(url,str(accounts['account1']))
	printResults(text,headers,'User 1 Should Be Gone')

	text,headers = queryUserByAccount(url,str(accounts['account2']))
	printResults(text,headers,'User 2 Should Be Gone')

	text,headers = queryUserByAccount(url,str(accounts['account3']))
	printResults(text,headers,'User 3 Should Be Gone')

	text,headers = queryDreamByUser(url,str(accounts['account1']),str(users['user1']))
	printResults(text,headers,'User 1 Dreams Should Be Gone')

	text,headers = queryDreamByUser(url,str(accounts['account2']),str(users['user2']))
	printResults(text,headers,'User 2 Dreams Should Be Gone')

	text,headers = queryDreamByUser(url,str(accounts['account3']),str(users['user3']))
	printResults(text,headers,'User 3 Dreams Should Be Gone')

	text,headers = queryAccounts(url)
	printResults(text,headers,'All Accounts Should Be Gone - Eventual Consistency')

def runTests():
	url = setHost()
	print '#########PHASE 1#############'
	print '\n'
	runPhase1(url)

	print '#########PHASE 2A############'
	print '\n'
	accounts,users = runPhase2A(url)

	print '#########PHASE 2B############'
	print '\n'
	runPhase2B(url,accounts,users)

	print'#########PHASE 2C#############'
	print '\n'
	runPhase2C(url,accounts,users)

	print'#########PHASE 3A#############'
	print '\n'
	dreams = runPhase3A(url,accounts,users)

	print'#########PHASE 3B#############'
	print '\n'
	runPhase3B(url,accounts,users)

	print'#########PHASE 3C#############'
	print '\n'
	runPhase3C(url,accounts,users,dreams)

	print'#########PHASE 4A#############'
	print '\n'
	runPhase4A(url,accounts,users,dreams)
	
	print'#########PHASE 4B#############'
	print '\n'
	runPhase4B(url,accounts,users)
	





if __name__ == '__main__':
    runTests()