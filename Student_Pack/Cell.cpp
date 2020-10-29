#include "Cell.h"
Cell::Cell(int x, const vector<Wall*>& y, Tissue* z){
    this->id=x;
    for(int i=0;i<y.size();i++){
        if(dynamic_cast<CurvyWall*>(y.at(i))){
            this->shape.push_back(new CurvyWall(y.at(i)->GetInitialParticle(),y.at(i)->GetFinalParticle(),((CurvyWall*)y.at(i))->GetCenter()));
        }
        else{
            this->shape.push_back(new Wall(y.at(i)->GetInitialParticle(),y.at(i)->GetFinalParticle()));
        }
        
    }
    this->typeCell=z;
}
Cell::Cell(const Cell& rhs){
    this->id=rhs.id;
    for(int i=0;i<rhs.GetCellWall().size();i++){
        if(dynamic_cast<CurvyWall*>(rhs.GetCellWall().at(i))){
            this->shape.push_back(new CurvyWall(rhs.GetCellWall().at(i)->GetInitialParticle(),rhs.GetCellWall().at(i)->GetFinalParticle(),((CurvyWall*)rhs.GetCellWall().at(i))->GetCenter()));
        }
        else{
            this->shape.push_back(new Wall(rhs.GetCellWall().at(i)->GetInitialParticle(),rhs.GetCellWall().at(i)->GetFinalParticle()));
        }    
    }
    this->typeCell=rhs.typeCell;
}
int Cell::GetCellID() const{
    return this->id;
}
Tissue* Cell::GetTissue() const{
    return this->typeCell;
}
const vector<Wall*>& Cell::GetCellWall() const{
    return (this->shape);
}
void Cell::RenewCellWall(vector<Wall*>& rhs){
    for(int i=0;i<rhs.size();i++){
        delete shape[i];
    }
    this->shape.clear();
    for(int a=0;a<rhs.size();a++){
        if(dynamic_cast<CurvyWall*>(rhs.at(a))){
            this->shape.push_back(new CurvyWall(rhs.at(a)->GetInitialParticle(),rhs.at(a)->GetFinalParticle(),((CurvyWall*)rhs.at(a))->GetCenter()));
        }
        else{
            this->shape.push_back(new Wall(rhs.at(a)->GetInitialParticle(),rhs.at(a)->GetFinalParticle()));
        }    
    }
    
}
void Cell::StrengthenCellWall(){
    //vector<Wall*> xxx;
    int ix=0;
    int ah=this->shape.size();
    for(int i=0;i<ah;i++){
        CurvyWall* cwall = dynamic_cast<CurvyWall*>((this->shape)[i]);
        if(cwall){
	        //curvywall için code
            try {
                if(i==0){
                    this->shape.push_back(new CurvyWall(*((CurvyWall*)(this->shape)[i])));
                }
                else if (dynamic_cast<CurvyWall*>(this->shape.at(this->shape.size()-1))){
                    if(((CurvyWall*)this->shape.at(this->shape.size()-1))->GetCenter()==((CurvyWall*)(this->shape)[i])->GetCenter()){
                        const Wall* apple_pear = &(*((CurvyWall*)this->shape.at(this->shape.size()-1)) + *((CurvyWall*)(this->shape)[i]));
                        delete shape[shape.size()-1];
                        this->shape.pop_back();
                        this->shape.push_back(apple_pear->Clone());
                        continue;
                    }
                    else{
                        this->shape.push_back(new CurvyWall(*((CurvyWall*)(this->shape)[i])));
                    }
                    
                }
                else{
                    this->shape.push_back(new CurvyWall(*((CurvyWall*)(this->shape)[i])));
                }
            }
	        catch (ApplePearException e) {
	        	continue;
            }
        }
        else{
	        //wall için code
            try {
                    if(i==0){
                        int a=1;
                        int b=0;
                        while(a){

                            if(this->shape.at(b)->IsContinuousLinear(*((this->shape)[b+1]))){
                                b++;
                            }
                            else{
                                this->shape.push_back(new Wall(*(this->shape)[b+1]));
                                a=0;
                                i=(b+1);
                            }
                        }
                    }
                    else{
                        
                        if(this->shape.at(this->shape.size()-1)->IsContinuousLinear(*((this->shape).at(i)->Clone()))){
                           const Wall* apple_pear = &(*(this->shape.at(this->shape.size()-1))+*((this->shape).at(i)));
                           delete shape[shape.size()-1];
                           this->shape.pop_back();
                           this->shape.push_back(apple_pear->Clone());
                           continue;
                        }
                        else{
                           this->shape.push_back(new Wall(*(this->shape)[i]));

                           continue;
                        }
                    }

            }
	        catch (ApplePearException e) {
	        	continue;
            }
        }
    }
    while(ah){
        delete shape[0];
        shape.erase(shape.begin());
        ah--;
    }
    /*
    for(int i=0;i<shape.size();i++){
        if(shape[i]!=NULL){
            delete shape[i]->Clone();
        }
    }
    shape.clear();
    for(int a=0;a<xxx.size();a++){
        this->shape.push_back(xxx[a]);
    }*/
}
Cell::~Cell(){
    for(int i=0;i<shape.size();i++){
        delete shape[i];
    }
    this->shape.clear();
}
ostream& operator<<(ostream& os , const Cell& rhs){    
    if(rhs.shape.size()==1){
        os<<rhs.shape.at(0)->Clone()->GetInitialParticle();
    }
    for(int i=0;i<rhs.shape.size()-1;i++){
        os<<(((rhs.shape).at(i)->Clone())->GetInitialParticle())<<"-";
        if(i==(rhs.shape.size()-2)){
            os<<rhs.shape.at(i)->Clone()->GetFinalParticle();
            break;
        }
    }
    return os;
}

