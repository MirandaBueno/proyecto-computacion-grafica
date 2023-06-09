#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>
#include <chrono>
#include <iostream>

#include <glew.h>
#include <glfw3.h>
#include <SDL\SDL.h>
#include <SDL\SDL_mixer.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include "Model.h"
#include "Skybox.h"

#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"

const float toRadians = 3.14159265f / 180.0f;

//Variables animaciones
float incrementoManoHuesoY = 0;
float offsetIncrementoManoHuesoY = 0.1;
int banderaincrementoManoHuesoY = 0;

float incSodaZ = 0;
float incSodaY = 0;
float incSodaRota = 0;
float offsetIncSoda = 0.1;
int bandIncSoda = 0;

float incFantasmaZ = 0;
float incFantasmaY = 0;
float incFantasmaRota = 0;
float offsetFantasma = 0.2;
int bandFantasma = 0;

float incFantasmaCompX = 0;
float tiempoFantasmaComp = 0;
float incFantasmaCompY = 0;
float incFantasmaCompZ = 0;
float incFantasmaCompRota = 0;
float offsetFantasmaComp = 0.1;
int bandFantasmaComp = 0;

float hozrota = 0;
bool hozbandera = false;

float girotiara = 0;
float tiarax = 0.0f;
float tiaray = 0.0f;
float tiaraz = 0.0f;
bool tiarab = false;

//Variables de configuraci�n
float toffsetu = 0.0f;
float toffsetv = 0.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

using std::vector;
const float PI = 3.14159265f;

float reproduciranimacion, habilitaranimacion,
guardoFrame, reinicioFrame, ciclo, ciclo2, contador = 0;

Camera camera;

Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;
Texture sailorTexture;
Texture sailorColetasTexture;
Texture traje;
Texture piel;
Texture piernatextura;
Texture rojo; 
Texture fachada;
Texture letrero;
Texture pisoGame;
Texture fachadaLado;

Model LapidaPH1;
Model LapidaPH2;
Model LapidaPH3;
Model vela;
Model arbolA;
Model calabaza;
Model reja;
Model camino;
Model tumba;
Model manoEsqueleto;
Model arcade;
Model arcadeDos;
Model expendedora;
Model banco;
Model soda;
Model dulces;
Model luminaria;
Model lamparaPared;
Model fantasma;

Model coleta;
Model chongo;
Model brazo;
Model torzo;
Model pierna;
Model tiara;
Model pelota;

Model cabezapurohueso;
Model tunicapurohueso;
Model manoph;
Model hoz;

Model jolcabeza;
Model jolsombrero;
Model jolropa;
Model jolpantalones;

Skybox skyboxDia;
Skybox skyboxAtardece;
Skybox skyboxNoche;

//materiales
Material Material_brillante;
Material Material_opaco;

//luz direccional
DirectionalLight mainLight;
//para declarar varias luces de tipo pointlight
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

Sphere coletas = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";

//PARA INPUT CON KEYFRAMES 
void inputKeyframes(bool* keys);

void CreaPiso()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		4, 5, 6,
		6, 7, 4,
		// back
		8, 9, 10,
		10, 11, 8,

		// left
		12, 13, 14,
		14, 15, 12,
		// bottom
		16, 17, 18,
		18, 19, 16,
		// top
		20, 21, 22,
		22, 23, 20,
	};

	GLfloat cubo_vertices[] = {
		// front
		//x		y		z		S		T			NX		NY		NZ
		-0.5f, -0.5f,  0.5f,	0.34f,  0.51f,		0.0f,	0.0f,	-1.0f,	//0
		0.5f, -0.5f,  0.5f,		0.65f,	0.51f,		0.0f,	0.0f,	-1.0f,	//1
		0.5f,  0.5f,  0.5f,		0.65f,	0.74f,		0.0f,	0.0f,	-1.0f,	//2
		-0.5f,  0.5f,  0.5f,	0.34f,	0.74f,		0.0f,	0.0f,	-1.0f,	//3
		// right
		//x		y		z		S		T
		0.5f, -0.5f,  0.5f,	   0.67f,	0.51f,		-1.0f,	0.0f,	0.0f,
		0.5f, -0.5f,  -0.5f,	0.99f,	0.51f,		-1.0f,	0.0f,	0.0f,
		0.5f,  0.5f,  -0.5f,	0.99f,	0.74f,		-1.0f,	0.0f,	0.0f,
		0.5f,  0.5f,  0.5f,	   0.67f,	0.74f,		-1.0f,	0.0f,	0.0f,
		// back
		-0.5f, -0.5f, -0.5f,	0.65f,	0.01f,		0.0f,	0.0f,	1.0f,
		0.5f, -0.5f, -0.5f,		0.34f,	0.01f,		0.0f,	0.0f,	1.0f,
		0.5f,  0.5f, -0.5f,	    0.34f,	0.24f,		0.0f,	0.0f,	1.0f,
		-0.5f,  0.5f, -0.5f,	0.65f,  0.24f,		0.0f,	0.0f,	1.0f,

		// left
		//x		y		z		S		T
		-0.5f, -0.5f,  -0.5f,	0.01f,  0.51f,		1.0f,	0.0f,	0.0f,
		-0.5f, -0.5f,  0.5f,	0.32f,	0.51f,		1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  0.5f,	0.32f,	0.74f,		1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  -0.5f,	0.01f,	0.74f,		1.0f,	0.0f,	0.0f,

		// bottom
		//x		y		z		S		T
		-0.5f, -0.5f,  0.5f,	0.34f,	0.49f,		0.0f,	1.0f,	0.0f,
		0.5f,  -0.5f,  0.5f,	0.65f,	0.49f,		0.0f,	1.0f,	0.0f,
		 0.5f,  -0.5f,  -0.5f,	0.65f,	0.26f,		0.0f,	1.0f,	0.0f,
		-0.5f, -0.5f,  -0.5f,	0.34f,  0.26f,		0.0f,	1.0f,	0.0f,

		//UP
		 //x		y		z		S		T
		 -0.5f, 0.5f,  0.5f,	0.34f,  0.76f,		0.0f,	-1.0f,	0.0f,
		 0.5f,  0.5f,  0.5f,	0.65f,	0.76f,		0.0f,	-1.0f,	0.0f,
		  0.5f, 0.5f,  -0.5f,	0.65f,	0.99f,		0.0f,	-1.0f,	0.0f,
		 -0.5f, 0.5f,  -0.5f,	0.34f,	0.99f,		0.0f,	-1.0f,	0.0f,

	};

	Mesh* piso = new Mesh();
	piso->CreateMesh(cubo_vertices, cubo_indices, 192, 36);
	meshList.push_back(piso);

}

void CreaParedesGamecenter() {
	unsigned int pared_indices[] = {
		0,1,2,
		0,3,2,
	};

	GLfloat pared_vertices[] = {
		// front
		//x		y		z		S		T			NX		NY		NZ
		-1.0f, 0.0f, 0.0f,		0.0f,  0.0f,		0.0f,	0.0f,	-1.0f,	//0
		 0.0f, 0.0f, 0.0f,		1.0f,	0.0f,		0.0f,	0.0f,	-1.0f,	//1
		 0.0f, 1.0f, 0.0f,		1.0f,	1.0f,		0.0f,	0.0f,	-1.0f,	//2
		-1.0f, 1.0f, 0.0f,		0.0f,	1.0f,		0.0f,	0.0f,	-1.0f,	//3
		
	};

	Mesh* dado = new Mesh();
	dado->CreateMesh(pared_vertices, pared_indices, 32,6);
	meshList.push_back(dado);
}

void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

