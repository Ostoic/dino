class Account:
	def __init__(self, username, password, first_name = None, last_name = None):
		if first_name is not None:
			first_name = username
		self.username = username
		self.password = password
		self.first_name = first_name
		self.last_name = last_name

	username = None
	password = None
	first_name = None
	last_name = None
