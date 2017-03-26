#include "buggy.h"
#include <pcx/pcx.h>
#include <jpeg/jpeg.h>
/*

buggy ODE 0.5 demo 

ported by L@ Cible

modified for ODE 0.5 by heinrich tillack (a128.ch9.de)
*/

// Load a texture ufsing pcx_load_texture and glKosTex2D 
static void loadtxr(const char *fn, GLuint *txr) 
{
    kos_img_t img;
    pvr_ptr_t txaddr;
	
    if (pcx_to_img(fn, &img) < 0) {
        printf("can't load %s\n", fn);
        return;
    }
	
    txaddr = pvr_mem_malloc(img.w * img.h * 2);
    pvr_txr_load_kimg(&img, txaddr, PVR_TXRLOAD_INVERT_Y);
    kos_img_free(&img, 0);
	
    glGenTextures(1, txr);
	
    glBindTexture(GL_TEXTURE_2D, *txr);
	
    glKosTex2D(GL_RGB565_TWID, img.w, img.h, txaddr);
}


// Load a texture ufsing pcx_load_texture and glKosTex2D 
static void loadtxr_jpg(const char *fn, GLuint *txr) 
{
    kos_img_t img;
    pvr_ptr_t txaddr;
	
    if (jpeg_to_img(fn,1, &img) < 0) {
        printf("can't load %s\n", fn);
        return;
    }
	
    txaddr = pvr_mem_malloc(img.w * img.h * 2);
    pvr_txr_load_kimg(&img, txaddr, PVR_TXRLOAD_INVERT_Y);
    kos_img_free(&img, 0);
	
    glGenTextures(1, txr);
	
    glBindTexture(GL_TEXTURE_2D, *txr);
	
    glKosTex2D(GL_RGB565_TWID, img.w, img.h, txaddr);
}


static void drawPatch (float p1[3], float p2[3], float p3[3], int level)
{
	int i;
	if (level > 0) {
		float q1[3],q2[3],q3[3];		 // sub-vertices
		for (i=0; i<3; i++) {
			q1[i] = 0.5f*(p1[i]+p2[i]);
			q2[i] = 0.5f*(p2[i]+p3[i]);
			q3[i] = 0.5f*(p3[i]+p1[i]);
		}
		float length1 = (float)(1.0/fsqrt(q1[0]*q1[0]+q1[1]*q1[1]+q1[2]*q1[2]));
		float length2 = (float)(1.0/fsqrt(q2[0]*q2[0]+q2[1]*q2[1]+q2[2]*q2[2]));
		float length3 = (float)(1.0/fsqrt(q3[0]*q3[0]+q3[1]*q3[1]+q3[2]*q3[2]));
		for (i=0; i<3; i++) {
			q1[i] *= length1;
			q2[i] *= length2;
			q3[i] *= length3;
		}
		drawPatch (p1,q1,q3,level-1);
		drawPatch (q1,p2,q2,level-1);
		drawPatch (q1,q2,q3,level-1);
		drawPatch (q3,q2,p3,level-1);
	}
	else {
		glNormal3f (p1[0],p1[1],p1[2]);
		glVertex3f (p1[0],p1[1],p1[2]);
		glNormal3f (p2[0],p2[1],p2[2]);
		glVertex3f (p2[0],p2[1],p2[2]);
		glNormal3f (p3[0],p3[1],p3[2]);
		glVertex3f (p3[0],p3[1],p3[2]);
	}
}



// ODE Matrix to GL Matrix
static void setTransform (const float pos[3], const float R[12])
{
	GLfloat matrix[16];
	matrix[0]=R[0];
	matrix[1]=R[4];
	matrix[2]=R[8];
	matrix[3]=0;
	matrix[4]=R[1];
	matrix[5]=R[5];
	matrix[6]=R[9];
	matrix[7]=0;
	matrix[8]=R[2];
	matrix[9]=R[6];
	matrix[10]=R[10];
	matrix[11]=0;
	matrix[12]=pos[0];
	matrix[13]=pos[1];
	matrix[14]=pos[2];
	matrix[15]=1;
	glMultMatrixf (matrix);
}


//GLuint CBox::m_BoxList=0;
GLuint CSphere::m_SphereList=0;
GLuint CCylinder::m_CylList=0;
//////////////////////////////////////////////////////////////////////
// CBox Class
//////////////////////////////////////////////////////////////////////

