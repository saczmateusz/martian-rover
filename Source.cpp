#include "DEFINITIONS.h"
#include "szescian/Rover/Rover.h"
#include "szescian/Grid/Grid.h"
#include "szescian/Terrain/Terrain.h"
#include "szescian/Obstacle/Obstacle.h"
#include "szescian/Cylinder/Cylinder.h"
#include <AntTweakBar.h>


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Color Palette handle
HPALETTE hPalette = NULL;

// Application name and instance storeage
static LPCTSTR lpszAppName = "Martian rover";
static HINSTANCE hInstance;

// Rotation amounts
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
static GLfloat zRot = 0.0f; 

static GLfloat velocity = 0.0f;
static GLfloat engineRot = 0.0f;
static GLfloat rotSpeed = 15.0f; //15.0f kryha
static GLfloat ErotSpeed = 5.0f; //15.0f kryha

static GLfloat roverRadius = 40.0f;
vector<float> roverPos;

GLfloat obs1[4] = { -205.0, -145.0, -155.0, -205.0 };
GLfloat obs2[4] = { 50, 355,  145, 265 };

GLfloat colour[3] = { 1, 0, 0 };

GLfloat obs1mid[3] = { -180, -175, 40 }; // x, y, z, r
GLfloat obs1radius = 25;

GLfloat obs2mid[3] = { 99, 308, 40 }; // x, y, z, r
GLfloat obs2radius = 46;

bool collision[2] = { 0, 0 };

static float cameraX;
static float cameraY;
static float cameraZ;

static GLfloat posX = 0.0f;
static GLfloat posY = 0.0f;
static GLfloat posZ = 0.0f;


GLfloat mrv[4] = { posX - 25, posY + 110, posX + 95, posY - 20 };

GLfloat rovmid[3] = { posX + 35, posY + 35, 40 }; // x, y, z, r
GLfloat rovradius = 55;

Cylinder obsRange(colour, rovmid, rovradius, 40, 0, 1);


GLfloat batteryLife = 100.0;

unsigned int dust = 0;
unsigned int banana = 0;
unsigned int rock = 0;
unsigned int smok = 0;

//new ones
static GLfloat rotAngle = 0.0f;
static GLfloat rotAngleDeg = 0.0f;
static GLfloat swingRadius = 0.0f;

static GLfloat const_velocity = 0.7f; //5.0f ja
static GLfloat velocityL = 0.0f;
static GLfloat velocityR = 0.0f;
static GLfloat momentumConst = 0.2*const_velocity;
bool velocityUpdate = 0;
//std::vector<GLfloat> midPointLocation{ 0.0f,0.0f,0.0f,0.0f };
std::vector<GLfloat> midPointLocation{ 0.0f,0.0f,0.0f };
std::vector<GLfloat> midPointLocationScaled{ 0,0,0 };



Grid grid(1000);
Rover rover(0, 0, 0);
Terrain terrain;
Obstacle ob1(-6, -6, 0.15f, 30);
Obstacle ob2(2, 6, 0.6f, 50);

static GLfloat zoom;

static GLsizei lastHeight;
static GLsizei lastWidth;

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
BITMAPINFOHEADER	bitmapInfoHeader;	// nag³ówek obrazu
unsigned char*		bitmapData;			// dane tekstury
unsigned int		texture[2];			// obiekt tekstury


// Declaration for Window procedure
LRESULT CALLBACK WndProc(   HWND    hWnd,
							UINT    message,
							WPARAM  wParam,
							LPARAM  lParam);

// Dialog procedure for about box
BOOL APIENTRY AboutDlgProc (HWND hDlg, UINT message, UINT wParam, LONG lParam);

// Set Pixel Format function - forward declaration
void SetDCPixelFormat(HDC hDC);

// Reduces a normal vector specified as a set of three coordinates,
// to a unit normal vector of length one.
void ReduceToUnit(float vector[3])
	{
	float length;
	
	// Calculate the length of the vector		
	length = (float)sqrt((vector[0]*vector[0]) + 
						(vector[1]*vector[1]) +
						(vector[2]*vector[2]));

	// Keep the program from blowing up by providing an exceptable
	// value for vectors that may calculated too close to zero.
	if(length == 0.0f)
		length = 1.0f;

	// Dividing each element by the length will result in a
	// unit normal vector.
	vector[0] /= length;
	vector[1] /= length;
	vector[2] /= length;
	}


