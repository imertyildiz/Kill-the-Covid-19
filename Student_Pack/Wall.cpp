#include "Wall.h"
bool Wall::isCurvyWall(){
    return false;
}
Wall::Wall(float x){
    this->len=x;
    this->endpt=NULL;
    this->startpt=NULL;
}

Wall::Wall(const Particle& par1, const Particle& par2){
    Particle *x1= new Particle(par1);
    Particle *x2= new Particle(par2);    
    this->startpt=x1;
    this->endpt=x2;
    this->len=par1.FindDistance(par2);
}

Wall::Wall(const Wall& rhs){
    Particle *x1= new Particle(rhs.GetInitialParticle());
    Particle *x2 = new Particle(rhs.GetFinalParticle());
    this->startpt=x1;
    this->endpt=x2;
    this->len=rhs.GetLength();
}

const Particle& Wall::GetInitialParticle() const{
    return *startpt;
}

const Particle& Wall::GetFinalParticle() const{
    return *endpt;
}

// Aciyi derece olarak tutuyorsun.
float Wall::FindAngleBetween(const Wall& rhs) const{
    float angle1 = (float) atan2(this->GetFinalParticle().Y()-this->GetInitialParticle().Y(),this->GetInitialParticle().X() -this->GetFinalParticle().X());
    float angle2 = (float) atan2(rhs.GetFinalParticle().Y()-rhs.GetInitialParticle().Y(),rhs.GetInitialParticle().X()-rhs.GetFinalParticle().X());
    float x= (angle1-angle2)* 180 / 3.14159265;
    if(x>=180){
        x-=180;
    }
    return x;
}

float Wall::GetLength() const{
    return this->len;    
}

void Wall::ComputeLength(){
    this->len=this->GetInitialParticle().FindDistance(this->GetFinalParticle());
}

Wall* Wall::Clone() const{
    return (Wall*)this;
}

bool Wall::IsContinuousLinear(const Wall& rhs) const{
    if(!(rhs.Clone()->isCurvyWall())){
        float slope1;
        float slope2;
        bool slopeseq;
        if(this->GetFinalParticle().X()-this->GetInitialParticle().X()==0){
            slope1=3164654488.6654;
        }
    
        else{
            if((this->GetFinalParticle().Y()-this->GetInitialParticle().Y())==0){
                slope1 = 0;
            }
            else{
                slope1=(this->GetFinalParticle().Y()-this->GetInitialParticle().Y())/(this->GetFinalParticle().X()-this->GetInitialParticle().X());
            }
        }
    
        if(rhs.GetFinalParticle().X()-rhs.GetInitialParticle().X()==0){
            slope2=3164654488.6654;
        }
    
        else{
            if((rhs.GetFinalParticle().Y()-rhs.GetInitialParticle().Y())==0){
                slope2=0;
            }
            else{
                slope2=(rhs.GetFinalParticle().Y()-rhs.GetInitialParticle().Y())/(rhs.GetFinalParticle().X()-rhs.GetInitialParticle().X());
            }
        }
    
        if ((slope1-slope2)==0){
            slopeseq=true;
        }
        else{
            slopeseq=false;
        }
        bool attach=(((this->GetInitialParticle().X()==rhs.GetFinalParticle().X())&&(this->GetInitialParticle().Y()==rhs.GetFinalParticle().Y()))||((this->GetFinalParticle().Y()==rhs.GetInitialParticle().Y())&&(this->GetFinalParticle().X()==rhs.GetInitialParticle().X())));
        return (attach && slopeseq);
    }
    else{
        return false;
    }
    
}
const Wall& Wall::operator+(const Wall& rhs) const{

    if(!(rhs.Clone()->isCurvyWall())){

        if(((this->GetInitialParticle().X()==rhs.GetFinalParticle().X())&&(this->GetInitialParticle().Y()==rhs.GetFinalParticle().Y()))||((this->GetFinalParticle().Y()==rhs.GetInitialParticle().Y())&&(this->GetFinalParticle().X()==rhs.GetInitialParticle().X()))){
            if((this->GetInitialParticle().X()==rhs.GetFinalParticle().X())&&(this->GetInitialParticle().Y()==rhs.GetFinalParticle().Y())){
                Wall *fin= new Wall(rhs.GetInitialParticle(),this->GetFinalParticle());
                return *fin;
                
            }
            else if((this->GetFinalParticle().Y()==rhs.GetInitialParticle().Y())&&(this->GetFinalParticle().X()==rhs.GetInitialParticle().X())){
                Wall *fin= new Wall(this->GetInitialParticle(),rhs.GetFinalParticle());
                return *fin;
            }
            else{
                ApplePearException e;
                throw e;
            }
        }
        else{
            ApplePearException e;
            throw e;
        }
    }
    else{
        ApplePearException e;
        throw e;
        
    }
}
Wall::~Wall(){
    if(this->startpt){
        delete this->startpt;
    }
    if(this->endpt){
        delete this->endpt;
    }
}
