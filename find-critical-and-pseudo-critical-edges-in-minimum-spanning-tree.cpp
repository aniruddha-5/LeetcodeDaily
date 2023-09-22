/*
Problem link: https://leetcode.com/problems/find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree/
1489. Find Critical and Pseudo-Critical Edges in Minimum Spanning Tree
Given a weighted undirected connected graph with n vertices numbered from 0 to n - 1, 
and an array edges where edges[i] = [ai, bi, weighti] represents a bidirectional and 
weighted edge between nodes ai and bi. A minimum spanning tree (MST) is a subset of the graph's 
edges that connects all vertices without cycles and with the minimum possible total edge weight.

Find all the critical and pseudo-critical edges in the given graph's minimum spanning tree (MST). 
An MST edge whose deletion from the graph would cause the MST weight to increase is called a critical edge. 
On the other hand, a pseudo-critical edge is that which can appear in some MSTs but not all.

Note that you can return the indices of the edges in any order.

Input: n = 5, edges = [[0,1,1],[1,2,1],[2,3,2],[0,3,2],[0,4,3],[3,4,3],[1,4,6]]
Output: [[0,1],[2,3,4,5]]
*/

class DSU{
    private:
        vector<int> parent, rank;
    public:
        DSU(int n){
            rank = vector<int>(n,1);
            parent.resize(n);
            for(int i=0;i<n;i++) parent[i]=i;
        }

        int findParent(int x){
            if(x==parent[x]) return x;
            else return parent[x] = findParent(parent[x]);
        }

        void Union(int x, int y){
            int parentOfx = findParent(x);
            int parentOfy = findParent(y);

            if(parentOfx == parentOfy) return;

            if(rank[parentOfx]>rank[parentOfy]) 
                swap(parentOfx,parentOfy);
            parent[parentOfx]=parentOfy;
            if(rank[parentOfx]==rank[parentOfy]) 
                rank[parentOfy]++;
        }
};

class Solution {
public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        for(int i=0;i<edges.size();i++){
            edges[i].push_back(i);
        }
        sort(edges.begin(),edges.end(), [](const vector<int> &a,const vector<int> &b){
            return a[2]<b[2];
        });
        int original_mst = getMst(n,edges,-1);
        vector<int> critical,non_critical;

        for(int i=0;i<edges.size();i++){
            if(original_mst < getMst(n,edges,i)){
                critical.push_back(edges[i][3]);
            }
            else if(original_mst == getMst(n,edges,-1,i)){
                non_critical.push_back(edges[i][3]);
            }
        }

        return {critical,non_critical};
    }
private:
    int getMst(const int n,const vector<vector<int>> &edges, int blockedge, int pre_edge=-1){
        DSU dsu(n);
        int wt=0;

        if(pre_edge != -1){
            wt+=edges[pre_edge][2];
            dsu.Union(edges[pre_edge][0],edges[pre_edge][1]);
        }

        for(int i=0;i<edges.size();i++){
            if(i==blockedge) continue;
            const vector<int> edge = edges[i];
            if(dsu.findParent(edge[0]) == dsu.findParent(edge[1])){
                continue;
            }
            dsu.Union(edge[0],edge[1]);
            wt+=edge[2];
        }

        for (int i = 0; i < n; ++i) {
            if (dsu.findParent(i) != dsu.findParent(0)) 
                return 1e9+7;
        }
        return wt;
        }
    

};