CBox::CBox(const float sides[3])
{

	float lx = sides[0]*0.5f;
	float ly = sides[1]*0.5f;
	float lz = sides[2]*0.5f;

	// Compute Mesh

	m_BoxList = glGenLists (1);
	glNewList (m_BoxList,GL_COMPILE);

	glBegin(GL_QUADS);
	
	glVertex3f( lx, ly,-lz);
	glVertex3f(-lx, ly,-lz);
	glVertex3f(-lx, ly, lz);
	glVertex3f( lx, ly, lz);
	
	glVertex3f( lx,-ly, lz);
	glVertex3f(-lx,-ly, lz);
	glVertex3f(-lx,-ly,-lz);
	glVertex3f( lx,-ly,-lz);
	
	glVertex3f( lx, ly, lz);
	glVertex3f(-lx, ly, lz);
	glVertex3f(-lx,-ly, lz);
	glVertex3f( lx,-ly, lz);
	
	glVertex3f( lx,-ly,-lz);
	glVertex3f(-lx,-ly,-lz);
	glVertex3f(-lx, ly,-lz);
	glVertex3f( lx, ly,-lz);
	
	glVertex3f(-lx, ly, lz);
	glVertex3f(-lx, ly,-lz);
	glVertex3f(-lx,-ly,-lz);
	glVertex3f(-lx,-ly, lz);
	
	glVertex3f( lx, ly,-lz);
	glVertex3f( lx, ly, lz);
	glVertex3f( lx,-ly, lz);
	glVertex3f( lx,-ly,-lz);
	glEnd();
	glEndList();
	

}




void CBox::Render()
{
	
	glCallList (m_BoxList);
	
}

//////////////////////////////////////////////////////////////////////
// CSphere Class
//////////////////////////////////////////////////////////////////////
CSphere::CSphere(const float radius)
{
	m_Radius=radius;
	memset(m_Color,0,sizeof(float)*3);
	// Compute Mesh
# define ICX 0.525731112119133606f
# define ICZ 0.850650808352039932f
	static GLfloat idata[12][3] = {
		{-ICX, 0, ICZ},
		{ICX, 0, ICZ},
		{-ICX, 0, -ICZ},
		{ICX, 0, -ICZ},
		{0, ICZ, ICX},
		{0, ICZ, -ICX},
		{0, -ICZ, ICX},
		{0, -ICZ, -ICX},
		{ICZ, ICX, 0},
		{-ICZ, ICX, 0},
		{ICZ, -ICX, 0},
		{-ICZ, -ICX, 0}
	};
	
	static int index[20][3] = {
		{0, 4, 1},	  {0, 9, 4},
		{9, 5, 4},	  {4, 5, 8},
		{4, 8, 1},	  {8, 10, 1},
		{8, 3, 10},   {5, 3, 8},
		{5, 2, 3},	  {2, 7, 3},
		{7, 10, 3},   {7, 6, 10},
		{7, 11, 6},   {11, 0, 6},
		{0, 1, 6},	  {6, 1, 10},
		{9, 0, 11},   {9, 11, 2},
		{9, 2, 5},	  {7, 2, 11},
	};
	
	if (m_SphereList==0) 
	{
		m_SphereList = glGenLists (1);
		glNewList (m_SphereList,GL_COMPILE);
		glBegin (GL_TRIANGLES);
		for (int i=0; i<20; i++) {
			drawPatch (&idata[index[i][2]][0],&idata[index[i][1]][0],
				&idata[index[i][0]][0],1);
		}
		glEnd();
		glEndList();
	}


}


void CSphere::Render()
{
	

	glScalef(m_Radius,m_Radius,m_Radius);
	
	
	glColor3f(m_Color[0],m_Color[1],m_Color[2]);
	glCallList (m_SphereList);
	
	
}