// Points p1, p2, & p3 specified in counter clock-wise order
void calcNormal(float v[3][3], float out[3])
	{
	float v1[3],v2[3];
	static const int x = 0;
	static const int y = 1;
	static const int z = 2;

	// Calculate two vectors from the three points
	v1[x] = v[0][x] - v[1][x];
	v1[y] = v[0][y] - v[1][y];
	v1[z] = v[0][z] - v[1][z];

	v2[x] = v[1][x] - v[2][x];
	v2[y] = v[1][y] - v[2][y];
	v2[z] = v[1][z] - v[2][z];

	// Take the cross product of the two vectors to get
	// the normal vector which will be stored in out
	out[x] = v1[y]*v2[z] - v1[z]*v2[y];
	out[y] = v1[z]*v2[x] - v1[x]*v2[z];
	out[z] = v1[x]*v2[y] - v1[y]*v2[x];

	// Normalize the vector (shorten length to one)
	ReduceToUnit(out);
	}



// Change viewing volume and viewport.  Called when window is resized
void ChangeSize(GLsizei w, GLsizei h)
	{
	GLfloat nRange = 200.0f;
	GLfloat fAspect;
	// Prevent a divide by zero
	if(h == 0)
		h = 1;

	lastWidth = w;
	lastHeight = h;
		
	fAspect=(GLfloat)w/(GLfloat)h;
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
	
	gluPerspective(60.0f,fAspect,1.0,2000.0f);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	}



// This function does any needed initialization on the rendering
// context.  Here it sets up and initializes the lighting for
// the scene.
void SetupRC()
	{
	// Light values and coordinates
	//GLfloat  ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	//GLfloat  diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	//GLfloat  specular[] = { 1.0f, 1.0f, 1.0f, 1.0f};
	//GLfloat	 lightPos[] = { 0.0f, 150.0f, 150.0f, 1.0f };
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
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f );
	// Black brush
	glColor3f(0.0,0.0,0.0);


	midPointLocation = rover.getPos();

	


	}

// LoadBitmapFile
// opis: ³aduje mapê bitow¹ z pliku i zwraca jej adres.
//       Wype³nia strukturê nag³ówka.
//	 Nie obs³uguje map 8-bitowych.
unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader)
{
	FILE *filePtr;							// wskaŸnik pozycji pliku
	BITMAPFILEHEADER	bitmapFileHeader;		// nag³ówek pliku
	unsigned char		*bitmapImage;			// dane obrazu
	unsigned int		imageIdx = 0;			// licznik pikseli
	unsigned char		tempRGB;				// zmienna zamiany sk³adowych

	// otwiera plik w trybie "read binary"
	filePtr = fopen(filename, "rb");
	if (filePtr == NULL)
		return NULL;

	// wczytuje nag³ówek pliku
	fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
	
	// sprawdza, czy jest to plik formatu BMP
	if (bitmapFileHeader.bfType != BITMAP_ID)
	{
		fclose(filePtr);
		return NULL;
	}

	// wczytuje nag³ówek obrazu
	fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);

	// ustawia wskaŸnik pozycji pliku na pocz¹tku danych obrazu
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);

	// przydziela pamiêæ buforowi obrazu
	bitmapImage = (unsigned char*)malloc(bitmapInfoHeader->biSizeImage);

	// sprawdza, czy uda³o siê przydzieliæ pamiêæ
	if (!bitmapImage)
	{
		free(bitmapImage);
		fclose(filePtr);
		return NULL;
	}

	// wczytuje dane obrazu
	fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);

	// sprawdza, czy dane zosta³y wczytane
	if (bitmapImage == NULL)
	{
		fclose(filePtr);
		return NULL;
	}

	// zamienia miejscami sk³adowe R i B 
	for (imageIdx = 0; imageIdx < bitmapInfoHeader->biSizeImage; imageIdx+=3)
	{
		tempRGB = bitmapImage[imageIdx];
		bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
		bitmapImage[imageIdx + 2] = tempRGB;
	}

	// zamyka plik i zwraca wskaŸnik bufora zawieraj¹cego wczytany obraz
	fclose(filePtr);
	return bitmapImage;
}
// Called to draw scene

