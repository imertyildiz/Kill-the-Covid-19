#include "Circular.h"

Circular::Circular(int a, float b):MicroOrganism(a,*(new const vector<Wall*>)){
    this->radius=b;
}
Circular::~Circular(){
    for(int i=0;i<edges.size();i++){
        delete edges[i];
    }
    edges.clear();
    this->connectedCell=NULL;
    this->isConnected=false;
}
void Circular::ConnectToCell(Cell * const rhs){
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
bool Circular::DoesFitInto(const Cell& rhs) const{
    bool iscircle=false;
    for (int i = 0; i < rhs.GetCellWall().size()-1; i++){
        if((dynamic_cast<CurvyWall*>(rhs.GetCellWall().at(i)))&&(dynamic_cast<CurvyWall*>(rhs.GetCellWall().at(i+1)))){
            if(((CurvyWall*)rhs.GetCellWall()[i])->GetCenter()==((CurvyWall*)rhs.GetCellWall()[i+1])->GetCenter()){
                iscircle=true;
            }
            else{
                iscircle=false;
            }
        }
        else{
            iscircle=false;
        }
    }
    if(iscircle){
        float ax;
        ax=((CurvyWall*)rhs.GetCellWall()[0])->GetCenter().FindDistance(rhs.GetCellWall()[0]->GetInitialParticle());
        if((this->radius==ax)){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}
void Circular::React(){
    vector<Wall*> xxx;
    for (int i = 0; i < this->connectedCell->GetCellWall().size(); i++){
        Particle *st,*en;
        float x1,x2,y1,y2;
        x1=2*(this->connectedCell->GetCellWall()[i]->GetInitialParticle().X()-((CurvyWall*)this->connectedCell->GetCellWall()[i])->GetCenter().X())+((CurvyWall*)this->connectedCell->GetCellWall()[i])->GetCenter().X();
        y1=2*(this->connectedCell->GetCellWall()[i]->GetInitialParticle().Y()-((CurvyWall*)this->connectedCell->GetCellWall()[i])->GetCenter().Y())+((CurvyWall*)this->connectedCell->GetCellWall()[i])->GetCenter().Y();
        x2=2*(this->connectedCell->GetCellWall()[i]->GetFinalParticle().X()-((CurvyWall*)this->connectedCell->GetCellWall()[i])->GetCenter().X())+((CurvyWall*)this->connectedCell->GetCellWall()[i])->GetCenter().X();
        y2=2*(this->connectedCell->GetCellWall()[i]->GetFinalParticle().Y()-((CurvyWall*)this->connectedCell->GetCellWall()[i])->GetCenter().Y())+((CurvyWall*)this->connectedCell->GetCellWall()[i])->GetCenter().Y();
        st= new Particle(x1,y1);
        en= new Particle(x2,y2);
        xxx.push_back(new CurvyWall(*st,*en,((CurvyWall*)this->connectedCell->GetCellWall()[i])->GetCenter()));
        delete st;
        delete en;
    }
    this->connectedCell->RenewCellWall(xxx);
    for(int i=0;i<xxx.size();i++){
        delete xxx[i];
    }
    xxx.clear();
}
bool Circular::DoesContain(const Particle& rhs) const{
    if(this->isConnected){
        float x=((CurvyWall*)(this->edges[0]))->GetCenter().X();
        float y=((CurvyWall*)(this->edges[0]))->GetCenter().Y();
        if ( ( (rhs.X()<=x) && (rhs.X()>=(-x)) ) && ( (rhs.Y()<=y) && (rhs.Y()>=y) ) ){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}