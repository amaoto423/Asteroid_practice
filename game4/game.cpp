#include "game.h"
#include<glew.h>
#include "SDL_image.h"
#include <algorithm>
#include "Actor.h"
#include "SpriteComponent.h"
#include "BGSpriteComponent.h"
#include "Asteroid.h"
#include"Ship.h"
Game::Game() :mWindow(nullptr)
, mRenderer(nullptr),
mContext(nullptr)
, mIsRunning(true)
, mUpdatingActors(false),mShip(nullptr),mTickCount(0)
{

}
bool Game::Initialize() {
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);

	if (sdlResult != 0) {
		SDL_Log("SDL failed %s", SDL_GetError());
		return false;
	}
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	mWindow = SDL_CreateWindow(
		"Chap5",
		100, 100, 1024, 764,
		SDL_WINDOW_OPENGL
	);
	mContext = SDL_GL_CreateContext(mWindow);
	if (!mContext) {
		SDL_Log("context failed %s", SDL_GetError());
		return false;
	}
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		SDL_Log("Init GLEW is failed");
		return false;
	}
	LoadShaders();

	InitSpriteVerts();
	glGetError();
	if (!mWindow) {
		SDL_Log("window failed %s", SDL_GetError());
		return false;
	}
	if (IMG_Init(IMG_INIT_PNG) == 0) {
		SDL_Log("image failed %s", SDL_GetError());
		return false;
	}

	mRenderer = SDL_CreateRenderer(
		mWindow,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);
	LoadData();
	mTickCount = SDL_GetTicks();
	return true;
}

void Game::RunLoop() {
	while (mIsRunning) {
		ProcessInput();
		UpdateGame();
		GenerateOutput();

	}
}
void Game::Shutdown() {
	IMG_Quit();
	SDL_DestroyRenderer(mRenderer);
	SDL_GL_DeleteContext(mContext);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}
void Game::InitSpriteVerts() {
	float vertexBuffer[] = {
	-0.5,0.5,0.0,0.0,0.0,
	0.5,0.5,0.0,1.0,0.0,
	0.5,-0.5,0.0,1.0,1.0,
	-0.5,-0.5,0.0,0.0,1.0
	};
	unsigned int indexBuffer[] = {
		0,1,2,
		2,3,0
	};
	mSpriteVerts = new VertexArray(vertexBuffer,4,indexBuffer,6);
}
void Game::GenerateOutput() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.86f, 0.86f, 0.86f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	mSpriteShader->SetActive();
	mSpriteVerts->SetActive();
	for (auto sprite : mSprites) {
		sprite->Draw(mSpriteShader);
	}
	SDL_GL_SwapWindow(mWindow);
	
}
void Game::UpdateGame() {
	

	float deltatime = (SDL_GetTicks() - mTickCount) / 1000.0f;
	//glUseProgram(mSpriteShader->GetShaderProgram());
	
	mTickCount = SDL_GetTicks();
	mUpdatingActors = true;
	for (auto actor : mActors) {
		actor->Update(deltatime);
	}
	mUpdatingActors = false;
	for (auto pending : mPendingActors) {
		pending->ComputeWorldTransform();
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();
	std::vector<Actor*> deadActors;
	for (auto actor : mActors) {
		if (actor->GetState() == Actor::EDead) {
			deadActors.emplace_back(actor);
		}

	}
	for (auto actor : deadActors) {
		delete actor;
	}
}


void Game::ProcessInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}

	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}
	mUpdatingActors = true;
	for (auto act : mActors) {
	
			act->ProcessInput(state);
		
	
	}
	mUpdatingActors = false;
	// Process ship input

}
void Game::AddActor(Actor* actor) {
	if (mUpdatingActors) {
		mPendingActors.emplace_back(actor);
	}
	else {
		mActors.emplace_back(actor);
	}
}
void Game::RemoveActor(Actor* actor) {
	// Is it in pending actors?
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	// Is it in actors?
	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

class Texture* Game::GetTexture(const std::string& fileName) {
	Texture* tex = nullptr;
	// Is the texture already in the map?
	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end())
	{
		tex = iter->second;
	}
	else
	{
		tex = new Texture();
		// Load from file
		if (tex->Load(fileName)) {
			mTextures.emplace(fileName, tex);
		}
		else
		{
			SDL_Log("Texture %s cant be loaded ", fileName.c_str());
			delete tex;
			tex = nullptr;
			
		}

	
	}
	return tex;
}
void Game::AddSprite(SpriteComponent* sprite)
{
	// Find the insertion point in the sorted vector
	// (The first element with a higher draw order than me)
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for (;
		iter != mSprites.end();
		++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}

	// Inserts element before position of iterator
	mSprites.insert(iter, sprite);
}
void Game::AddAsteroid(Asteroid* ast) {
	mAstroids.emplace_back(ast);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
	// (We can't swap because it ruins ordering)
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}

void Game::LoadData()
{

	
	const int numAsteroid = 20;
	for (int i = 0; i < numAsteroid; i++) {
		new Asteroid(this);
	}
	mShip = new Ship(this);
	
	mShip->SetPosition(Vector2(100.0f, 384.0f));
	mShip->SetScale(1.5f);
}
void Game::UnloadData()
{
	// Delete actors
	// Because ~Actor calls RemoveActor, have to use a different style loop
	while (!mActors.empty())
	{
		delete mActors.back();
	}

	// Destroy textures
	for (auto i : mTextures)
	{
		i.second->Unload();
	}
	mTextures.clear();
}
void Game::RemoveAsteroid(Asteroid* ast)
{
	auto iter = std::find(mAstroids.begin(),
		mAstroids.end(), ast);
	if (iter != mAstroids.end())
	{
		mAstroids.erase(iter);
	}
}

bool Game::LoadShaders() {
	mSpriteShader = new Shader();
	Matrix4 viewProj = Matrix4::CreateSimpleViewProj(1024.0f, 768.0f);
	
	if (!mSpriteShader->Load("Sprite.vert", "Sprite.frag")) {
		return false;

	}
	mSpriteShader->SetActive();
	mSpriteShader->SetMatrixUniform("uViewProj", viewProj);
	
	return true;
	
}
