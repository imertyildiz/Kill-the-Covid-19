#include"MicroOrganism.h"
MicroOrganism::MicroOrganism(int a, const vector<Wall*>& edges){
    this->id=a;
    for(int i=0;i<edges.size();i++){
        if(dynamic_cast<CurvyWall*>(edges.at(i))){
            this->edges.push_back(new CurvyWall(edges.at(i)->GetLength(),((CurvyWall*)edges.at(i))->GetRadius()));
        }
        else{
            this->edges.push_back(new Wall(edges.at(i)->GetLength()));
        }
        
    }
    this->isConnected=false;
    const vector<Wall*> *x;
    x=&edges;
    delete x;

}
ostream& operator<<(ostream& os, const MicroOrganism& rhs){
    if(rhs.isConnected){
        os<<"The microorganism <"<<rhs.id<<"> was successfully placed into the cell <"<<rhs.connectedCell->GetCellID()<<">.";
    }
    else{
        os<<"The microorganism <"<<rhs.id<<"> could not be placed into any cell!";
    }
    return os;
}
MicroOrganism::~MicroOrganism(){

}

