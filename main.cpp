//Semestre 2019 - 1
//************************************************************//
//************************************************************//
//************** Cruz Santos Isaac *********************************//
//*************  Proyecto Final Laboratorio de Computación Gráfica***//
//*************	 Grupo : 01										******//
//************************************************************//
//************************************************************//

#include "texture.h"
#include "figuras.h"

#include "Noise.h"
#include "KameHouse.h"

#include <ctime>


#define FPS 60



/// Perlin Noise Relacionados//
float dummy = 0.0f;
float ampNoise = 1.0f;

//TV

float currentTime = 0;
float lastUpdateTime = 0;
float elapsedTime = 0;

int tempCounter;
int currentFrame = 0;
int tv_sprite = 0;

// Camera


float angle = 0.0f;

float lx = 0.0f, lz = -1.0f;

float x = 0.0f, z = 5.0f;


float deltaAngle = 0.0f;
float deltaMove = 0;
int xOrigin = -1;
float up_view = 0.0f;
//

//Puerta
bool open_door = false;
bool isOpen = false;
float openAngle = 0.0f;

//


//Agua
bool runningWater = false;
bool activateWater = false;
float waterLevel = 0.0f;
//

int font=(int)GLUT_BITMAP_HELVETICA_18;


GLfloat Diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };				// Diffuse Light Values

GLfloat Specular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat Position[]= { 0.0f, 7.0f, -5.0f, 0.0f };			// Light Position
GLfloat Position2[]= { 0.0f, 0.0f, -5.0f, 1.0f };			// Light Position



CFiguras fig1;
CFiguras fig3;

CTexture text1;
CTexture text2;
CTexture text3;	//Flecha
CTexture text4;	//Pavimento
CTexture text5;	//Pasto01
CTexture text6;	//Casa01



CTexture muebleTV_text;
CTexture alfombra_text;
CTexture mesa_Centro_text;
CTexture sillon_text;
CTexture mesa_text;
CTexture refri_text;
CTexture mueblesito_text;
CTexture lampara_text;
CTexture muebleCocina_text;
CTexture estufa_text;
CTexture lavamanos_text;
CTexture cajonesSup_text;
CTexture trapecio_text;
CTexture paredInterna_text;
CTexture llaves_text;
CTexture casa_text;
CTexture techito_text;
CTexture escalones_text;
CTexture ventanaFrente_text;
CTexture ventanader_text;
CTexture ventanaiz_text;
CTexture puerta_text;
CTexture isla_text;
CTexture rocas_text;
CTexture palmera1_text;
CTexture palmera2_text;
CTexture palmera3_text;
CTexture tapete_text;
CTexture casita_text;
CTexture techo_text;
CTexture techoIn_text;
CTexture sillad_text;
CTexture sillai_text;
CTexture sillao_text;
CTexture tele_text;
CTexture agua_text;

CTexture tv0;
CTexture tv1;
CTexture tv2;
CTexture tv3;
CTexture tv4;
CTexture tv5;

CTexture tv[6] = { tv0,tv1,tv2,tv3,tv4,tv5 };

CTexture agua;
CFiguras cubo;
CFiguras sky;

//END NEW//////////////////////////////////////////







float RunTimeInSeconds()
{

	clock_t programTickCount = clock();


	float seconds = float(programTickCount) / CLOCKS_PER_SEC;

	return seconds;
}


void computePos(float deltaMove) {

	x += deltaMove * lx * 0.1f;
	z += deltaMove * lz * 0.1f;
}

void processNormalKeys(unsigned char key, int xx, int yy) {

	switch (key) {

	case 'w':   //Movimientos de camara
	case 'W':
		deltaMove = 0.8f;
		
		break;

	case 's':
	case 'S':
		deltaMove = -0.8f;
		
		break;

	case 'D':
	case 'd':
		up_view += 0.5;
		break;

	case 'A':
	case 'a':
		up_view -= 0.5;
		break;

	case 'Q':
	case 'q':
		open_door = !open_door;

		break;

	case 'E':
	case 'e':
		activateWater = !activateWater;

		break;


	case 27:        // Cuando Esc es presionado...
		exit(0);   // Salimos del programa
		break;
	default:        // Cualquier otra
		break;
	}
}