void CrearSailorMoonCabeza()
{
	unsigned int sailor_indices[] = {
		// front
		0, 1, 10,
		0, 10, 11,
		1, 2, 9,
		1, 9, 10,
		2, 3, 8,
		2, 8, 9,
		3, 4, 7,
		3, 7, 8,
		4, 5, 6,
		4, 6, 7,

		//derecho
		12, 13, 14,
		12, 14, 15,
		13, 16, 17,
		13, 17, 14,
		16, 18, 19,
		16, 19, 17,
		18, 20, 21,
		18, 21, 19,
		20, 22, 23,
		20, 23, 21,

		// izq
		24, 25, 26,
		24, 26, 27,
		25, 28, 29,
		25, 29, 26,
		28, 30, 31,
		28, 31, 29,
		30, 32, 33,
		30, 33, 31,
		32, 34, 35,
		32, 35, 33,

		//abajo
		36, 37, 38,
		36, 38, 39,

		40, 41, 46,
		40, 45, 46,
		//41, 42, 47,
		42, 47, 50,


		//41, 46, 47,
		51, 50, 47,


		42, 43, 48,
		48, 42, 47,

		43, 44, 49,
		43, 49, 48
	};

	GLfloat sailor_vertices[] = {

		//cabeza

		// rostro
		//x		y		z			S				T					NX		NY		NZ
		-0.35f, 0.25f,  0.3f,		(0.009f * 27),  (0.009f * 90),		0.28f, 0.02f, -0.01f,	//0
		-0.35f, -0.1f,  0.3f,		(0.009f * 27),	(0.009f * 64),		0.28f, 0.02f, -0.01f,	//1
		-0.33f,  -0.15f,  0.28f,	(0.009f * 28),	(0.009f * 60),		0.28f, 0.02f, -0.01f,	//2
		-0.30f,  -0.2f,  0.25f,		(0.009f * 30),	(0.009f * 56),		0.28f, 0.02f, -0.01f,	//3
		-0.25f,  -0.23f,  0.20f,	(0.009f * 34),	(0.009f * 54),		0.28f, 0.02f, -0.01f,	//4
		-0.20f,  -0.25f,  0.15f,	(0.009f * 38),	(0.009f * 53),		0.28f, 0.02f, -0.01f,	//5
		0.20f,  -0.25f,  0.15f,		(0.009f * 69),	(0.009f * 53),		0.28f, 0.02f, -0.01f,	//6
		0.25f,  -0.23f,  0.20f,		(0.009f * 73),	(0.009f * 54),		0.28f, 0.02f, -0.01f,	//7
		0.30f,  -0.2f,  0.25f,		(0.009f * 77),	(0.009f * 56),		0.28f, 0.02f, -0.01f,	//8
		0.33f,  -0.15f,  0.28f,		(0.009f * 79),	(0.009f * 60),		0.28f, 0.02f, -0.01f,	//9
		0.35f, -0.1f,  0.3f,		(0.009f * 80),	(0.009f * 64),		0.28f, 0.02f, -0.01f,	//10
		0.35f, 0.25f,  0.3f,		(0.009f * 80),  (0.009f * 90),		0.28f, 0.02f, -0.01f,	//11

		// derecho
		//x		y		z			S				T					NX		NY		 NZ
		0.35f, 0.25f,  0.3f,		(0.009f * 83),  (0.009f * 90),		0.21f,  0.0f, -0.1225f,	//12
		0.35f, -0.1f,  0.3f,		(0.009f * 83),	(0.009f * 64),		0.21f,  0.0f, -0.1225f,	//13
		0.35f, -0.1f,  -0.3f,		(0.009f * 83),	(0.009f * 64),		0.21f,  0.0f, -0.1225f,	//14
		0.35f, 0.25f,  -0.3f,		(0.009f * 83),  (0.009f * 90),		0.21f,  0.0f, -0.1225f,	//15

		0.33f, -0.15f,  0.28f,		(0.009f * 83),	(0.009f * 64),		0.028f, -0.015f, -0.015f,	//16
		0.33f, -0.15f,  -0.28f,		(0.009f * 83),	(0.009f * 64),		0.028f, -0.015f, -0.015f,	//17
		0.3f, -0.2f,  0.25f,		(0.009f * 83),	(0.009f * 64),		0.028f, -0.015f, -0.015f,	//18
		0.3f, -0.2f,  -0.25f,		(0.009f * 83),	(0.009f * 64),		0.028f, -0.015f, -0.015f,	//19

		0.25f, -0.23f,  0.2f,		(0.009f * 83),	(0.009f * 64),		-0.08f,	 0.0f,	0.01f,	//20
		0.25f, -0.23f,  -0.2f,		(0.009f * 83),	(0.009f * 64),		-0.08f,	 0.0f,	0.01f,	//21
		0.2f, -0.25f,  0.15f,		(0.009f * 83),	(0.009f * 64),		-0.08f,	 0.0f,	0.01f,	//22
		0.2f, -0.25f,  -0.15f,		(0.009f * 83),	(0.009f * 64),		-0.08f,	 0.0f,	0.01f,	//23

		// izquierdo
		//x		y		z			S				T					NX		NY		NZ
		-0.35f, 0.25f,  0.3f,		(0.009f * 83),  (0.009f * 90),		0.21f,  0.0f, -0.122f,	//24
		-0.35f, -0.1f,  0.3f,		(0.009f * 83),	(0.009f * 64),		0.21f,  0.0f, -0.122f,	//25
		-0.35f, -0.1f,  -0.3f,		(0.009f * 83),	(0.009f * 64),		0.21f,  0.0f, -0.122f,	//26
		-0.35f, 0.25f,  -0.3f,		(0.009f * 83),  (0.009f * 90),		0.21f,  0.0f, -0.122f,	//27

		-0.33f, -0.15f,  0.28f,		(0.009f * 83),	(0.009f * 64),		-0.028f, 0.015f, 0.015f,	//28
		-0.33f, -0.15f,  -0.28f,	(0.009f * 83),	(0.009f * 64),		-0.028f, 0.015f, 0.015f,	//29
		-0.3f, -0.2f,  0.25f,		(0.009f * 83),	(0.009f * 64),		-0.028f, 0.015f, 0.015f,	//30
		-0.3f, -0.2f,  -0.25f,		(0.009f * 83),	(0.009f * 64),		-0.028f, 0.015f, 0.015f,	//31

		-0.25f, -0.23f,  0.2f,		(0.009f * 83),	(0.009f * 64),		-0.08f, 0.0f,  0.01f,	//32
		-0.25f, -0.23f,  -0.2f,		(0.009f * 83),	(0.009f * 64),		-0.08f, 0.0f,  0.01f,	//33
		-0.2f, -0.25f,  0.15f,		(0.009f * 83),	(0.009f * 64),		-0.08f, 0.0f,  0.01f,	//34
		-0.2f, -0.25f,  -0.15f,		(0.009f * 83),	(0.009f * 64),		-0.08f, 0.0f,  0.01f,	//35

		// abajo
		//x		y		z			S				T					NX		NY		NZ
		0.2f,  -0.25f,  0.15f,		(0.009f * 72),	(0.009f * 53),		0.0f, 0.12f,   0.0f,	//36 
		0.2f, -0.25f,  -0.15f,		(0.009f * 83),	(0.009f * 64),		0.0f, 0.12f,   0.0f,	//37
		-0.2f,  -0.25f,  -0.15f,	(0.009f * 72),	(0.009f * 53),		0.0f, 0.12f,   0.0f,	//38
		-0.2f,  -0.25f,  0.15f,		(0.009f * 72),	(0.009f * 53),		0.0f, 0.12f,   0.0f,	//39

		0.35f, -0.1f,  -0.3f,		(0.009f * 83),	(0.009f * 64),		0.01f, 0.02f, -0.03f,	//40 a
		//(-0.33, -0.15,  -0.28)
		0.33f, -0.15f,  -0.28f,		(0.009f * 83),	(0.009f * 64),		0.01f, 0.02f, -0.03f,	//41 b
		0.3f, -0.2f,  -0.25f,		(0.009f * 83),	(0.009f * 64),		0.0f, -0.18f, -0.315f,	//42 c
		0.25f, -0.23f,  -0.2f,		(0.009f * 83),	(0.009f * 64),		0.01f, -0.0025f, -0.01f,	//43 d
		0.2f, -0.25f,  -0.15f,		(0.009f * 83),	(0.009f * 64),		0.01f, -0.0025f, -0.01f,	//44 e
		-0.35f, -0.1f,  -0.3f,		(0.009f * 83),	(0.009f * 64),		0.01f, 0.02f, -0.03f,	//45 f
		-0.33f, -0.15f,  -0.28f,	(0.009f * 83),	(0.009f * 64),		0.01f, 0.02f, -0.03f,	//46 g
		-0.3f, -0.2f,  -0.25f,		(0.009f * 83),	(0.009f * 64),		0.0f, -0.18f, -0.315f,	//47
		-0.25f, -0.23f,  -0.2f,		(0.009f * 83),	(0.009f * 64),		0.01f, -0.0025f, -0.01f,	//48
		-0.2f, -0.25f,  -0.15f,		(0.009f * 83),	(0.009f * 64),		0.01f, -0.0025f, -0.01f,	//49

		0.33f,  -0.15f,  -0.28f,		(0.009f * 83),	(0.009f * 64),	0.0f, -0.18f, -0.315f,	//41 b 50
		-0.33f, -0.15f,  -0.28f,	(0.009f * 83),	(0.009f * 64),		0.0f, -0.18f, -0.315f,		//46 g 51

	};

	Mesh* sailor = new Mesh();
	sailor->CreateMesh(sailor_vertices, sailor_indices, 416, 120);
	meshList.push_back(sailor);

}

