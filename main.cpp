#include <iostream>
#include <list>
#include <queue>
#include <vector>

using namespace std;

struct Kant;
struct Node {
    char m_navn;
    bool m_besokt;
    std::list<Kant> m_kanter;
    Node(char navn) : m_navn(navn), m_besokt(false) { }
    void settinn_kant(const Kant &kant);
};

void Node::settinn_kant(const Kant &kant) {
    m_kanter.emplace(m_kanter.end(), kant);
}

struct Kant {
    float m_vekt;
    Node* m_tilnode;
    Kant(float vekt, Node* tilnode) : m_vekt(vekt), m_tilnode(tilnode) { }
    bool operator > (const Kant& k) const { return m_vekt > k.m_vekt; }
};
struct Path;
struct Graf {
    std::list<Node*> noder;
    Graf() { }
    Node* finn_node(char navn);
    void settinn_node(char navn);
    void settinn_kant(char fra_navn, char til_navn, float vekt);
    float mst();
    Path Dijkstra(char nFra, char nTil);
};

Node* Graf::finn_node(char navn) {
   for(auto n : noder){
       if(n->m_navn == navn) return n;
   }
    return nullptr;
}

void Graf::settinn_node(char navn) {
    auto Newnode = new Node(navn);
    noder.emplace(noder.end(), Newnode);
}

void Graf::settinn_kant(char fra_navn, char til_navn, float vekt) {
    auto fra = finn_node(fra_navn);
    auto til = finn_node(til_navn);

    if(fra && til){
        auto NyKant = new Kant(vekt,til);
        fra->settinn_kant(*NyKant);
    }

}

struct Path{
    Path() = default;
    Path(Kant start){Kanter.push_back(start);}

    std::list<Kant> Kanter;
    float PathCost() const;
    bool operator > (const Path& rightside)const {return PathCost() > rightside.PathCost();};

    void Print(){
        for(auto Kant : Kanter){
            std::cout << Kant.m_tilnode->m_navn;
        }
        std::cout << " (" << PathCost() << ") \n";
    }
};

float Path::PathCost() const{
    float Cost{};
    for(auto Kant: Kanter){
        Cost += Kant.m_vekt;
    }
    return Cost;
}

Path Graf::Dijkstra(char nFra, char nTil){

    std::priority_queue<Path,std::vector<Path>,std::greater<>> Paths;
    auto S = finn_node(nFra);
    auto T = finn_node(nTil);

    //fake first kant S
    Path p{Kant{0,S}};
        Paths.push(p);

    while(!Paths.empty()){
        auto ShortestPath = Paths.top();
        Paths.pop(); // remove top

        if(ShortestPath.Kanter.back().m_tilnode == T ) return ShortestPath;// return shortest path

        ShortestPath.Kanter.back().m_tilnode->m_besokt = true;
        for(auto Kant : ShortestPath.Kanter.back().m_tilnode->m_kanter){
            if(Kant.m_tilnode->m_besokt) continue;
            Path p{ShortestPath};
            p.Kanter.push_back(Kant);
            Paths.push(p);
            p.Print();
        }
    }
}


int main() {
    Graf TestGraf;

    //putt noder i graf
    TestGraf.settinn_node('A');
    TestGraf.settinn_node('B');
    TestGraf.settinn_node('C');
    TestGraf.settinn_node('D');
    TestGraf.settinn_node('E');

    //Bigger graph
    TestGraf.settinn_node('F');
    TestGraf.settinn_node('G');

    //lag kanter med vekt
    TestGraf.settinn_kant('A','B',1);
    TestGraf.settinn_kant('A','C',2);
    TestGraf.settinn_kant('B','C',2);
    TestGraf.settinn_kant('C','D',3);
    TestGraf.settinn_kant('D','E',1);
    TestGraf.settinn_kant('A','E',5);
    TestGraf.settinn_kant('C','E',4);

    //bigger graph
    TestGraf.settinn_kant('D','A',1);
    TestGraf.settinn_kant('F','G',3);
    TestGraf.settinn_kant('G','F',2);
    TestGraf.settinn_kant('E','F',3);
    TestGraf.settinn_kant('A','G',8);
    TestGraf.settinn_kant('A','F',20);

    auto ShortestPath = TestGraf.Dijkstra('A','F');
    std::cout << "Shortest path ";
    ShortestPath.Print();

    return 0;
}