/*
void Cell::StrengthenCellWall(){
    vector<Wall*> xxx;
    int ix=0;
    int ah=this->shape.size();
    for(int i=0;i<ah;i++){
        CurvyWall* cwall = dynamic_cast<CurvyWall*>((this->shape)[i]);
        if(cwall){
	        //curvywall için code
            try {
                if(i==0){
                    xxx.push_back((CurvyWall*)(this->shape)[i]);
                }
                else if (dynamic_cast<CurvyWall*>(xxx.at(xxx.size()-1))){
                    if(((CurvyWall*)xxx.at(xxx.size()-1))->GetCenter()==((CurvyWall*)(this->shape)[i])->GetCenter()){
                        const Wall* apple_pear = &(*((CurvyWall*)xxx.at(xxx.size()-1)) + *((CurvyWall*)(this->shape)[i]));
                        xxx.pop_back();
                        xxx.push_back(apple_pear->Clone());
                        continue;
                    }
                    else{
                        xxx.push_back(((CurvyWall*)(this->shape)[i]));
                    }
                    
                }
                else{
                    xxx.push_back(((CurvyWall*)(this->shape)[i]));
                }
            }
	        catch (ApplePearException e) {
	        	continue;
            }
        }
        else{
	        //wall için code
            try {
                    if(i==0){
                        int a=1;
                        int b=0;
                        while(a){

                            if(this->shape.at(b)->IsContinuousLinear(*((this->shape).at(b+1)->Clone()))){
                                b++;
                            }
                            else{
                                xxx.push_back((this->shape).at(b+1)->Clone());
                                a=0;
                                i=(b+1);
                            }
                        }
                    }
                    else{
                        
                        if(xxx.at(xxx.size()-1)->IsContinuousLinear(*((this->shape).at(i)->Clone()))){
                           const Wall* apple_pear = &(*(xxx.at(xxx.size()-1))+*((this->shape).at(i)));
                           xxx.pop_back();
                           xxx.push_back(apple_pear->Clone());
                           continue;
                        }
                        else{
                           xxx.push_back((this->shape).at(i)->Clone());

                           continue;
                        }
                    }

            }
	        catch (ApplePearException e) {
	        	continue;
            }
        }
    }/*
    for(int i=0;i<shape.size();i++){
        if(shape[i]!=NULL){
            delete shape[i]->Clone();
        }
    }
    shape.clear();
    for(int a=0;a<xxx.size();a++){
        this->shape.push_back(xxx[a]);
    }*/


