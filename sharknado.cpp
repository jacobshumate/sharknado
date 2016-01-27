/**********************************************************************************************
 * sharknado.cpp

 * Jacob Shumate

 * To Compile:
   OS X: g++ -framework GLUT -framework OpenGL -framework Cocoa sharknado.cpp -o test
   Linux: g++ -o test sharknado.cpp -lglut -lGL -lGLU -lX11 -lm 
***********************************************************************************************/

#ifdef  __APPLE__      // For use with OS X
#include <GLUT/glut.h>
#include <cstdlib>
#else   	       // Other (Linux)
#include <GL/glut.h>
#include <cstdlib>
#endif
/* glut.h includes gl.h and glu.h*/

//Angle of rotation
static GLfloat theta = 0.0;

//twister rotations
static GLfloat rot1 = 0.0;
static GLfloat rot2 = 0.0;
static GLfloat rot3 = 0.0;

//Colors
GLfloat red[] = {0.4, 0.0, 0.0, 1.0};
GLfloat blue[] = {0.0, 0.0, 0.4, 1.0};
GLfloat lightBlue[] = {0.0, 0.5, 0.9, 1.0};
GLfloat offWhite[] = {0.8, 0.8, 0.8, 1.0};
GLfloat cyan[] = {0.0, 1.0, 1.0, 0.2};
GLfloat black[] = {0.0, 0.0, 0.0, 1.0};
GLfloat brown[] = {0.4, 0.3, 0.1, 1.0};
GLfloat lightBrown[] = {0.8, 0.6, 0.2, 1.0};
GLfloat white[] = {1.0, 1.0, 1.0, 0.5};
GLfloat grey[] = {0.5, 0.5 ,0.5, 1.0};
GLfloat green[] = {0.0, 0.3, 0.0, 1.0};
GLfloat orange[] = {1.0, 0.45, 0.0, 1.0};
GLfloat purple[] = {0.5, 0.0, 0.5, 1.0};
GLfloat transgrey[] = {0.5, 0.5, 0.5, 0.1};
GLfloat tornadogrey[] = {0.5, 0.5, 0.5, 0.8};

//camera movment on all axis
float camZ = 400.0;
float camY = 0.0;
float camX = 0.0;

//camer movement with mouse
float lastX = 0.0; 
float lastY = 0.0;

//move reference point 
bool view2 = false;
float eyeX = 0.0;
float eyeY = 3.0;

//tornado movement
float tmov = 400.0;
float pullmov = 0.0;
float ymov = 0.0;

//tornado booleans
bool tornadoOn = false;
bool dbr = false;
bool shrk = false;
bool pull = false;

//tornado formation
float torx = 0.05;
float tory = 0.0;
float torz = 0.05;

//wave motion
float wavmov = 0.0;

void vortex(float r, float pullD, float ymovD)
{
	if(pull)
	{
		glTranslatef(pullmov-pullD, 0.0, -pullmov+pullD);
	}

	if(tmov < 50)
        {
                glTranslatef(tmov, 0.0, -tmov);
                glPushMatrix();
                                        
                glRotatef(-theta, 0.0, 1.0, 0.0);
		glRotatef(r, 0.0, 1.0, 0.0);
                glTranslatef(40, ymov-ymovD, 0.0);
		glRotatef(theta, 1.0, 0.0, 1.0);
        }
}

void clouds()
{

	for(float x = 1.0; x < 3; x++)
	{

		glPushMatrix();
		glTranslatef((x-1)*40+10, 155.0, 0.0);
		glRotatef((x-1)*180, 0.0, 0.0, 1.0);
		glRotatef(90, 0.0, 0.0, 1.0);
		glPushMatrix();
        	glPushMatrix();
        	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, grey);
        	glTranslatef(0.0, 30.0, 0.0);
        	glutSolidSphere(40.0, 20, 20);
        	glPopMatrix();

                       
		glPushMatrix();
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, grey);
        	glTranslatef(0.0, 0.0, -30.0);
        	glutSolidSphere(40.0, 20, 20);
        	glPopMatrix();

        	glPushMatrix();
        	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, grey);
       		glTranslatef(0.0, 0.0, 30.0);
        	glutSolidSphere(40.0, 20, 20);
        	glPopMatrix();
		glPopMatrix();
		glPopMatrix();
	}

}