void CrearSailorMoonPelo()
{
	unsigned int indices[] = {
		// fleco 18
		0, 1, 2,
		1, 2, 3,
		2, 3, 4,
		3, 4, 5,
		4, 5, 6,
		5,6,7,
		5,7,8,
		3,5,8,
		8, 9,10,
		3,8,10,
		1,3,15,
		3, 10,11,
		11,12,13,
		3,11,14,
		11,13,14,
		3, 14, 15,
		14, 15, 16,
		14, 16, 17,
		// 36
		0 + 18,	1 + 18, 2 + 18,
		1 + 18, 2 + 18, 3 + 18,
		2 + 18, 3 + 18, 4 + 18,
		3 + 18, 4 + 18, 5 + 18,
		4 + 18, 5 + 18, 6 + 18,
		5 + 18,	6 + 18,	7 + 18,
		5 + 18,	7 + 18,	8 + 18,
		3 + 18,	5 + 18,	8 + 18,
		8 + 18, 9 + 18,	10 + 18,
		3 + 18,	8 + 18,	10 + 18,
		1 + 18,	3 + 18,	15 + 18,
		3 + 18, 10 + 18,11 + 18,
		11 + 18,12 + 18,13 + 18,
		3 + 18,	11 + 18,14 + 18,
		11 + 18,13 + 18,14 + 18,
		3 + 18, 14 + 18, 15 + 18,
		14 + 18, 15 + 18, 16 + 18,
		14 + 18, 16 + 18, 17 + 18,
		//41
		14, 17, 36,
		16, 17, 36,
		15, 16, 37,
		16, 36, 37,
		36, 37, 38,
		//46
		32, 35, 39,
		34, 35, 39,
		33, 34, 40,
		34, 39, 40,
		39, 40, 41,
		//54
		15, 42,33,
		42, 33, 43,
		15, 42, 37,
		42, 37, 44,
		33, 43, 40,
		43, 40, 45,
		42, 43, 44,
		45, 44, 43,
		//58
		38, 37, 41,
		37, 41, 40,
		37, 40, 44,
		40, 44, 45

	};

	GLfloat vertices[] = {

		// fleco
		//x		y		z			S				T					NX		NY		NZ
		0.0f, 0.25f,  0.3f,		(0.009f * 27),  (0.009f * 90),		0.05f, -0.04f, -0.04f,	//0
		0.0f, 0.29f,  0.35f,	(0.009f * 27),	(0.009f * 64),		0.05f, -0.04f, -0.04f,	//1
		0.08f, 0.2f,  0.3f,		(0.009f * 27),	(0.009f * 64),		0.05f, -0.04f, -0.04f,	//2
		0.09f, 0.2f,  0.35f,	(0.009f * 27),	(0.009f * 64),		0.05f, -0.04f, -0.04f,	//3
		0.09f, 0.17f,  0.3f,	(0.009f * 27),	(0.009f * 64),		-0.015f, -0.0005f, -0.0003f,	//4
		0.1f, 0.17f,  0.35f,	(0.009f * 27),	(0.009f * 64),		-0.015f, -0.0005f, -0.0003f,	//5
		0.07f, 0.1f,  0.3f,		(0.009f * 27),	(0.009f * 64),		-0.015f, -0.0005f, -0.0003f,	//6
		0.13f, 0.1f,  0.3f,		(0.009f * 27),	(0.009f * 64),		0.004f, 0.001f, -0.001f,	//7
		0.18f, 0.11f,  0.31f,	(0.009f * 27),	(0.009f * 64),		0.004f, 0.001f, -0.001f,	//8
		0.19f, 0.09f,  0.31f,	(0.009f * 27),	(0.009f * 64),		-0.0004f, 0.0016f, -0.0002f,	//9
		0.23f, 0.09f,  0.31f,	(0.009f * 27),	(0.009f * 64),		-0.0004f, 0.0016f, -0.0002f,	//10
		0.26f, 0.1f,  0.31f,	(0.009f * 27),	(0.009f * 64),		-0.0004f, 0.0016f, -0.0002f,	//11
		0.27f, 0.08f,  0.31f,	(0.009f * 27),	(0.009f * 64),		-0.0004f, 0.0016f, -0.0002f,	//12
		0.3f, 0.08f,  0.31f,	(0.009f * 27),	(0.009f * 64),		-0.0004f, 0.0016f, -0.0002f,	//13
		0.36f, 0.09f,  0.31f,	(0.009f * 27),	(0.009f * 64),		-0.0064f, -0.0008f, 0.004f,	//14
		0.36f, 0.29f,  0.34f,	(0.009f * 27),	(0.009f * 64),		-0.0064f, -0.0008f, 0.004f,	//15
		0.38f, 0.23f,  0.35f,	(0.009f * 27),	(0.009f * 64),		-0.0064f, -0.0008f, 0.004f,	//16
		0.38f, 0.15f,  0.35f,	(0.009f * 27),	(0.009f * 64),		-0.0064f, -0.0008f, 0.004f,	//17

		0.0f, 0.25f,  0.3f,		(0.009f * 27),  (0.009f * 90),		0.05f, -0.04f, -0.04f,	//0 18
		0.0f, 0.29f,  0.35f,	(0.009f * 27),	(0.009f * 64),		0.05f, -0.04f, -0.04f,	//1 19
		-0.08f, 0.2f,  0.3f,	(0.009f * 27),	(0.009f * 64),		0.05f, -0.04f, -0.04f,	//2 20
		-0.09f, 0.2f,  0.35f,	(0.009f * 27),	(0.009f * 64),		0.05f, -0.04f, -0.04f,	//3 21
		-0.09f, 0.17f,  0.3f,	(0.009f * 27),	(0.009f * 64),		-0.015f, -0.0005f, -0.0003f,	//4 22
		-0.1f, 0.17f,  0.35f,	(0.009f * 27),	(0.009f * 64),		-0.015f, -0.0005f, -0.0003f,	//5 23
		-0.07f, 0.1f,  0.3f,	(0.009f * 27),	(0.009f * 64),		-0.015f, -0.0005f, -0.0003f,	//6 24
		-0.13f, 0.1f,  0.3f,	(0.009f * 27),	(0.009f * 64),		0.004f, 0.001f, -0.001f,	//7 25
		-0.18f, 0.11f,  0.31f,	(0.009f * 27),	(0.009f * 64),		0.004f, 0.001f, -0.001f,	//8 26
		-0.19f, 0.09f,  0.31f,	(0.009f * 27),	(0.009f * 64),		-0.0004f, 0.0016f, -0.0002f,	//9 27
		-0.23f, 0.09f,  0.31f,	(0.009f * 27),	(0.009f * 64),		-0.0004f, 0.0016f, -0.0002f,	//10 28
		-0.26f, 0.1f,  0.31f,	(0.009f * 27),	(0.009f * 64),		-0.0004f, 0.0016f, -0.0002f,	//11 29
		-0.27f, 0.08f,  0.31f,	(0.009f * 27),	(0.009f * 64),		-0.0004f, 0.0016f, -0.0002f,	//12 30
		-0.3f, 0.08f,  0.31f,	(0.009f * 27),	(0.009f * 64),		-0.0004f, 0.0016f, -0.0002f,	//13 31
		-0.36f, 0.09f,  0.31f,	(0.009f * 27),	(0.009f * 64),		-0.0064f, -0.0008f, 0.004f,	//14 32
		-0.36f, 0.29f,  0.34f,	(0.009f * 27),	(0.009f * 64),		-0.0064f, -0.0008f, 0.004f,	//15 33
		-0.38f, 0.23f,  0.35f,	(0.009f * 27),	(0.009f * 64),		-0.0064f, -0.0008f, 0.004f,	//16 34
		-0.38f, 0.15f,  0.35f,	(0.009f * 27),	(0.009f * 64),		-0.0064f, -0.0008f, 0.004f,	//17 35

		//// izquierdo
		////x		y		z			S				T					NX		NY		NZ
		0.36f, 0.0f,  0.0f,		(0.009f * 27),	(0.009f * 64),		-0.0899f, 0.0f, 0.0f,	//36
		0.36f, 0.29f,  -0.31f,	(0.009f * 27),	(0.009f * 64),		-0.0899f, 0.0f, 0.0f,	//37
		0.36f, -0.17f,  -0.31f,	(0.009f * 27),	(0.009f * 64),		-0.0899f, 0.0f, 0.0f,	//38

		//// derecho
		////x		y		z			S				T					NX		NY		NZ
		-0.36f, 0.0f,  0.0f,		(0.009f * 27),	(0.009f * 64),		0.0899f, 0.0f, 0.0f,	//39
		-0.36f, 0.29f,  -0.31f,		(0.009f * 27),	(0.009f * 64),		0.0899f, 0.0f, 0.0f,	//40
		-0.36f, -0.17f,  -0.31f,	(0.009f * 27),	(0.009f * 64),		0.0899f, 0.0f, 0.0f,	//41

		//// arriba
		////x		y		z			S				T					NX		NY		NZ
		0.28f, 0.35f,  0.3f,	(0.009f * 27),	(0.009f * 64),		0.0f, -0.28f, -0.0256f,	//42
		-0.28f, 0.35f,  0.3f,	(0.009f * 27),	(0.009f * 64),		0.0f, -0.28f, -0.0256f,	//43
		0.33f, 0.35f,  -0.20f,	(0.009f * 27),	(0.009f * 64),		0.0f, -0.28f, -0.0256f,	//44
		-0.33f, 0.35f,  -0.20f,	(0.009f * 27),	(0.009f * 64),		0.0f, -0.28f, -0.0256f,	//45
	};

	Mesh* sailor = new Mesh();
	sailor->CreateMesh(vertices, indices, 368, 174);
	meshList.push_back(sailor);

}

