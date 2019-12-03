from hashlib import sha256
from random import random
from . import db

# Hash username with random salt
def make_token(username):
	hash = sha256()
	hash.update('{}{}'.format(username, random()).encode())
	return hash.hexdigest()
	
sessions = []

def find(token):
	return next(filter(lambda session: session.token() == token, sessions), None)
	
def user_has_session(username):
	for session in sessions:
		if session.account_data().username == username:
			return True
	return False

class Session:
	def __init__(self, account_data = None, token = None):
		if account_data is not None:
			self.__account_data = account_data
			self.login(account_data.username, account_data.password)
		elif token is not None:
			session = find(token)
			if session:
				self = session

	def login(self, username, password):
		account_data = db.find_account(username = username)
		if not account_data:
			return False
			
		if account_data.password == password:
			self.__token = make_token(account_data.username)
			self.__account_data = account_data
			sessions.append(self)
			print('Session added: {}'.format(self))
			return True
			
		return False
		
	def logout(self):
		print('Session remove: {}'.format(self))
		self.__token = None
		sessions.remove(self)
		
	def logged_in(self):
		return self.token() is not None
		
	def token(self):
		return self.__token
		
	def account_data(self):
		return self.__account_data
		
	def __str__(self):
		if self.logged_in():
			return '{}:{}'.format(self.__account_data.username, self.__token)
		else:
			return 'Dropped session'
	
	__account_data = None
	__token = None
	