void RenderScene(void)
	{
	//float normal[3];	// Storeage for calculated surface normal

	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Save the matrix state and do the rotations
	glPushMatrix();

	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	glRotatef(zRot, 0.0f, 0.0f, 1.0f);
	glRotatef(zoom, 0, 0, 0);
	
	roverPos = rover.getPos();

	if (velocityUpdate)
	{
		velocity = (velocityL + velocityR) / 2;
		velocityUpdate = 0;
	}

	if (velocityL != velocityR)
	{
		if (swingRadius = 50.0f*(velocityL + velocityR) / (2 * (velocityL - velocityR))) // to je swing radius a nie swing angle xD
			rotAngle += atan2(swingRadius, 0) - atan2(swingRadius, velocity);
		//rotAngle = asin(velocity / swingRadius);

	}
	//else if (velocityL == 0)
		//rotAngle = 0;

	//Sposób na odróŸnienie "przedniej" i "tylniej" œciany wielok¹ta:
	//glPolygonMode(GL_BACK,GL_LINE);
	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	
	posX += velocity * sin(-rotAngle); // Obliczanie nowej pozycji w osi x; X = x_0 + v*t; gdzie t = sin(-a);
	posY += velocity * cos(rotAngle);// Obliczanie nowej pozycji w osi y; Y = y_0 + v*t; gdzie t = cos(a);

	gluLookAt(
		posX+30, // eye X
		posY-200, // eye Y
		posZ + 350, // eye Z
		posX+30,// center X
		posY+40, // center Y
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
			if (velocityL - momentumConst > 0)
				velocityL -= momentumConst;
			else velocityL = 0;
		}
		else
		{
			if (velocityL + momentumConst < 0)
				velocityL += momentumConst;
			else velocityL = 0;
		}


		if (velocityR > 0)
		{
			if (velocityR - momentumConst > 0)
				velocityR -= momentumConst;
			else velocityR = 0;
		}
		else
		{
			if (velocityR + momentumConst < 0)
				velocityR += momentumConst;
			else velocityR = 0;
		}
		velocity = (velocityL + velocityR) / 2;
		if (engineRot < 0)
		{
			engineRot += ErotSpeed / 4;
		}
		else if (engineRot > 0)
		{
			engineRot -= ErotSpeed / 4;
		}
	}

	midPointLocationScaled = { midPointLocation[0], midPointLocation[1], midPointLocation[2] };

	glTranslatef(midPointLocationScaled[0], midPointLocationScaled[1], midPointLocationScaled[2]); // powrót do pozycji wyjœciowej
	glRotatef(rotAngle * 180 / GL_PI, 0.0f, 0.0f, 1.0f); // obrót wokó³ punktu 0,0 po osi Z
	glTranslatef(-midPointLocationScaled[0], -midPointLocationScaled[1], -midPointLocationScaled[2]); // translacja do punktu 0,0

	rover.drawRover(engineRot, 0, 0, 1);
	glPopMatrix();
	
	//GLfloat color[3] = { 1.0, 0.0, 0.0 };
	//GLfloat aa[3] = { posX + 85, posY - 10, 0.0 };
	//GLfloat bb[3] = { posX + 85, posY + 80, 0.0 };
	//GLfloat cc[3] = { posX -  5, posY + 80, 0.0 };
	//GLfloat dd[3] = { posX -  5, posY - 10, 0.0 };

	//Cuboid rock1(color, aa, bb, cc, dd, 40, 0);
	//rock1.drawCuboid(0, 0, 0, 0);
	
	//GLfloat aaa[3] = { 50, 355, 0.0 };
	//GLfloat bab[3] = { 50, 265, 0.0 };
	//GLfloat cac[3] = { 145, 265, 0.0 };
	//GLfloat dad[3] = { 145, 355, 0.0 };

	//Cuboid rock2(color, aaa, bab, cac, dad, 40, 0);
	//rock2.drawCuboid(0, 0, 0, 0);

	//obsRange.drawCylinder(90, 0, 1, 0);

	rovmid[0] = posX + 35;
	rovmid[1] = posY + 35;

	collision[0] = !(distanceCalculate(rovmid[0], rovmid[1], obs1mid[0], obs1mid[1]) > rovradius + obs1radius);
	collision[1] = !(distanceCalculate(rovmid[0], rovmid[1], obs2mid[0], obs2mid[1]) > rovradius + obs2radius);

	rotAngleDeg = fmod(rotAngle * 180 / GL_PI, 360);

	grid.drawGrid();
	terrain.drawTerrain();

	ob1.drawObstacle();
	ob2.drawObstacle();
	

	///////////////////////////////////////////////////////////////////////////////////
	TwInit(TW_OPENGL, NULL);
	TwBar *bar;
	bar = TwNewBar("Parametry");

	TwWindowSize(800, 800);
	TwAddButton(bar, "Martian rover", NULL, NULL, "");
	TwAddVarRO(bar, "Velocity", TW_TYPE_FLOAT, &velocity, "precision=1");
	TwAddVarRO(bar, "Velocity L", TW_TYPE_FLOAT, &velocityL, "precision=1");
	TwAddVarRO(bar, "Velocity R", TW_TYPE_FLOAT, &velocityR, "precision=1");
	TwAddSeparator(bar, "Battery life", "battery");
	TwAddVarRO(bar, "Battery life %", TW_TYPE_FLOAT, &batteryLife, "precision=0");
	TwAddSeparator(bar, "Position", "pos");
	TwAddVarRO(bar, "X", TW_TYPE_FLOAT, &posX, "precision=0");
	TwAddVarRO(bar, "Y", TW_TYPE_FLOAT, &posY, "precision=0");
	TwAddSeparator(bar, NULL, "");
	TwAddVarRW(bar, "obstacle 1", TW_TYPE_BOOLCPP, &collision[0], "");
	TwAddVarRW(bar, "obstacle 2", TW_TYPE_BOOLCPP, &collision[1], "");
	TwAddSeparator(bar, NULL, "");
	TwAddVarRW(bar, "rot", TW_TYPE_FLOAT, &rotAngleDeg, "precision=0");
	TwAddVarRW(bar, "Erot", TW_TYPE_FLOAT, &engineRot, "precision=0");
	
	TwDraw();

	batteryLife -= 0.05;
	if (batteryLife < 0.0)
	{
		batteryLife = 0.0;
		velocity = 0.0;
		velocityL = 0.0;
		velocityR = 0.0;
	}
	rotAngleDeg = abs(fmod(rotAngle * 180 / GL_PI, 360));

	if (collision[0] || collision[1] )
	{
		velocityL = -0.5*velocityL;
		velocityR = -0.5*velocityR;
		velocity = -0.5*velocity;
	}

	///////////////////////////////////////////////////////////////////////////////////////

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
	BYTE RedRange,GreenRange,BlueRange;
								// Range for each color entry (7,7,and 3)


	// Get the pixel format index and retrieve the pixel format description
	nPixelFormat = GetPixelFormat(hDC);
	DescribePixelFormat(hDC, nPixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

	// Does this pixel format require a palette?  If not, do not create a
	// palette and just return NULL
	if(!(pfd.dwFlags & PFD_NEED_PALETTE))
		return NULL;

	// Number of entries in palette.  8 bits yeilds 256 entries
	nColors = 1 << pfd.cColorBits;	

	// Allocate space for a logical palette structure plus all the palette entries
	pPal = (LOGPALETTE*)malloc(sizeof(LOGPALETTE) +nColors*sizeof(PALETTEENTRY));

	// Fill in palette header 
	pPal->palVersion = 0x300;		// Windows 3.0
	pPal->palNumEntries = nColors; // table size

	// Build mask of all 1's.  This creates a number represented by having
	// the low order x bits set, where x = pfd.cRedBits, pfd.cGreenBits, and
	// pfd.cBlueBits.  
	RedRange = (1 << pfd.cRedBits) -1;
	GreenRange = (1 << pfd.cGreenBits) - 1;
	BlueRange = (1 << pfd.cBlueBits) -1;

	// Loop through all the palette entries
	for(i = 0; i < nColors; i++)
		{
		// Fill in the 8-bit equivalents for each component
		pPal->palPalEntry[i].peRed = (i >> pfd.cRedShift) & RedRange;
		pPal->palPalEntry[i].peRed = (unsigned char)(
			(double) pPal->palPalEntry[i].peRed * 255.0 / RedRange);

		pPal->palPalEntry[i].peGreen = (i >> pfd.cGreenShift) & GreenRange;
		pPal->palPalEntry[i].peGreen = (unsigned char)(
			(double)pPal->palPalEntry[i].peGreen * 255.0 / GreenRange);

		pPal->palPalEntry[i].peBlue = (i >> pfd.cBlueShift) & BlueRange;
		pPal->palPalEntry[i].peBlue = (unsigned char)(
			(double)pPal->palPalEntry[i].peBlue * 255.0 / BlueRange);

		pPal->palPalEntry[i].peFlags = (unsigned char) NULL;
		}
		

	// Create the palette
	hRetPal = CreatePalette(pPal);

	// Go ahead and select and realize the palette for this device context
	SelectPalette(hDC,hRetPal,FALSE);
	RealizePalette(hDC);

	// Free the memory used for the logical palette structure
	free(pPal);

	// Return the handle to the new palette
	return hRetPal;
	}

