#include<stdio.h>
#include <raylib.h>
#include"ecs.h"

#define MAX_ENTITIES 5

int main(){

    const int screenWidth = 800;
    const int screenHeight  = 600;

    InitWindow(screenWidth, screenHeight, "raylib");
    SetTargetFPS(60);

    Entity *entities[MAX_ENTITIES];
    int max_id = 0;
    
    //create all entities
    for(int i = 0; i < MAX_ENTITIES; i++){
        entities[i] = createEntity(max_id);
	max_id += 1;
    }

    //set components for first entity
    addComponent(entities[0], COMPONENT_POSITION);
    setPosition(&entities[0], 0.0f, 0.0f);

    addComponent(entities[0], COMPONENT_ACCELERATION);
    setAcceleration(&entities[0], 0.1f, 0.2f);
    

    while(!WindowShouldClose()){
	//logic
	for(int i = 0; i < 10; i++){
	    SystemPhysics(entities, 5);
	}

	//drawing
        BeginDrawing();
	ClearBackground(BLACK);

	DrawCircle(getPosition(entities[0]).x, getPosition(entities[0]).y, 20, RED);
	
	EndDrawing();
    }

    //free all entities
    for(int i = 0; i < MAX_ENTITIES; i++){
	destroyEntity(entities[i]);
    }
    
    return 0;
}