void debris()
{ 
	float windRadius = 50.0;
	glPushMatrix();
	glTranslatef(20.0, 0.0, 0.0);

	glPushMatrix();
	glRotatef(-2*theta, 0.0, 1.0, 0.0);
	for(float y = 0; y < 7; y++)
	{		
		glTranslatef(0.0, y, 0.0);
		glPushMatrix();
		for(float x = -1; x < 2; x+=2)
		{
			glPushMatrix();
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, grey);
			glTranslatef(x*(windRadius/2+y), 0.0, 0.0);
			glutSolidCube(0.5);
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();

	glPushMatrix();
        glRotatef(-2*theta, 0.0, 1.0, 0.0);
	glRotatef(90, 0.0, 1.0, 0.0);
        for(float y = 0; y < 7; y++)
        {
                glTranslatef(0.0, y, 0.0);
                glPushMatrix();
                for(float x = -1; x < 2; x+=2)
                {
                        glPushMatrix();
                        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, grey);
                        glTranslatef(x*(windRadius/2+y), 0.0, 0.0);
                        glutSolidCube(0.5);
                        glPopMatrix();
                }
                glPopMatrix();
        }
        glPopMatrix();

	glPushMatrix();
        glRotatef(-2*theta, 0.0, 1.0, 0.0);
        glRotatef(45, 0.0, 1.0, 0.0);
        for(float y = 0; y < 3; y++)
        {
                glTranslatef(0.0, y, 0.0);
                glPushMatrix();
                for(float x = -1; x < 2; x+=2)
                {
                        glPushMatrix();
                        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, grey);
                        glTranslatef(x*(windRadius+y)/2, 0.0, 0.0);
			glRotatef(90, 0.0, 1.0, 0.0);
			glScalef(8.0, 2.0, 0.1);
                        glutSolidCube(0.5);
                        glPopMatrix();
                }
                glPopMatrix();
        }
        glPopMatrix();

	glPushMatrix();
        glRotatef(-2*theta, 0.0, 1.0, 0.0);
        glRotatef(-45, 0.0, 1.0, 0.0);
        for(float y = 2; y < 3; y++)
        {
                glTranslatef(0.0, y, 0.0);
                glPushMatrix();
                for(float x = -1; x < 2; x+=2)
                {
                        glPushMatrix();
                        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, grey);
                        glTranslatef(x*(windRadius+y)/2, 0.0, 0.0);
                        glutSolidTeapot(0.5);
                        glPopMatrix();
                }
                glPopMatrix();
        }
        glPopMatrix();
	
	glPushMatrix();
        glRotatef(-2*theta, 0.0, 1.0, 0.0);
	glRotatef(45, 0.0, 1.0, 0.0);
        for(float y = 0; y < 10; y+=2)
        { 
                glTranslatef(0.0, y, 0.0);
                glPushMatrix();
                for(float x = -1; x < 2; x+=2)
                {
                        glPushMatrix();
                        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, grey);
                        glTranslatef(x*(windRadius+y)/1.5, 0.0, 0.0);
			glRotatef(90, 0.0, 1.0, 0.0);
			glScalef(1.5, 1.5, 0.1);
                        glutSolidCube(1.0);
                        glPopMatrix();
                }
                glPopMatrix();
        }
        glPopMatrix();

	//inner clouds
        glPushMatrix();
        glRotatef(-2.5*theta, 0.0, 1.0, 0.0);
        //glRotatef(45, 0.0, 1.0, 0.0);
        for(float y = 0; y < 3; y+=2)
        {
                glTranslatef(0.0, y, 0.0);
                glPushMatrix();
                for(float x = -1; x < 2; x+=2)
                {
                        glPushMatrix();
                        glRotatef(-theta, 1.0, 0.0, 0.0);
                        glPushMatrix();
                        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, transgrey);
                        glTranslatef(x*(windRadius/2+y)/1.5, 9.0, 0.0);
                        //glScalef(1.0, 0.5, 0.5);
                        glutSolidSphere(10.0, 20, 20);
                        glPopMatrix();

                        glPushMatrix();
                        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, transgrey);
                        glTranslatef(x*(windRadius/2+y)/1.5, 0.0, -9.0);
                        //glScalef(2.0, 0.5, 0.5);
                        glutSolidSphere(10.0, 20, 20);
                        glPopMatrix();

                        glPushMatrix();
                        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, transgrey);
                        glTranslatef(x*(windRadius/2+y)/1.5, 0.0, 9.0);
                        //glScalef(2.0, 0.5, 0.5);
                        glutSolidSphere(10.0, 20, 20);
                        glPopMatrix();
                        glPopMatrix();

                }
                glPopMatrix();
        }
        glPopMatrix();

	glPushMatrix();
        glRotatef(-2.5*theta, 0.0, 1.0, 0.0);
        glRotatef(90, 0.0, 1.0, 0.0);
        for(float y = 0; y < 3; y+=2)
        {
                glTranslatef(0.0, y, 0.0);
                glPushMatrix();
                for(float x = -1; x < 2; x+=2)
                {
                        glPushMatrix();
                        glRotatef(-theta, 1.0, 0.0, 0.0);
                        glPushMatrix();
                        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, transgrey);
                        glTranslatef(x*(windRadius/2+y)/1.5, 9.0, 0.0);
                        //glScalef(1.0, 0.5, 0.5);
                        glutSolidSphere(10.0, 20, 20);
                        glPopMatrix();

                        glPushMatrix();
                        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, transgrey);
                        glTranslatef(x*(windRadius/2+y)/1.5, 0.0, -9.0);
                        //glScalef(2.0, 0.5, 0.5);
                        glutSolidSphere(10.0, 20, 20);
                        glPopMatrix();

                        glPushMatrix();
                        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, transgrey);
                        glTranslatef(x*(windRadius/2+y)/1.5, 0.0, 9.0);
                        //glScalef(2.0, 0.5, 0.5);
                        glutSolidSphere(10.0, 20, 20);
                        glPopMatrix();
                        glPopMatrix();

                }
                glPopMatrix();
        }
        glPopMatrix();

	//outer clouds
	glPushMatrix();
        glRotatef(-2.5*theta, 0.0, 1.0, 0.0);
        //glRotatef(45, 0.0, 1.0, 0.0);
        for(float y = 0; y < 11; y+=10)
        {
                glTranslatef(0.0, y, 0.0);
                glPushMatrix();
                for(float x = -1; x < 2; x+=2)
                {
			glPushMatrix();
			glRotatef(-theta, 1.0, 0.0, 0.0);
                        glPushMatrix();
                        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, transgrey);
                        glTranslatef(x*(windRadius+y)/1.5, 9.0, 0.0);
			//glScalef(1.0, 0.5, 0.5);
                        glutSolidSphere(10.0, 20, 20);
                        glPopMatrix();
		
			glPushMatrix();
                        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, transgrey);
                        glTranslatef(x*(windRadius+y)/1.5, 0.0, -9.0);
                        //glScalef(2.0, 0.5, 0.5);
                        glutSolidSphere(10.0, 20, 20);
                        glPopMatrix();

			glPushMatrix();
                        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, transgrey);
                        glTranslatef(x*(windRadius+y)/1.5, 0.0, 9.0);
                        //glScalef(2.0, 0.5, 0.5);
                        glutSolidSphere(10.0, 20, 20);
                        glPopMatrix();
			glPopMatrix();

                }
                glPopMatrix();
        }
        glPopMatrix();

	glPushMatrix();
        glRotatef(-2.5*theta, 0.0, 1.0, 0.0);
        glRotatef(90, 0.0, 1.0, 0.0);
        for(float y = 0; y < 11; y+=10)
        {
                glTranslatef(0.0, y, 0.0);
                glPushMatrix();
                for(float x = -1; x < 2; x+=2)
                {
                        glPushMatrix();
                        glRotatef(-theta, 1.0, 0.0, 0.0);
                        glPushMatrix();
                        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, transgrey);
                        glTranslatef(x*(windRadius+y)/1.5, 9.0, 0.0);
                        //glScalef(1.0, 0.5, 0.5);
                        glutSolidSphere(10.0, 20, 20);
                        glPopMatrix();

                        glPushMatrix();
                        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, transgrey);
                        glTranslatef(x*(windRadius+y)/1.5, 0.0, -9.0);
                        //glScalef(2.0, 0.5, 0.5);
                        glutSolidSphere(10.0, 20, 20);
                        glPopMatrix();

                        glPushMatrix();
                        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, transgrey);
                        glTranslatef(x*(windRadius+y)/1.5, 0.0, 9.0);
                        //glScalef(2.0, 0.5, 0.5);
                        glutSolidSphere(10.0, 20, 20);
                        glPopMatrix();
                        glPopMatrix();

                }
                glPopMatrix();
        }
        glPopMatrix();

	//outside boards
	glPushMatrix();
        glRotatef(-2*theta, 0.0, 1.0, 0.0);
        for(float y = 0; y < 10; y+=2)
        {
                glTranslatef(0.0, y, 0.0);
                glPushMatrix();
                for(float x = -1; x < 2; x+=2)
                {
                        glPushMatrix();
                        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, grey);
                        glTranslatef(x*(windRadius+y), 0.0, 0.0);
                        glRotatef(90, 0.0, 1.0, 0.0);
                        glScalef(3.5, 0.5, 0.1);
                        glutSolidCube(1.0);
                        glPopMatrix();
                }
                glPopMatrix();
        }
        glPopMatrix();

	//outside blocks
	glPushMatrix();
        glRotatef(-2*theta, 0.0, 1.0, 0.0);
	glRotatef(90, 0.0, 1.0, 0.0);
        for(float y = 0; y < 10; y+=2)
        {
                glTranslatef(0.0, y, 0.0);
                glPushMatrix();
                for(float x = -1; x < 2; x+=2)
                {
                        glPushMatrix();
                        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, grey);
                        glTranslatef(x*(windRadius+y), 0.0, 0.0);
                        glRotatef(90, 0.0, 1.0, 0.0);
                        glScalef(0.5, 0.5, 0.5);
                        glutSolidCube(1.0);
                        glPopMatrix();
                }
                glPopMatrix();
        }
        glPopMatrix();


	glPopMatrix();
     
}