// Entry point of all Windows programs
int APIENTRY WinMain(   HINSTANCE       hInst,
						HINSTANCE       hPrevInstance,
						LPSTR           lpCmdLine,
						int                     nCmdShow)
	{
	MSG                     msg;            // Windows message structure
	WNDCLASS        wc;                     // Windows class structure
	HWND            hWnd;           // Storeage for window handle

	hInstance = hInst;

	// Register Window style
	wc.style                        = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc          = (WNDPROC) WndProc;
	wc.cbClsExtra           = 0;
	wc.cbWndExtra           = 0;
	wc.hInstance            = hInstance;
	wc.hIcon                        = NULL;
	wc.hCursor                      = LoadCursor(NULL, IDC_ARROW);
	
	// No need for background brush for OpenGL window
	wc.hbrBackground        = NULL;         
	
	wc.lpszMenuName         = MAKEINTRESOURCE(IDR_MENU);
	wc.lpszClassName        = lpszAppName;

	// Register the window class
	if(RegisterClass(&wc) == 0)
		return FALSE;


	// Create the main application window
	hWnd = CreateWindow(
				lpszAppName,
				lpszAppName,
				
				// OpenGL requires WS_CLIPCHILDREN and WS_CLIPSIBLINGS
				WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
	
				// Window position and size
				-1050, 50,
				800, 800,
				NULL,
				NULL,
				hInstance,
				NULL);

	// If window was not created, quit
	if(hWnd == NULL)
		return FALSE;


	// Display the window
	ShowWindow(hWnd,SW_SHOW);
	UpdateWindow(hWnd);

	// Process application messages until the application closes
	while( GetMessage(&msg, NULL, 0, 0))
		{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		}

	return int(msg.wParam);
	}