void pressKey(int key, int xx, int yy) {

	switch (key) {
	case GLUT_KEY_UP: up_view += 0.5f; break;
	case GLUT_KEY_DOWN: up_view -= 0.5f; break;
	}
}

void releaseKey(int key, int x, int y) {

	switch (key) {
	case GLUT_KEY_UP:
	case GLUT_KEY_DOWN: 
		deltaMove = 0; 
		break;
	}
}

void releaseNormalKeys(unsigned char key, int xx, int yy) {

	switch (key) {
	case 'W':
	case 'w':
	case 'S':
	case 's':
		deltaMove = 0;
		break;
	}
}

void mouseMove(int x, int y) {

	// this will only be true when the left button is down
	if (xOrigin >= 0) {

		// update deltaAngle
		deltaAngle = (x - xOrigin) * 0.001f;

		// update camera's 
		lx = sin(angle + deltaAngle);

		//lx = 1;
		lz = -cos(angle + deltaAngle);
	}
}

void mouseButton(int button, int state, int x, int y) {

	// only start motion if the left button is pressed
	if (button == GLUT_LEFT_BUTTON) {

		// when the button is released
		if (state == GLUT_UP) {
			angle += deltaAngle;
			xOrigin = -1;
		}
		else {// state = GLUT_DOWN
			xOrigin = x;
		}
	}
}



			
void InitGL ( GLvoid )     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo	

	glEnable(GL_TEXTURE_2D);

	glShadeModel (GL_SMOOTH);
	//Para construir la figura comentar esto
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, Diffuse);//Luz_ISAAC


	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable ( GL_COLOR_MATERIAL );

	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);


	//Inicializacion Texturas
    
    text1.LoadBMP("02.bmp");
	text1.BuildGLTexture();
	text1.ReleaseImage();


	muebleTV_text.LoadBMP("Textures/MuebleTV.bmp");
	muebleTV_text.BuildGLTexture();
	muebleTV_text.ReleaseImage();

	sillon_text.LoadBMP("Textures/sillon.bmp");
	sillon_text.BuildGLTexture();
	sillon_text.ReleaseImage();

	alfombra_text.LoadBMP("Textures/tapeteg.bmp");
	alfombra_text.BuildGLTexture();
	alfombra_text.ReleaseImage();

	mesa_Centro_text.LoadBMP("Textures/Mesa.bmp");
	mesa_Centro_text.BuildGLTexture();
	mesa_Centro_text.ReleaseImage();

	mesa_text.LoadBMP("Textures/Mesamadera.bmp");
	mesa_text.BuildGLTexture();
	mesa_text.ReleaseImage();

	refri_text.LoadBMP("Textures/Refri.bmp");
	refri_text.BuildGLTexture();
	refri_text.ReleaseImage();

	mueblesito_text.LoadBMP("Textures/Mueblesito.bmp");
	mueblesito_text.BuildGLTexture();
	mueblesito_text.ReleaseImage();

	lampara_text.LoadBMP("Textures/lampara.bmp");
	lampara_text.BuildGLTexture();
	lampara_text.ReleaseImage();

	muebleCocina_text.LoadBMP("Textures/Mueblecocina1.bmp");
	muebleCocina_text.BuildGLTexture();
	muebleCocina_text.ReleaseImage();

	estufa_text.LoadBMP("Textures/estufa.bmp");
	estufa_text.BuildGLTexture();
	estufa_text.ReleaseImage();

	lavamanos_text.LoadBMP("Textures/lavamanos.bmp");
	lavamanos_text.BuildGLTexture();
	lavamanos_text.ReleaseImage();

	cajonesSup_text.LoadBMP("Textures/cajonesup.bmp");
	cajonesSup_text.BuildGLTexture();
	cajonesSup_text.ReleaseImage();

	trapecio_text.LoadBMP("Textures/trapecio.bmp");
	trapecio_text.BuildGLTexture();
	trapecio_text.ReleaseImage();

	paredInterna_text.LoadBMP("Textures/interna.bmp");
	paredInterna_text.BuildGLTexture();
	paredInterna_text.ReleaseImage();

	llaves_text.LoadBMP("Textures/llaves.bmp");
	llaves_text.BuildGLTexture();
	llaves_text.ReleaseImage();

	sillad_text.LoadBMP("Textures/sillader.bmp");
	sillad_text.BuildGLTexture();
	sillad_text.ReleaseImage();

	sillai_text.LoadBMP("Textures/sillaiz.bmp");
	sillai_text.BuildGLTexture();
	sillai_text.ReleaseImage();

	sillao_text.LoadBMP("Textures/sillafon.bmp");
	sillao_text.BuildGLTexture();
	sillao_text.ReleaseImage();

	tele_text.LoadBMP("Textures/tele.bmp");
	tele_text.BuildGLTexture();
	tele_text.ReleaseImage();

	casa_text.LoadBMP("Textures/Casa.bmp");
	casa_text.BuildGLTexture();
	casa_text.ReleaseImage();

	tv[0].LoadBMP("Textures/tv0.bmp");
	tv[0].BuildGLTexture();
	tv[0].ReleaseImage();

	tv[1].LoadBMP("Textures/tv1.bmp");
	tv[1].BuildGLTexture();
	tv[1].ReleaseImage();

	tv[2].LoadBMP("Textures/tv2.bmp");
	tv[2].BuildGLTexture();
	tv[2].ReleaseImage();

	tv[3].LoadBMP("Textures/tv3.bmp");
	tv[3].BuildGLTexture();
	tv[3].ReleaseImage();

	tv[4].LoadBMP("Textures/tv4.bmp");
	tv[4].BuildGLTexture();
	tv[4].ReleaseImage();

	tv[5].LoadBMP("Textures/tv5.bmp");
	tv[5].BuildGLTexture();
	tv[5].ReleaseImage();

	techito_text.LoadBMP("Textures/techito.bmp");
	techito_text.BuildGLTexture();
	techito_text.ReleaseImage();

	escalones_text.LoadBMP("Textures/escalones.bmp");
	escalones_text.BuildGLTexture();
	escalones_text.ReleaseImage();

	ventanaFrente_text.LoadBMP("Textures/ventanaFrente.bmp");
	ventanaFrente_text.BuildGLTexture();
	ventanaFrente_text.ReleaseImage();


	ventanader_text.LoadBMP("Textures/ventanader.bmp");
	ventanader_text.BuildGLTexture();
	ventanader_text.ReleaseImage();

	ventanaiz_text.LoadBMP("Textures/ventanaiz.bmp");
	ventanaiz_text.BuildGLTexture();
	ventanaiz_text.ReleaseImage();

	puerta_text.LoadBMP("Textures/Puerta.bmp");
	puerta_text.BuildGLTexture();
	puerta_text.ReleaseImage();
	
	isla_text.LoadBMP("Textures/isla.bmp");
	isla_text.BuildGLTexture();
	isla_text.ReleaseImage();

	palmera1_text.LoadBMP("Textures/palmera1.bmp");
	palmera1_text.BuildGLTexture();
	palmera1_text.ReleaseImage();

	palmera2_text.LoadBMP("Textures/palmera2.bmp");
	palmera2_text.BuildGLTexture();
	palmera2_text.ReleaseImage();

	palmera3_text.LoadBMP("Textures/palmera3.bmp");
	palmera3_text.BuildGLTexture();
	palmera3_text.ReleaseImage();

	rocas_text.LoadBMP("Textures/rocas.bmp");
	rocas_text.BuildGLTexture();
	rocas_text.ReleaseImage();

	tapete_text.LoadBMP("Textures/tapete.bmp");
	tapete_text.BuildGLTexture();
	tapete_text.ReleaseImage();

	casita_text.LoadBMP("Textures/casita.bmp");
	casita_text.BuildGLTexture();
	casita_text.ReleaseImage();

	techo_text.LoadBMP("Textures/techo.bmp");
	techo_text.BuildGLTexture();
	techo_text.ReleaseImage();

	techoIn_text.LoadBMP("Textures/techoin.bmp");
	techoIn_text.BuildGLTexture();
	techoIn_text.ReleaseImage();

	agua_text.LoadTGA("Textures/water.tga");
	agua_text.BuildGLTexture();
	agua_text.ReleaseImage();



	

}

