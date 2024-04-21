#include"ecs.h"

Entity createStackEntity(int id){
    Entity e;
    e.id = id;
    memset(e.components, 0, sizeof(void*) * COMPONENT_COUNT);
    return e;
}
Entity* createEntity(int id){
    Entity* e = malloc(sizeof(Entity));
    e->id = id;
    for(int i = 0; i < COMPONENT_COUNT; i++){
	e->components[i] = NULL;
    }

    return e;
}

void destroyEntity(Entity* entity){
    freeComponents(entity);
}

void addComponent(Entity *pointer_entity, COMPONENT_INDEX comp){
    if(pointer_entity == NULL){
	printf("Null entity on addComponent\n");
	return;
    }

    if(comp >= COMPONENT_COUNT){
	printf("Invalid component recived on addComponent");
	return;
    }
    
    if(pointer_entity->components[comp] != NULL){
	printf("component already exist!");
	return;
    }    

    switch(comp){
    case COMPONENT_POSITION:
	{
	    comp_position *pos = (comp_position*)malloc(sizeof(comp_position));
	    pos->x = 0;
	    pos->y = 0;
	    if(pos == NULL){
		printf("Failed when allocating position component\n");
		return;
	    }
	
	    pointer_entity->components[comp] = (void*)pos;
	}
        break;
    case COMPONENT_ACCELERATION:
	{
	comp_acceleration* acc = (comp_acceleration*)malloc(sizeof(comp_acceleration));
	acc->x = 0;
	acc->y = 0;
	if(acc == NULL){
	    printf("Failed when allocating acceleration component\n");
	}
	pointer_entity->components[comp] = (void*)acc;
	}
	break;
	
    case COMPONENT_COUNT:
	printf("bad component value");
	break;
    }
}

void removeComponent(Entity* ent, COMPONENT_INDEX comp){
    if(ent == NULL){
	printf("Null entity on addComponent\n");
	return;
    }

    if(comp >= COMPONENT_COUNT){
	printf("Invalid component recived on addComponent");
	return;
    }

    if(ent->components[comp] == NULL){
	printf("component doesnt exist!");
	return;
    }    
    free(ent->components[comp]);
}

void freeComponents(Entity* entity){
    if(entity == NULL){
	printf("Entity void pointer found on freeComponents\n");
	return;
    }
    
    for(int i = 0; i < 2; i++){
	free(entity->components[i]);   
    }
}

void showComponents(const Entity* entity){
    if(((comp_position*)entity->components[0]) == NULL){
	printf("0");
    }else{
	printf("x");
    }

    printf("|");
    
    if(((comp_acceleration*)entity->components[1]) == NULL){
	printf("0");
    }else{
	printf("x");
    }

    printf("\n");
}

void setPosition(Entity** ent, float x, float y){
    if(ent == NULL || *ent == NULL){
	printf("Null entity on setPosition: %d\n", (*ent)->id);
	return;
    }

    if((comp_position*)(*ent)->components[COMPONENT_POSITION] == NULL){
	printf("Entity doesn't have a position component: %d\n", (*ent)->id);
	return;
    }    

    comp_position* position = (comp_position*)(*ent)->components[COMPONENT_POSITION];

    position->x = x;
    position->y = y;
}

comp_position getPosition(const Entity *entity){
    return *(comp_position*)(entity)->components[COMPONENT_POSITION];
}

//#define GET_COMPONENT(ent, comp) (comp*)(*ent)->componenets[COMPONENT_POSITION]

void setAcceleration(Entity** ent, float x, float y){
    if(ent == NULL || *ent == NULL){
	printf("Null entity on onAcceleration: %d\n", (*ent)->id);
	return;
    }

    if((comp_acceleration*)(*ent)->components[COMPONENT_ACCELERATION] == NULL){
	printf("Entity doesn't have a acceleration component: %d\n", (*ent)->id);
	return;
    }
    
    comp_acceleration* acc = (*ent)->components[COMPONENT_ACCELERATION];
    acc->x = x;
    acc->y = y;    
}

comp_acceleration getAcceleration(const Entity *entity){
    return *(comp_acceleration*)(entity)->components[COMPONENT_ACCELERATION];
}

void SystemPhysics(Entity** entity_collection, int size){
    for(int i = 0; i < size; i++){
	Entity* entity = entity_collection[i];

	if(entity->components[COMPONENT_POSITION] != NULL && entity->components[COMPONENT_ACCELERATION] != NULL){
	    setPosition(&entity,
			getPosition(entity).x + getAcceleration(entity).x,
			getPosition(entity).x + getAcceleration(entity).y);
	}
    }
}