void subenManosTumbas(){
	if (banderaincrementoManoHuesoY == 0) {
		if (incrementoManoHuesoY < 10.0f) {
			incrementoManoHuesoY += offsetIncrementoManoHuesoY * deltaTime;
		}
		else {
			banderaincrementoManoHuesoY = 1;
		}
	}
	if (banderaincrementoManoHuesoY == 1) {
		if (incrementoManoHuesoY > 0.0f) {
			incrementoManoHuesoY -= offsetIncrementoManoHuesoY * deltaTime;
		}
		else {
			banderaincrementoManoHuesoY = 0;
		}
	}
}

void hozRota() {
	if (hozbandera == false && hozrota < 60) {
		hozrota += 0.5 * deltaTime;
	}
	else if (hozbandera == false && hozrota > 60) {
		hozbandera = true;
	}
	else if (hozbandera == true && hozrota > 0) {
		hozrota -= 0.5 * deltaTime;
	}
	else if (hozbandera == true && hozrota < 0) {
		hozbandera = false;
	}
}

void caeSoda() {
	if (bandIncSoda == 0) {
		if (incSodaZ < 2.0f) {
			incSodaZ += offsetIncSoda * deltaTime;
			incSodaY -= offsetIncSoda * deltaTime;
			incSodaRota -= 2 * deltaTime;
		}
		else {
			bandIncSoda = 1;
		}
	}
	if (bandIncSoda == 1) {
		if (incSodaZ < 26.0f) {
			incSodaZ += offsetIncSoda * deltaTime;
			incSodaRota -= 2 * deltaTime;
		}
		else {
			bandIncSoda = 0;
			incSodaZ = 0;
			incSodaY = 0;
		}
	}
}

void mueveFantasma(){
	if (bandFantasma == 0) {
		if (incFantasmaY < 15.0f) {
			incFantasmaY += offsetFantasma * deltaTime;
		}
		else {
			bandFantasma = 1;
		}
	}
	if (bandFantasma == 1) {
		if (incFantasmaZ < 50.0f) {
			incFantasmaZ += offsetFantasma * deltaTime;
		}
		else {
			bandFantasma = 2;
		}
	}
	if (bandFantasma == 2) {
		if (incFantasmaY > 0.0f) {
			incFantasmaY -= offsetFantasma * deltaTime;
		}
		else {
			bandFantasma = 3;
		}
	}
	if (bandFantasma == 3) {
		if (incFantasmaRota < 180.0f) {
			incFantasmaRota += 2 * deltaTime;
		}
		else {
			bandFantasma = 4;
		}
	}
	if (bandFantasma == 4) {
		if (incFantasmaY < 15.0f) {
			incFantasmaY += offsetFantasma * deltaTime;
		}
		else {
			bandFantasma = 5;
		}
	}
	if (bandFantasma == 5) {
		if (incFantasmaZ > 0.0f) {
			incFantasmaZ -= offsetFantasma * deltaTime;
		}
		else {
			bandFantasma = 6;
		}
	}
	if (bandFantasma == 6) {
		if (incFantasmaY > 0.0f) {
			incFantasmaY -= offsetFantasma * deltaTime;
		}
		else {
			bandFantasma = 7;
		}
	}
	if (bandFantasma == 7) {
		if (incFantasmaRota > 180.0f) {
			incFantasmaRota -= 2 * deltaTime;
		}
		else {
			bandFantasma = 0;
			incFantasmaZ = 0;
			incFantasmaY = 0;
			incFantasmaRota = 0;
		}
	}
}

void complejaFantasma() {
	if (bandFantasmaComp == 0) {
		if (incFantasmaCompX < 74.0f) {
			incFantasmaCompX += offsetFantasmaComp * deltaTime;
		}
		else {
			bandFantasmaComp = 1;
		}
	}
	if (bandFantasmaComp == 1) {
		if (incFantasmaCompRota > -90.0f) {
			incFantasmaCompRota -= 2 * deltaTime;
		}
		else {
			bandFantasmaComp = 2;
		}
	}
	if (bandFantasmaComp == 2) {
		if (incFantasmaCompZ < 21.0f) {
			incFantasmaCompZ += offsetFantasmaComp * deltaTime;
		}
		else {
			bandFantasmaComp = 3;
		}
	}
	if (bandFantasmaComp == 3) {
		if (incFantasmaCompRota < 0.0f) {
			incFantasmaCompRota += 2 * deltaTime;
		}
		else {
			bandFantasmaComp = 4;
		}
	}
	if (bandFantasmaComp == 4) {
		if (incFantasmaCompX < 97.0f) {
			incFantasmaCompX += offsetFantasmaComp * deltaTime;
		}
		else {
			bandFantasmaComp = 5;
		}
	}
	if (bandFantasmaComp == 5) {
		if (incFantasmaCompY < 5.0f) {
			incFantasmaCompY += offsetFantasmaComp * deltaTime;
			incFantasmaCompRota += 2 * deltaTime;
		}
		else {
			bandFantasmaComp = 6;
		}
	}
	if (bandFantasmaComp == 6) {
		if (incFantasmaCompZ > 16.0f) {
			incFantasmaCompZ -= offsetFantasmaComp * deltaTime;
		}
		else {
			bandFantasmaComp = 7;
		}
	}
	if (bandFantasmaComp == 7) {
		if (tiempoFantasmaComp < 50.0f) {
			tiempoFantasmaComp += offsetFantasmaComp * deltaTime;
		}
		else {
			bandFantasmaComp = 0;
			incFantasmaCompRota = 0;
			incFantasmaCompX = 0;
			incFantasmaCompY = 0;
			incFantasmaCompZ = 0;
			tiempoFantasmaComp = 0;
		}
	}
}

void giraTiara() {
	/*tiarax = 0.05 * girotiara * cos(girotiara);
	tiaraz = 0.05 * girotiara * sin(girotiara);
	*/
	if (tiarab == false && girotiara < 360){
		girotiara += 0.05 * deltaTime;
		tiaray -= 0.001 * deltaTime;
	}
	else {
		tiarab = true;
	}
	if (tiarab == true && girotiara > 0) {
		girotiara -= 0.05 * deltaTime;
		tiaray += 0.001 * deltaTime;
	}
	else {
		tiarab = false;
	}

	tiarax = 16 * sqrt(2.0) * cos(girotiara) / (sin(girotiara) * sin(girotiara) + 1);
	tiaraz = 32 * sqrt(2.0) * cos(girotiara) * sin(girotiara) / (sin(girotiara) * sin(girotiara) + 1);

}

///////////////////////////////KEYFRAMES/////////////////////

bool animacion = false;

//NEW Keyframes
float pelotax = -70.0, pelotay = 0.0, pelotaz = 0.0;
float movpelota_x = 0.0f, movpelota_y = 0.0f, movpelota_z = 0.0f;
float giropelota = 0;

#define MAX_FRAMES 119
int i_max_steps = 90;
int i_curr_steps = 119;
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float movpelota_x;		//Variable para PosicionX
	float movpelota_y;		//Variable para PosicionY
	float movpelota_z;		//Variable para PosicionY
	float movpelota_xInc;		//Variable para IncrementoX
	float movpelota_yInc;		//Variable para IncrementoY
	float movpelota_zInc;		//Variable para IncrementoY
	float giropelota;
	float giropelotaInc;
}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 119;			//introducir datos
bool play = false;
int playIndex = 0;

void resetElements(void)
{
	movpelota_x = KeyFrame[0].movpelota_x;
	movpelota_y = KeyFrame[0].movpelota_y;
	movpelota_z = KeyFrame[0].movpelota_z;
	giropelota = KeyFrame[0].giropelota;
}

void interpolation(void)
{
	KeyFrame[playIndex].movpelota_xInc = (KeyFrame[playIndex + 1].movpelota_x - KeyFrame[playIndex].movpelota_x) / i_max_steps;
	KeyFrame[playIndex].movpelota_yInc = (KeyFrame[playIndex + 1].movpelota_y - KeyFrame[playIndex].movpelota_y) / i_max_steps;
	KeyFrame[playIndex].movpelota_zInc = (KeyFrame[playIndex + 1].movpelota_z - KeyFrame[playIndex].movpelota_z) / i_max_steps;
	KeyFrame[playIndex].giropelotaInc = (KeyFrame[playIndex + 1].giropelota - KeyFrame[playIndex].giropelota) / i_max_steps;

}

void animate(void)
{
	//Movimiento del objeto
	if (play)
	{
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
				interpolation();
			}
		}
		else
		{
			movpelota_x += KeyFrame[playIndex].movpelota_xInc;
			movpelota_y += KeyFrame[playIndex].movpelota_yInc;
			movpelota_z += KeyFrame[playIndex].movpelota_zInc;
			giropelota += KeyFrame[playIndex].giropelotaInc;
			i_curr_steps++;
		}

	}
}