void pintaTexto(float x, float y, float z, void *font,char *string)
{
  
  char *c;     //Almacena los caracteres a escribir
  glRasterPos3f(x, y, z);	//Posicion apartir del centro de la ventana
  //glWindowPos2i(150,100);
  for (c=string; *c != '\0'; c++) //Condicion de fin de cadena
  {
    glutBitmapCharacter(font, *c); //imprime
  }
}





void waves(int size) {

	glPointSize(5.0f);
	float noise;
	GLfloat vertices[4096][3];
	

	
	for (int x = 0; x < size; x++) {
		for (int y = 0; y < size; y++) {

			noise = perlin2d(x + dummy, y + (dummy*0.5), 0.1, 4)*ampNoise;
			
			
			vertices[y+(x*size)][0] = x ;
			vertices[(y + (x * size))][1] = noise;
			vertices[(y + (x * size))][2] = y;
			


		}
	}
	glEnd();
	glColor3f(0, 0, 1);

	glBegin(GL_TRIANGLE_STRIP);
	for (int v = 0; v < (size*size)-size; v+=2) {
		glVertex3fv(vertices[v]);
		glVertex3fv(vertices[v+size]);
		glVertex3fv(vertices[v + 1]);
		glVertex3fv(vertices[v + size+1]);
	}


	glColor3f(1, 1, 1);
	glEnd();

}

