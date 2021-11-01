#include <iostream>
#include <list>
#include <queue>

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
struct Graf {
    std::list<Node*> noder;
    Graf() { }
    Node* finn_node(char navn);
    void settinn_node(char navn);
    void settinn_kant(char fra_navn, char til_navn, float vekt);
    float mst();
};

Node *Graf::finn_node(char navn) {
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

    auto NyKant = new Kant(vekt,til);
    fra->settinn_kant(*NyKant);

}

int main() {
    Graf TestGraf;

    //putt noder i graf
    TestGraf.settinn_node('A');
    TestGraf.settinn_node('B');
    TestGraf.settinn_node('C');
    TestGraf.settinn_node('D');
    TestGraf.settinn_node('E');

    //lag kanter med vekt
    TestGraf.settinn_kant('A','B',1);
    TestGraf.settinn_kant('A','C',2);
    TestGraf.settinn_kant('B','C',2);
    TestGraf.settinn_kant('C','D',3);
    TestGraf.settinn_kant('D','E',1);
    TestGraf.settinn_kant('A','E',5);
    TestGraf.settinn_kant('C','E',4);





    return 0;
}
