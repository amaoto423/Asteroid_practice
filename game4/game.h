#pragma once
#pragma once
#pragma once
#include<SDL.h>
#include<vector>
#include<unordered_map>
#include"SpriteComponent.h"
#include<string>
#include "Asteroid.h"
#include"glew.h"
#include"VertexArray.h"
#include"Shader.h"
#include"Texture.h"
class Game {
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();
	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	void RemoveActor(class Actor* actor);
	void AddActor(class Actor* actor);
	class Texture* GetTexture(const std::string& fileName);
	void AddAsteroid(class Asteroid* ast);
	std::vector<class Asteroid* > GetAsteroid() {
		return mAstroids;
	}
	void RemoveAsteroid(Asteroid* ast);
	void InitSpriteVerts();
	bool LoadShaders();
private:
	void GenerateOutput();
	void ProcessInput();
	void UpdateGame();

	void LoadData();
	void UnloadData();
	float elapsed_time = 0;
	bool mIsRunning;
	bool mUpdatingActors;
	Uint32 mTickCount;
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	SDL_GLContext mContext;
	std::unordered_map<std::string, class Texture*>mTextures;
	std::vector<class Asteroid*> mAstroids;
	std::vector<class Actor*> mActors, mPendingActors;
	std::vector<class SpriteComponent*> mSprites;
	class Ship* mShip;
	class VertexArray* mSpriteVerts;
	class Shader* mSpriteShader;
	
};