void waterEffect() {
	glEnable(GL_BLEND);     // Turn Blending On
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR);

	if (activateWater) {
		
		water(agua_text.GLindex, dummy*0.3);

		
		runningWater = true;
		
	}
	
	
	else if (runningWater && !activateWater) {
		runningWater = false;
	}
	glPushMatrix();
	glTranslatef(0.0, waterLevel + 0.06, 0);
	water_plane(agua_text.GLindex, dummy*0.02);
	glDisable(GL_BLEND);
	glPopMatrix();
}

void display ( void )   // Creamos la funcion donde se dibuja
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	
		
	glPushMatrix();
		

		/*gluLookAt(	objCamera.mPos.x,  objCamera.mPos.y,  objCamera.mPos.z,	
					objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,	
					objCamera.mUp.x,   objCamera.mUp.y,   objCamera.mUp.z);*/
		if (deltaMove) {
			computePos(deltaMove);
		}
			
		gluLookAt(x, 1.5f+up_view, z,
				  x + lx, 1.5f+up_view, z + lz,
				  0.0f, 1.0f, 0.0f);
	

		glPushMatrix();		
			glPushMatrix(); //Creamos cielo
				glDisable(GL_LIGHTING);
				glTranslatef(0,20,0);
				fig1.skybox(130.0, 130.0, 130.0,text1.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-25, -1.5, -25);

				waves(64);

			

			glPopMatrix();
			
			glTranslatef(0, 0, -8.0);

			glPushMatrix();
		
				sillon(sillon_text.GLindex);
				alfombra(alfombra_text.GLindex);
				mesaCentro(mesa_Centro_text.GLindex);
				muebleTV(muebleTV_text.GLindex);
				mesa(mesa_text.GLindex);
				refri(refri_text.GLindex);
				mueblesito(mueblesito_text.GLindex);
				lampara(lampara_text.GLindex);
				muebleCocina(muebleCocina_text.GLindex);
				estufa(estufa_text.GLindex);
				lavamanos(lavamanos_text.GLindex);
				cajonesSup(cajonesSup_text.GLindex);
				trapecio(trapecio_text.GLindex);
				paredInterna(paredInterna_text.GLindex);
				llaves(llaves_text.GLindex);
				tele(tele_text.GLindex);
				pantalla(tv[tv_sprite].GLindex);
				tapete(tapete_text.GLindex);
				casa(casa_text.GLindex);
				techito(techito_text.GLindex);
				ventanaFrente(ventanaFrente_text.GLindex);
				escalones(escalones_text.GLindex);
				isla(isla_text.GLindex);
				rocas(rocas_text.GLindex);
				palmera1(palmera1_text.GLindex);
				palmera2(palmera2_text.GLindex);
				palmera3(palmera3_text.GLindex);
				tapete(tapete_text.GLindex);
				techo(techo_text.GLindex);
				casita(casita_text.GLindex);
				techoIn(techoIn_text.GLindex);
				
				waterEffect();

				
				//Silla Derecha
				glPushMatrix();
					glTranslatef(1.34468f,0.0f , -1.91383f);
					silla(sillad_text.GLindex);
				glPopMatrix();

				//Silla Izquierda
				glPushMatrix();
					glTranslatef(-0.776643f, 0.0f, -1.91383f);
					glRotatef(180, 0.0f, 1.0f, 0.0f);
					silla(sillai_text.GLindex);
				glPopMatrix();

				//Silla principio

				glPushMatrix();
					glTranslatef(-0.56804f, 0.0f, 4.13631);
					glRotatef(-147, 0.0f, 1.0f, 0.0f);
					silla(sillao_text.GLindex);
				glPopMatrix();
				//Ventana Derecha
				glPushMatrix();
					glTranslatef(3.9245f, 2.74399f, 1.56438f);
					ventana(ventanader_text.GLindex);
				glPopMatrix();
				//Ventana Derecha izquierda
				glPushMatrix();
					glTranslatef(-3.9245f, 2.74399f, 0);
					glRotatef(180, 0.0f, 1.0f, 0.0f);
					ventana(ventanaiz_text.GLindex);
				glPopMatrix();
				//puerta
				glPushMatrix();
					glTranslatef(2.92907f, 0, 4.78039f);
					glRotatef(openAngle, 0.0f, 1.0f, 0.0f);
					puerta(puerta_text.GLindex);
				glPopMatrix();

				
			
			glPopMatrix();

			
			



			glPopMatrix();



			glColor3f(1.0,1.0,1.0);

		glPopMatrix(); 

		

	glPopMatrix();

	glutSwapBuffers ( );

}

