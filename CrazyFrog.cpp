#include "TextureBuilder.h"
#include "Model_3DS.h"
#include "GLTexture.h"
#include <glut.h>

int WIDTH = 1280;
int HEIGHT = 720;

GLuint tex;
char title[] = "Crazy Frog";

// 3D Projection Options
GLdouble fovy = 45.0;
GLdouble aspectRatio = (GLdouble)WIDTH / (GLdouble)HEIGHT;
GLdouble zNear = 0.1;
GLdouble zFar = 100;
GLdouble xStand = 17.5;
boolean Right = false;

GLdouble xFrog = 0;
GLdouble yFrog = 0;
GLdouble zFrog = 14;
GLdouble Win = 0;
int time1 = 20;
int zEye = 35;
class Vector {
public:
	GLdouble x, y, z;
	Vector() {}
	Vector(GLdouble _x, GLdouble _y, GLdouble _z) : x(_x), y(_y), z(_z) {}
	//================================================================================================//
	// Operator Overloading; In C++ you can override the behavior of operators for you class objects. //
	// Here we are overloading the += operator to add a given value to all vector coordinates.        //
	//================================================================================================//
	void operator +=(float value)
	{
		x += value;
		y += value;
		z += value;
	}
};

Vector Eye(0, 10, zEye);
Vector At(0, 0, 0);
Vector Up(0, 1, 0);

int cameraZoom = 0;

// Model Variables
Model_3DS model_house;
Model_3DS model_tree;
Model_3DS model_Frog;
Model_3DS model_Stand;
Model_3DS model_Fence;

// Textures
GLTexture tex_Lake;
GLTexture tex_Ground;


// Lighting Configuration Function
void InitLightSource() {
	// Enable Lighting for this OpenGL Program
	glEnable(GL_LIGHTING);

	// Enable Light Source number 0
	// OpengL has 8 light sources
	glEnable(GL_LIGHT0);

	// Define Light source 0 ambient light
	GLfloat ambient[] = { 0.1f, 0.1f, 0.1, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	// Define Light source 0 diffuse light
	GLfloat diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

	// Define Light source 0 Specular light
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	// Finally, define light source 0 position in World Space
	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}


// Material Configuration Function
void InitMaterial() {
	// Enable Material Tracking
	glEnable(GL_COLOR_MATERIAL);

	// Sich will be assigneet Material Properties whd by glColor
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Set Material's Specular Color
	// Will be applied to all objects
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

	// Set Material's Shine value (0->128)
	GLfloat shininess[] = { 96.0f };
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}


// OpengGL Configuration Function
void myInit(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(fovy, aspectRatio, zNear, zFar);
	//*******************************************************************************************//
	// fovy:			Angle between the bottom and top of the projectors, in degrees.			 //
	// aspectRatio:		Ratio of width to height of the clipping plane.							 //
	// zNear and zFar:	Specify the front and back clipping planes distances from camera.		 //
	//*******************************************************************************************//

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);
	//*******************************************************************************************//
	// EYE (ex, ey, ez): defines the location of the camera.									 //
	// AT (ax, ay, az):	 denotes the direction where the camera is aiming at.					 //
	// UP (ux, uy, uz):  denotes the upward orientation of the camera.							 //
	//*******************************************************************************************//

	InitLightSource();

	InitMaterial();

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_NORMALIZE);
}


void RenderLake() {
	glDisable(GL_LIGHTING);	// Disable lighting 

	glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit

	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing

	glBindTexture(GL_TEXTURE_2D, tex_Lake.texture[0]);	// Bind the ground texture

	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-20, 0, -20);
	glTexCoord2f(5, 0);
	glVertex3f(20, 0, -20);
	glTexCoord2f(5, 5);
	glVertex3f(20, 0, 20);
	glTexCoord2f(0, 5);
	glVertex3f(-20, 0, 20);
	glEnd();
	glPopMatrix();

	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.
}
void RenderGround() {
	glDisable(GL_LIGHTING);	// Disable lighting 

	glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit

	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing

	glBindTexture(GL_TEXTURE_2D, tex_Ground.texture[0]);	// Bind the ground texture

	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-20, 0, -20);
	glTexCoord2f(5, 0);
	glVertex3f(20, 0, -20);
	glTexCoord2f(5, 5);
	glVertex3f(20, 0, 20);
	glTexCoord2f(0, 5);
	glVertex3f(-20, 0, 20);
	glEnd();
	glPopMatrix();

	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.
}
void Logic() {
	if ((xFrog <= (xStand + 3) && xFrog >= (xStand - 3)) && ((zFrog <= -8 && zFrog >= -12) || (zFrog <= 4 && zFrog >= 0))) {
		xFrog = xStand;
	}
	else {
		if ((xFrog <= (-xStand + 3) && xFrog >= (-xStand -3)) && ((zFrog <= -2 && zFrog >= -6) || (zFrog <= 10 && zFrog >= 6)) ) {
			xFrog = (-xStand);
		}
		else {
			if ((zFrog <= 10 && zFrog >= -12 && yFrog >= -1)) {
				yFrog -= 0.01;
				Win = -2;
			}
			else {
				if(zFrog <= -14 && zFrog >= -20) {
					yFrog = 0;
					Win = 1;
				}
				else {
					if ((zFrog <= 20 && zFrog >= 14)) {
						yFrog = 0;
					}
				}
			}
		}

	}
	glutPostRedisplay();
}

