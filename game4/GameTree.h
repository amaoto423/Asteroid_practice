#pragma once

#include<algorithm>
#include<vector>
struct GameState {
	enum SquareState{Empty,X,O};
	SquareState mBoard[3][3];
	
};
struct GTNode{
	std::vector<GTNode*> mChildren;
	GameState mState;
};

float GetScore(const GameState){}
float MaxPlayer(const GTNode* node) {
	if (node->mChildren.empty()) {
		return GetScore(node->mState);
	}
	float MaxValue=-std::numeric_limits<float>::infinity();
	for (const GTNode* child : node->mChildren) {
		MaxValue = std::max(MaxValue, MinPlayer(child));
	}
}
float MinPlayer(const GTNode* node) {
	if (node->mChildren.empty()) {
		return GetScore(node->mState);
	}
	float MinValue = std::numeric_limits<float>::infinity();
	for (const GTNode* child : node->mChildren) {
		MinValue = std::min(MinValue, MaxPlayer(child));
	}

}
GTNode* DecideNode(const GTNode* node) {
	const GTNode* Next;
	float MinValue = std::numeric_limits<float>::infinity();
	for (const GTNode* child : node->mChildren) {
		if (MinValue < MaxPlayer(child)) {
			Next = child;
		}
		MinValue = std::min(MinValue, MaxPlayer(child));
		
	}

}

const GameState* AlphaBetaDecide(const GameState* root, int maxDepth) {
	const GameState* choice = nullptr;
	float maxValue = -std::numeric_limits<float>::infinity();
	float beta= std::numeric_limits<float>::infinity();
	for (const GameState* child : root->) {

	}
}