//////////////////////////////////////////////////////////////////////
// CCylinder Class
//////////////////////////////////////////////////////////////////////
CCylinder::CCylinder(float _lz, float _r)
{
	memset(m_Color,0,sizeof(float)*3);

	if (m_CylList==0) 
	{
		m_CylList = glGenLists (1);
		glNewList (m_CylList,GL_COMPILE);
		glRotatef(M_PI/2.f,0.f,1.f,0.f);
		float l=_lz;
		float  r= _r;
		int i;
		float tmp,ny,nz,a,ca,sa;
		float zoffset = 0.f; //l/2.f;
		const int n = 24;	// number of sides to the cylinder (divisible by 4)
		
		l *= 0.5;
		a = float(M_PI*2.0)/float(n);
		sa = (float) fsin(a);
		ca = (float) fcos(a);
		
		// draw cylinder body
		ny=1; nz=0;		  // normal vector = (0,ny,nz)
		glBegin (GL_TRIANGLE_STRIP);
		for (i=0; i<=n; i++) {
			glNormal3f (ny,nz,0);
			glVertex3f (ny*r,nz*r,l+zoffset);
			glNormal3f (ny,nz,0);
			glVertex3f (ny*r,nz*r,-l+zoffset);
			// rotate ny,nz
			tmp = ca*ny - sa*nz;
			nz = sa*ny + ca*nz;
			ny = tmp;
		}
		glEnd();
		
		// draw top cap
		ny=1; nz=0;		  // normal vector = (0,ny,nz)
		glBegin (GL_TRIANGLE_FAN);
		glNormal3f (0,0,1);
		glVertex3f (0,0,l+zoffset);
		for (i=0; i<=n; i++) {
			
			glNormal3f (0,0,1);
			glVertex3f (ny*r,nz*r,l+zoffset);
			
			
			// rotate ny,nz
			tmp = ca*ny - sa*nz;
			nz = sa*ny + ca*nz;
			ny = tmp;
		}
		glEnd();
		
		// draw bottom cap
		ny=1; nz=0;		  // normal vector = (0,ny,nz)
		glBegin (GL_TRIANGLE_FAN);
		glNormal3f (0,0,-1);
		glVertex3f (0,0,-l+zoffset);
		for (i=0; i<=n; i++) {
			glNormal3f (0,0,-1);
			glVertex3f (ny*r,nz*r,-l+zoffset);
			
			// rotate ny,nz
			tmp = ca*ny + sa*nz;
			nz = -sa*ny + ca*nz;
			ny = tmp;
		}
		glEnd();
		
		glEndList();
	}	

}

void CCylinder::Render()
{
	
	
	glColor3f(m_Color[0],m_Color[1],m_Color[2]);
	glCallList (m_CylList);
		
	
}

//////////////////////////////////////////////////////////////////////
// Buggy Class
//////////////////////////////////////////////////////////////////////
Buggy::Buggy()
{
	static const float carside[3] = {	2.4f, 0.4f, 1.4f };
	// car body
	dMass m;
	dMassSetBox(&m, 1, 2.4f, 0.4f, 1.4f); // density,lx,ly,lz
	dMassAdjust(&m, 50); // mass
	
	carBodies[0] = dBodyCreate(CWorldSpace::m_phWorld);
	dBodySetMass(carBodies[0], &m);
	dBodySetPosition(carBodies[0], 0, 3, 10); // x,y,z
	
	carGeom[0] = dCreateBox(0, 2.4f, 0.4f, 1.4f); // lx,ly,lz
	dGeomSetBody(carGeom[0], carBodies[0]);
	
	// wheel bodies
	dMassSetSphere(&m, 1, 0.3f); // density, radius
	dMassAdjust(&m, 10); // mass
//	dQuaternion q;
//	dQFromAxisAndAngle(q, 1, 0, 0, M_PI * 0.5);
	for(int i = 1; i <= 4; ++i)
	{
		carBodies[i] = dBodyCreate(CWorldSpace::m_phWorld);
		dBodySetMass(carBodies[i], &m);
//		dBodySetQuaternion(carBodies[i], q);
		carGeom[i] = dCreateSphere(0, 0.3f);
		dGeomSetBody(carGeom[i], carBodies[i]);
	}
	dBodySetPosition(carBodies[1], -0.9, 2.6,  10.7); // x,y,z
	dBodySetPosition(carBodies[2], -0.9, 2.6,   9.3); // x,y,z
	dBodySetPosition(carBodies[3],  0.9, 2.6,  10.7); // x,y,z
	dBodySetPosition(carBodies[4],  0.9, 2.6,   9.3); // x,y,z
	
	// wheel joints
	for(int i = 0; i < 4; ++i)
	{
		carJoints[i] = dJointCreateHinge2(CWorldSpace::m_phWorld, 0);
		dJointAttach(carJoints[i], carBodies[0], carBodies[i+1]);
		const dReal* const wPos = dBodyGetPosition(carBodies[i+1]);
		dJointSetHinge2Anchor(carJoints[i], wPos[0], wPos[1], wPos[2]);
		dJointSetHinge2Axis1(carJoints[i], 0, 1, 0);
		dJointSetHinge2Axis2(carJoints[i], 0, 0, ((i % 2) == 0) ? -1 : 1);
		
		dJointSetHinge2Param(carJoints[i], dParamLoStop, 0);
		dJointSetHinge2Param(carJoints[i], dParamHiStop, 0);
		dJointSetHinge2Param(carJoints[i], dParamFMax, 50);
		
		dJointSetHinge2Param(carJoints[i], dParamVel2, 0);
		dJointSetHinge2Param(carJoints[i], dParamFMax2, 80);
		
		dJointSetHinge2Param(carJoints[i], dParamSuspensionERP, 0.25);
		dJointSetHinge2Param(carJoints[i], dParamSuspensionCFM, 0.004);
	}
	
	// space for the car
	
	static dSpaceID car_space;
	
	 car_space = dSimpleSpaceCreate (CWorldSpace::m_phSpace);
  	dSpaceSetCleanup (car_space,0);
  	for(int i = 0; i < 5; ++i)
		 dSpaceAdd(car_space, carGeom[i]);
	
  
	// car meshes
	m_Carmesh = new CBox(carside);
	m_WheelMesh = new CCylinder(0.25f,0.3f);
   
}

