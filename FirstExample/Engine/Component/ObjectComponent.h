
#ifndef CLUTCH_OBJECTCOMPONENT_H
#define CLUTCH_OBJECTCOMPONENT_H


class ObjectComponent {
    public:
    virtual void onTick(float deltaTime) = 0;
    virtual void tick(float deltaTime);
};


#endif //CLUTCH_OBJECTCOMPONENT_H
