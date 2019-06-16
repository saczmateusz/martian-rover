#include "DEFINITIONS.h"
#include "szescian/Rover/Rover.h"
#include "szescian/Grid/Grid.h"
#include "szescian/Cylinder/Cylinder.h"
#include "szescian/Cone/Cone.h"
#include "szescian/Terrain/Terrain.h"
#include "szescian/Obstacle/Obstacle.h"
#include <AntTweakBar.h>
#include <irrKlang.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Color Palette handle
HPALETTE hPalette = NULL;

// Application name and instance storeage
static LPCTSTR lpszAppName = "Martian rover";
static HINSTANCE hInstance;

//scoreboard file
fstream scoreboard;
list<int> sbList;

int properSB[5] = { 0, 0, 0, 0, 0 };

//create audio engine
irrklang::ISoundEngine* playSound = irrklang::createIrrKlangDevice();

// Rotation amounts - camera
static GLfloat cameraXrot = 0.0f;
static GLfloat cameraYrot = 0.0f;
static GLfloat cameraZrot = 0.0f;

static GLfloat velocity = 0.0f;
static GLfloat engineRot = 0.0f;
static GLfloat roverRotSpeed = 15.0f;
static GLfloat engineRotSpeed = 5.0f;

static GLfloat roverRadius = 40.0f;
vector<float> roverPos;


GLfloat obs1mid[3] = { -180, -175, 40 }; // x, y, z
GLfloat obs1radius = 25;

GLfloat obs2mid[3] = { 99, 308, 40 }; // x, y, z
GLfloat obs2radius = 46;

bool collision[3] = { 0, 0, 0 };

static GLfloat posX = 0.0f;
static GLfloat posY = 0.0f;
static GLfloat posZ = 0.0f;

GLfloat rovmid[3] = { posX + 35, posY + 35, 40 }; // x, y, z

//Cylinder obsRange(colour, rovmid, roverRadius, 40, 0, 1);

GLfloat batteryLife = 100.0;

unsigned int dust = 0;
unsigned int banana = 0;
unsigned int rock = 0;
unsigned int smok = 0;

//new ones
static GLfloat rotAngle = 0.0f;
static GLfloat rotAngleDeg = 0.0f;
static GLfloat swingRadius = 0.0f;

static GLfloat const_velocity = 0.7f;
static GLfloat velocityL = 0.0f;
static GLfloat velocityR = 0.0f;
static GLfloat momentumConst = 0.2f*const_velocity;
bool velocityUpdate = 0;
std::vector<GLfloat> midPointLocation{ 0.0f,0.0f,0.0f };

Grid grid(1000);
Rover rover(0, 0, 0);
Terrain terrain;
Obstacle ob1(-6, -6, 0.15f, 30);
Obstacle ob2(2, 6, 0.6f, 50);

GLfloat colour[3] = { 218/(float)255, 185/ (float)255, 35/(float)255 };
GLfloat checkpointLocation[3] = {40, 160, 70 };
Cone checkpoint(colour, checkpointLocation, 15, 40);

static bool counterXD = true;

int points = 0;

static GLfloat zoom;

static GLsizei lastHeight;
static GLsizei lastWidth;

void ogarnijScoreboard()
{
	if (scoreboard.good())
	{
		string napis;
		while (!scoreboard.eof())
		{
			getline(scoreboard, napis);
			if (napis.length() > 0)
			{
				sbList.push_back(stoi(napis));
			}
		}
		scoreboard.close();
		sbList.sort();
		sbList.reverse();
		int i = 0;
		for (list<int>::iterator it = sbList.begin(); it != sbList.end(); it++)
		{
			properSB[i] = *it;
			++i;
			if (i > 4)
				break;
		}
	}
}

