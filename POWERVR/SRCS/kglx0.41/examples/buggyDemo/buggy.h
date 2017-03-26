
#ifndef __BUGGY_H__
#define __BUGGY_H__

#include <kos.h>
#include <ode/ode.h>

#include <GL/gl.h>
#include <GL/glu.h>

//////////////////////////////////////////////////////////////////////
// Texture & Global stuff
//////////////////////////////////////////////////////////////////////

GLuint m_TexBox = 0;
GLuint m_TexCar = 0;
GLuint m_TexGround = 0;
GLuint m_TexStone = 0;
GLuint m_Texball = 0;
//////////////////////////////////////////////////////////////////////
// CBox Class
//////////////////////////////////////////////////////////////////////

class CBox  
{
	
protected:
	 GLuint	 m_BoxList;
	
	
public:
	CBox(const float sides[3]);
	//	virtual ~CBox();	
	
	void Render();
	
};

//////////////////////////////////////////////////////////////////////
// CSphere Class
//////////////////////////////////////////////////////////////////////

class CSphere  
{
	
protected:
	float				m_Radius;
	float				m_Color[3];
	static  GLuint		m_SphereList;
	
	
public:
	CSphere(const float radius);
	
	inline void SetColor(float _red,float _green,float _blue)
	{
		m_Color[0]= _red;
		m_Color[1]= _green;
		m_Color[2]= _blue;
	}	
	
	void Render();
	
};

//////////////////////////////////////////////////////////////////////
// CCylinder Class
//////////////////////////////////////////////////////////////////////

class CCylinder  
{
	
protected:
	float				m_Radius;
	float				m_Color[3];
	static  GLuint		m_CylList;
	
	
public:
	CCylinder(float lz, float _r);
	
	inline void SetColor(float _red,float _green,float _blue)
	{
		m_Color[0]= _red;
		m_Color[1]= _green;
		m_Color[2]= _blue;
	}
	
	
	void Render();
	
};

class Buggy
{
protected:
	dGeomID		carGeom[5], carGeomGroup;
	dBodyID		carBodies[5];	
	dJointID	 carJoints[4];
	CBox		*m_Carmesh;
	CCylinder   *m_WheelMesh;
		

public:
	Buggy();

	void Update(float velocity, float steering);
	
	void Render();

	inline void Return()
	{
		dBodyAddForce(carBodies[0], 0, 800, 0);
		dBodyAddRelTorque(carBodies[0], 70, 0, 0);
	}


	float * GetPos();

	float * GetCameraPos();

};


//////////////////////////////////////////////////////////////////////
// CWorldSpace Class
//////////////////////////////////////////////////////////////////////

class CWorldSpace  
{
public:
	static dWorldID m_phWorld;
	static dSpaceID m_phSpace;
	static dJointGroupID m_phContactGroup;
	static dGeomID m_phEnvGeomGroup;
	static dGeomID m_phGround;
	static dGeomID wallGeom[5];
	
	static void Create(const float Gravity[3]);
	static void Destroy();
	
	static void NearCallback(void* data, dGeomID o1, dGeomID o2);
	static void ComputeCollide();
	
	static void drawGround();
	
	
	
};

//////////////////////////////////////////////////////////////////////
// CJumpRamp Class
//////////////////////////////////////////////////////////////////////

class CJumpRamp 
{
protected:
	CBox * jumpMeshes[2];
	dGeomID jumpGeom[12];
	
	
public:
	CJumpRamp();

	void Render();
};

//////////////////////////////////////////////////////////////////////
// CBeachBalls Class
//////////////////////////////////////////////////////////////////////
class CBeachBalls
{
protected:	
	dGeomID  ballGeom[27];
	dBodyID  ballBodies[27];
	dGeomID  ballGuardGeom[4];
	CSphere* ballMesh;
	CBox *   ballGuardMesh;

public :
	CBeachBalls();

	void Render();

};


#endif //__BUGGY_H__