void sharks()
{
	float tornadoRadius = 90.0;
	float height = -10.0;

	glPushMatrix();
        glTranslatef(30.0, 60.0, 0.0);
	glRotatef(20, 0.0, 0.0, 1.0);
        glRotatef(-theta, 0.0, 1.0, 0.0);
        glPushMatrix();
        for(float x = -1; x < 2; x+=2)
        {
        	glPushMatrix();
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, grey);
                glTranslatef(x*(tornadoRadius/3), height, 0.0);
		glScalef(2.0, 2.0, 4.5);
                glutSolidCube(1.5);
                glPopMatrix();

		glPushMatrix();
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, grey);
                glTranslatef(x*(tornadoRadius/3), height, -5.0);
		glScalef(1.5, 1.5, 3.5);
                glutSolidCube(1.5);
                glPopMatrix();

		glPushMatrix();
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, grey);
                glTranslatef(x*(tornadoRadius/3), height, -8.0);
                glScalef(1.0, 1.0, 3.5);
                glutSolidCube(1.5);
                glPopMatrix();

		glPushMatrix();
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, grey);
                glTranslatef(x*(tornadoRadius/3), height, -11.0);
		glRotatef(90, 1.0, 0.0, 0.0);
		glRotatef(90, 0.0, 0.0, 1.0);
                glScalef(2.0, 1.0, 4.5);
                glutSolidTetrahedron();
                glPopMatrix();

		glPushMatrix();
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, grey);
                glTranslatef(x*(tornadoRadius/3), height+2, 1.0);
                glRotatef(90, 1.0, 0.0, 0.0);
                glRotatef(90, 0.0, 1.0, 0.0);
                glScalef(1.0, 3.0, 1.0);
                glutSolidTetrahedron();
                glPopMatrix();

		glPushMatrix();
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, grey);
                glTranslatef(x*(tornadoRadius/3)+2, height-1, 1.0);
                glRotatef(90, 1.0, 0.0, 0.0);
                glScalef(2.0, 2.0, 0.5);
                glutSolidTetrahedron();
                glPopMatrix();

		glPushMatrix();
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, grey);
                glTranslatef(x*(tornadoRadius/3)-2, height-1, 1.0);
		glRotatef(180, 0.0, 0.0, 1.0);
                glRotatef(90, 1.0, 0.0, 0.0);
                glScalef(2.0, 2.0, 0.5);
                glutSolidTetrahedron();
                glPopMatrix();

		glPushMatrix();
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, grey);
                glTranslatef(x*(tornadoRadius/3), height, 4.0);
                glScalef(1.75, 1.75, 3.2);
                glutSolidCube(1.5);
                glPopMatrix();

		height+=30;
        }
        glPopMatrix();
	glPopMatrix();

	tornadoRadius+=30;
	height = -10.0;

	glPushMatrix();
	glTranslatef(35.0, 100.0, 0.0);
	glRotatef(20, 0.0, 0.0, 1.0);
        glRotatef(-(theta+90), 0.0, 1.0, 0.0);
        glPushMatrix();
	for(float x = -1; x < 2; x+=2)
        {

		glPushMatrix();
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, grey);
                glTranslatef(x*(tornadoRadius/3), height, 0.0);
                glScalef(2.0, 2.0, 4.5);
                glutSolidCube(1.5);
                glPopMatrix();

                glPushMatrix();
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, grey);
                glTranslatef(x*(tornadoRadius/3), height, -5.0);
                glScalef(1.5, 1.5, 3.5);
                glutSolidCube(1.5);
                glPopMatrix();

                glPushMatrix();
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, grey);
                glTranslatef(x*(tornadoRadius/3), height, -8.0);
                glScalef(1.0, 1.0, 3.5);
                glutSolidCube(1.5);
                glPopMatrix();

                glPushMatrix();
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, grey);
                glTranslatef(x*(tornadoRadius/3), height, -11.0);
                glRotatef(90, 1.0, 0.0, 0.0);
                glRotatef(90, 0.0, 0.0, 1.0);
                glScalef(2.0, 1.0, 4.5);
                glutSolidTetrahedron();
                glPopMatrix();

                glPushMatrix();
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, grey);
                glTranslatef(x*(tornadoRadius/3), height+2, 1.0);
                glRotatef(90, 1.0, 0.0, 0.0);
                glRotatef(90, 0.0, 1.0, 0.0);
                glScalef(1.0, 3.0, 1.0);
                glutSolidTetrahedron();
                glPopMatrix();

                glPushMatrix();
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, grey);
                glTranslatef(x*(tornadoRadius/3)+2, height-1, 1.0);
                glRotatef(90, 1.0, 0.0, 0.0);
                glScalef(2.0, 2.0, 0.5);
                glutSolidTetrahedron();
                glPopMatrix();

                glPushMatrix();
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, grey);
                glTranslatef(x*(tornadoRadius/3)-2, height-1, 1.0);
                glRotatef(180, 0.0, 0.0, 1.0);
                glRotatef(90, 1.0, 0.0, 0.0);
                glScalef(2.0, 2.0, 0.5);
                glutSolidTetrahedron();
                glPopMatrix();

                glPushMatrix();
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, grey);
                glTranslatef(x*(tornadoRadius/3), height, 4.0);
                glScalef(1.75, 1.75, 3.2);
                glutSolidCube(1.5);
                glPopMatrix();

                height+=20;
        }
        glPopMatrix();
	glPopMatrix();

}