void animacion()
{
	dummy+=0.1;
	
		fig3.text_izq-= 0.001;
		fig3.text_der-= 0.001;
		if(fig3.text_izq<-1)
			fig3.text_izq=0;
		if(fig3.text_der<0)
			fig3.text_der=1;
	


	currentTime = RunTimeInSeconds();
	elapsedTime = currentTime - lastUpdateTime;


	//Animacion TV
	if (elapsedTime >= 1.0 / FPS) {

		tempCounter++;
		tempCounter = tempCounter % 3;
		

		if (tempCounter >= 2) {
			tv_sprite++;

			tv_sprite = tv_sprite % 6;
		}
		lastUpdateTime = currentTime;
		glutPostRedisplay();
	}

	//Puerta

	if (open_door && openAngle>-90) {
		
		openAngle -= 1;
	}
	else if (!open_door &&openAngle < 0) {
		openAngle += 1;
	}

	//Agua
	if (runningWater&& waterLevel<0.33){
		waterLevel += 0.001;
		}

	else if (!runningWater&& waterLevel > 0) {
		waterLevel -= 0.001;
		
	}




	glutPostRedisplay();
}

void reshape ( int width , int height )   // Creamos funcion Reshape
{
  if (height==0)										// Prevenir division entre cero
	{
		height=1;
	}

	glViewport(0,0,width,height);	

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	float aspectRatio;
	aspectRatio = 1.0*width / height;
	// Tipo de Vista
	
	glFrustum (-0.1*aspectRatio, 0.1*aspectRatio,-0.1, 0.1, 0.1, 170.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}







int main ( int argc, char** argv )   // Main Function
{
  PlaySound(TEXT("DragonBall.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
	
	
  glutInit            (&argc, argv); // Inicializamos OpenGL
  glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
  glutInitWindowSize  (500, 500);	// Tamaño de la Ventana
  glutInitWindowPosition (0, 0);	//Posicion de la Ventana
  glutCreateWindow    ("Final"); // Nombre de la Ventana
  //glutFullScreen     ( );         // Full Screen
  InitGL ();		// Parametros iniciales de la aplicacion
  
  glutDisplayFunc     ( display );  //Indicamos a Glut función de dibujo
  glutReshapeFunc     ( reshape );	//Indicamos a Glut función en caso de cambio de tamano
  //glutKeyboardFunc    ( keyboard );	//Indicamos a Glut función de manejo de teclado
  //glutSpecialFunc     ( arrow_keys );	//Otras

  glutIgnoreKeyRepeat(1);
  glutKeyboardFunc(processNormalKeys);
  glutSpecialFunc(pressKey);
  glutSpecialUpFunc(releaseKey);
  glutKeyboardUpFunc(releaseNormalKeys);
  // here are the two new functions
  glutMouseFunc(mouseButton);
  glutMotionFunc(mouseMove);


  glutIdleFunc		  ( animacion );


  glutMainLoop        ( );          // 

  
 
	  
		  


  
  return 0;
}
