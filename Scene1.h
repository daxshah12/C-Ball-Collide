#ifndef SCENE1_H
#define SCENE1_H
#include "Scene.h"
#include "Vector.h"
using namespace MATH;
union SDL_Event;
class Camera;
class GameObject;
class Shader;
class Texture;
class Mesh;


class Scene1 : public Scene {

private:
	Camera *camera;

	Mesh *meshPtr;
	Shader *shaderPtr;

	Texture *texturePtr;
	Texture *texturePtr2;




	GameObject *LeftBall;
	GameObject *RightBall;

	Vec3 lightSource;
public:
	explicit Scene1();
	virtual ~Scene1();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime_) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event &sdlEvent) override;
};



#endif // !SCENE1_H