void Buggy::Update(float velocity, float steering)
{
	static const float steeringRate = M_PI * 4 / 3;
	static const float steeringLimit = M_PI / 6;
	
	float wheelVelocity = 12 * M_PI * velocity;// * 1.20; (sorry Nate, but this is waaay to fast for keyboarders) :)
	
	// a little bit of deadband seems to make it a bit easier to control
	if (fabs (steering) < 0.1)
		steering = 0;
	
	for(int i = 0; i < 4; ++i)
	{
		float desiredPosition = steering * ((i > 1) ? -1 : 1);
		float actualPosition = dJointGetHinge2Angle1(carJoints[i]);
		float steeringVelocity = (desiredPosition - actualPosition) * 10;
		
		dJointSetHinge2Param(carJoints[i], dParamHiStop, steeringLimit);
		dJointSetHinge2Param(carJoints[i], dParamLoStop, -steeringLimit);
		dJointSetHinge2Param(carJoints[i], dParamVel, steeringVelocity);
	}
	
	for(int i = 0; i < 4; ++i)
		dJointSetHinge2Param(carJoints[i], dParamVel2, ((i % 2) == 0) ? -wheelVelocity : wheelVelocity);
	
}

float * Buggy::GetPos()
{
	return (float *)dBodyGetPosition(carBodies[0]);
}

float * Buggy::GetCameraPos()
{
	static float Campos[3];
	float matrix[4][4];
	float vx = -4.f;
	float vy = 1.5f;
	float vz = 0.f;
	
	matrix[0][0]=dBodyGetRotation(carBodies[0])[0];
	matrix[0][1]=dBodyGetRotation(carBodies[0])[4];
	matrix[0][2]=dBodyGetRotation(carBodies[0])[8];
	matrix[0][3]=0;
	matrix[1][0]=dBodyGetRotation(carBodies[0])[1];
	matrix[1][1]=dBodyGetRotation(carBodies[0])[5];
	matrix[1][2]=dBodyGetRotation(carBodies[0])[9];
	matrix[1][3]=0;
	matrix[2][0]=dBodyGetRotation(carBodies[0])[2];
	matrix[2][1]=dBodyGetRotation(carBodies[0])[6];
	matrix[2][2]=dBodyGetRotation(carBodies[0])[10];
	matrix[2][3]=0;
	matrix[3][0]=dBodyGetPosition(carBodies[0])[0];
	matrix[3][1]=dBodyGetPosition(carBodies[0])[1];
	matrix[3][2]=dBodyGetPosition(carBodies[0])[2];
	matrix[3][3]=1;

	Campos[0] =	matrix[0][0]*vx + matrix[1][0]*vy + matrix[2][0]*vz + matrix[3][0];
	Campos[1] =	matrix[0][1]*vx + matrix[1][1]*vy + matrix[2][1]*vz + matrix[3][1];
	Campos[2] =	matrix[0][2]*vx + matrix[1][2]*vy + matrix[2][2]*vz + matrix[3][2];
	
	if (Campos[1]<0.5f)
		Campos[1]*=-1.f;
	return Campos;

}