void StandAnim() {
	if (xStand <= 17.5 && Right == false) {
		xStand += 0.02;
	}
	else {
		Right = true;
	}

	if (xStand >= -17.5 && Right == true) {
		xStand -= 0.02;

	}
	else {
		Right = false;
	}
	
	
	glutPostRedisplay();
}
void FrogAnimFront() {
	if (zFrog >= -17.5) {
		zFrog -= 6;
		
	}
	glutPostRedisplay();
}
void FrogAnimBack() {
	if (zFrog <= 17.5) {
		zFrog += 0.2;
	}
	glutPostRedisplay();
}
void FrogAnimRight() {
	if (xFrog <= 17.5) {
		xFrog += 0.2;
	}

	glutPostRedisplay();
}
void FrogAnimLeft() {
	if (xFrog >= -17.5) {
		xFrog -= 0.2;
	}

	glutPostRedisplay();
}
void FrogAnimUp() {
		yFrog += 0.2;

	glutPostRedisplay();
}
void FrogAnimDown() {
    	yFrog -= 0.2;
	

	glutPostRedisplay();
}
void print(float x, float y, char* string)
{
	int len, i;
	len = 20;
	glRasterPos2f(x, y);
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}
void Timer1(int value) {
	if (time1 > 0 && Win == 0) {
		time1 -= 1;
		glutTimerFunc(1 * 1000, Timer1, 0);
	}
	else {
		Win = -1;
	}

	glutPostRedisplay();
}
void myDisplay(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLfloat lightIntensity[] = { 0.7, 0.7, 0.7, 1.0f };
	GLfloat lightPosition[] = { 0.0f, 100.0f, 0.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);
	
	if (Win == 0) {
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(0, 0, 0);
		char* sc[30];
		sprintf((char*)sc, "Time Left : %d", time1);
		print(-3, 12, (char*)sc);
	}
	if (Win == -1) {
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1, 0, 0);
		char* sc[20];
		sprintf((char*)sc, "Timeout!");
		print(-3, 12, (char*)sc);
	}
	if (Win == -2) {
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1, 0, 0);
		char* sc[20];
		sprintf((char*)sc, "Frog Sank!");
		print(-3, 12, (char*)sc);
	}
	if (Win == 1) {
		glColor3d(0, 1, 0);
		char* sc[20];
		sprintf((char*)sc, "You Won !");
		print(-3, 12, (char*)sc);

		glColor3d(0, 1, 0);
		char* sc1[20];
		sprintf((char*)sc1, "Score : %d", time1*5);
		print(-3, 10, (char*)sc1);
	}

	// Draw Lake
	RenderLake();

	// Draw Start Ground
	glPushMatrix();
	glTranslatef(0, 0.1, -20);
	glScalef(1, 0.7, 0.3);
	RenderGround();
	glPopMatrix();

	// Draw End Ground
	glPushMatrix();
	glTranslatef(0, 0.1, 20);
	glScalef(1, 0.7, 0.3);
	RenderGround();
	glPopMatrix();



	// Draw Tree 1 Model
	glPushMatrix();
	glTranslatef(10, 0, -20);
	glScalef(0.7, 0.7, 0.7);
	model_tree.Draw();
	glPopMatrix();

	// Draw Tree 2 Model
	glPushMatrix();
	glTranslatef(-10, 0, -20);
	glScalef(0.7, 0.7, 0.7);
	model_tree.Draw();
	glPopMatrix();

	// Draw house Model
	glPushMatrix();
	glTranslatef(0, 0, -20);
	glRotatef(90.f, 1, 0, 0);
	model_house.Draw();
	glPopMatrix();

	// Draw Left Fence Model
	glPushMatrix();
	glTranslatef(-20, 0, 0);
	glRotatef(90.f, 0, 1, 0);
	glScalef(0.2, 0.04, 0.05);
	model_Fence.Draw();
	glPopMatrix();

	// Draw Right Fence Model
	glPushMatrix();
	glTranslatef(20, 0, 0);
	glRotatef(90.f, 0, 1, 0);
	glScalef(0.2, 0.04, 0.05);
	model_Fence.Draw();
	glPopMatrix();

	// Draw Front Fence Model
	glPushMatrix();
	glTranslatef(0, 0, -23);
	glScalef(0.18, 0.04, 0.05);
	model_Fence.Draw();
	glPopMatrix();

	// Draw Stand 1 Model
	glPushMatrix();
	glTranslatef(xStand, 0, -10);
	glScalef(0.05, 0.05, 0.05);
	glutIdleFunc(StandAnim);
	model_Stand.Draw();
	glPopMatrix();

	// Draw Stand 2 Model
	glPushMatrix();
	glTranslatef(-xStand, 0, -4);
	glScalef(0.05, 0.05, 0.05);
	glutIdleFunc(StandAnim);
	model_Stand.Draw();
	glPopMatrix();

	// Draw Stand 3 Model
	glPushMatrix();
	glTranslatef(xStand, 0, 2);
	glScalef(0.05, 0.05, 0.05);
	glutIdleFunc(StandAnim);
	model_Stand.Draw();
	glPopMatrix();

	// Draw Stand 4 Model
	glPushMatrix();
	glTranslatef(-xStand, 0, 8);
	glScalef(0.05, 0.05, 0.05);
	glutIdleFunc(StandAnim);
	model_Stand.Draw();
	glPopMatrix();


	// Draw Frog Model
	glPushMatrix();
	glTranslatef(xFrog,yFrog, zFrog);
	glScalef(30, 30, 30);
	glRotatef(180.f, 0, 1, 0);
	model_Frog.Draw();
	glPopMatrix();


	//sky box
	glPushMatrix();
	glRotatef(-45.f, 0, 1, 0);
	GLUquadricObj* qobj;
	qobj = gluNewQuadric();
	glTranslated(50, 0, 0);
	glRotated(90, 1, 0, 1);
	glBindTexture(GL_TEXTURE_2D, tex);
	gluQuadricTexture(qobj, true);
	gluQuadricNormals(qobj, GL_SMOOTH);
	gluSphere(qobj, 100, 100, 100);
	gluDeleteQuadric(qobj);

	glPopMatrix();
	Logic();

	glutSwapBuffers();
}