void sharknado()
{
	glTranslatef(tmov, 0.0, -tmov);
	glPushMatrix();	

	glTranslatef(25.0-(torx*25), 125.0-(tory*125), 0.0);
	glScalef(torx, tory, torz);
	glPushMatrix();

	glRotatef(-30, 0.0, 0.0, 1.0);
	glRotatef(90, 0.0, 1.0, 0.0);	
	for(float i = 1; i < 5; i+=0.5)
	{
		glTranslatef(0.0, 1.0, 0.0);
	
		glPushMatrix();
        	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, tornadogrey);
		glRotatef(90, 1.0, 0.0, 0.0);
		glRotatef(theta, 0.0, 0.0, 1.0);
        	glutSolidTorus(0.5*i, 1.0*i, 15, 15);
        	glPopMatrix();
	}

	for(float i = 1; i < 10; i++)
        {
                glTranslatef(0.0, 1.5, 0.5);

                glPushMatrix();
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, tornadogrey);
                glRotatef(90-(5*i), 1.0, 0.0, 0.0);
		glRotatef(theta, 0.0, 0.0, 1.0);
                glutSolidTorus(2.25+(i*0.25), 4.25+(i*0.25), 15, 15);
                glPopMatrix();
        }

	for(float i = 1; i < 20; i++)
        {
                glTranslatef(0.0, 2.0, -0.5);

                glPushMatrix();
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, tornadogrey);
                glRotatef(40, 1.0, 0.0, 0.0);
		glRotatef(theta, 0.0, 0.0, 1.0);
                glutSolidTorus(3.5+(0.25*i), 6.5+(0.25*i), 15, 15);
                glPopMatrix();
        }

	for(float i = 1; i < 25; i++)
        {
                glTranslatef(0.0, 2.5, -1.0);

                glPushMatrix();
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, tornadogrey);
                glRotatef(40, 1.0, 0.0, 0.0);
		glRotatef(theta, 0.0, 0.0, 1.0);
                glutSolidTorus(5+(0.5*i), 11+(0.5*i), 15, 15);
                glPopMatrix();
        }

	glPopMatrix();

	if(dbr)
		debris();
	glPopMatrix();

	if(shrk)
		sharks();
}

void waves()
{
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, lightBlue);
	glTranslatef(450, 0.0, 0.0);
	glScalef(400, .5, 400);
	glutSolidCube(2.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(5, 0.0, 0.0, 1.0);
	
	for(int i = 0; i < 10; i++)
	{
		glPushMatrix();
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, cyan);
		glTranslatef(500-(i*40)-wavmov, 0.0, 0.0);
		glScalef(5, 4, 200);
		glutSolidSphere(2.0, 20, 20);
		glPopMatrix();
	}

	glPopMatrix();
}

void base(float sclx, float sclz)
{
	//base
        glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, grey);
        glScalef(5.0+sclx, 0.5, 5.0+sclz);
        glutSolidCube(2.0);
        glPopMatrix();
	/*
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, lightBrown);
	glTranslatef(-50.0, -0.5, 0.0);
	glScalef(100, 0.125, 300);
	glutSolidCube(2.0);
	glPopMatrix();
	*/
	//waves();

}