void Buggy::Render()
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_KOS_AUTO_UV);
	
	
	glPushMatrix();
		setTransform(dBodyGetPosition(carBodies[0]),dBodyGetRotation(carBodies[0]));
		glBindTexture(GL_TEXTURE_2D, m_TexCar);		
		glColor3f(1.f,1.f,1.f);
		m_Carmesh->Render();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_KOS_AUTO_UV);
	
	for(int i = 1; i <= 4; ++i)
	{
		glPushMatrix();
			setTransform(dBodyGetPosition(carBodies[i]),dBodyGetRotation(carBodies[i]));
			m_WheelMesh->Render();
		glPopMatrix();
	}
	
}
//////////////////////////////////////////////////////////////////////
// CWorldSpace Class
//////////////////////////////////////////////////////////////////////
dWorldID		CWorldSpace::m_phWorld=NULL;
dSpaceID		CWorldSpace::m_phSpace=NULL;
dJointGroupID	CWorldSpace::m_phContactGroup=NULL;
dGeomID			CWorldSpace::m_phEnvGeomGroup=NULL;
dGeomID			CWorldSpace::m_phGround=NULL;
dGeomID			CWorldSpace::wallGeom[5];

void CWorldSpace::NearCallback(void* data, dGeomID o1, dGeomID o2)
{
	const int N = 6;
	dContact contacts[N];
	// get the contacts up to a maximum of N contacts
	const int n = dCollide(o1, o2, N, &contacts[0].geom, sizeof(dContact));
	for(int i = 0; i < n; ++i)
	{
        contacts[i].surface.mode = dContactBounce;
		contacts[i].surface.mu = 250;
		contacts[i].surface.bounce = 0.3;
		contacts[i].surface.bounce_vel = 0.05;
		dJointID c = dJointCreateContact(m_phWorld, m_phContactGroup, &contacts[i]);
		dJointAttach(c, dGeomGetBody(contacts[i].geom.g1), dGeomGetBody(contacts[i].geom.g2));	}
}

void CWorldSpace::Create(const float Gravity[3])
{
	m_phWorld= dWorldCreate();
	m_phSpace= dHashSpaceCreate(0);//new in ODe 0.35
	m_phContactGroup = dJointGroupCreate(0);
	
	
	//m_phEnvGeomGroup = dCreateGeomGroup(m_phSpace);	
	dWorldSetGravity(m_phWorld, Gravity[0], Gravity[1], Gravity[2]);
	
	m_phGround  = dCreatePlane(0, 0.f, 1.f, 0.f, 0.f);
	wallGeom[0] = dCreatePlane(0,  1.f, 0.f,  0.f, -70.f); // x,y,z,d
	wallGeom[1] = dCreatePlane(0, -1.f, 0.f,  0.f, -70.f); // x,y,z,d
	wallGeom[2] = dCreatePlane(0,  0.f, 0.f,  1.f, -70.f); // x,y,z,d
	wallGeom[3] = dCreatePlane(0,  0.f, 0.f, -1.f, -70.f); // x,y,z,d
	wallGeom[4] = dCreatePlane(0,  0.f, -1.f,  0.f, -70.f);
	
	
	 dSpaceAdd(m_phSpace, m_phGround);
	 
	for(int i = 0; i < 5; ++i)
		 dSpaceAdd(m_phSpace,  wallGeom[i]);

	//loadtxr("/rd/grass.pcx", &m_TexGround);
	loadtxr_jpg("/rd/ground.jpg", &m_TexGround);
	loadtxr_jpg("/rd/beachball.jpg", &m_Texball);
	
	loadtxr("/rd/grey.pcx", &m_TexStone);
	loadtxr("/rd/banana.pcx", &m_TexCar);
	loadtxr("/rd/crate.pcx", &m_TexBox);

}

