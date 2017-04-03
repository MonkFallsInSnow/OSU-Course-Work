import sys
import os
from google.appengine.ext import vendor

# Add any libraries installed in the "lib" folder.
vendor.add('lib')

# needed to overide bug when using Flask and Click
if os.environ.get('SERVER_SOFTWARE','').startswith('Google App Engine'):
	sys.path.insert(0,'lib.zip')
else:
	if os.name == 'nt':
		os.name = None
		sys.platform = ''