void windowWall(float sclx)
{
	//right wall of window
        glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blue);
        glTranslatef(2.6+sclx, 3.5, 4.5);
        glRotatef(90, 1.0, 0.0, 0.0);
        glScalef(1.4+sclx, 0.5, 3.0);
        glutSolidCube(2.0);
        glPopMatrix();

        //left wall of window
        glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blue);
        glTranslatef(-2.6-sclx, 3.5, 4.5);
        glRotatef(90, 1.0, 0.0, 0.0);
        glScalef(1.4+sclx, 0.5, 3.0);
        glutSolidCube(2.0);
        glPopMatrix();

	if(sclx < 0)
		sclx = 0;

	 //top wall of window
        glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blue);
        glTranslatef(0.0, 6.1, 4.5);
        glRotatef(90, 1.0, 0.0, 0.0);
        glScalef(1.2+sclx, 0.5, 0.4);
        glutSolidCube(2.0);
        glPopMatrix();

        //window
        glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, cyan);
        glTranslatef(0.0, 3.9, 4.5);
        glRotatef(90, 1.0, 0.0, 0.0);
        glScalef(1.2, 0.5, 1.8);
        glutSolidCube(2.0);
        glPopMatrix();

        //bottom wall of window
        glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blue);
        glTranslatef(0.0, 1.3, 4.5);
        glRotatef(90, 1.0, 0.0, 0.0);
        glScalef(1.2+sclx, 0.5, 0.8);
        glutSolidCube(2.0);
        glPopMatrix();
}

void roomDoor(float sclx)
{
        glPushMatrix();

        //right wall of door
        glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blue);
        glTranslatef(2.5+sclx, 3.5, 4.5);
        glRotatef(90, 1.0, 0.0, 0.0);
        glScalef(1.0+sclx, 0.5, 3.0);
        glutSolidCube(2.0);
        glPopMatrix();

        //door
        glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, brown);
        glTranslatef(0.7, 3.1, 3.0);
        glRotatef(-65, 0.0, 1.0, 0.0);
        glRotatef(90, 1.0, 0.0, 0.0);
        glScalef(1.5, 0.2, 2.6);
        glutSolidCube(2.0);
        glPopMatrix();

        //left wall of door
        glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blue);
        glTranslatef(-2.5-sclx, 3.5, 4.5);
        glRotatef(90, 1.0, 0.0, 0.0);
        glScalef(1.0+sclx, 0.5, 3.0);
        glutSolidCube(2.0);
        glPopMatrix();

        if(sclx < 0)
                sclx = 0;
        //top wall of door
        glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blue);
        glTranslatef(0.0, 6.1, 4.5);
        glRotatef(90, 1.0, 0.0, 0.0);
        glScalef(1.5+sclx, 0.5, 0.4);
        glutSolidCube(2.0);
        glPopMatrix();

        glPopMatrix();
}

void door(float sclx)
{
	glPushMatrix();

	//right wall of door
	glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blue);
        glTranslatef(1.7+sclx, 3.5, 4.5);
        glRotatef(90, 1.0, 0.0, 0.0);
        glScalef(sclx, 0.5, 3.0);
        glutSolidCube(2.0);
        glPopMatrix();

	//door
	glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, green);
        glTranslatef(-0.5, 3.1, 6.0);
	glRotatef(-45, 0.0, 1.0, 0.0);
        glRotatef(90, 1.0, 0.0, 0.0);
        glScalef(1.5, 0.2, 2.6);
        glutSolidCube(2.0);
        glPopMatrix();

        //left wall of door
        glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blue);
        glTranslatef(-2.8-sclx, 3.5, 4.5);
        glRotatef(90, 1.0, 0.0, 0.0);
        glScalef(1.2+sclx, 0.5, 3.0);
        glutSolidCube(2.0);
        glPopMatrix();

	if(sclx < 0)
		sclx = 0;
	//top wall of door
        glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blue);
        glTranslatef(0.0, 6.1, 4.5);
        glRotatef(90, 1.0, 0.0, 0.0);
        glScalef(1.4+sclx, 0.5, 0.4);
        glutSolidCube(2.0);
        glPopMatrix();

	glPopMatrix();
}

void couch()
{
	//base
	glPushMatrix();
	glRotatef(90, 0.0, 1.0, 0.0);
	glScalef(1.0, 0.8, 1.2);
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, green);
	glTranslatef(0.0, 1.0, 0.0);
        glScalef(4.0, 1.0, 2.0);
        glutSolidCube(1.0);
	glPopMatrix();

	//right arm
	glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, green);
        glTranslatef(2.0, 2.0, 0.0);
        glScalef(0.5, 1.0, 2.0);
        glutSolidCube(1.0);
        glPopMatrix();

	//left arm
	glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, green);
        glTranslatef(-2.0, 2.0, 0.0);
        glScalef(0.5, 1.0, 2.0);
        glutSolidCube(1.0);
        glPopMatrix();

	//back
	glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, green);
        glTranslatef(0.0, 1.8, -0.9);
	glRotatef(90, 1.0, 0.0, 0.0);
        glScalef(4.0, 0.8, 2.5);
        glutSolidCube(1.0);
        glPopMatrix();

	glPopMatrix();

}


void ceilingFan()
{
	glPushMatrix();
	glTranslatef(1.0, 0.5, 0.0);
	//light bulb
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, white);
	glTranslatef(0.0, 5.0, 0.0);
	glScalef(0.3, 0.3, 0.3);
	glutSolidDodecahedron();
	glPopMatrix();

	//spinning fan blades
	glPushMatrix();
	glRotatef(theta, 0.0, 1.0, 0.0);

	glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, black);
        glTranslatef(0.0, 5.5, 1.0);
        glRotatef(90, 0.0, 1.0, 0.0);
        glScalef(2.0, 0.2, 0.5);
        glutSolidCube(1.0);
        glPopMatrix();

	glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, black);
        glTranslatef(0.0, 5.5, -1.0);
        glRotatef(90, 0.0, 1.0, 0.0);
        glScalef(2.0, 0.2, 0.5);
        glutSolidCube(1.0);
        glPopMatrix();

	glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, black);
        glTranslatef(1.0, 5.5, 0.0);
        glScalef(2.0, 0.2, 0.5);
        glutSolidCube(1.0);
        glPopMatrix();

	glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, black);
        glTranslatef(-1.0, 5.5, 0.0);
        glScalef(2.0, 0.2, 0.5);
        glutSolidCube(1.0);
        glPopMatrix();

	glPopMatrix();

	glPopMatrix();
}

