#pragma once
#include<vector>
#include<unordered_map>
#include<algorithm>
struct GraphNode {
	std::vector<GraphNode*> mAdjacent;
};
struct Graph {
	std::vector<GraphNode*> mNodes;
};

struct WeightedEdge {
	struct WeightedGraphNode* mFrom;
	struct WeightedGraphNode* mTo;
	float mWeight;
};
struct WeightedGraphNode {
	std::vector<WeightedEdge*> mEdges;
};
struct WeightedGraph {
	std::vector<WeightedGraphNode*> mNodes;
};
struct GBFSScratch {
	const WeightedEdge* mParentEdge = nullptr;
	float mHeuristic = 0;
	bool mInOpneSet = false;
	bool mInClosedSet = false;

};
float ComputeHeuristic(const WeightedGraphNode* current, const WeightedGraphNode* goal) {
	float w;
	return w;
}
using GBFSMap = std::unordered_map<const WeightedGraphNode*, GBFSScratch>;

bool GBFS(const WeightedGraph& g, const WeightedGraphNode* start, const WeightedGraphNode* goal, GBFSMap& outMap) {
	std::vector<WeightedGraphNode*> OpenSet;
	const WeightedGraphNode* Current = start;
	outMap[Current].mInClosedSet = true;

	do {
		for (const WeightedEdge* edge : Current->mEdges) {
			GBFSScratch& data = outMap[edge->mTo];
			if (!data.mInClosedSet) {
				data.mParentEdge = edge;
				if (!data.mInOpneSet) {
					data.mHeuristic = ComputeHeuristic(edge->mTo, goal);
					data.mInOpneSet = true;
					OpenSet.emplace_back(edge->mTo);
				}
			}
		}
		if (OpenSet.empty()) {
			break;
		}
		auto itr = std::min_element(OpenSet.begin(), OpenSet.end(), [&outMap](const WeightedGraphNode* a, const WeightedGraphNode* b) {return outMap[a].mHeuristic < outMap[b].mHeuristic; });
		Current = *itr;
		OpenSet.erase(itr);
		outMap[Current].mInOpneSet = false;
		outMap[Current].mInClosedSet = true;
	} while (Current != goal);
	return (goal == Current) ? true : false;
}
struct AStarScratch {
	const WeightedEdge* mParentEdge = nullptr;
	float mActualFromStart = 0;
	float mHeuristic = 0;
	bool mInOpneSet = false;
	bool mInClosedSet = false;

};
using AStarMap = std::unordered_map<const WeightedGraphNode*, AStarScratch>;

bool AStarSerch(const WeightedGraph& g, const WeightedGraphNode* start, const WeightedGraphNode* goal, AStarMap& outMap) {
	std::vector<WeightedGraphNode*> OpenSet;
	const WeightedGraphNode* Current = start;
	outMap[Current].mInClosedSet = true;

	do {
		for (const WeightedEdge* edge : Current->mEdges) {
			AStarScratch& data = outMap[edge->mTo];
			if (!data.mInClosedSet) {
				data.mParentEdge = edge;
				if (!data.mInOpneSet) {
					data.mHeuristic = ComputeHeuristic(edge->mTo, goal);
					data.mActualFromStart = outMap[Current].mActualFromStart + edge->mWeight;
					data.mInOpneSet = true;
					OpenSet.emplace_back(edge->mTo);
				}
				else {
					float newG = outMap[Current].mActualFromStart + edge->mWeight;
					if (newG < data.mActualFromStart) {
						data.mActualFromStart = newG;
						data.mParentEdge = edge;
					}
				}
			}
		}
		if (OpenSet.empty()) {
			break;
		}
		auto itr = std::min_element(OpenSet.begin(), OpenSet.end(), [&outMap](const WeightedGraphNode* a, const WeightedGraphNode* b) {return outMap[a].mHeuristic < outMap[b].mHeuristic; });
		Current = *itr;
		OpenSet.erase(itr);
		outMap[Current].mInOpneSet = false;
		outMap[Current].mInClosedSet = true;
	} while (Current != goal);
	return (goal == Current) ? true : false;
}