// Window procedure, handles all messages for this program
LRESULT CALLBACK WndProc(       HWND    hWnd,
							UINT    message,
							WPARAM  wParam,
							LPARAM  lParam)
	{
	static HGLRC hRC;               // Permenant Rendering context
	static HDC hDC;                 // Private GDI Device context

	switch (message)
		{
		// Window creation, setup for OpenGL
		case WM_CREATE:
			// Store the device context
			hDC = GetDC(hWnd);              

			// Select the pixel format
			SetDCPixelFormat(hDC);          

			// Create palette if needed
			hPalette = GetOpenGLPalette(hDC);

			// Create the rendering context and make it current
			hRC = wglCreateContext(hDC);
			wglMakeCurrent(hDC, hRC);
			SetupRC();
			glGenTextures(2, &texture[0]);                  // tworzy obiekt tekstury			
			
			// ³aduje pierwszy obraz tekstury:
			bitmapData = LoadBitmapFile("Bitmapy\\checker.bmp", &bitmapInfoHeader);
			
			glBindTexture(GL_TEXTURE_2D, texture[0]);       // aktywuje obiekt tekstury

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );

			// tworzy obraz tekstury
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth,
						 bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);
			
			if(bitmapData)
			free(bitmapData);

			// ³aduje drugi obraz tekstury:
			bitmapData = LoadBitmapFile("Bitmapy\\crate.bmp", &bitmapInfoHeader);
			glBindTexture(GL_TEXTURE_2D, texture[1]);       // aktywuje obiekt tekstury

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );

			// tworzy obraz tekstury
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth,
						 bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);
			
			if(bitmapData)
			free(bitmapData);
			///////////////////////////////////////////////////////////////////

			dust = LoadTexture("Textures/dust.png", 1);
			banana = LoadTexture("Textures/banana.png", 1);
			rock = LoadTexture("Textures/rock.png", 1);
			smok = LoadTexture("Textures/smok.png", 1);
			terrain.setTexture(dust);
			rover.setTextures(banana, smok);
			ob1.setTexture(rock);
			ob2.setTexture(rock);

			// ustalenie sposobu mieszania tekstury z t³em
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE);
			break;

		// Window is being destroyed, cleanup
		case WM_DESTROY:
			// Deselect the current rendering context and delete it
			wglMakeCurrent(hDC,NULL);
			wglDeleteContext(hRC);

			// Delete the palette if it was created
			if(hPalette != NULL)
				DeleteObject(hPalette);

			// Tell the application to terminate after the window
			// is gone.
			PostQuitMessage(0);
			break;

		// Window is resized.
		case WM_SIZE:
			// Call our function which modifies the clipping
			// volume and viewport
			ChangeSize(LOWORD(lParam), HIWORD(lParam));
			break;


		// The painting function.  This message sent by Windows 
		// whenever the screen needs updating.
		case WM_PAINT:
			{
			// Call OpenGL drawing code
			RenderScene();

			SwapBuffers(hDC);
			// Validate the newly painted client area
			InvalidateRect(hWnd, NULL, FALSE);
			}
			break;

		// Windows is telling the application that it may modify
		// the system palette.  This message in essance asks the 
		// application for a new palette.
		case WM_QUERYNEWPALETTE:
			// If the palette was created.
			if(hPalette)
				{
				int nRet;

				// Selects the palette into the current device context
				SelectPalette(hDC, hPalette, FALSE);

				// Map entries from the currently selected palette to
				// the system palette.  The return value is the number 
				// of palette entries modified.
				nRet = RealizePalette(hDC);

				// Repaint, forces remap of palette in current window
				InvalidateRect(hWnd,NULL,FALSE);

				return nRet;
				}
			break;

	
		// This window may set the palette, even though it is not the 
		// currently active window.
		case WM_PALETTECHANGED:
			// Don't do anything if the palette does not exist, or if
			// this is the window that changed the palette.
			if((hPalette != NULL) && ((HWND)wParam != hWnd))
				{
				// Select the palette into the device context
				SelectPalette(hDC,hPalette,FALSE);

				// Map entries to system palette
				RealizePalette(hDC);
				
				// Remap the current colors to the newly realized palette
				UpdateColors(hDC);
				return 0;
				}
			break;

		// Key press, check for arrow keys to do cube rotation.
		case WM_KEYDOWN:
			{
			if(wParam == VK_NUMPAD8)
				xRot-= 5.0f;

			if(wParam == VK_NUMPAD2)
				xRot += 5.0f;

			if(wParam == VK_NUMPAD4)
				yRot -= 5.0f;

			if(wParam == VK_NUMPAD6)
				yRot += 5.0f;

			if (wParam == VK_NUMPAD9)
				zRot -= 5.0f;

			if (wParam == VK_NUMPAD7)
				zRot += 5.0f;

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
				if (velocity < 5)
				{
					velocityL += const_velocity;
					velocityR += const_velocity;
					velocityUpdate = 1;
				}
			}

			if (wParam == 'S')
			{
				if (velocity > -5)
				{
					velocityL -= const_velocity;
					velocityR -= const_velocity;
					velocityUpdate = 1;
				}
			}

			if (wParam == 'A')
			{
				if (velocity < 5)
				{
					velocityL += const_velocity;
					velocityUpdate = 1;
				}

				if (engineRot >= -30.0f)
				{
					engineRot -= ErotSpeed;
				}
			}

			if (wParam == 'D')
			{
				if (velocity < 5)
				{
					velocityR += const_velocity;
					velocityUpdate = 1;
				}
				
				if (engineRot <= 30.0f)
				{
					engineRot += ErotSpeed;
				}
			}

			if (wParam == VK_CONTROL) // w gore
			{
				posZ -= const_velocity;
				velocityUpdate = 1;
			}
			if (wParam == VK_SHIFT) // w dol
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



			/*if (wParam == VK_DOWN || wParam == VK_LEFT || wParam == VK_RIGHT || wParam == VK_UP) {
				glLoadIdentity();
				xRot = 0;
				yRot = 0;
				zRot = 0;

				if (wParam == VK_DOWN)
					gluLookAt(cameraX, cameraY + 20, cameraZ + 20, cameraX, cameraY, cameraZ, 0, 0, 1);


				if (wParam == VK_UP)
					gluLookAt(cameraX, cameraY - 60, cameraZ + 40, cameraX, cameraY, cameraZ, 0, 0, 1);

				if (wParam == VK_LEFT)
					gluLookAt(cameraX + 40, cameraY, cameraZ + 20, cameraX, cameraY, cameraZ, 0, 0, 1);

				if (wParam == VK_RIGHT)
					gluLookAt(cameraX - 40, cameraY, cameraZ + 20, cameraX, cameraY, cameraZ, 0, 0, 1);
			}*/
			break;

		// A menu command
		case WM_COMMAND:
			{
			switch(LOWORD(wParam))
				{
				// Exit the program
				case ID_FILE_EXIT:
					DestroyWindow(hWnd);
					break;

				// Display the about box
				case ID_HELP_ABOUT:
					DialogBox (hInstance,
						MAKEINTRESOURCE(IDD_DIALOG_ABOUT),
						hWnd,
						DLGPROC(AboutDlgProc));
					break;
				}
			}
			break;


	default:   // Passes it on if unproccessed
	    return (DefWindowProc(hWnd, message, wParam, lParam));

	}

    return (0L);
	}




