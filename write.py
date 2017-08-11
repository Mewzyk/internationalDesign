import json
	
class Object:
	def toJSON(self):
		return json.dumps(self, default=lambda o: o.__dict__, sort_keys=True, indent=4)

class Tile:
	moveDirs = 0
	token = '-'

	def __init__(self):
		self.moveDirs = 0
		self.token = '-'

me = Object()
me.turn = "0"
me.p1Token = "x"
me.p2Token = "^"
me.turnCount = "5"

board = [[Tile() for _ in range(8)] for _ in range(8)]
me.board = board

file_object = open("db.json", "a")
file_object.write(me.toJSON())
file_object.close()
