#!BPY

# Blender simple export plugin by Christian Henz

"""
Name: 'C code (.h)...'
Blender: 232
Group: 'Export'
Tooltip: 'Export selected mesh to C code (*.h)'
"""

__bpydoc__ = """\
"""

import Blender

def write(filename):

	file = open(filename, "wb")

	objects = Blender.Object.GetSelected()
	objname = objects[0].name
	meshname = objects[0].data.name
	mesh = Blender.NMesh.GetRaw(meshname)

	obj = Blender.Object.Get(objname)

	file.write( "/* Generated file, do not edit! */\n" )
	file.write( "/* Object: %s */\n" % objname )

	file.write( "const int %s_num_vertices = %d; \n" % ( objname, len( mesh.verts ) ) )
	file.write( "const float %s_vertices[%d][3] = { \n" % ( objname, len( mesh.verts ) ) )

	for i in range( len( mesh.verts ) ):
		x, y, z = mesh.verts[i].co
		file.write( "  { %ff, %ff, %ff }, \n" % ( x, y, z ) )

	file.write( "}; \n" );


	file.write( "const int %s_num_triangles = %d; \n" % ( objname, len( mesh.faces ) ) )
	file.write( "const int %s_triangles[%d][3] = { \n" % ( objname, len( mesh.faces ) ) )

	for i in range( len( mesh.faces ) ):
	
		if len( mesh.faces[ i ].v ) == 3:
			file.write( "  { %d, %d, %d }, \n" % ( mesh.faces[ i ].v[0].index, mesh.faces[ i ].v[1].index, mesh.faces[ i ].v[2].index ) )
		else:
			print "Warning: Dropping non-triangle!!!"

	file.write( "}; \n" );

	
	file.write( "const int %s_num_materials[%d][4] = { \n" % (objname, len( mesh.materials ) ) )
	file.write( "const float %s_materials[%d][4] = { \n" % (objname, len( mesh.materials ) ) )
	
	for m in mesh.materials:

		file.write( "  { %ff, %ff, %ff, %ff }, \n" % ( m.R, m.G, m.B, m.alpha ) )
	
	file.write( "}; \n" );


	file.write( "const int %s_triangle_materials[%d] = { \n" % ( objname, len( mesh.faces ) ) )

	for i in range( len( mesh.faces ) ):
	
		if len( mesh.faces[ i ].v ) == 3:
			file.write( "  %d, \n" % ( mesh.faces[ i ].materialIndex ) )
		else:
			print "Warning: Dropping non-triangle!!!"

	file.write( "}; \n" );


	file.write( "const float %s_triangle_normals[%d][3] = { \n" % (objname, len( mesh.faces ) ) )

	for t in mesh.faces:

		if len( t.v ) == 3:
			file.write( "  { %ff, %ff, %ff }, \n" % ( t.normal[0], t.normal[1], t.normal[2] ) )
		else:
			print "Warning: Dropping non-triangle!!!"

	file.write( "}; \n" );
	

	file.write( "const float %s_vertex_normals[%d][3] = { \n" % (objname, len( mesh.verts ) ) )
	
	for v in mesh.verts:

		file.write( "  { %ff, %ff, %ff }, \n" % ( v.no[0], v.no[1], v.no[2] ) )

	file.write( "}; \n" );


	file.close()

def fs_callback( filename ):
	if filename.find( '.h', -2 ) <= 0: filename += '.h'
	write( filename )

Blender.Window.FileSelector( fs_callback, "Export C code" )