void CWorldSpace::drawGround()
{
    glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_TexGround);
	
	glPushMatrix();
	
	GLfloat matrix[16];
	matrix[0]=1;
	matrix[1]=0;
	matrix[2]=0;
	matrix[3]=0;
	matrix[4]=1;
	matrix[5]=0;
	matrix[6]=0;
	matrix[7]=0;
	matrix[8]=0;
	matrix[9]=0;
	matrix[10]=1;
	matrix[11]=0;
	matrix[12]=0;
	matrix[13]=0;
	matrix[14]=0;
	matrix[15]=1;
	glMultMatrixf (matrix);

	const float gsize = 70.0f;
	glColor3f (1.f,1.f,1.f);
	
	glBegin (GL_QUADS);
	glNormal3f (0,0,1);
	
	glTexCoord2f (0, 0);
	glVertex3f (-gsize,-0.5f,-gsize);
	
	glTexCoord2f (0, gsize);
	glVertex3f (gsize,-0.5f,-gsize);
	
	glTexCoord2f (gsize, gsize);
	glVertex3f (gsize,-0.5f,gsize);
	
	glTexCoord2f (gsize, 0);
	glVertex3f (-gsize,-0.5f,gsize);
	
	glEnd();

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}


void CWorldSpace::Destroy()
{
	dWorldDestroy(m_phWorld);
	dSpaceDestroy(m_phSpace);
	
}


void CWorldSpace::ComputeCollide()
{
	
	dSpaceCollide(m_phSpace, 0, &NearCallback);

	dWorldStep(m_phWorld, 0.03f);

	dJointGroupEmpty(m_phContactGroup);

}

static float * Interpole(float CamPos[3])
{
  static float ret[3];
  static bool firstcall = true;
  if(firstcall)
  {
	memcpy(ret,CamPos,3*sizeof(float));
	firstcall = false;
	return ret;
  }
  else
  {
	  float x = CamPos[0]-ret[0];
	  float y = CamPos[1]-ret[1];
	  float z = CamPos[2]-ret[2];
	  
	  float l = fsqrt(x*x + y*y + z*z);
	  if(l>30.f)
		  return CamPos;
	  else
	  {
		  float mag=l*1/30.f;
		  
		  ret[0]+=mag*x;
		  ret[1]+=mag*y;
		  ret[2]+=mag*z;
		  return ret;
	  }

  }

}
extern uint8 romdisk[];
KOS_INIT_FLAGS(INIT_DEFAULT);
KOS_INIT_ROMDISK(romdisk);

int main(int argc, char **argv) {
    maple_device_t * caddr;
    cont_state_t * cont;

	bool a_pressed = false;
    float camera[3];
	
   	float gravity[3]={0.f,-8.01f,0.f};//-9.81
	pvr_init_params_t params = {{PVR_BINSIZE_16, PVR_BINSIZE_0, PVR_BINSIZE_16, PVR_BINSIZE_0, PVR_BINSIZE_0},1024*1024};
	
    /* PowerVR init */
     pvr_init(&params);

    /* Get KGL stuff initialized */
    glKosInit();

	CWorldSpace::Create(gravity);
	Buggy car;
	CJumpRamp jpramp;
	CBeachBalls bballs;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(60.0f, 640.0f / 480.0f, 0.001f, 1000.0f);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_FILTER, GL_FILTER_BILINEAR);
	glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATEALPHA);
	
    /* Expect CW verts */
    glFrontFace(GL_CW);

    /* Enable Transparancy */
   // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	
	
	  glEnable(GL_KOS_NEARZ_CLIPPING);
  
    while(1) 
	{

		float   vel=0.f,steer=0.f;
		
        /* Check controller/key status */
        if ((caddr = maple_enum_type(0, MAPLE_FUNC_CONTROLLER)) == NULL)
            break;

		cont = (cont_state_t *)maple_dev_status(caddr);
        if ((cont->buttons & CONT_START))
            break;

		if ((cont->buttons & CONT_Y))
            car.Return();

       
		

		vel= (cont->rtrig/255.f)-(cont->ltrig/255.f);
		steer = cont->joyx/127.f;

		if ((cont->buttons & CONT_A))
            vel*=1.5f;
	
		car.Update(vel,-steer);

		memcpy(camera,Interpole(car.GetCameraPos()),3*sizeof(float));
		CWorldSpace::ComputeCollide();
		
		glClearColor(0.3f, 0.4f, 0.5f, 1.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		gluLookAt(	camera[0] ,camera[1],camera[2],
					car.GetPos()[0] ,car.GetPos()[1], car.GetPos()[2],
					0.f,1.f,0.f);
		
		
		/* Begin frame */
        glKosBeginFrame();
		
      
        
		car.Render();
		jpramp.Render();
		bballs.Render();

		
		
		CWorldSpace::drawGround();
	
	
		
		glKosFinishFrame();

		

       
    }


     glKosShutdown() ;

    return 0;
}