GLfloat distanceCalculate(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
{
	return sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
}

unsigned int LoadTexture(const char* file, GLenum textureSlot)
{
	GLuint texHandle;
	// Copy file to OpenGL
	glGenTextures(textureSlot, &texHandle);
	glBindTexture(GL_TEXTURE_2D, texHandle);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	const auto data = stbi_load(file, &width, &height, &nrChannels, 0);
	if (data)
	{
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		gluBuild2DMipmaps(GL_TEXTURE_2D, nrChannels, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
	else
	{
		//error
	}
	stbi_image_free(data);
	return texHandle;
}

// Opis tekstury
BITMAPINFOHEADER	bitmapInfoHeader;	// nagłówek obrazu
unsigned char*		bitmapData;			// dane tekstury
unsigned int		texture[2];			// obiekt tekstury


// Declaration for Window procedure
LRESULT CALLBACK WndProc(HWND    hWnd,
	UINT    message,
	WPARAM  wParam,
	LPARAM  lParam);

// Set Pixel Format function - forward declaration
void SetDCPixelFormat(HDC hDC);

// Reduces a normal vector specified as a set of three coordinates,
// to a unit normal vector of length one.

// Change viewing volume and viewport.  Called when window is resized
void ChangeSize(GLsizei w, GLsizei h)
{
	GLfloat nRange = 200.0f;
	GLfloat fAspect;
	// Prevent a divide by zero
	if (h == 0)
		h = 1;

	lastWidth = w;
	lastHeight = h;

	fAspect = (GLfloat)w / (GLfloat)h;
	// Set Viewport to window dimensions
	glViewport(0, 0, w, h);

	// Reset coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Establish clipping volume (left, right, bottom, top, near, far)
	/*if (w <= h)
		glOrtho (-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
	else
		glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);
*/
// Establish perspective: 

	gluPerspective(60.0f, fAspect, 1.0, 2000.0f);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}



// This function does any needed initialization on the rendering
// context.  Here it sets up and initializes the lighting for
// the scene.
void SetupRC()
{
	// Light values and coordinates
	//GLfloat  ambientLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	//GLfloat  diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	//GLfloat  specular[] = { 1.0f, 1.0f, 1.0f, 1.0f};
	//GLfloat	 lightPos[] = { 200.0f, -150.0f, 400.0f, 1.0f };
	//GLfloat  specref[] =  { 1.0f, 1.0f, 1.0f, 1.0f };


	glEnable(GL_DEPTH_TEST);	// Hidden surface removal
	glFrontFace(GL_CCW);		// Counter clock-wise polygons face out
	//glEnable(GL_CULL_FACE);		// Do not calculate inside of jet

	// Enable lighting
	//glEnable(GL_LIGHTING);

	// Setup and enable light 0
	//glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
	//glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);
	//glLightfv(GL_LIGHT0,GL_SPECULAR,specular);
	//glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
	//glEnable(GL_LIGHT0);

	// Enable color tracking
	//glEnable(GL_COLOR_MATERIAL);

	// Set Material properties to follow glColor values
	//glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// All materials hereafter have full specular reflectivity
	// with a high shine
	//glMaterialfv(GL_FRONT, GL_SPECULAR,specref);
	//glMateriali(GL_FRONT,GL_SHININESS,128);


	// White background
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	// Black brush
	glColor3f(0.0, 0.0, 0.0);


	midPointLocation = rover.getPos();
}

void RenderScene(void)
{
	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

	glRotatef(cameraXrot, 1.0f, 0.0f, 0.0f);
	glRotatef(cameraYrot, 0.0f, 1.0f, 0.0f);
	glRotatef(cameraZrot, 0.0f, 0.0f, 1.0f);
	glRotatef(zoom, 0, 0, 0);

	roverPos = rover.getPos();

	if (velocityUpdate)
	{
		velocity = (velocityL + velocityR) / 2;
		velocityUpdate = 0;
	}

	if (velocityL != velocityR)
	{
		if (swingRadius = 50.0f*(velocityL + velocityR) / (2 * (velocityL - velocityR)))
			rotAngle += GLfloat(atan2(swingRadius, 0) - atan2(swingRadius, velocity));
	}

	//Sposób na odróźnienie "przedniej" i "tylniej" ściany wielokąta:
	//glPolygonMode(GL_BACK,GL_LINE);
	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

	posX += velocity * sin(-rotAngle); // Obliczanie nowej pozycji w osi x; X = x_0 + v*t; gdzie t = sin(-a);
	posY += velocity * cos(rotAngle); // Obliczanie nowej pozycji w osi y; Y = y_0 + v*t; gdzie t = cos(a);

	gluLookAt(
		posX + 30, // eye X
		posY - 200, // eye Y
		posZ + 350, // eye Z
		posX + 30,// center X
		posY + 40, // center Y
		posZ, // center Z
		0.0,
		1.0,
		0.0
	);

	glPushMatrix();

	glTranslatef(posX, posY, posZ); // translacja o wektory przemieszczenia obliczone wyzej

	if (!velocityUpdate)
	{
		if (velocityL > 0)
		{
			if (velocityL - 4 * momentumConst > 0)
				velocityL -= 4 * momentumConst;
			else velocityL = 0;
		}
		else
		{
			if (velocityL + 4 * momentumConst < 0)
				velocityL += 4 * momentumConst;
			else velocityL = 0;
		}


		if (velocityR > 0)
		{
			if (velocityR - 4 * momentumConst > 0)
				velocityR -= 4 * momentumConst;
			else velocityR = 0;
		}
		else
		{
			if (velocityR + 4 * momentumConst < 0)
				velocityR += 4 * momentumConst;
			else velocityR = 0;
		}
		velocity = (velocityL + velocityR) / 2;
		if (engineRot < 0)
		{
			engineRot += engineRotSpeed / 4;
		}
		else if (engineRot > 0)
		{
			engineRot -= engineRotSpeed / 4;
		}
	}

	glTranslatef(midPointLocation[0], midPointLocation[1], midPointLocation[2]); // powrót do pozycji wyjściowej
	glRotatef(GLfloat(rotAngle * 180 / GL_PI), 0.0f, 0.0f, 1.0f); // obrót wokół punktu 0,0 po osi Z
	glTranslatef(-midPointLocation[0], -midPointLocation[1], -midPointLocation[2]); // translacja do punktu 0,0

	rover.drawRover(engineRot, 0, 0, 1);
	glPopMatrix();

	if (checkpointLocation[2] < 80 && counterXD == true)
	{
		checkpointLocation[2] += 1;
		counterXD = checkpointLocation[2] < 80 ? true : false;
	}
	else if (checkpointLocation[2] > 60 && counterXD == false)
	{
		checkpointLocation[2] -= 1;
		counterXD = checkpointLocation[2] > 60 ? false : true;
	}

	checkpoint.center[2] = checkpointLocation[2];
	checkpoint.drawCone(180, 1, 0, 0);

	rovmid[0] = posX + 35;
	rovmid[1] = posY + 35;

	collision[0] = !(distanceCalculate(rovmid[0], rovmid[1], obs1mid[0], obs1mid[1]) > roverRadius + obs1radius);
	collision[1] = !(distanceCalculate(rovmid[0], rovmid[1], obs2mid[0], obs2mid[1]) > roverRadius + obs2radius);
	collision[2] = !(distanceCalculate(rovmid[0], rovmid[1], checkpoint.center[0], checkpoint.center[1]) > roverRadius + checkpoint.radius);

	if (collision[2])
	{
		playSound->play2D("Audio/bell.wav");
		++points;
		checkpointLocation[0] = checkpoint.center[0] = (rand() % 700) - 350.0f;
		checkpointLocation[1] = checkpoint.center[1] = (rand() % 700) - 350.0f;
		batteryLife = batteryLife < 70.0f ? batteryLife + 30.0f : 100.0f;
	}

	if (velocity < -0.4f || velocity > 0.4f)
	{
		batteryLife -= 0.3f;
		if (batteryLife < 0.0f)
		{
			batteryLife = 0.0f;
			velocity = 0.0f;
			velocityL = 0.0f;
			velocityR = 0.0f;
			playSound->play2D("Audio/gameover.wav");
			fstream zapiszWynik;
			zapiszWynik.open("scoreboard.txt", ios::app);
			//zapiszWynik.write(to_string(points));
			zapiszWynik << points << endl;
			zapiszWynik.close();
		}
	}

	if (collision[0] || collision[1])
	{
		playSound->play2D("Audio/explosion.wav");
		velocityL = -0.5f*velocityL;
		velocityR = -0.5f*velocityR;
		velocity = -0.5f*velocity;
	}

	rotAngleDeg = GLfloat(fmod(rotAngle * 180.0f / GL_PI, 360));

	grid.drawGrid();
	terrain.drawTerrain();

	
	//glTranslatef(midPointLocation[0], midPointLocation[1], midPointLocation[2]); // powrót do pozycji wyjściowej
	//glRotatef(GLfloat(rotAngle * 180 / GL_PI), 0.0f, 0.0f, 1.0f); // obrót wokół punktu 0,0 po osi Z
	//glTranslatef(-midPointLocation[0], -midPointLocation[1], -midPointLocation[2]); // translacja do punktu 0,0

	//checkpoint.drawCone(engineRot, 0, 0, 1);
	


	ob1.drawObstacle();
	ob2.drawObstacle();


	///////////////////////////////////////////////////////////////////////////////////
	TwInit(TW_OPENGL, NULL);
	TwBar *bar;
	bar = TwNewBar("Parametry");

	int barsize[] = { 200,500 };

	TwWindowSize(800,700);
	TwSetParam(bar, NULL, "size", TW_PARAM_INT32, 2, barsize);
	TwAddButton(bar, "Martian rover", NULL, NULL, "");
	TwAddVarRO(bar, "Velocity", TW_TYPE_FLOAT, &velocity, "precision=1");
	TwAddVarRO(bar, "Velocity L", TW_TYPE_FLOAT, &velocityL, "precision=1");
	TwAddVarRO(bar, "Velocity R", TW_TYPE_FLOAT, &velocityR, "precision=1");
	TwAddSeparator(bar, "Battery life", "battery");

	//TwAddVarRW(bar, "obstacle 1", TW_TYPE_BOOLCPP, &collision[0], "");
	//TwAddVarRW(bar, "obstacle 2", TW_TYPE_BOOLCPP, &collision[1], "");
	//TwAddSeparator(bar, NULL, "");

	TwAddVarRO(bar, "X", TW_TYPE_FLOAT, &posX, "precision=0");
	TwAddVarRO(bar, "Y", TW_TYPE_FLOAT, &posY, "precision=0");
	TwAddSeparator(bar, NULL, "");

	TwAddVarRO(bar, "checkpoint X", TW_TYPE_FLOAT, &checkpointLocation[0], "precision=0");
	TwAddVarRO(bar, "checkpoint Y", TW_TYPE_FLOAT, &checkpointLocation[1], "precision=0");
	TwAddSeparator(bar, NULL, "");

	TwAddVarRO(bar, "Rocket fuel %", TW_TYPE_FLOAT, &batteryLife, "precision=0");
	TwAddSeparator(bar, "Position", "pos");

	TwAddVarRO(bar, "points", TW_TYPE_INT32, &points, "");
	TwAddSeparator(bar, NULL, "");

	//TwAddButton(bar, "Scoreboard", NULL, NULL, "");
	TwAddVarRO(bar, "1:", TW_TYPE_INT32, &properSB[0], "");
	TwAddVarRO(bar, "2:", TW_TYPE_INT32, &properSB[1], "");
	TwAddVarRO(bar, "3:", TW_TYPE_INT32, &properSB[2], "");
	TwAddVarRO(bar, "4:", TW_TYPE_INT32, &properSB[3], "");
	TwAddVarRO(bar, "5:", TW_TYPE_INT32, &properSB[4], "");

	

	TwDraw();

	//////////////////////////////////////////////////////////////

	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glFlush();
}


// Select the pixel format for a given device context
void SetDCPixelFormat(HDC hDC)
{
	int nPixelFormat;

	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),  // Size of this structure
		1,                                                              // Version of this structure    
		PFD_DRAW_TO_WINDOW |                    // Draw to Window (not to bitmap)
		PFD_SUPPORT_OPENGL |					// Support OpenGL calls in window
		PFD_DOUBLEBUFFER,                       // Double buffered
		PFD_TYPE_RGBA,                          // RGBA Color mode
		24,                                     // Want 24bit color 
		0,0,0,0,0,0,                            // Not used to select mode
		0,0,                                    // Not used to select mode
		0,0,0,0,0,                              // Not used to select mode
		32,                                     // Size of depth buffer
		0,                                      // Not used to select mode
		0,                                      // Not used to select mode
		PFD_MAIN_PLANE,                         // Draw in main plane
		0,                                      // Not used to select mode
		0,0,0 };                                // Not used to select mode

	// Choose a pixel format that best matches that described in pfd
	nPixelFormat = ChoosePixelFormat(hDC, &pfd);

	// Set the pixel format for the device context
	SetPixelFormat(hDC, nPixelFormat, &pfd);
}



// If necessary, creates a 3-3-2 palette for the device context listed.
HPALETTE GetOpenGLPalette(HDC hDC)
{
	HPALETTE hRetPal = NULL;	// Handle to palette to be created
	PIXELFORMATDESCRIPTOR pfd;	// Pixel Format Descriptor
	LOGPALETTE *pPal;			// Pointer to memory for logical palette
	int nPixelFormat;			// Pixel format index
	int nColors;				// Number of entries in palette
	int i;						// Counting variable
	BYTE RedRange, GreenRange, BlueRange;
	// Range for each color entry (7,7,and 3)


// Get the pixel format index and retrieve the pixel format description
	nPixelFormat = GetPixelFormat(hDC);
	DescribePixelFormat(hDC, nPixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

	// Does this pixel format require a palette?  If not, do not create a
	// palette and just return NULL
	if (!(pfd.dwFlags & PFD_NEED_PALETTE))
		return NULL;

	// Number of entries in palette.  8 bits yeilds 256 entries
	nColors = 1 << pfd.cColorBits;

	// Allocate space for a logical palette structure plus all the palette entries
	pPal = (LOGPALETTE*)malloc(sizeof(LOGPALETTE) + nColors * sizeof(PALETTEENTRY));

	// Fill in palette header 
	pPal->palVersion = 0x300;		// Windows 3.0
	pPal->palNumEntries = nColors; // table size

	// Build mask of all 1's.  This creates a number represented by having
	// the low order x bits set, where x = pfd.cRedBits, pfd.cGreenBits, and
	// pfd.cBlueBits.  
	RedRange = (1 << pfd.cRedBits) - 1;
	GreenRange = (1 << pfd.cGreenBits) - 1;
	BlueRange = (1 << pfd.cBlueBits) - 1;

	// Loop through all the palette entries
	for (i = 0; i < nColors; i++)
	{
		// Fill in the 8-bit equivalents for each component
		pPal->palPalEntry[i].peRed = (i >> pfd.cRedShift) & RedRange;
		pPal->palPalEntry[i].peRed = (unsigned char)(
			(double)pPal->palPalEntry[i].peRed * 255.0 / RedRange);

		pPal->palPalEntry[i].peGreen = (i >> pfd.cGreenShift) & GreenRange;
		pPal->palPalEntry[i].peGreen = (unsigned char)(
			(double)pPal->palPalEntry[i].peGreen * 255.0 / GreenRange);

		pPal->palPalEntry[i].peBlue = (i >> pfd.cBlueShift) & BlueRange;
		pPal->palPalEntry[i].peBlue = (unsigned char)(
			(double)pPal->palPalEntry[i].peBlue * 255.0 / BlueRange);

		pPal->palPalEntry[i].peFlags = (unsigned char)NULL;
	}


	// Create the palette
	hRetPal = CreatePalette(pPal);

	// Go ahead and select and realize the palette for this device context
	SelectPalette(hDC, hRetPal, FALSE);
	RealizePalette(hDC);

	// Free the memory used for the logical palette structure
	free(pPal);

	// Return the handle to the new palette
	return hRetPal;
}

// Entry point of all Windows programs
int APIENTRY WinMain(HINSTANCE       hInst,
	HINSTANCE       hPrevInstance,
	LPSTR           lpCmdLine,
	int                     nCmdShow)
{
	MSG                     msg;            // Windows message structure
	WNDCLASS        wc;                     // Windows class structure
	HWND            hWnd;           // Storeage for window handle

	hInstance = hInst;

	// Register Window style
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);

	// No need for background brush for OpenGL window
	wc.hbrBackground = NULL;

	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU);
	wc.lpszClassName = lpszAppName;

	// Register the window class
	if (RegisterClass(&wc) == 0)
		return FALSE;


	// Create the main application window
	hWnd = CreateWindow(
		lpszAppName,
		lpszAppName,

		// OpenGL requires WS_CLIPCHILDREN and WS_CLIPSIBLINGS
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,

		// Window position and size
		-1000, 50,
		800, 800,
		NULL,
		NULL,
		hInstance,
		NULL);

	// If window was not created, quit
	if (hWnd == NULL)
		return FALSE;


	// Display the window
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	// Process application messages until the application closes
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return int(msg.wParam);
}




