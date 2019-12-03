import flask
from flask import request
from flask_cors import CORS
from functools import wraps

from .session import Session
from .session import find as find_session
from .session import user_has_session

from .db import accounts

app = flask.Flask(__name__)
CORS(app)

@app.errorhandler(404)
def not_found(error):
    return flask.make_response(flask.jsonify({'error': 'Page not found'}), 404)

@app.errorhandler(401)
def acess_denied(error):
    return flask.make_response(flask.jsonify({'error': 'Access denied'}), 401)
	
	
def cors_jsonify(message):
	response = flask.jsonify(message)
	response.headers.add('Access-Control-Allow-Origin', '*')
	return response
	
def make_error(message):
	return cors_jsonify({
		'error': message
	})
	
# Fix this decorator
def authorized_route(fn):
	@wraps(fn)
	def wrapper(rule, **options):
		endpoint = options.pop("endpoint", None)
		app.add_url_rule(rule, endpoint, lambda: wrapper(fn), **options)
		
		if request.json is None:
			return make_error('Content must be in json format')
			
		token = request.json.get('token')
		session = find_session(token)
		if not session.logged_in():
			return make_error('Not logged in')
			
		return lambda: fn(session)
		
	return wrapper

@app.route('/')
def hello(): 
	return "Hello Ade!\r\nI have implemented a basic login service at the /login route.\r\nTo login, send a POST request to /login with either\r\nusername and password, or your session key"

@app.route('/login', methods = ['POST'])
def login():
	if request.json is None:
		return make_error('Content must be in json format')
		
	username = request.json.get('username')
	password = request.json.get('password')
	
	if username is None or password is None:
		return make_error('Username and password requird')
	
	session = Session()
	if user_has_session(username):
		return make_error('User already logged in')
		
	if not session.login(username, password):
		return make_error('Invalid username or password')
		
	return cors_jsonify({
		'success': 'logged in',
		'token': session.token()
	})
		
@app.route('/logout', methods = ['PUT'])
def logout():
	if request.json is None:
		return make_error('Content must be in json format')
		
	token = request.json.get('token')
	session = find_session(token)
	if session is None or not session.logged_in():
		return make_error('Not logged in')

	session.logout()
	return cors_jsonify({
		'success': 'logged out'
	})
	
		
@app.route('/user-exists', methods = ['GET'])
def user_exists():
	if request.json is None:
		return make_error('Content must be in json format')
		
	username = request.json.get('username')
	if accounts.find_account(username) is not None:	
		return cors_jsonify({
			'result': 'user exists'
		})
	else:
		return cors_jsonify({
			'result': 'user does not exist'
		})
		

@app.route('/account/summary')
def account_summary():
	if request.json is None:
		return make_error('Content must be in json format')
		
	token = request.json.get('token')
	session = find_session(token)
	if session is None or not session.logged_in():
		return make_error('Not logged in')

	return cors_jsonify({
		'username': session.account_data().username,
		'first_name': session.account_data().first_name,
		'last_name': session.account_data().last_name
	})

def start(host, port = '63122'):
	app.run(host = host, port = port)
