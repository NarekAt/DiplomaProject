#pragma once

#include <string>
#include <vector>
#include <set>

class Graph
{
public:
	Graph(void);
	virtual ~Graph(void);

	void ReadFromEdgelist(const std::string& fname);
	void ReadFromPajeck(const std::string& fname);
	void CalcModMtrix();

	int Size() const {return m_size;}
	int CommunityNumber() const {return m_communityNumber;};
	double EdgeWeight(int i, int j) const;
	bool IsCommunityEmpty(int comm) const;

	double Modularity() const;
	std::vector< std::vector<double> > GetModularitySubmatrix(const std::vector<int>& indices) const;
	std::vector<double> GetCorrectionVector(const std::vector<int>& origCommInd, const std::vector<int>& destCommInd) const;
	
	void SetCommunities(const std::vector<int>& new_communities, int number = -1);
	std::vector<int> Communities() const {return m_communities;};
	std::vector<int> CommunityIndices(int comm) const;

	void PerformSplit(int origin, int dest, const std::vector<int>& split_communities);
	bool DeleteCommunityIfEmpty(int comm);
	void Print() const;
	void PrintCommunity(const std::string& fileName) const;

	void FillModMatrix(const std::vector<int>& src, const std::vector<int>& dst, const std::vector<double>& weight);
    std::vector<int> getCommunities() const;

private:
	void FillMatrix(const std::vector<int>& src, const std::vector<int>& dst, const std::vector<double>& weight);

private:
	int m_size;
	double m_totalWeight;
	int m_communityNumber;
	bool m_isOriented;
	std::vector<std::vector<double> > m_matrix;
	std::vector<std::vector<double> > m_modMatrix;
	std::vector<int> m_communities;
};