// Dialog procedure.
BOOL APIENTRY AboutDlgProc (HWND hDlg, UINT message, UINT wParam, LONG lParam)
	{
	
    switch (message)
	{
		// Initialize the dialog box
	    case WM_INITDIALOG:
			{
			int i;
			GLenum glError;

			// glGetString demo
			SetDlgItemText(hDlg,IDC_OPENGL_VENDOR,LPCSTR(glGetString(GL_VENDOR)));
			SetDlgItemText(hDlg,IDC_OPENGL_RENDERER, LPCSTR(glGetString(GL_RENDERER)));
			SetDlgItemText(hDlg,IDC_OPENGL_VERSION, LPCSTR(glGetString(GL_VERSION)));
			SetDlgItemText(hDlg,IDC_OPENGL_EXTENSIONS, LPCSTR(glGetString(GL_EXTENSIONS)));

			// gluGetString demo
			SetDlgItemText(hDlg,IDC_GLU_VERSION, LPCSTR(gluGetString(GLU_VERSION)));
			SetDlgItemText(hDlg,IDC_GLU_EXTENSIONS, LPCSTR(gluGetString(GLU_EXTENSIONS)));


			// Display any recent error messages
			i = 0;
			do {
				glError = glGetError();
				SetDlgItemText(hDlg,IDC_ERROR1+i, LPCSTR(gluErrorString(glError)));
				i++;
				}
			while(i < 6 && glError != GL_NO_ERROR);


			return (TRUE);
			}
			break;

		// Process command messages
	    case WM_COMMAND:      
			{
			// Validate and Make the changes
			if(LOWORD(wParam) == IDOK)
				EndDialog(hDlg,TRUE);
		    }
			break;

		// Closed from sysbox
		case WM_CLOSE:
			EndDialog(hDlg,TRUE);
			break;
		}

	return FALSE;
	}
