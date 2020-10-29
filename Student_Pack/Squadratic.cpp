#include"Squadratic.h"

Squadratic::Squadratic(int a, float b):MicroOrganism(a,*(new vector<Wall*>)){
    this->kenar=b;
}
Squadratic::Squadratic(const Squadratic& rhs):MicroOrganism(rhs.id,rhs.edges){
    this->kenar=rhs.kenar;
    this->connectedCell=rhs.connectedCell;
    this->isConnected=rhs.isConnected;
}
Squadratic::~Squadratic(){
    for(int i=0;i<edges.size();i++){
        delete edges[i];
    }
    edges.clear();
    this->connectedCell=NULL;
    this->isConnected=false;
}
void Squadratic::ConnectToCell(Cell* const rhs){
    this->connectedCell=rhs;
    for(int i=0;i<rhs->GetCellWall().size();i++){
        if(dynamic_cast<CurvyWall*>(rhs->GetCellWall().at(i))){
            this->edges.push_back(new CurvyWall(rhs->GetCellWall()[i]->GetInitialParticle(),rhs->GetCellWall()[i]->GetFinalParticle(),((CurvyWall*)rhs->GetCellWall()[i])->GetCenter()));
        }
        else{
            this->edges.push_back(new Wall(rhs->GetCellWall()[i]->GetInitialParticle(),rhs->GetCellWall()[i]->GetFinalParticle()));
        }
    }
    this->isConnected=true;
}
bool Squadratic::DoesFitInto(const Cell& rhs)const{
    Cell *ali= new Cell(rhs);
    bool allok=false;
    ali->StrengthenCellWall();
    float cx = ali->GetCellWall()[0]->GetInitialParticle().FindDistance(ali->GetCellWall()[0]->GetFinalParticle());
    delete ali;
    if(abs(cx-this->kenar)<0.01){
        return true;
    }
    else{
        return false;
    }
    
}
void Squadratic::React(){

}