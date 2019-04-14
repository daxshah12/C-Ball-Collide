#include <glew.h>
#include <iostream>
#include "Window.h"
#include "Debug.h"
#include "Scene1.h"
#include "Camera.h"
#include "GameObject.h"
#include "ObjLoader.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "MMath.h"
#include "Collider.h"
#include "Audio.h"

using namespace std;

#define print(x) std::cout << x << std::endl;
Scene1::Scene1() {
}


Scene1::~Scene1() {
}

bool Scene1::OnCreate() {

	camera = new Camera();
	/////////////////////////////////////////////////////////////////

	if (ObjLoader::loadOBJ("sphere.obj") == false) {
		return false;
	}

	//////////////////////////////////////////////////////////////////
	meshPtr = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);
	shaderPtr = new Shader("textureVert.glsl", "textureFrag.glsl");
	texturePtr = new Texture();
////////////////////////////////////////////////////////////////////////

	//ths is for LeftBall;
	if (meshPtr == nullptr || shaderPtr == nullptr || texturePtr == nullptr)
	{
		Debug::FatalError("Couldn't Creat game object assets", __FILE__, __LINE__);
		return false;
	}
	if (texturePtr->LoadImage("earth_texture.jpg") == false) {
		Debug::FatalError("Couldn't load texture", __FILE__, __LINE__);
		return false;
	}

	LeftBall = new GameObject(meshPtr, shaderPtr, texturePtr);

	if (LeftBall == nullptr) {
		Debug::FatalError("LeftBall could not be created", __FILE__, __LINE__);
		return false;
	}
///////////////////////////////////////////////////
	//lightSource = Vec3(3.0, 16.0, 0.0);
///////////////////////////////////////////////////



	//this if for RightBall;
	texturePtr2 = new Texture();

	if (texturePtr2->LoadImage("moon_texture.jpg") == false) {
		Debug::FatalError("Couldn't load texture", __FILE__, __LINE__);
		return false;
	}

	
	RightBall = new GameObject(meshPtr, shaderPtr, texturePtr2);

	if (RightBall == nullptr) {
		Debug::FatalError("RightBall could not be created", __FILE__, __LINE__);
		return false;
	}



	
////////////////////////////////////////////////////////////

	//setting up position for both balls;

	LeftBall->position = Vec3(-3.9f, 0.0f, 0.0f);

	RightBall->position = Vec3(3.9f, 0.0f, 0.0f);

	lightSource = Vec3(3.0, 16.0, 0.0);

////////////////////////////////////////////////////////////

	LeftBall->velocity = Vec3(3.5f, 0.0f, 0.0f);

	RightBall->velocity = Vec3(-3.5f, 0.0f, 0.0f);

//////////////////////////////////////////////////////////

	//LeftBall->accel = Vec3(1.5f, 0.0f, 0.0f);

//	RightBall->accel = Vec3(-1.5f, 0.0f, 0.0f);

	return true;
	

}

void Scene1::OnDestroy()
{
	if (camera) delete camera, camera = nullptr;

	if (LeftBall) delete LeftBall, LeftBall = nullptr;
	if (RightBall) delete RightBall, RightBall = nullptr;

	if (meshPtr) delete meshPtr, meshPtr = nullptr;

	if (texturePtr) delete texturePtr, texturePtr = nullptr;
	if (texturePtr2) delete texturePtr2, texturePtr2 = nullptr;

	if (shaderPtr) delete shaderPtr, shaderPtr = nullptr;
}

void Scene1::HandleEvents(const SDL_Event &sdlEvent) {}

void Scene1::Update(const float deltaTime_)
{

	//Moving Left Ball
		Collider::SimpleNewtonMotion(*LeftBall, deltaTime_);
	//Moving Right Ball
	Collider::SimpleNewtonMotion(*RightBall, deltaTime_);
	

	//Cheaking if the collision if happingin or not
	if (Collider::SphereSphereCollision(*LeftBall, *RightBall) == true)
		{
		// if the collisiton happends then collision respose happends after it touches
			Collider::SphereSphereCollisionResponse(*LeftBall, *RightBall);
		Game::Game();
		}

	
	
	// making the ball collide to the end of the screen and go back so i dont have to opent the consol everytime
	if (*LeftBall->position < -6.0f && *RightBall->position > 6.0f)
	{
		LeftBall->velocity = Vec3(3.0f, 0.0f, 0.0f);
		RightBall->velocity = Vec3(-3.0f, 0.0f, 0.0f);
	Game::Game();
	}

	

	//Updating the Left and Right Ball;
	LeftBall->Update(deltaTime_);
	RightBall->Update(deltaTime_);


}

void Scene1::Render() const
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/// Draw your scene here
	GLuint program = LeftBall->getShader()->getProgram();


	glUseProgram(program);


	/// This should not be done here. You only need to get these
	/// ID's once after the sharder has been created - TODO
	//projection makes the object bigger or smaller
	GLint projectionMatrixID = glGetUniformLocation(program, "projectionMatrix");
	GLint viewMatrixID = glGetUniformLocation(program, "viewMatrix");
	GLint lightPosID = glGetUniformLocation(program, "lightPos");



	/// These pass the matricies and the light position to the GPU
	glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, camera->getProjectionMatrix());
	glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, camera->getViewMatrix());
	glUniform3fv(lightPosID, 1, lightSource);

	
	LeftBall->Render();

	RightBall->Render();


	glUseProgram(0);
}
