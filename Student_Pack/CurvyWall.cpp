#include "CurvyWall.h"
bool CurvyWall::isCurvyWall(){
    return true;
}
CurvyWall::CurvyWall(float x, float y):Wall(x){
    this->rad=y;
    this->centerpt=NULL;
    this->endpt=NULL;
    this->startpt=NULL;
}
CurvyWall::CurvyWall(const Particle& st, const Particle& en, const Particle& center):Wall(st,en){
    Particle *x1= new Particle(center);
    this->centerpt=x1;
    this->rad=this->centerpt->FindDistance(*endpt);
    this->ComputeLength();
}
CurvyWall::CurvyWall(const CurvyWall& rhs):Wall(rhs){
    Particle *x3= new Particle(rhs.GetCenter());
    this->centerpt=x3;
    this->rad=rhs.GetRadius();
}
float CurvyWall::GetRadius() const{
    return this->rad;
}
const Particle& CurvyWall::GetCenter() const{
    return *centerpt;
}
void CurvyWall::ComputeLength(){
    float angle1 = (float) atan2(this->GetInitialParticle().Y()-this->GetCenter().Y(),this->GetCenter().X()-this->GetInitialParticle().X());
    float angle2 = (float) atan2(this->GetFinalParticle().Y()-this->GetCenter().Y(),this->GetCenter().X()-this->GetFinalParticle().X());
    float x= (angle1-angle2)* 180 / 3.14159265;
    if(x<0){
        x+=360;
    }
    if(x>=180){
        x-=180;
    }
    this->len=(x/360)*(2*PI*this->rad);
}
Wall* CurvyWall::Clone() const{
    return (Wall*)this;
}
bool CurvyWall::IsContinuousLinear(const Wall& rhs) const{
    return false;
    //CurvyWall* cwall = dynamic_cast<CurvyWall*>(rhs.Clone());
}
const Wall& CurvyWall::operator+(const Wall& rhs) const{
    if(rhs.Clone()->isCurvyWall()){     
        if((this->GetCenter().X()==(((CurvyWall*)rhs.Clone())->GetCenter().X()))&&(this->GetCenter().Y()==(((CurvyWall*)rhs.Clone())->GetCenter().Y()))){       
            if((this->GetInitialParticle().X()==rhs.GetFinalParticle().X())&&(this->GetInitialParticle().Y()==rhs.GetFinalParticle().Y())){    
                const Wall *finn = new CurvyWall(rhs.GetInitialParticle(),this->GetFinalParticle(),((CurvyWall*)rhs.Clone())->GetCenter());
                return *finn;
            }
            else if((this->GetFinalParticle().Y()==rhs.GetInitialParticle().Y())&&(this->GetFinalParticle().X()==rhs.GetInitialParticle().X())){  
                const Wall *finn = new CurvyWall(this->GetInitialParticle(),rhs.GetFinalParticle(),((CurvyWall*)rhs.Clone())->GetCenter());
                return *finn;
            }
            else{
                ApplePearException e;
                throw e;
            }
        }
        else {
            ApplePearException e;
            throw e;
        }
    }
    else{
        ApplePearException e;
        throw e;
    }
    
}
CurvyWall::~CurvyWall(){
    if(this->centerpt){
        delete this->centerpt;
    }
}