// Window procedure, handles all messages for this program
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HGLRC hRC;
	static HDC hDC;

	switch (message)
	{
	case WM_CREATE:
		hDC = GetDC(hWnd);
		SetDCPixelFormat(hDC);
		hPalette = GetOpenGLPalette(hDC);
		hRC = wglCreateContext(hDC);
		wglMakeCurrent(hDC, hRC);
		SetupRC();

		scoreboard.open("scoreboard.txt", std::ios::in);
		ogarnijScoreboard();
		playSound->play2D("Audio/startup.wav");
		srand(int(time(NULL)));
		dust = LoadTexture("Textures/dust.png", 1);
		banana = LoadTexture("Textures/banana.png", 1);
		rock = LoadTexture("Textures/rock.png", 1);
		smok = LoadTexture("Textures/smok.png", 1);
		terrain.setTexture(dust);
		rover.setTextures(banana, smok);
		ob1.setTexture(rock);
		ob2.setTexture(rock);
		break;

	case WM_DESTROY:
		playSound->drop();
		wglMakeCurrent(hDC, NULL);
		wglDeleteContext(hRC);
		if (hPalette != NULL)
			DeleteObject(hPalette);
		PostQuitMessage(0);
		break;

	case WM_SIZE:
		ChangeSize(LOWORD(lParam), HIWORD(lParam));
		break;

	case WM_PAINT:
	{
		RenderScene();
		SwapBuffers(hDC);
		InvalidateRect(hWnd, NULL, FALSE);
	}
	break;

	case WM_QUERYNEWPALETTE:
		if (hPalette)
		{
			int nRet;
			SelectPalette(hDC, hPalette, FALSE);
			nRet = RealizePalette(hDC);
			InvalidateRect(hWnd, NULL, FALSE);
			return nRet;
		}
		break;

	case WM_PALETTECHANGED:
		if ((hPalette != NULL) && ((HWND)wParam != hWnd))
		{
			SelectPalette(hDC, hPalette, FALSE);
			RealizePalette(hDC);
			UpdateColors(hDC);
			return 0;
		}
		break;

	case WM_KEYDOWN:
	{
		if (wParam == VK_NUMPAD8)
			cameraXrot -= 5.0f;

		if (wParam == VK_NUMPAD2)
			cameraXrot += 5.0f;

		if (wParam == VK_NUMPAD4)
			cameraYrot -= 5.0f;

		if (wParam == VK_NUMPAD6)
			cameraYrot += 5.0f;

		if (wParam == VK_NUMPAD9)
			cameraZrot -= 5.0f;

		if (wParam == VK_NUMPAD7)
			cameraZrot += 5.0f;
		
		if (wParam == VK_NUMPAD5)
		{
			cameraXrot = 0.0f;
			cameraYrot = 0.0f;
			cameraZrot = 0.0f;
		}

		if (wParam == VK_SUBTRACT)
			zoom += 20.0f;

		if (wParam == VK_ADD)
			zoom -= 20.0f;

		if (wParam == 'R')
		{
			posX = posY = velocityL = velocityR = velocity = 0;
		}

		if (wParam == 'W')
		{
			if (velocity < 5 && batteryLife > 0.0f)
			{
				velocityL += 4 * const_velocity;
				velocityR += 4 * const_velocity;
				velocityUpdate = 1;
			}
		}

		if (wParam == 'S' && batteryLife > 0.0f)
		{
			if (velocity > -5)
			{
				velocityL -= 4 * const_velocity;
				velocityR -= 4 * const_velocity;
				velocityUpdate = 1;
			}
		}

		if (wParam == 'A' && batteryLife > 0.0f)
		{
			if (velocity >= 0 && velocity < 5)
			{
				velocityL += const_velocity;
				velocityUpdate = 1;
				if (engineRot >= -30.0f)
				{
					engineRot -= engineRotSpeed;
				}
			}
			else if (velocity > -5 && velocity <= 0)
			{
				velocityL -= const_velocity;
				velocityUpdate = 1;
				if (engineRot >= -30.0f)
				{
					engineRot -= engineRotSpeed;
				}
			}
		}

		if (wParam == 'D' && batteryLife > 0.0f)
		{
			if (velocity >= 0 && velocity < 5)
			{
				velocityR += const_velocity;
				velocityUpdate = 1;
				if (engineRot <= 30.0f)
				{
					engineRot += engineRotSpeed;
				}
			}
			else if (velocity > -5 && velocity <= 0)
			{
				velocityR -= const_velocity;
				velocityUpdate = 1;
				if (engineRot <= 30.0f)
				{
					engineRot += engineRotSpeed;
				}
			}
		}

		if (wParam == VK_CONTROL)
		{
			posZ -= const_velocity;
			velocityUpdate = 1;
		}
		if (wParam == VK_SHIFT)
		{
			posZ += const_velocity;
			velocityUpdate = 1;
		}
		if (wParam == VK_SPACE)
		{
			velocityR = velocityL = 0;
			velocityUpdate = 1;
		}

		InvalidateRect(hWnd, NULL, FALSE);
	}
	break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case ID_FILE_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			break;
		}
		break;
	}

	default:
		return (DefWindowProc(hWnd, message, wParam, lParam));

	}

	return (0L);
}