void books()
{
	for(float i = 0; i < 3; i+=1.025)
        {
	glPushMatrix();
	glTranslatef(0.0, 2.05-i, 0.0);
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, red);
        glTranslatef(7.6, 2.0, 4.0);
        glScalef(0.2, 0.9, 0.8);
        glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, black);
        glTranslatef(7.4, 1.9, 4.0);
        glScalef(0.2, 0.7, 0.8);
        glutSolidCube(1.0);
        glPopMatrix();

	glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, green);
        glTranslatef(7.2, 1.95, 4.0);
        glScalef(0.2, 0.8, 0.8);
        glutSolidCube(1.0);
        glPopMatrix();

	glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, orange);
        glTranslatef(7.0, 2.0, 4.0);
        glScalef(0.2, 0.9, 0.8);
        glutSolidCube(1.0);
        glPopMatrix();

	glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, purple);
        glTranslatef(7.8, 1.95, 4.0);
        glScalef(0.2, 0.8, 0.8);
        glutSolidCube(1.0);
        glPopMatrix();
	glPopMatrix();
	}
}

void bookShelf()
{
	glPushMatrix();

	glTranslatef(7.2, 0.7, -1.0);
	glRotatef(-90, 0.0, 1.0, 0.0);
	glScalef(1.0, 0.85, 0.8);
	
	//back
	glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, brown);
        glTranslatef(5.0, 2.0, 0.0);
	glRotatef(90, 0.0, 0.0, 1.0);
        glScalef(4.5, 0.2, 2.0);
        glutSolidCube(1.0);
        glPopMatrix();

	//right side
	glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, brown);
        glTranslatef(4.6, 2.0, -0.9);
	glRotatef(90, 0.0, 1.0, 0.0);
        glRotatef(90, 0.0, 0.0, 1.0);
        glScalef(4.5, 0.2, 0.6);
        glutSolidCube(1.0);
        glPopMatrix();

	//left side
	glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, brown);
        glTranslatef(4.6, 2.0, 0.9);
	glRotatef(90, 0.0, 1.0, 0.0);
        glRotatef(90, 0.0, 0.0, 1.0);
        glScalef(4.5, 0.2, 0.6);
        glutSolidCube(1.0);
        glPopMatrix();

	//shelves
	glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, brown);
        glTranslatef(4.7, 4.3, 0.0);
        glRotatef(90, 0.0, 1.0, 0.0);
        glScalef(2.0, 0.2, 0.8);
        glutSolidCube(1.0);
        glPopMatrix();

	glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, brown);
        glTranslatef(4.7, 3.275, 0.0);
        glRotatef(90, 0.0, 1.0, 0.0);
        glScalef(2.0, 0.2, 0.8);
        glutSolidCube(1.0);
        glPopMatrix();

	glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, brown);
        glTranslatef(4.7, 2.25, 0.0);
        glRotatef(90, 0.0, 1.0, 0.0);
        glScalef(2.0, 0.2, 0.8);
        glutSolidCube(1.0);
        glPopMatrix();

	glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, brown);
        glTranslatef(4.7, 1.125, 0.0);
        glRotatef(90, 0.0, 1.0, 0.0);
        glScalef(2.0, 0.2, 0.8);
        glutSolidCube(1.0);
        glPopMatrix();

	glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, brown);
        glTranslatef(4.7, -0.2, 0.0);
        glRotatef(90, 0.0, 1.0, 0.0);
        glScalef(2.0, 0.2, 0.8);
        glutSolidCube(1.0);
        glPopMatrix();



	glPopMatrix();
}

void table()
{
	glPushMatrix();
	
	glTranslatef(-2.5, -0.4, 0.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	//table
        glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, brown);
        glTranslatef(0.0, 2.0, 0.0);
        glScalef(4.0, 0.4, 2.5);
        glutSolidCube(1.0);
        glPopMatrix();

	glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, brown);
        glTranslatef(1.6, 1.3, 1.0);
        glScalef(1.0, 2.0, 1.0);
        glutSolidCube(0.5);
        glPopMatrix();

	glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, brown);
        glTranslatef(1.6, 1.3, -1.0);
        glScalef(1.0, 2.0, 1.0);
        glutSolidCube(0.5);
        glPopMatrix();

	glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, brown);
        glTranslatef(-1.6, 1.3, 1.0);
        glScalef(1.0, 2.0, 1.0);
        glutSolidCube(0.5);
        glPopMatrix();

	glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, brown);
        glTranslatef(-1.6, 1.3, -1.0);
        glScalef(1.0, 2.0, 1.0);
        glutSolidCube(0.5);
        glPopMatrix();

	glPopMatrix();
}