/* FIN KEYFRAMES*/

int initE = SDL_Init(SDL_INIT_AUDIO);

int main(int argc, char * argv[])
{
	//Se declaran los objetos de audio y se comprueba que se abran correctamente.
	Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,1024);
	Mix_Music* musicDia = Mix_LoadMUS("sonidos/dia.wav");
	Mix_Music* musicNoche = Mix_LoadMUS("sonidos/noche.wav");
	Mix_Chunk* camina = Mix_LoadWAV("sonidos/pasoSailor.wav");
	Mix_VolumeChunk(camina, 50);
	if (!musicDia) {
		std::cout << "No se pudo abrir el archivo" << Mix_GetError();
	}
	if (!musicNoche) {
		std::cout << "No se pudo abrir el archivo" << Mix_GetError();
	}
	if (!camina) {
		std::cout << "No se pudo abrir el archivo" << Mix_GetError();
	}

	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreaPiso();
	CreateShaders();
	CrearSailorMoonCabeza();
	CrearSailorMoonPelo();
	CreaParedesGamecenter();

	coletas.init();
	coletas.load();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 5.0f, 0.5f);

	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTextureA();
	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureA();
	pisoTexture = Texture("Textures/FondoPiso.jpg");
	pisoTexture.LoadTextureA();
	sailorTexture = Texture("Textures/sailormoon_textura.png");
	sailorTexture.LoadTextureA();
	sailorColetasTexture = Texture("Textures/coletas.png");
	sailorColetasTexture.LoadTextureA();
	fachada = Texture("Textures/fachada.png");
	fachada.LoadTextureA();
	letrero = Texture("Textures/letrero.png");
	letrero.LoadTextureA();
	pisoGame = Texture("Textures/pisoGame.png");
	pisoGame.LoadTextureA();
	fachadaLado = Texture("Textures/fachadaLado.png");
	fachadaLado.LoadTextureA();

	vela = Model();
	vela.LoadModel("Models/vela.obj");
	LapidaPH1 = Model();
	LapidaPH1.LoadModel("Models/miLapidaA.obj");
	LapidaPH2 = Model();
	LapidaPH2.LoadModel("Models/miLapidaB.obj");
	LapidaPH3 = Model();
	LapidaPH3.LoadModel("Models/miLapidaC.obj");
	arbolA = Model();
	arbolA.LoadModel("Models/ArbolA.obj");
	calabaza = Model();
	calabaza.LoadModel("Models/calabaza.obj");
	reja = Model();
	reja.LoadModel("Models/rejaA.obj");
	camino = Model();
	camino.LoadModel("Models/caminoJuegos.obj");
	tumba = Model();
	tumba.LoadModel("Models/tumba.obj");
	manoEsqueleto = Model();
	manoEsqueleto.LoadModel("Models/esqueleto.obj");
	banco = Model();
	banco.LoadModel("Models/banquito.obj");
	arcade = Model();
	arcade.LoadModel("Models/arcade.obj");
	arcadeDos = Model();
	arcadeDos.LoadModel("Models/arcadeDos.obj");
	expendedora = Model();
	expendedora.LoadModel("Models/expendedora.obj");
	soda = Model();
	soda.LoadModel("Models/soda.obj");
	dulces = Model();
	dulces.LoadModel("Models/dulces.obj");
	luminaria = Model();
	luminaria.LoadModel("Models/luminaria.obj");
	lamparaPared = Model();
	lamparaPared.LoadModel("Models/lamparaPared.obj");
	fantasma = Model();
	fantasma.LoadModel("Models/fantasma.obj");

	coleta = Model();
	coleta.LoadModel("Models/coleta.obj");
	chongo = Model();
	chongo.LoadModel("Models/chongo.obj");
	brazo = Model();
	brazo.LoadModel("Models/mano.obj");
	torzo = Model();
	torzo.LoadModel("Models/cuerpo.obj");
	pierna = Model();
	pierna.LoadModel("Models/pierna.obj");
	tiara = Model();
	tiara.LoadModel("Models/tiara.obj");
	pelota = Model();
	pelota.LoadModel("Models/pelota.obj");

	cabezapurohueso = Model();
	cabezapurohueso.LoadModel("Models/cabezaph.obj");
	tunicapurohueso = Model();
	tunicapurohueso.LoadModel("Models/tunicaph.obj");
	manoph = Model();
	manoph.LoadModel("Models/manoph.obj");
	hoz = Model();
	hoz.LoadModel("Models/hoz.obj");

	jolcabeza = Model();
	jolcabeza.LoadModel("Models/jolcabeza.obj");
	jolsombrero = Model();
	jolsombrero.LoadModel("Models/jolsombrero.obj");
	jolropa = Model();
	jolropa.LoadModel("Models/jolropa.obj");
	jolpantalones = Model();
	jolpantalones.LoadModel("Models/jolpantalones.obj");

	std::vector<std::string> skyboxFacesDia;
	std::vector<std::string> skyboxFacesAtardece;
	std::vector<std::string> skyboxFacesNoche;

	skyboxFacesNoche.push_back("Textures/Skybox/nocheright.png");
	skyboxFacesNoche.push_back("Textures/Skybox/nocheleft.png");
	skyboxFacesNoche.push_back("Textures/Skybox/nochebottom.png");
	skyboxFacesNoche.push_back("Textures/Skybox/nochetop.png");
	skyboxFacesNoche.push_back("Textures/Skybox/nocheback.png");
	skyboxFacesNoche.push_back("Textures/Skybox/nochefront.png");

	skyboxFacesDia.push_back("Textures/Skybox/diaback.png");
	skyboxFacesDia.push_back("Textures/Skybox/dialeft.png");
	skyboxFacesDia.push_back("Textures/Skybox/diabottom.png");
	skyboxFacesDia.push_back("Textures/Skybox/diatop.png");
	skyboxFacesDia.push_back("Textures/Skybox/diafront.png");
	skyboxFacesDia.push_back("Textures/Skybox/diaright.png");

	skyboxFacesAtardece.push_back("Textures/Skybox/atardeceright.png");
	skyboxFacesAtardece.push_back("Textures/Skybox/atardeceleft.png");
	skyboxFacesAtardece.push_back("Textures/Skybox/atardecebottom.png");
	skyboxFacesAtardece.push_back("Textures/Skybox/atardecetop.png");
	skyboxFacesAtardece.push_back("Textures/Skybox/atardecefront.png");
	skyboxFacesAtardece.push_back("Textures/Skybox/atardeceback.png");

	skyboxDia = Skybox(skyboxFacesDia);
	skyboxNoche = Skybox(skyboxFacesNoche);
	skyboxAtardece = Skybox(skyboxFacesAtardece);

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);

	//luz direccional
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.5f, 0.5f,
		0.0f, 0.0f, -1.0f);

	//contador de luces puntuales
	unsigned int pointLightCount = 0;

	//Lampara pared
	pointLights[0] = PointLight(1.0f, 0.5f, 0.0f,
		1.0f, 10.0f,
		-20.0f,25.0f,-23.5f,
		0.3f, 0.2f, 0.1f);//ec de 2do grado
	pointLightCount++;

	//Lampara pared
	pointLights[1] = PointLight(1.0f, 0.5f, 0.0f,
		1.0f, 10.0f,
		10.0f,25.0f,-23.5f,
		0.3f, 0.1f, 0.1f);//ec de 2do grado
	pointLightCount++;

	//Calabazas Izquierda a derecha
	pointLights[2] = PointLight(1.0f, 0.5f, 0.0f,
		2.0f, 10.0f,
		-60.0f, 0.0f, -70.0f,
		0.3f, 0.1f, 0.1f);//ec de 2do grado
	pointLightCount++;

	pointLights[3] = PointLight(1.0f, 0.5f, 0.0f,
		2.0f, 10.0f,
		40.0f, 0.0f, -70.0f,
		0.3f, 0.1f, 0.1f);//ec de 2do grado
	pointLightCount++;

	pointLights[4] = PointLight(1.0f, 0.5f, 0.0f,
		2.0f, 10.0f,
		70.0f, 0.0f, 10.0f,
		0.3f, 0.1f, 0.1f);//ec de 2do grado
	pointLightCount++;

	pointLights[5] = PointLight(1.0f, 0.5f, 0.0f,
		2.0f, 10.0f,
		40.0f, 0.0f, 70.0f,
		0.3f, 0.1f, 0.1f);//ec de 2do grado
	pointLightCount++;

	pointLights[6] = PointLight(1.0f, 0.5f, 0.0f,
		2.0f, 10.0f,
		-60.0f, 0.0f, 70.0f,
		0.3f, 0.1f, 0.1f);//ec de 2do grado
	pointLightCount++;

	//Veladoras
	pointLights[7] = PointLight(1.0f, 0.1f, 0.0f,
		3.0f, 30.0f,
		40.0f, 0.0f, 30.0f,
		0.3f, 0.1f, 0.1f);//ec de 2do grado
	pointLightCount++;

	pointLights[8] = PointLight(1.0f, 0.1f, 0.0f,
		3.0f, 30.0f,
		40.0f, 0.0f, -30.0f,
		0.3f, 0.1f, 0.1f);//ec de 2do grado
	pointLightCount++;

	pointLights[9] = PointLight(1.0f, 0.1f, 0.0f,
		3.0f, 30.0f,
		-65.0f, 0.0f, -50.0f,
		0.3f, 0.1f, 0.1f);//ec de 2do grado
	pointLightCount++;

	//Calabazas restantes
	pointLights[10] = PointLight(1.0f, 0.5f, 0.0f,
		2.0f, 10.0f,
		70.0f, 0.0f, -40.0f,
		0.3f, 0.1f, 0.1f);//ec de 2do grado
	pointLightCount++;

	pointLights[11] = PointLight(1.0f, 0.5f, 0.0f,
		2.0f, 10.0f,
		70.0f, 0.0f, 60.0f,
		0.3f, 0.1f, 0.1f);//ec de 2do grado
	pointLightCount++;

	pointLights[12] = PointLight(1.0f, 0.5f, 0.0f,
		2.0f, 10.0f,
		-10.0f, 0.0f, -70.0f,
		0.3f, 0.1f, 0.1f);//ec de 2do grado
	pointLightCount++;

	pointLights[13] = PointLight(1.0f, 0.5f, 0.0f,
		2.0f, 10.0f,
		-10.0f, 0.0f, 70.0f,
		0.3f, 0.1f, 0.1f);//ec de 2do grado
	pointLightCount++;

	//contador de luces spotlight
	unsigned int spotLightCount = 0;

	//Luces de luminarias
	spotLights[0] = SpotLight(0.4f, 0.4f, 0.0f,
		0.0f, 0.02f,
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		10.0f);//alcance
	spotLightCount++;

	spotLights[1] = SpotLight(0.4f, 0.4f, 0.0f,
		0.0f, 0.02f,
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		10.0f);//alcance
	spotLightCount++;

	glm::vec3 pospelota = glm::vec3(0.0f, 0.0f, 0.0f);

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0, uniformColor = 0, uniformTextureOffset = 0;;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);

	auto inicial = std::chrono::steady_clock::now();
	int contador = 0, estadoSky=0,estadoLuz=0,i,banderaSonido=0, banderaCamina=0;

	std::string content;
	std::ifstream fileStream("keyframe.txt", std::ios::in);
	int indice=0;

	if (!fileStream.is_open()) {
		printf("Failed to read keyframes.txt File doesn't exist.");
	}
	std::string line = "";
	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		KeyFrame[indice].movpelota_x = std::stoi(line);
		std::getline(fileStream, line);
		KeyFrame[indice].movpelota_y = std::stoi(line);
		std::getline(fileStream, line);
		KeyFrame[indice].movpelota_z = std::stoi(line);
		std::getline(fileStream, line);
		KeyFrame[indice].giropelota = std::stoi(line);
		indice++;
	}
	fileStream.close();

	i_curr_steps = FrameIndex;
	
	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		//animaciones complejas siempre ejecutandose y las simples solo si se aprieta la tecla I
		caeSoda();
		complejaFantasma();
		giraTiara();
		if (mainWindow.getIniciaAnimacion()) {
			subenManosTumbas();
			mueveFantasma();
			hozRota();
		}

		//para keyframes
		inputKeyframes(mainWindow.getsKeys());
		animate();

		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime, mainWindow.getCamara());
		camera.mouseControl(mainWindow.getXChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Dibujado del skybox de d�a y de noche
		auto final = std::chrono::steady_clock::now();
		auto diferenciaTiempo = std::chrono::duration_cast<std::chrono::milliseconds>(final - inicial).count();

		//Cambio del skybox en base al tiempo que vaya pasando que es del 30 seg.
		if (estadoSky == 0) {
			if (banderaSonido == 0) {
				Mix_PlayMusic(musicDia, -1);
				estadoLuz = 0;
				banderaSonido = 1;
			}
			if (diferenciaTiempo < 30000) {
				skyboxDia.DrawSkybox(camera.calculateViewMatrix(), projection);
			}
			else {
				skyboxDia.DrawSkybox(camera.calculateViewMatrix(), projection);
				estadoSky = 1;
				inicial = final;
			}
		}

		diferenciaTiempo = std::chrono::duration_cast<std::chrono::milliseconds>(final - inicial).count();
		if (estadoSky == 1) {
			if (diferenciaTiempo < 30000) {
				skyboxAtardece.DrawSkybox(camera.calculateViewMatrix(), projection);
			}
			else {
				skyboxAtardece.DrawSkybox(camera.calculateViewMatrix(), projection);
				estadoSky = 2;
				inicial = final;
			}
		}

		diferenciaTiempo = std::chrono::duration_cast<std::chrono::milliseconds>(final - inicial).count();
		if (estadoSky == 2) {
			//Comprueba la pista a reproducir.
			if(banderaSonido == 1) {
				Mix_PlayMusic(musicNoche, -1);
				estadoLuz = 1;
				banderaSonido = 0;
			}
			if (diferenciaTiempo < 30000) {
				skyboxNoche.DrawSkybox(camera.calculateViewMatrix(), projection);
			}
			else {
				skyboxNoche.DrawSkybox(camera.calculateViewMatrix(), projection);
				estadoSky = 0;
				inicial = final;
			}
		}

		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();
		uniformTextureOffset = shaderList[0].getOffsetLocation();

		//informaci�n en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		//luz ligada a la c�mara de tipo flash 
		spotLights[0].SetFlash(glm::vec3(-90.0f, 0.0f, 20.0f), glm::vec3(1.0f, 0.3f, -0.1f));
		spotLights[1].SetFlash(glm::vec3(-90.0f, 0.0f, -24.0f), glm::vec3(1.0f, 0.3f, 0.1f));

		//informaci�n al shader de fuentes de iluminaci�n
		shaderList[0].SetDirectionalLight(&mainLight);

		//Apado y encendido de las luces.
		if (estadoLuz == 0) {
			shaderList[0].SetPointLights(pointLights, 0);
		}
		else {
			shaderList[0].SetPointLights(pointLights, pointLightCount);
		}

		if (mainWindow.getapagaLuces()) {
			shaderList[0].SetSpotLights(spotLights, spotLightCount);
		}
		else {
			shaderList[0].SetSpotLights(spotLights, 0);
		}

		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::vec2 toffset = glm::vec2(0.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(200.0f, 20.0f, 200.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pisoTexture.UseTexture();

		//agregar material al plano de piso
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[0]->RenderMesh();

		/////////////////////////////////////////// SAILOR MOON //////////////////////////////////////////////////////////////

		// TORZO	
		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(mainWindow.getsailorx(), 3.5f, mainWindow.getsailorz() + 30.0f));
		model = glm::rotate(model, mainWindow.getgiro() * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.6f, 1.6f, 1.6f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		torzo.RenderModel();

		// ROSTRO
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 2.4f, 0.0f));
		model = glm::scale(model, glm::vec3(5.5f, 5.5f, 5.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		sailorTexture.UseTexture();
		meshList[1]->RenderMesh();

		// FLECO
		model = modelaux;
		color = glm::vec3(1.00000f, 0.9f, 0.19608f);
		model = glm::translate(model, glm::vec3(0.0f, 2.4f, 0.0f));
		model = glm::scale(model, glm::vec3(5.5f, 5.5f, 5.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		meshList[2]->RenderMesh();

		// CHONGOS
		model = modelaux;
		model = glm::translate(model, glm::vec3(1.8f, 4.4f, -1.6f));
		model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		sailorColetasTexture.UseTexture();
		chongo.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-1.8f, 4.4f, -1.6f));
		model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		sailorColetasTexture.UseTexture();
		chongo.RenderModel();

		// COLETAS
		model = modelaux;
		model = glm::translate(model, glm::vec3(2.7f, 0.6f, -1.5f));
		model = glm::scale(model, glm::vec3(0.5f, 0.6f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		coleta.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-2.7f, 0.6f, -1.5f));
		model = glm::scale(model, glm::vec3(0.5f, 0.6f, 0.5f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		coleta.RenderModel();

		// Animaci�n y renderizado de los BRAZOS 
		model = modelaux;
		color = glm::vec3(0.91373f, 0.81176f, 0.50196f);
		model = glm::translate(model, glm::vec3(-0.7f, 0.5f, 0.0f));
		model = glm::rotate(model, 10 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, 70 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.15f, 0.35f, 0.35f));
		if (mainWindow.getbrazo() == 1) {

		}
		else if (mainWindow.getbrazo() % 2 == 0) {
			model = glm::rotate(model, 10 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		}
		else {
			model = glm::rotate(model, -10 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		}
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		piel.UseTexture();
		brazo.RenderModel();

		model = modelaux;
		color = glm::vec3(0.91373f, 0.81176f, 0.50196f);
		model = glm::translate(model, glm::vec3(0.7f, 0.5f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, 30 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, -50 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(-0.15f, -0.35f, -0.35f));
		if (mainWindow.getbrazo() == 1) {

		}
		else if (mainWindow.getbrazo() % 2 == 0) {
			model = glm::rotate(model, -10 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		}
		else {
			model = glm::rotate(model, 10 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		}
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		piel.UseTexture();
		brazo.RenderModel();

		// Animaci�n y renderizado de las PIERNAS
		model = modelaux;
		color = glm::vec3(0.91373f, 0.81176f, 0.50196f);
		model = glm::translate(model, glm::vec3(0.3f, -2.3f, 0.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.23f, 0.22f, 0.23f));
		if (mainWindow.getpierna() == 1) {

		}
		else if (mainWindow.getpierna() % 2 == 0) {
			//Indica el sonido
			if (banderaCamina == 0) {
				int canal = Mix_PlayChannel(2, camina, 0);
				banderaCamina = 1;
			}
			model = glm::rotate(model, 30 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::translate(model, glm::vec3(2.5f, -1.5f, 0.0f));
			model = glm::translate(model, glm::vec3(2.0f, 0.5f, 0.0f));
		}
		else {
			//Indica el sonido
			if (banderaCamina == 1) {
				int canal = Mix_PlayChannel(2, camina, 0);
				banderaCamina = 0;
			}
			model = glm::rotate(model, -30 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::translate(model, glm::vec3(-2.5f, -1.5f, 0.0f));
			model = glm::translate(model, glm::vec3(-2.0f, 0.5f, 0.0f));
		}
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		pierna.RenderModel();

		model = modelaux;
		color = glm::vec3(0.91373f, 0.81176f, 0.50196f);
		model = glm::translate(model, glm::vec3(-0.3f, -2.3f, 0.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.23f, 0.22f, 0.23f));
		if (mainWindow.getpierna() == 1) {

		}
		else if (mainWindow.getpierna() % 2 == 0) {
			model = glm::rotate(model, -30 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::translate(model, glm::vec3(-2.5f, -1.5f, 0.0f));
			model = glm::translate(model, glm::vec3(-2.0f, 0.5f, 0.0f));
		}
		else {
			model = glm::rotate(model, 30 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::translate(model, glm::vec3(2.5f, -1.5f, 0.0f));
			model = glm::translate(model, glm::vec3(2.0f, 0.5f, 0.0f));
		}
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		pierna.RenderModel();

		// TIARA
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f + tiarax, 20.0f + tiaray, 30.0f + tiaraz));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tiara.RenderModel();
		
		//Regresar el color normal
		color = glm::vec3(1.f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		//LUNA PELOTA
		model = glm::mat4(1.0);
		pospelota = glm::vec3(pelotax + movpelota_x, pelotay + movpelota_y, pelotaz + movpelota_z);
		model = glm::translate(model, pospelota);
		model = glm::rotate(model, giropelota * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		pelota.RenderModel();

		//////////////////////////////////////////// MODELOS DEL AMBIENTE HUESO ////////////////////////////////////////
		//Vela
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(40.0f, 0.0f, 30.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		vela.RenderModel();

		//Vela
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(40.0f, 0.0f, -30.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		vela.RenderModel();

		//Vela
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-65.0f, 0.0f, -50.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		vela.RenderModel();

		//LapidaC - frente primero
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(70.0f, 0.0f, -50.0f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		LapidaPH3.RenderModel();

		//LapidaB - frente segundo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(70.0f, 3.0f, 0.0f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		LapidaPH2.RenderModel();

		//LapidaA - frente tercero
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(70.0f, 0.0f, 50.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		LapidaPH1.RenderModel();

		//LapidaC - izquierda primero
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-50.0f, 0.0f, -70.0f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		LapidaPH3.RenderModel();

		//LapidaB - izquierda segundo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 3.0f, -70.0f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		LapidaPH2.RenderModel();

		//LapidaA - izquierda tercero
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(50.0f, 0.0f, -70.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		LapidaPH1.RenderModel();

		//LapidaA - derecha primero
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-50.0f, 0.0f, 70.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		LapidaPH1.RenderModel();

		//LapidaB - derecha segundo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 3.0f, 70.0f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		LapidaPH2.RenderModel();

		//LapidaC - derecha tercero
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(50.0f, 0.0f, 70.0f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		LapidaPH3.RenderModel();

		//tumbaTierra - izquierda primero
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-50.0f, 0.0f, -60.0f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tumba.RenderModel();

		//tumbaTierra - izquierda segundo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -60.0f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tumba.RenderModel();

		//tumbaTierra - izquierda tercero
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(50.0f, 0.0f, -60.0f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tumba.RenderModel();

		//tumbaTierra - frente segundo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(70.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tumba.RenderModel();

		//tumbaTierra - frente tercero
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(70.0f, 0.0f, 50.0f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tumba.RenderModel();

		//tumbaTierra - frente primero
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(70.0f, 0.0f, -50.0f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tumba.RenderModel();

		//tumbaTierra - derecha primero
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-50.0f, 0.0f, 70.0f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tumba.RenderModel();

		//tumbaTierra - derecha segundo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 70.0f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tumba.RenderModel();

		//tumbaTierra - derecha tercero
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(50.0f, 0.0f, 70.0f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tumba.RenderModel();

		//Mano esqueleto - derecha tercera
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(56.0f, -17.0f + incrementoManoHuesoY, 55.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		manoEsqueleto.RenderModel();

		//Mano esqueleto - derecha segunda
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(6.0f, -17.0f + incrementoManoHuesoY, 55.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		manoEsqueleto.RenderModel();

		//Mano esqueleto - derecha primera
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-44.0f, -17.0f + incrementoManoHuesoY, 55.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		manoEsqueleto.RenderModel();

		//Mano esqueleto - frente primera
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(57.0f, -17.0f + incrementoManoHuesoY, -56.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//manoEsqueleto.RenderModel();

		//Mano esqueleto - frente segunda
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(57.0f, -17.0f + incrementoManoHuesoY, -6.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//manoEsqueleto.RenderModel();

		//Mano esqueleto - frente tercera
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(57.0f, -17.0f + incrementoManoHuesoY, 44.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		manoEsqueleto.RenderModel();

		//Mano esqueleto - izquierda tercera
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(44.0f, -17.0f + incrementoManoHuesoY, -55.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		manoEsqueleto.RenderModel();

		//Mano esqueleto - izquierda segunda
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-6.0f, -17.0f + incrementoManoHuesoY, -55.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		manoEsqueleto.RenderModel();

		//Mano esqueleto - izquierda primera
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-56.0f, -17.0f + incrementoManoHuesoY, -55.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		manoEsqueleto.RenderModel();

		//Arbol - derecha fondo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(40.0f, 3.0f, 80.0f));
		model = glm::scale(model, glm::vec3(1.0f, 2.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbolA.RenderModel();

		//Arbol - derecha primero
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-120.0f, 3.0f, 80.0f));
		model = glm::scale(model, glm::vec3(1.0f, 2.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbolA.RenderModel();

		//Arbol - izquierda primero
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-120.0f, 3.0f, -80.0f));
		model = glm::scale(model, glm::vec3(1.0f, 2.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbolA.RenderModel();

		//Arbol - izquierda fondo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(40.0f, 3.0f, -80.0f));
		model = glm::scale(model, glm::vec3(1.0f, 2.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbolA.RenderModel();

		//Calabaza frente primera
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(70.0f, 0.0f, -40.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		calabaza.RenderModel();

		//Calabaza frente segunda
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(70.0f, 0.0f, 10.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		calabaza.RenderModel();

		//Calabaza frente tercera
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(70.0f, 0.0f, 60.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		calabaza.RenderModel();

		//Calabaza izquierda segunda
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-10.0f, 0.0f, -70.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		calabaza.RenderModel();

		//Calabaza izquierda primera
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-60.0f, 0.0f, -70.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		calabaza.RenderModel();

		//Calabaza izquierda tercera
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(40.0f, 0.0f, -70.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		calabaza.RenderModel();

		//Calabaza derecha primera
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-60.0f, 0.0f, 70.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		calabaza.RenderModel();

		//Calabaza derecha segunda
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-10.0f, 0.0f, 70.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		calabaza.RenderModel();

		//Calabaza derecha tercera
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(40.0f, 0.0f, 70.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		calabaza.RenderModel();

		//Reja superior izquierda
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(80.0f, 0.0f, -95.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		reja.RenderModel();

		//Reja superior izquierda
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(42.0f, 0.0f, -95.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		reja.RenderModel();

		//Reja superior izquierda
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(4.0f, 0.0f, -95.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		reja.RenderModel();

		//Reja superior izquierda
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-34.0f, 0.0f, -95.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		reja.RenderModel();

		//Reja superior izquierda
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-72.0f, 0.0f, -95.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		reja.RenderModel();

		//Reja superior derecha
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(95.0f, 0.0f, -73.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		reja.RenderModel();

		//Reja superior derecha
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(95.0f, 0.0f, -35.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		reja.RenderModel();

		//Reja superior derecha
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(95.0f, 0.0f, 3.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		reja.RenderModel();

		//Reja superior derecha
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(95.0f, 0.0f, 41.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		reja.RenderModel();

		//Reja superior derecha
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(95.0f, 0.0f, 79.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		reja.RenderModel();

		//Reja superior inferior
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(72.0f, 0.0f, 98.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		reja.RenderModel();

		//Reja superior inferior
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(34.0f, 0.0f, 98.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		reja.RenderModel();

		//Reja superior inferior
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-4.0f, 0.0f, 98.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		reja.RenderModel();

		//Reja superior inferior
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-42.0f, 0.0f, 98.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		reja.RenderModel();

		//Reja superior inferior
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-80.0f, 0.0f, 98.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		reja.RenderModel();

		//Reja frente
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-97.0f, 0.0f, -80.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		reja.RenderModel();

		//Reja frente
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-97.0f, 0.0f, -42.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		reja.RenderModel();

		//Reja frente
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-97.0f, 0.0f, 75.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		reja.RenderModel();

		//Reja frente
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-97.0f, 0.0f, 37.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		reja.RenderModel();

		//Camino de piedra
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-80.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		camino.RenderModel();

		//Camino de piedra
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-50.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		camino.RenderModel();

		//Dulces
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-50.0f, 0.0f, 50.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dulces.RenderModel();

		//Dulces
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(30.0f, 0.0f, 80.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dulces.RenderModel();

		//Dulces
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(50.0f, 0.0f, 30.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dulces.RenderModel();

		//Dulces
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(80.0f, 0.0f, -30.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dulces.RenderModel();

		//Dulces
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(20.0f, 0.0f, -80.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dulces.RenderModel();

		//Dulces
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, 0.0f, -60.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dulces.RenderModel();

		//Dulces
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(70.0f, 0.0f, -60.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dulces.RenderModel();

		//Dulces
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, 0.0f, 80.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dulces.RenderModel();

		//Dulces
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(80.0f, 0.0f, 60.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dulces.RenderModel();

		///////////////////////////////////////////////////////////////////////////////////////////
		//Fantasma Tumbas Frente
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(65.0f, -10.0f + incFantasmaY, -50.0f + incFantasmaZ));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, incFantasmaRota * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		fantasma.RenderModel();

		//Fantasma Recorrido
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-100.0f + incFantasmaCompX, 0.0f + incFantasmaCompY, 0.0f + incFantasmaCompZ));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, incFantasmaCompRota * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		fantasma.RenderModel();

		// PURO HUESO
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-68.5f, 16.0f, -56.0f));
		model = glm::rotate(model, 120 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.5f, 2.5f, 2.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		cabezapurohueso.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-70.0f, 0.0f, -60.0f));
		model = glm::rotate(model, 37 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		tunicapurohueso.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-72.0f, 11.0f, -54.0f));
		model = glm::scale(model, glm::vec3(0.06f, 0.06f, 0.06f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		manoph.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-62.0f, 14.0f, -57.0f));
		model = glm::scale(model, glm::vec3(-0.06f, -0.06f, -0.06f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f)); //se mueve
		model = glm::rotate(model, -hozrota * toRadians, glm::vec3(0.0f, 1.0f, 0.0f)); //se mueve
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		manoph.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-61.0f, 14.0f, -57.0f));
		model = glm::scale(model, glm::vec3(3.5f, 4.5f, 3.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, hozrota * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hoz.RenderModel();

		// Jack O'Lantern
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(50.5f, 0.0f, 50.0f));
		model = glm::rotate(model, 120 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.5f, 2.5f, 2.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		jolcabeza.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(50.5f, 0.2f, 50.0f));
		model = glm::rotate(model, 120 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.5f, 2.5f, 2.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		jolsombrero.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(50.5f, 0.0f, 50.0f));
		model = glm::rotate(model, 120 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.5f, 2.5f, 2.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		jolropa.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(50.5f, 0.0f, 50.0f));
		model = glm::rotate(model, 120 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.5f, 2.5f, 2.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		jolpantalones.RenderModel();

		/////////////////////////////// SAILOR MOON AMBIENTE /////////////////////////////////////////////////////////

		//Expendedora
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(8.0f, 0.0f, -22.0f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		expendedora.RenderModel();

		//Soda
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(7.5f, 2.5f + incSodaY, -20.0f + incSodaZ));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, incSodaRota * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		soda.RenderModel();

		//ArcadeDos primera
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-20.0f, 0.0f, -20.5f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arcadeDos.RenderModel();

		//ArcadeDos segunda
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-13.0f, 0.0f, -20.5f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arcadeDos.RenderModel();

		//ArcadeDos tercera
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-6.0f, 0.0f, -20.5f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arcadeDos.RenderModel();

		//Arcade primera
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(5.0f, 0.0f, 8.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arcade.RenderModel();

		//Arcade segunda
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-3.0f, 0.0f, 8.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arcade.RenderModel();

		//Arcade tercera
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-11.0f, 0.0f, 8.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arcade.RenderModel();

		//Arcade cuarta
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-19.0f, 0.0f, 8.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arcade.RenderModel();

		//Banco primero
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(5.0f, 0.0f, 16.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		color = glm::vec3(0.9f, 0.5f, 0.45f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		banco.RenderModel();

		//Banco segundo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-3.0f, 0.0f, 16.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		banco.RenderModel();

		//Banco tercero
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-11.0f, 0.0f, 16.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		banco.RenderModel();

		//Banco cuarto
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-19.0f, 0.0f, 16.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		banco.RenderModel();

		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		//Fachada Game Center
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-30.0f, 0.0f, 25.0f));
		model = glm::scale(model, glm::vec3(50.0f, 40.0f, 50.0f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		fachada.UseTexture();
		meshList[3]->RenderMeshGeometry();

		//Pared Game Center Exterior
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-30.0f, 0.0f, -25.0f));
		model = glm::scale(model, glm::vec3(50.0f, 40.0f, 50.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		fachadaLado.UseTexture();
		meshList[3]->RenderMeshGeometry();
		
		//Piso Game Center
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(20.0f, 0.1f, 25.0f));
		model = glm::scale(model, glm::vec3(50.0f, 50.0f, 50.0f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pisoGame.UseTexture();
		meshList[3]->RenderMeshGeometry();

		glEnable(GL_BLEND); //Se tiene que desabilitar, se aplicar a las futuras texturas
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		//Animaci�n del letrero del game center por medio del movimiento de la textura.
		toffsetu += 0.01 * deltaTime;
		toffsetv += 0.01 * deltaTime;

		if (toffsetu > 1.0)
			toffsetu = 0.0;
		if (toffsetv > 1.0)
			toffsetv = 0;

		toffset = glm::vec2(toffsetu, 0.0f);

		//Letrero Game Center
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-30.1f, 9.0f, 25.0f));
		model = glm::scale(model, glm::vec3(50.0f, 15.0f, 50.0f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		letrero.UseTexture();
		meshList[3]->RenderMeshGeometry();

		glDisable(GL_BLEND);
		toffset = glm::vec2(0.0f, 0.0f); //Setear con nulos para que no mueva las texturas
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));

		//Luminaria derecha
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-90.0f, 0.0f, 20.0f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		luminaria.RenderModel();

		//Luminaria izquierda
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-90.0f, 0.0f, -24.0f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		luminaria.RenderModel();

		//Lampara pared
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-20.0f, 25.0f, -23.5f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 2.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		color = glm::vec3(0.9f, 0.5f, 0.45f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		lamparaPared.RenderModel();

		//Lampara pared
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(10.0f, 25.0f, -23.5f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 2.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		lamparaPared.RenderModel();

		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		glUseProgram(0);
		mainWindow.swapBuffers();
	}

	//Liberar el audio
	Mix_FreeMusic(musicDia);
	Mix_FreeMusic(musicNoche);
	Mix_FreeChunk(camina);
	Mix_Quit();
	SDL_Quit();
	return 0;
}

void inputKeyframes(bool* keys)
{
	if (keys[GLFW_KEY_SPACE])
	{
		if (reproduciranimacion < 1)
		{
			if (play == false && (FrameIndex > 1))
			{
				resetElements();
				//First Interpolation				
				interpolation();
				play = true;
				playIndex = 0;
				i_curr_steps = 0;
				reproduciranimacion++;
				printf("\nPresiona 0 para habilitar reproducir de nuevo la animaci�n'\n");
				habilitaranimacion = 0;

			}
			else
			{
				play = false;
			}
		}
	}
	if (keys[GLFW_KEY_0])//habilita reproducir de nuevo
	{
		if (habilitaranimacion < 1)
		{
			reproduciranimacion = 0;
		}
	}

}