//////////////////////////////////////////////////////////////////////
// CJumpRamp Class
//////////////////////////////////////////////////////////////////////

CJumpRamp::CJumpRamp()
{
	static const float offsetX = 20.f;
	static const float rampThickness = 0.4f;
	static const float supportThickness = 0.2f;
	
	
	static const float rampLength = 10.f;
	static const float rampWidth = 5.f;
	static const float rampHeight = 4.f;
	static const float rampSpacing = 9.f;
	
	static const float rampFootprint = fsqrt(rampLength * rampLength - rampHeight * rampHeight);
	
	static const float rampScale[3]= { rampLength, rampThickness, rampWidth};	
	static const float supportScale[3]= {supportThickness, rampHeight - rampThickness, supportThickness};
	
	// create the ramps
	float tmp = (rampFootprint + rampSpacing) / 2.f;
	dMatrix3 r, s, t;
	jumpGeom[0] = dCreateBox(0, rampScale[0], rampScale[1], rampScale[2]);
	dRFromAxisAndAngle(r, 0, 0, 1, asin(rampHeight / rampLength));
	dGeomSetRotation(jumpGeom[0], r);
	dGeomSetPosition(jumpGeom[0], offsetX - tmp, (rampHeight - rampThickness) / 2.f, 0.f);
	jumpGeom[1] = dCreateBox(0, rampScale[0], rampScale[1], rampScale[2]);
	dRFromAxisAndAngle(s, 0, 1, 0, M_PI / 2.f);
	dMULTIPLY0_333(t, s, r);
	dGeomSetRotation(jumpGeom[1], t);
	dGeomSetPosition(jumpGeom[1], offsetX, (rampHeight - rampThickness) / 2.f, tmp);
	jumpGeom[2] = dCreateBox(0, rampScale[0], rampScale[1], rampScale[2]);
	dRFromAxisAndAngle(s, 0, 1, 0, M_PI);
	dMULTIPLY0_333(t, s, r);
	dGeomSetRotation(jumpGeom[2], t);
	dGeomSetPosition(jumpGeom[2], offsetX + tmp, (rampHeight - rampThickness) / 2.f, 0.f);
	jumpGeom[3] = dCreateBox(0, rampScale[0], rampScale[1], rampScale[2]);
	dRFromAxisAndAngle(s, 0, 1, 0, -M_PI / 2.f);
	dMULTIPLY0_333(t, s, r);
	dGeomSetRotation(jumpGeom[3], t);
	dGeomSetPosition(jumpGeom[3], offsetX, (rampHeight - rampThickness) / 2.f, -tmp);
	
	// support the ramps
	tmp = rampSpacing / 2.f + supportThickness;
	float tmp2 = rampWidth / 2.f - supportThickness;
	for(int i = 4; i < 12; ++i)
		jumpGeom[i] = dCreateBox(0, supportScale[0], supportScale[1], supportScale[2]);
	dGeomSetPosition(jumpGeom[4], offsetX - tmp, supportScale[1] / 2.f, -tmp2);
	dGeomSetPosition(jumpGeom[5], offsetX - tmp, supportScale[1] / 2.f, tmp2);
	dGeomSetPosition(jumpGeom[6], offsetX + tmp, supportScale[1] / 2.f, -tmp2);
	dGeomSetPosition(jumpGeom[7], offsetX + tmp, supportScale[1] / 2.f, tmp2);
	dGeomSetPosition(jumpGeom[8], offsetX - tmp2, supportScale[1] / 2.f, -tmp);
	dGeomSetPosition(jumpGeom[9], offsetX + tmp2, supportScale[1] / 2.f, -tmp);
	dGeomSetPosition(jumpGeom[10], offsetX - tmp2, supportScale[1] / 2.f, tmp);
	dGeomSetPosition(jumpGeom[11], offsetX + tmp2, supportScale[1] / 2.f, tmp);
	
	// add to the environment geometry group
	for(int i = 0; i < 12; ++i)
		 dSpaceAdd(CWorldSpace::m_phSpace, jumpGeom[i]);
	
	// ramp meshes 
    jumpMeshes[0]= new CBox(rampScale);
	jumpMeshes[1]= new CBox(supportScale);
	
	
}

