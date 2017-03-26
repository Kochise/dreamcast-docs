######################
# (c)Paul Boese 2001 #
######################
#
# 2001/09/10 22:06:10
# Revision: 1.0.1
#
# Note before using this to export you MUST make sure your meshes consist
# of only triangle polygons. You must also join the meshes into one mesh.
# This script only exports one mesh with one texture. For complex objects
# I suggest you save your work before joining your meshes =)
# 
# This script runs under Blender 2.12 for sure but not 2.20.
#
# Thanks the Jan Walter for his Blender export examples
#
import Blender

class DCExport:
	def __init__(self, filename):
		self.file = open(filename, "w")

	def export(self, scene):
		print "exporting DC header file..."
		self.writeHeader()
		for name in scene.objects:
			object = Blender.getObject(name)
			if object.type == "Mesh":
				mesh = Blender.getMesh(object.data)
				self.writeStuff(name, object, mesh, normals = 0)
		self.writeEnd()

	def writeEnd(self):
		self.file.write("#define MESH_VERTICES (sizeof(mesh_coords)/sizeof(float))/3\n")
		self.file.write("#define MESH_FACE_IDXS sizeof(mesh_face_idx)/sizeof(int)\n")
		self.file.write("#define MESH_UVS (sizeof(mesh_uv)/sizeof(float))/2\n\n")
		self.file.write("#endif /* __MESH_DATA_H */\n")
		self.file.close()
		print " ... finished exporting DC header file."

	def writeHeader(self):
		self.file.write("/* Surface data - Blender Export - dcexport.py */\n\n")
		self.file.write("#ifndef __MESH_DATA_H\n")
		self.file.write("#define __MESH_DATA_H\n\n")

	def writeStuff(self, name, object, mesh, normals = 0):
		self.file.write("/* Vertices */\n")
		self.file.write("float mesh_coords[][3] = {\n")
		for vertex in mesh.vertices:
			self.file.write("{%s, %s, %s},\n" % (vertex[0], vertex[1], vertex[2]))
		self.file.write("};\n\n")
		# faces
		self.file.write("/* Faces */\n")
		self.file.write("int mesh_face_idx[] = {\n")
		for face in mesh.faces:
			if face[2] != 0:
				if face[3] == 0 and face[4] == 1:
					# triangle
					self.file.write("%s, %s, %s, -1,\n" % (face[0], face[1], face[2]))
				elif face[3] != 0 and face[4] == 1:
					# quad
					self.file.write("%s, %s, %s, %s, -1,\n" % (face[0], face[1], face[2], face[3]))
		for face in mesh.faces:
			if face[2] != 0:
				if face[3] == 0 and face[4] == 0:
					# triangle
					self.file.write("%s, %s, %s, -1,\n" % (face[0], face[1], face[2]))
				elif face[3] != 0 and face[4] == 0:
					# quad
					self.file.write("%s, %s, %s, %s, -1,\n" % (face[0], face[1], face[2], face[3]))
		self.file.write("};\n\n")
		# texture
		if mesh.texture:
			self.file.write("/* Texture Coords per vertex per face */\n")
			self.file.write("float mesh_uv[][2] = {\n")
			for face in mesh.texcoords:
				for texcoord in face:
					self.file.write("%s, %s,\n" % (texcoord[0], texcoord[1]))
			self.file.write("};\n\n")
		else:
			self.file.write("/* No Texture!!! */\n")
			self.file.write("float mesh_uv[][2] = { };\n\n")
			print " *** Oops *** No Texture *** "

dcexport = DCExport("mesh_data.h")
scene = Blender.getCurrentScene()
dcexport.export(scene)