void myKeyboard(unsigned char button, int x, int y) {
	switch (button) {
	case 'p':
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;

	case 'r':
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	case 27:
		exit(0);
		break;
	case 'w':
		glutIdleFunc(FrogAnimFront);
		break;
	case 's':
		glutIdleFunc(FrogAnimBack);
		break;
	case 'd':
		glutIdleFunc(FrogAnimRight);
		break;
	case 'a':
		glutIdleFunc(FrogAnimLeft);
		break;

	case 'z':
		zEye = 35;
		break;

	case 'x':
		zEye = zFrog;
		break;

	default:
		break;
	}

	glutPostRedisplay();
}


void myMotion(int x, int y) {
	y = HEIGHT - y;

	if (cameraZoom - y > 0) {
		Eye.x += -0.1;
		Eye.z += -0.1;
	}
	else {
		Eye.x += 0.1;
		Eye.z += 0.1;
	}

	cameraZoom = y;

	glLoadIdentity();	//Clear Model_View Matrix

	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);	//Setup Camera with modified paramters

	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glutPostRedisplay();	//Re-draw scene 
}


void myMouse(int button, int state, int x, int y) {
	y = HEIGHT - y;
	if (state == GLUT_DOWN) {
		cameraZoom = y;
	}
}


void myReshape(int w, int h) {
	if (h == 0) {
		h = 1;
	}

	WIDTH = w;
	HEIGHT = h;

	// set the drawable region of the window
	glViewport(0, 0, w, h);

	// set up the projection matrix 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, (GLdouble)WIDTH / (GLdouble)HEIGHT, zNear, zFar);

	// go back to modelview matrix so we can move the objects about
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);
}


void LoadAssets() {
	// Loading Model files
	model_house.Load("Models/house/house.3DS");
	model_tree.Load("Models/tree/Tree1.3ds");
	model_Frog.Load("Models/Frog/3ds/Frog.3ds");
	model_Stand.Load("Models/Stand/stand.3DS");
	model_Fence.Load("Models/Fence/Fence with window N280817.3DS");

	// Loading texture files
	tex_Ground.Load("Textures/Ground.bmp");
	tex_Lake.Load("Textures/Lake.bmp");
	loadBMP(&tex, "Textures/blu-sky-3.bmp", true);
}


void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(100, 150);
	glutCreateWindow(title);
	glutDisplayFunc(myDisplay);
	glutKeyboardFunc(myKeyboard);
	glutMotionFunc(myMotion);
	glutMouseFunc(myMouse);
	glutReshapeFunc(myReshape);
	myInit();
	LoadAssets();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);
	Timer1(1);
	glutMainLoop();
}