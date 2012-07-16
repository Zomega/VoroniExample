import string

class point:
	name = None
	x = 0
	y = 0
	z = 0
	def __init__( self, x, y, z, name = None ):
		self.x = x
		self.y = y
		self.z = z
		self.name = name
	def __str__( self ):
		result =  "<point\t"
		if self.name != None:
			result += "name=\"" + str(self.name) + "\"\t"
		result += "x=\"" + str(self.x) + "\"\t"
		result += "y=\"" + str(self.y) + "\"\t"
		result += "z=\"" + str(self.z) + "\"\t"
		result += "/>"
		return result

def writePointcloud( filename, points ):
	outfile = open(filename, 'w')
	outfile.write("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n")
	outfile.write("<?scene version=\"0.1\"?>\n")
	outfile.write("<scene>\n")
	for point in pointcloud:
		outfile.write("\t"+str(point)+"\n")
	outfile.write("</scene>")

def loadPointcloud( filename ):
	pointcloud = []
	prefile = open(filename, 'r')
	for line in prefile:
		[x,y,z] = [ float( num ) for num in line.split() ]
		pointcloud.append( point(x,y,z) )
	return pointcloud

pointcloud = loadPointcloud('bunny1.pre')
print "Points are loaded. Writing to file..."
writePointcloud("bunny1.scene", pointcloud)
print "Done! Exiting..."
