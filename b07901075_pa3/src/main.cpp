#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
struct Node
    {
        int p;
        int rank;
        char color;
    };
struct Edge
{
    int w;
    int s;
    int e;
};
bool edge_compare(const Edge &a,const Edge &b){
        return a.w > b.w;
    }
int Find_Set(int a, Node *nodes){
        if (nodes[a].p != a){
            nodes[a].p = Find_Set(nodes[a].p,nodes);
        }
        return nodes[a].p;
    }
void Link(int x, int y, Node *nodes){
        if (nodes[x].rank > nodes[y].rank){
            nodes[y].p = x;
        }
        else{
            nodes[x].p = y;
            if(nodes[x].rank == nodes[y].rank){
                nodes[y].rank = nodes[y].rank + 1;
            }
        }
    }

void Union(int x, int y,Node *nodes){
        Link(Find_Set(x,nodes),Find_Set(y,nodes),nodes);
    }

void DFS_Visit(Node *nodes,vector<short> *Adj_list,int number_of_node, int u,bool &cycle){
    // vector<short>* Adj_list = new vector<short>[number_of_node]; 
    nodes[u].color = 'G';
    for(int i=0;i<Adj_list[u].size();i++){
        if(nodes[Adj_list[u][i]].color == 'G'){
            // cout<<"Back edge!!!!!";
            cycle = true;
        }
        if(nodes[Adj_list[u][i]].color == 'W'){
            nodes[Adj_list[u][i]].p = u;
            DFS_Visit(nodes,Adj_list,number_of_node,Adj_list[u][i],cycle);
        }
    }
    nodes[u].color = 'B';
    // cout<<"safe";
}

void Loop_Check(Node *nodes,vector<short> *Adj_list,int number_of_node, int u,bool &cycle){  //Adj_node 不確定要怎麼傳
    for(int i = 0; i < number_of_node ; i++){
        nodes[i].color = 'W';
        nodes[i].p = -1;
    }
    // cout<<DFS_Visit(nodes,Adj_list,number_of_node,u);
    DFS_Visit(nodes,Adj_list,number_of_node,u,cycle);
}



int main(int argc, char* argv[]){

    //////////// read the input file /////////////
    char buffer[200];
    char kind_of_graph;
    int _number_of_node,_number_of_edge;
    int w,s,e;
    vector<int> weight,start,end;
    vector<Node> node_vec;
    Node node;
    vector<Edge> edge_vec;
    Edge edge;
    fstream fin(argv[1]);
    if (!fin){
        cout<<"error"<<endl;
    }
    fstream fout;
    fout.open(argv[2],ios::out);
    fin>>kind_of_graph;
    fin>>_number_of_node;
    fin>>_number_of_edge;
    const int number_of_node = _number_of_node;
    const int number_of_edge = _number_of_edge;
    // vector<int> C;
    // C.reserve(size);
    while (fin >> s >> e >> w){
        weight.push_back(w);
        start.push_back(s);
        end.push_back(e);
        //cout<<w<<' '<<s<<' '<<e<<endl;
    }
    
    //////////// the undirectred part ////////////////
    
    
    
    if(kind_of_graph == 'u'){
        if(number_of_edge==number_of_node-1){
            fout<<0;
            fin.close();
            fout.close();
        }
        else{
            Edge edges[number_of_edge];
            Node nodes[number_of_node];

            for(int i=0;i<number_of_edge;i++){
                edges[i].s = start[i];
                edges[i].e = end[i];
                edges[i].w = weight[i];
            }

            for(int i = 0;i < number_of_node;i++){
                nodes[i].p = i;
                nodes[i].rank = 0;
            }

            sort(edges,edges + number_of_edge, edge_compare);
            
            for(int i = 0; i < number_of_edge; i++){
                if(Find_Set(edges[i].s,nodes)!=Find_Set(edges[i].e,nodes)){
                    Union(edges[i].s,edges[i].e,nodes);
                }
                else{
                    edge_vec.push_back(edges[i]);
                    //cout<<edge_vec.size()<<endl;
                }
            }
            int answer_w = 0;
            Edge answer_edge[edge_vec.size() ];
            for(int i=0;i<edge_vec.size();i++){
                answer_w += edge_vec[i].w;
                answer_edge[i] = edge_vec[i];
            }
            fout<<answer_w<<'\n';
            sort(answer_edge,answer_edge+edge_vec.size(),edge_compare);

            for(int i=0;i<edge_vec.size();i++){
                fout<<answer_edge[i].s<<' '<<answer_edge[i].e<<' '<<answer_edge[i].w<<'\n';
            }
        }
    }
    
    if(kind_of_graph == 'd'){
        if(number_of_edge==number_of_node-1){
            fout<<0;
            fin.close();
            fout.close();
        }
        else{
            Edge edges[number_of_edge];
            Node nodes[number_of_node];
            vector<short> Adj_list[number_of_node];
            vector<Edge> edge_answer;

            for(int i = 0;i < number_of_node;i++){
                nodes[i].p = i;
                nodes[i].rank = 0;
            }

            for(int i=0;i<number_of_edge;i++){
                edges[i].s = start[i];
                edges[i].e = end[i];
                edges[i].w = weight[i];
            }

            sort(edges,edges+number_of_edge,edge_compare);

            for(int i = 0; i < number_of_edge; i++){
                if(Find_Set(edges[i].s,nodes)!=Find_Set(edges[i].e,nodes)){
                    Union(edges[i].s,edges[i].e,nodes);
                    Adj_list[edges[i].s].push_back(edges[i].e);
                }
                else{
                    edge_vec.push_back(edges[i]);
                    //cout<<edge_vec.size()<<endl;
                }
            }
            sort(edge_vec.begin(),edge_vec.end(),edge_compare);

            bool cycle = false;

            for(int i = 0; i < edge_vec.size(); i++){
                Adj_list[edge_vec[i].s].push_back(edge_vec[i].e);
                cycle = false;
                Loop_Check(nodes,Adj_list,number_of_node,edge_vec[i].s,cycle);
                if(cycle == true || edge_vec[i].w < 0){
                    edge_answer.push_back(edge_vec[i]);
                    Adj_list[edge_vec[i].s].pop_back();
                }
            }
            
            int answer_w = 0;
            for(int i=0;i<edge_answer.size();i++){
                answer_w += edge_answer[i].w;
            }
            fout<<answer_w<<'\n';

            for(int i=0;i<edge_answer.size();i++){
                fout<<edge_answer[i].s<<' '<<edge_answer[i].e<<' '<<edge_answer[i].w<<'\n';
            }
        }
    }
    
    
    
    // //////////// write the output file ///////////
    
    fin.close();
    fout.close();
    return 0;
}