void roof()
{
	glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, red);
        glTranslatef(0.0, 6.8, 0.0);
        glScalef(5.0, 0.3, 5.0);
        glutSolidCube(2.0);
        glPopMatrix();

	glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, red);
        glTranslatef(0.0, 7.3, 0.0);
        glScalef(4.0, 0.3, 4.0);
        glutSolidCube(2.0);
        glPopMatrix();

	glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, red);
        glTranslatef(0.0, 7.8, 0.0);
        glScalef(3.0, 0.3, 3.0);
        glutSolidCube(2.0);
        glPopMatrix();

	glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, red);
        glTranslatef(0.0, 8.3, 0.0);
        glScalef(2.0, 0.3, 2.0);
        glutSolidCube(2.0);
        glPopMatrix();

	glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, red);
        glTranslatef(0.0, 8.8, 0.0);
        glScalef(1.0, 0.3, 1.0);
        glutSolidCube(2.0);
        glPopMatrix();
	glPopMatrix();


	/*
      	glPushMatrix();
	//draw triangles
      	glBegin(GL_TRIANGLE_FAN);
      	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, red);
      	glVertex3f(  0.0,  1.0, 0.0);
      	glVertex3f(-1.0, -1.0, 1.0);
      	glVertex3f( 1.0, -1.0, 1.0);
      	glVertex3f( 1.0, -1.0, -1.0);
      	glVertex3f( -1.0, -1.0, -1.0);
      	glVertex3f(-1.0, -1.0, 1.0);
      	glEnd();

	//draw square
      	glBegin(GL_QUADS);
      	glVertex3f(-1.0, -1.0, 1.0);
      	glVertex3f( -1.0, -1.0, -1.0);
      	glVertex3f( 1.0, -1.0, -1.0);
      	glVertex3f( 1.0, -1.0, 1.0);
      	glEnd();
      	glPopMatrix();
	*/
}

void tv()
{
	glPushMatrix();
	glTranslatef(8.0, 0.0, 0.0);

	glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, black);
        glTranslatef(0.0, 0.5, 0.0);
        glScalef(0.25, 0.3, 2.0);
        glutSolidCube(2.0);
        glPopMatrix();

	glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, black);
        glTranslatef(0.0, 2.0, -1.77);
	glRotatef(90, 1.0, 0.0, 0.0);
        glScalef(0.25, 0.2, 1.2);
        glutSolidCube(2.0);
        glPopMatrix();

	glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, black);
        glTranslatef(0.0, 2.0, 1.77);
        glRotatef(90, 1.0, 0.0, 0.0);
        glScalef(0.25, 0.2, 1.2);
        glutSolidCube(2.0);
        glPopMatrix();

	glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, black);
        glTranslatef(0.0, 3.3, 0.0);
        glScalef(0.25, 0.2, 2.0);
        glutSolidCube(2.0);
        glPopMatrix();

	glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, white);
        glTranslatef(0.0, 2.0, 0.0);
        glScalef(0.25, 1.1, 1.55);
        glutSolidCube(2.0);
        glPopMatrix();

	glPopMatrix();
}
void bed()
{
	glPushMatrix();
        glTranslatef(-2.4, 0.0, -7.25);

	glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, lightBlue);
        glTranslatef(0.0, 1.0, 0.0);
        glScalef(3.3, 0.75, 2.0);
        glutSolidCube(2.0);
        glPopMatrix();

	glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, offWhite);
        glTranslatef(-2.5, 2.5, 1.0);
	glRotatef(-45, 0.0, 0.0, 1.0);
        glScalef(0.8, 0.5, 0.9);
        glutSolidCube(2.0);
        glPopMatrix();

	glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, offWhite);
        glTranslatef(-2.5, 2.5, -1.0);
	glRotatef(-45, 0.0, 0.0, 1.0);
        glScalef(0.8, 0.5, 0.9);
        glutSolidCube(2.0);
        glPopMatrix();


	glPopMatrix();
}

void house()
{
	glPushMatrix();
	//base
	glPushMatrix();
	glTranslatef(1.0, 0.0, -2.5);
	base(3.0, 3.5);
	glPopMatrix();


	glPushMatrix();
	if(tmov < 45)
		vortex(80, 0, 20);	
	table();

	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	if(tmov < 45)
		vortex(180, 0, 15);
	bookShelf();
	books();

	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	if(tmov < 80)
		vortex(25, 0, 20);

	ceilingFan();

	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	if(tmov < 40)
		vortex(45, 0, 15);
	glPushMatrix();
	glTranslatef(2.5, 0.0, 0.0);
	couch();
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	if(tmov < 30)
		vortex(20, 5, 10);
	
	door(1);

	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	if(tmov < 40)
		vortex(250, 0, 20);
	tv();

	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	if(tmov < 45)
		vortex(290, 0, 15);

	bed();

	glPopMatrix();
	glPopMatrix();
	
	glPushMatrix();	
	if(tmov < 60)
		vortex(180, 5, 10);

	glPushMatrix();
	glTranslatef(5.5, 0.0, -8.5);
	roomDoor(0);
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
	

	//front offset window wall
	glPushMatrix();
	if(tmov < 40)
		vortex(180, 5, 25);

	glPushMatrix();
  	glTranslatef(5.0, 0.0, 0.0);
        windowWall(-0.5);
        glPopMatrix();

	glPopMatrix();
	glPopMatrix();

	//left window wall
	glPushMatrix();
	if(tmov < 30)
		vortex(100, 0, 30);

	glPushMatrix();
	glTranslatef(-2.0, 0.0, 0.0);
        glRotatef(-90, 0.0, 1.0, 0.0);
        windowWall(0);
        glPopMatrix();

	glPopMatrix();
	glPopMatrix();
	
	//left wall
	glPushMatrix();
	if(tmov < 25)
		vortex(45, 0, 35);

	glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blue);
        glTranslatef(-6.5, 3.5, -6.0);
        glRotatef(90, 0.0, 0.0, 1.0);
        glScalef(3.0, 0.5, 3.0);
        glutSolidCube(2.0);
        glPopMatrix();
	
	glPopMatrix();
	glPopMatrix();	
	//roof
	glPushMatrix();
	
	vortex(0, 0, 0);

	glPushMatrix();
	glTranslatef(1.0, 0.0, -2.3);
	glScalef(1.75, 1.0, 1.75);
	roof();
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
	
	
	//back wall
	glPushMatrix();

	if(tmov < 75)
		vortex(45, 1, 2);

	glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blue);
        glTranslatef(-2.0, 3.5, -4.0);
        glRotatef(90, 1.0, 0.0, 0.0);
        glScalef(4.0, 0.5, 3.0);
        glutSolidCube(2.0);
        glPopMatrix();
	
	//back window wall
	glPushMatrix();
        glTranslatef(1.0, 0.0, -14.0);
        windowWall(2.0);
        glPopMatrix();

	glPopMatrix();
	glPopMatrix();
	
	//right wall
	glPushMatrix();

	if(tmov < 80)
		vortex(90, 0.5, 1);
	
	glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blue);
	glTranslatef(8.5, 3.5, -2.5);
	glRotatef(90, 0.0, 0.0, 1.0);
        glScalef(3.0, 0.5, 6.5);
        glutSolidCube(2.0);
        glPopMatrix();

	glPopMatrix();
	glPopMatrix();
	
	glPopMatrix();
	
}

