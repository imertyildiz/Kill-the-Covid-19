#include "Particle.h"

Particle::Particle(float x, float y){
    this->x_coordinate=x;
    this->y_coordinate=y;
}
Particle::Particle(const Particle& rhs){
    this->x_coordinate=rhs.X();
    this->y_coordinate=rhs.Y();
}
float Particle::X() const{
    return this->x_coordinate;
}
float Particle::Y() const{
    return this->y_coordinate;
}
float Particle::FindDistance(const Particle& rhs)const{
    float xminus,yminus;
    if(this->x_coordinate >= rhs.X()){
        xminus=(this->x_coordinate)-(rhs.X());
    }
    else{
        xminus=(rhs.X())-(this->x_coordinate);
    }
    if((this->y_coordinate) >= (rhs.Y())){
        yminus=(this->y_coordinate)-(rhs.Y());
    }
    else{
        yminus=(rhs.Y())-(this->y_coordinate);
    }
    return sqrt((xminus*xminus)+(yminus*yminus));
}
bool Particle::operator==(const Particle& rhs) const{
    return ((abs(this->x_coordinate-rhs.X())<EPSILON) && (abs(this->y_coordinate-rhs.Y())<EPSILON));
}
ostream& operator<<(ostream& os, const Particle& rhs){
    os<<"("<<rhs.X()<<","<<rhs.Y()<<")";
    return os;
}