void CJumpRamp::Render()
{
	int i;
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_KOS_AUTO_UV);
	glBindTexture(GL_TEXTURE_2D, m_TexStone);		
	glColor3f(1.f,1.f,1.f);
	for(i = 0; i < 4; ++i)
	{
	
		glPushMatrix();
		setTransform(dGeomGetPosition(jumpGeom[i]),dGeomGetRotation(jumpGeom[i]));
		
		jumpMeshes[0]->Render();
		glPopMatrix();
	}
	
	for(i = 4; i < 12; ++i)
	{
		glPushMatrix();
		setTransform(dGeomGetPosition(jumpGeom[i]),dGeomGetRotation(jumpGeom[i]));
		jumpMeshes[1]->Render();
		glPopMatrix();
	}

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_KOS_AUTO_UV);
	
}

//////////////////////////////////////////////////////////////////////
// CBeachBalls Class
//////////////////////////////////////////////////////////////////////
CBeachBalls::CBeachBalls()
{
	static const float offsetX = -25.f;
	
	// general stuff
	static const float radius = 1.f;
	static const float spacing =1.f;
	static const float boxside[3] = { 0.4f, 0.4f, 5.f};
	
	// the ball mass
	dMass m;
	dMassSetSphere(&m, 1, radius);
	dMassAdjust(&m, 2);
	
	// balls
	for(int k = 0, i = 0; k < 3; ++k)
	{
		for(int v = 0; v < 3; ++v)
		{
			for(int u = 0; u < 3; ++u, ++i)
			{
				ballGeom[i] = dCreateSphere(CWorldSpace::m_phSpace, radius);
				ballBodies[i] = dBodyCreate(CWorldSpace::m_phWorld);
				dBodySetMass(ballBodies[i], &m);
				dGeomSetBody(ballGeom[i], ballBodies[i]);
				dBodySetPosition(ballBodies[i], offsetX + 2.f * u - 2.f * spacing, 2.f * k + 1.f * spacing, 2.f * v - 2.f * spacing);
			}
		}
	}
	
	// guards
	for(int i = 0; i < 4; ++i)
		ballGuardGeom[i] = dCreateBox(0, 0.4f, 0.4f, 5.f);
	
	dMatrix3 r, s, t;
	dRFromAxisAndAngle(r, 0, 0, 1, M_PI / 4.f);
	dRFromAxisAndAngle(s, 0, 1, 0, M_PI / 2.f);
	dMULTIPLY0_333(t, s, r);
	
	dGeomSetRotation(ballGuardGeom[0], r);
	dGeomSetPosition(ballGuardGeom[0], offsetX + 2.8f, 0.f, 0.f);
	dGeomSetRotation(ballGuardGeom[1], r);
	dGeomSetPosition(ballGuardGeom[1], offsetX - 2.8f, 0.f, 0.f);
	dGeomSetRotation(ballGuardGeom[2], t);
	dGeomSetPosition(ballGuardGeom[2], offsetX, 0.f, 2.8f);
	dGeomSetRotation(ballGuardGeom[3], t);
	dGeomSetPosition(ballGuardGeom[3], offsetX, 0.f, -2.8f);
	
	for(int i = 0; i < 4; ++i)
		 dSpaceAdd(CWorldSpace::m_phSpace,  ballGuardGeom[i]);
	
	// ball meshes
	ballMesh=new CSphere(radius);
	ballMesh->SetColor(1.f,1.f,0.f);

	ballGuardMesh=new CBox(boxside);
	
}

void CBeachBalls::Render()
{
	int i;
	for(i = 0; i < 27; ++i)
	{
		glPushMatrix();
		setTransform(dGeomGetPosition(ballGeom[i]),dGeomGetRotation(ballGeom[i]));
		ballMesh->Render();	
		glPopMatrix();
		
	}
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_KOS_AUTO_UV);
	glBindTexture(GL_TEXTURE_2D, m_Texball);		
	glColor3f(1.f,1.f,1.f);
	for(i = 0; i < 4; ++i)
	{
		glPushMatrix();
		setTransform(dGeomGetPosition(ballGuardGeom[i]),dGeomGetRotation(ballGuardGeom[i]));
		ballGuardMesh->Render();
		glPopMatrix();
	}
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_KOS_AUTO_UV);

}