void animation()
{
	if(tornadoOn)
	{
		tmov -= 0.5;

		if(tmov < -200)
			tmov = 600;

		if(tory < 1)
			tory += 0.005;
		else
		{
			dbr = true;

			if(torx < 1.0)
				torx += 0.0025;
			if(torz < 1.0)
				torz += 0.0025;
			else
				shrk = true;
		}	
	}

	if(tmov < 100 && tmov >= 50)
		pull = true;
	else
		pull = false;
	
	if(tmov < 50)
		ymov += 0.25;
	else
		ymov = 0.0;	

	if(pull)
		pullmov += 0.05;
	else
		pullmov = 0.0;

	theta += 5;
	wavmov += 0.5;

	if(theta > 360.0)
                theta -= 360;

	if(wavmov > 20)
		wavmov = 0.0;

	glutPostRedisplay();
}

void camera()
{
	//rotates house x and y axis with mouse
	//and up and down viewing angle with camera
	if(!view2)
	{
		gluLookAt(0.0, 0.0, camZ, eyeX, eyeY, 0.0, 0.0, 1.0, 0.0);
		glRotatef(camX, 0.0, 1.0, 0.0);
        	glRotatef(camY, 1.0, 0.0, 0.0);
	}	

	//rotates inside house on x axis
	//and up and down viewing angle with camera
	else
	{
		gluLookAt(0.0, 3.0, camZ, eyeX, eyeY, 0.0, 0.0, 1.0, 0.0);
		glRotatef(camX, 0.0, 1.0, 0.0);
	}
}


void switchViews()
{
	//set camera inside house
	if(!view2)
	{
		view2 = true;
		camY = 0.0;
		camZ = 4.0;
	}

	//set back to original view
	else
	{
		view2 = false;
		camX = 0.0;
		camY = 0.0;
        	camZ = 200.0;
		eyeY = 3.0;
		eyeX = 0.0;
	}
}

void myKey(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'q': exit(0);
			break;
		case 'Q': exit(0);
			break;
		//zoom in or out of origin
		case '+': camZ -= 1.0;
			break;
		case '-': camZ += 1.0;
			break;
		//switch between 2 different camera views
		case 's': switchViews();
			break;
		case 't': tornadoOn = !tornadoOn;
			break;
	}

	glutPostRedisplay();
}

void specialInput(int skey, int x, int y)
{
	//camera movement on x and y axis
	switch(skey)
        {
        	case GLUT_KEY_RIGHT:
                	eyeX += 0.5;
               		break;

               	case GLUT_KEY_LEFT:
                        eyeX -= 0.5;
                        break;

               	case GLUT_KEY_UP:
                        eyeY += 0.5;
                        break;

               	case GLUT_KEY_DOWN:
                        eyeY -= 0.5;
                        break;
        }

	glutPostRedisplay();
}

void onMotion(int x, int y)
{
	//check difference between current x and last x position
	int diffX = x - lastX;
	//check difference between current y and last y position
	int diffY = y - lastY;
	//set lastx to current x position
	lastX = x;
	//set lasty to current y position
	lastY = y;
	//set camX to Camx + difference in y position
	camX += (float) diffX;
	//set camY to CamY + difference in x position
	camY += (float) diffY;
}

void reshape(int w, int h)
{
	//set the viewport
	glViewport(0, 0, w, h);
	//Apply subsequent matrix operation
	//to projection matrix stack
	glMatrixMode(GL_PROJECTION);
	//replace current matrix with identity matrix
	glLoadIdentity();
	//set field of view, aspect ratio, distance to near
	gluPerspective(60.0, 1.0, 1.0, 2000.0);
}

void init()
{
/*	
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
   	GLfloat light_position[] = { 0.0, 5.0, 0.0, 0.0 };
   	glClearColor (1.0, 1.0, 1.0, 0.0);
   	glShadeModel (GL_SMOOTH);

   	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
*/	
   	glEnable(GL_LIGHTING);
   	glEnable(GL_LIGHT0);
   	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
	
	//background color
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

void display()
{
	//clear buffer to enable color writing
        //and depth buffer
        glClear(GL_COLOR_BUFFER_BIT |
                GL_DEPTH_BUFFER_BIT);
        //Apply subsequent matrix operation
        //to modelview matrix stack
        glMatrixMode(GL_MODELVIEW);
        //replace current matrix with identity matrix
        glLoadIdentity();

	camera();
	house();
	sharknado();
	//clouds();
	//flush GL buffer
	glFlush();
	//swap buffers of current window if double
	//buffered
	glutSwapBuffers();
}

int main(int argc, char **argv)
{
	//Initialize window and display mode
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE |
			    GLUT_DEPTH);
	//set window size
	glutInitWindowSize(700, 700);
	//set window title to fancy room
	glutCreateWindow("Fancy Room!");

	//Register Callbacks
	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);
	glutPassiveMotionFunc(onMotion);
	glutKeyboardFunc(myKey);
	glutSpecialFunc(specialInput);
	glutIdleFunc(animation);

	//Enter GLUT even processing loop
	glutMainLoop();

	return 0;
}
