#ifndef ECS_H
#define ECS_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef void* component_t;

typedef struct{
    float x;
    float y;
}comp_position;

typedef struct{
    float x;
    float y;
}comp_acceleration;

typedef enum ENUM_COMPONENTS{
    COMPONENT_POSITION = 0,
    COMPONENT_ACCELERATION,
    COMPONENT_COUNT
}COMPONENT_INDEX;

typedef struct Entity_s{    
    int id;
    component_t components[COMPONENT_COUNT];
}Entity;

Entity createStackEntity(int);
Entity* createEntity(int);
void destroyEntity(Entity*);

void addComponent(Entity*, COMPONENT_INDEX);
void removeComponent(Entity*, COMPONENT_INDEX);
void freeComponents(Entity*);
void showComponents(const Entity *);

//Physics components and systems

void setPosition(Entity **, float, float);
comp_position getPosition(const Entity *);

void setAcceleration(Entity **, float, float);
comp_acceleration getAcceleration(const Entity *);

void SystemPhysics(Entity **, int);
#endif
