#define SDL_MAIN_HANDLED
#include "stdio.h"
#include "stdlib.h"
#include "sdl.h"
#include "SDL2_gfx-1.0.1/SDL2_gfxPrimitives.h"
#include "time.h"

#include "formulas.h"
#include "wall.h"
#include "robot.h"

int done = 0;


int main(int argc, char *argv[]) {
    SDL_Window *window;
    SDL_Renderer *renderer;

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        return 1;
    }

    window = SDL_CreateWindow("Robot Maze", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, OVERALL_WINDOW_WIDTH, OVERALL_WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    window = SDL_CreateWindow("Robot Maze", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, OVERALL_WINDOW_WIDTH, OVERALL_WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, -1, 0);

    struct Robot robot;
    struct Wall_collection *head = NULL;
    int front_centre_sensor, left_sensor, right_sensor=0;
    clock_t start_time, end_time;
    int msec;
    int crashed = 0;

    // SETUP MAZE
    // You can create your own maze here. line of code is adding a wall.
    // You describe position of top left corner of wall (x, y), then width and height going down/to right
    // Relative positions are used (OVERALL_WINDOW_WIDTH and OVERALL_WINDOW_HEIGHT)
    // But you can use absolute positions. 10 is used as the width, but you can change this.
//    insertAndSetFirstWall(&head, 1,  OVERALL_WINDOW_WIDTH/2, OVERALL_WINDOW_HEIGHT/2, 10, OVERALL_WINDOW_HEIGHT/2);
//    insertAndSetFirstWall(&head, 2,  OVERALL_WINDOW_WIDTH/2-100, OVERALL_WINDOW_HEIGHT/2+100, 10, OVERALL_WINDOW_HEIGHT/2-100);
//    insertAndSetFirstWall(&head, 3,  OVERALL_WINDOW_WIDTH/2-250, OVERALL_WINDOW_HEIGHT/2+100, 150, 10);
//    insertAndSetFirstWall(&head, 4,  OVERALL_WINDOW_WIDTH/2-150, OVERALL_WINDOW_HEIGHT/2, 150, 10);
//    insertAndSetFirstWall(&head, 5,  OVERALL_WINDOW_WIDTH/2-250, OVERALL_WINDOW_HEIGHT/2-200, 10, 300);
//    insertAndSetFirstWall(&head, 6,  OVERALL_WINDOW_WIDTH/2-150, OVERALL_WINDOW_HEIGHT/2-100, 10, 100);
//    insertAndSetFirstWall(&head, 7,  OVERALL_WINDOW_WIDTH/2-250, OVERALL_WINDOW_HEIGHT/2-200, 450, 10);
//    insertAndSetFirstWall(&head, 8,  OVERALL_WINDOW_WIDTH/2-150, OVERALL_WINDOW_HEIGHT/2-100, 250, 10);
//    insertAndSetFirstWall(&head, 9,  OVERALL_WINDOW_WIDTH/2+200, OVERALL_WINDOW_HEIGHT/2-200, 10, 300);
//    insertAndSetFirstWall(&head, 10,  OVERALL_WINDOW_WIDTH/2+100, OVERALL_WINDOW_HEIGHT/2-100, 10, 300);
//    insertAndSetFirstWall(&head, 11,  OVERALL_WINDOW_WIDTH/2+100, OVERALL_WINDOW_HEIGHT/2+200, OVERALL_WINDOW_WIDTH/2-100, 10);
//    insertAndSetFirstWall(&head, 12,  OVERALL_WINDOW_WIDTH/2+200, OVERALL_WINDOW_HEIGHT/2+100, OVERALL_WINDOW_WIDTH/2-100, 10);
//

//    Maze 2
//    insertAndSetFirstWall(&head, 0, 110, 360, 10, 100);
//    insertAndSetFirstWall(&head, 1, 110, 460, 510, 10);
//    insertAndSetFirstWall(&head, 2, 210, 270, 10, 100);
//    insertAndSetFirstWall(&head, 3, 390, 360, 10, 100);
//    insertAndSetFirstWall(&head, 4, 310, 360, 80, 10);
//    insertAndSetFirstWall(&head, 5, 500, 270, 10, 100);
//    insertAndSetFirstWall(&head, 6, 20, 170, 10, 300);
//    insertAndSetFirstWall(&head, 7, 20, 170, 95, 10);
//    insertAndSetFirstWall(&head, 8, 110, 170, 10, 100);
//    insertAndSetFirstWall(&head, 9, 110, 170, 285, 10);
//    insertAndSetFirstWall(&head, 10, 310, 270, 85, 10);
//    insertAndSetFirstWall(&head, 11, 390, 170, 10, 100);
//    insertAndSetFirstWall(&head, 12, 390, 270, 115, 10);
//    insertAndSetFirstWall(&head, 14, 610, 10, 10, 455);
//    insertAndSetFirstWall(&head, 15, 300, 90, 200, 10);
//    insertAndSetFirstWall(&head, 16, 300, 90, 10, 85);
//    insertAndSetFirstWall(&head, 17, 210, 10, 10, 85);
//    insertAndSetFirstWall(&head, 18, 110, 10, 500, 10);
//    insertAndSetFirstWall(&head, 19, 110, 90, 10, 85);
//    insertAndSetFirstWall(&head, 20, 20, 10, 10, 165);
//    insertAndSetFirstWall(&head, 21, 500, 90, 10, 100);


//    Maze 3
    // Borders
//    insertAndSetFirstWall(&head, 1, 0, 0, 8, 480);
//    insertAndSetFirstWall(&head, 1, 70, 472, 470, 8);
//    insertAndSetFirstWall(&head, 1, 0, 0, 640, 8);
//    insertAndSetFirstWall(&head, 1, 632, 0, 8, 480);
//    insertAndSetFirstWall(&head, 1, 70, 330, 8, 200);
//    insertAndSetFirstWall(&head, 1, 140, 300, 8, 100);
//    insertAndSetFirstWall(&head, 1, 210, 330, 8, 200);
//    insertAndSetFirstWall(&head, 1, 280, 250, 8, 290);
//    insertAndSetFirstWall(&head, 1, 50, 0, 8, 80);
//    insertAndSetFirstWall(&head, 1, 210, 0, 8, 70);
//    insertAndSetFirstWall(&head, 1, 210, 130, 8, 125);
//    insertAndSetFirstWall(&head, 1, 280, 70, 8, 80);
//    insertAndSetFirstWall(&head, 1, 410, 0, 8, 153);
//    insertAndSetFirstWall(&head, 1, 465, 260, 8, 105);
//    insertAndSetFirstWall(&head, 1, 535, 260, 8, 220);
//    insertAndSetFirstWall(&head, 1, 210, 250, 70, 8);
//    insertAndSetFirstWall(&head, 1, 90, 130, 125, 8);
//    insertAndSetFirstWall(&head, 1, 280, 70, 70, 8);
//    insertAndSetFirstWall(&head, 1, 280, 145, 130, 8);
//    insertAndSetFirstWall(&head, 1, 422, 260, 120, 8);
//    insertAndSetFirstWall(&head, 1, 280, 145, 130, 8);
//    insertAndSetFirstWall(&head, 1, 300, 200, 360, 8);
//    insertAndSetFirstWall(&head, 1, 8, 80, 50, 8);
//    insertAndSetFirstWall(&head, 1, 410, 85, 168, 8);

//    for (int i = 0; i < 75; i++) {
//        insertAndSetFirstWall(&head, i + 14, 70 - 70 * cos(i * (M_PI/75)), 300 - 70 * sin(i * (M_PI/75)), 8, 8);
//    }
//    for (int i = 0; i < 75; i++) {
//        insertAndSetFirstWall(&head, 0, 140 - 70 * cos(i * (M_PI/75)), 410 + 70 * sin(i * (M_PI/75)), 8, 8);
//    }
//    for (int i = 50; i < 100; i++) {
//        insertAndSetFirstWall(&head, 0,  280 - 70 * cos(i * (M_PI/100))*2, 475 - 70 * sin(i * (M_PI/100))*3.2, 8, 8);
//    }
//    for (int i = 150; i < 175; i++) {
//        insertAndSetFirstWall(&head, 0,  280 - 100 * cos(i * (M_PI/200))*2, 475 - 100 * sin(i * (M_PI/200))*3, 8, 8);
//    }
//    for (int i = 50; i < 80; i++) {
//        insertAndSetFirstWall(&head, 0,  410 - 100 * cos(i * (M_PI/100))*2, 4 + 100 * sin(i * (M_PI/100))*1.4, 8, 8);
//    }
//
//    for (int i = 0; i < 40 ; i++){
//        insertAndSetFirstWall(&head, 0, 210 - i*3, 250 - i*3, 8, 8);
//    }
//    for (int i = 0; i < 40 ; i++){
//        insertAndSetFirstWall(&head, 0, 80 - i*3, 230 - i*3, 8, 8);
//    }
// Maze 4
//insertAndSetFirstWall(&head, 1,  OVERALL_WINDOW_WIDTH/2, OVERALL_WINDOW_HEIGHT/2+120, 10, OVERALL_WINDOW_HEIGHT/4);
//insertAndSetFirstWall(&head, 2,  OVERALL_WINDOW_WIDTH/2-100, OVERALL_WINDOW_HEIGHT/2+120, 10, OVERALL_WINDOW_HEIGHT/4);
//for (float i = 0; i<8; i+=0.1){
//    insertAndSetFirstWall(&head, i,  OVERALL_WINDOW_WIDTH/2+5*i*cos(i*PI/180), OVERALL_WINDOW_HEIGHT/2+120-50*i*sin(i*PI/180), 10, 10);
//    insertAndSetFirstWall(&head, i,  OVERALL_WINDOW_WIDTH/2-100+5*i*cos(i*PI/180), OVERALL_WINDOW_HEIGHT/2+120-50*i*sin(i*PI/180), 10, 10);
//}
//float y = OVERALL_WINDOW_HEIGHT/2+120-50*7.9*sin(7.9*PI/180);
//float x = OVERALL_WINDOW_WIDTH/2+5*7.9*cos(7.9*PI/180);
//for (float i = 0; i<8; i+=0.1){
//    insertAndSetFirstWall(&head, i,  x-5*i*cos(i*PI/180), y-50*i*sin(i*PI/180), 10, 10);
//    insertAndSetFirstWall(&head, i,  x-5*i*cos(i*PI/180)-100, y-50*i*sin(i*PI/180), 10, 10);
//}
//float y2 = y-50*7.9*sin(7.9*PI/180);
//float x2 = x-5*7.9*cos(7.9*PI/180);
//for (float i = 0; i<8; i+=0.1){
//    insertAndSetFirstWall(&head, i,  x2+5*i*cos(i*PI/180), y2-50*i*sin(i*PI/180), 10, 10);
//    insertAndSetFirstWall(&head, i,  x2+5*i*cos(i*PI/180)-100, y2-50*i*sin(i*PI/180), 10, 10);
//}
//float y3 = y2-50*7.9*sin(7.9*PI/180);
//float x3 = x2+5*7.9*cos(7.9*PI/180);
//for (float i = 0; i < 8; i+=.1){
//    insertAndSetFirstWall(&head, i,  x3-5*i*cos(i*PI/180), y3-50*i*sin(i*PI/180), 10, 10);
//    insertAndSetFirstWall(&head, i,  x3-5*i*cos(i*PI/180)-100, y3-50*i*sin(i*PI/180), 10, 10);
//}
//float y4 = y3-50*7.9*sin(7.9*PI/180);
//float x4 = x3-5*7.9*cos(7.9*PI/180);
//for (float i = 0; i<8; i+=0.1){
//    insertAndSetFirstWall(&head, i,  x4+5*i*cos(i*PI/180), y4-50*i*sin(i*PI/180), 10, 10);
//    insertAndSetFirstWall(&head, i,  x4+5*i*cos(i*PI/180)-100, y4-50*i*sin(i*PI/180), 10, 10);
//}
//float y5 = y4-50*7.9*sin(7.9*PI/180);
//float x5 = x4+5*7.9*cos(7.9*PI/180);
//for (float i = 0; i < 8; i+=.1){
//    insertAndSetFirstWall(&head, i,  x5-5*i*cos(i*PI/180), y5-50*i*sin(i*PI/180), 10, 10);
//    insertAndSetFirstWall(&head, i,  x5-5*i*cos(i*PI/180)-100, y5-50*i*sin(i*PI/180), 10, 10);
//}
//float y6 = y5-50*7.9*sin(7.9*PI/180);
//float x6 = x5-5*7.9*cos(7.9*PI/180);
//for (float i = 0; i<6; i+=0.1){
//    insertAndSetFirstWall(&head, i,  x6+5*i*cos(i*PI/180), y6-50*i*sin(i*PI/180), 10, 10);
//    insertAndSetFirstWall(&head, i,  x6+5*i*cos(i*PI/180)-100, y6-50*i*sin(i*PI/180), 10, 10);
//}
// Maze 5
//insertAndSetFirstWall(&head, 1,  OVERALL_WINDOW_WIDTH/2, OVERALL_WINDOW_HEIGHT/2, 10, OVERALL_WINDOW_HEIGHT/2);
//insertAndSetFirstWall(&head, 2,  OVERALL_WINDOW_WIDTH/2-100, OVERALL_WINDOW_HEIGHT/2, 10, OVERALL_WINDOW_HEIGHT/2);
//
//for (int i = 0; i < 100; i++){
//    insertAndSetFirstWall(&head, i,
//                          (i * 2)+OVERALL_WINDOW_WIDTH/2,
//                          OVERALL_WINDOW_HEIGHT/2 - 130*sin(1.8*i * PI/180),
//                          10, 10);
//    insertAndSetFirstWall(&head, i,
//                          (i * 4)+OVERALL_WINDOW_WIDTH/2-100,
//                          OVERALL_WINDOW_HEIGHT/2 - 230*sin(1.8*i * PI/180),
//                          10, 10);
//}
//double x2 = (99 * 2)+OVERALL_WINDOW_WIDTH/2;
//double x22 = (99 * 4)+OVERALL_WINDOW_WIDTH/2-100;
//double y2 = OVERALL_WINDOW_HEIGHT/2 - 130*sin(1.8*99 * PI/180);
//double y22 = OVERALL_WINDOW_HEIGHT/2 - 230*sin(1.8*99 * PI/180);
//
//insertAndSetFirstWall(&head, 1,  x2, y2, 10, OVERALL_WINDOW_HEIGHT/2);
//insertAndSetFirstWall(&head, 2,  x22, y22, 10, OVERALL_WINDOW_HEIGHT/2);
// Maze 6
    insertAndSetFirstWall(&head, 1, 15, 25, 10, 430);
    insertAndSetFirstWall(&head, 1, 75, 145, 10, 60);
    insertAndSetFirstWall(&head, 1, 75, 325, 10, 120);
    insertAndSetFirstWall(&head, 1, 135, 85, 10, 60);
    insertAndSetFirstWall(&head, 1, 135, 325, 10, 60);
    insertAndSetFirstWall(&head, 1, 195, 145, 10, 300);
    insertAndSetFirstWall(&head, 1, 255, 145, 10, 120);
    insertAndSetFirstWall(&head, 1, 315, 25, 10, 60);
    insertAndSetFirstWall(&head, 1, 315, 265, 10, 130);
    insertAndSetFirstWall(&head, 1, 375, 85, 10, 70);
    insertAndSetFirstWall(&head, 1, 375, 265, 10, 120);
    insertAndSetFirstWall(&head, 1, 435, 85, 10, 60);
    insertAndSetFirstWall(&head, 1, 435, 325, 10, 130);
    insertAndSetFirstWall(&head, 1, 495, 145, 10, 180);
    insertAndSetFirstWall(&head, 1, 555, 25, 10, 130);
    insertAndSetFirstWall(&head, 1, 555, 205, 10, 190);
    insertAndSetFirstWall(&head, 1, 615, 25, 10, 430);

    insertAndSetFirstWall(&head, 1, 15, 25, 540, 10);
    insertAndSetFirstWall(&head, 1, 75, 85, 190, 10);
    insertAndSetFirstWall(&head, 1, 435, 85, 60, 10);
    insertAndSetFirstWall(&head, 1, 315, 145, 60, 10);
    insertAndSetFirstWall(&head, 1, 495, 145, 60, 10);
    insertAndSetFirstWall(&head, 1, 75, 205, 60, 10);
    insertAndSetFirstWall(&head, 1, 315, 205, 180, 10);
    insertAndSetFirstWall(&head, 1, 15, 265, 120, 10);
    insertAndSetFirstWall(&head, 1, 255, 265, 60, 10);
    insertAndSetFirstWall(&head, 1, 375, 265, 60, 10);
    insertAndSetFirstWall(&head, 1, 195, 325, 60, 10);
    insertAndSetFirstWall(&head, 1, 255, 385, 60, 10);
    insertAndSetFirstWall(&head, 1, 495, 385, 60, 10);
    insertAndSetFirstWall(&head, 1, 75, 445, 540, 10);


    setup_robot(&robot);
    updateAllWalls(head, renderer);

    SDL_Event event;
    while(!done){
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        SDL_RenderClear(renderer);

        //Move robot based on user input commands/auto commands
        if (robot.auto_mode == 1)
            robotAutoMotorMove(&robot, front_centre_sensor, left_sensor, right_sensor);
        robotMotorMove(&robot, crashed);

        //Check if robot reaches endpoint. and check sensor values
        if (checkRobotReachedEnd(&robot, OVERALL_WINDOW_WIDTH, OVERALL_WINDOW_HEIGHT/2+100, 10, 100)){
            end_time = clock();
            msec = (end_time-start_time) * 1000 / CLOCKS_PER_SEC;
            robotSuccess(&robot, msec);
        }
        else if(crashed == 1 || checkRobotHitWalls(&robot, head)){
            robotCrash(&robot);
            crashed = 1;
        }
        //Otherwise compute sensor information
        else {
            front_centre_sensor = checkRobotSensorFrontCentreAllWalls(&robot, head);
            if (front_centre_sensor>0)
                printf("Getting close on the centre. Score = %d\n", front_centre_sensor);

            left_sensor = checkRobotSensorLeftAllWalls(&robot, head);
            if (left_sensor>0)
                printf("Getting close on the left. Score = %d\n", left_sensor);

            right_sensor = checkRobotSensorRightAllWalls(&robot, head);
            if (right_sensor>0)
                printf("Getting close on the right. Score = %d\n", right_sensor);
        }
        robotUpdate(renderer, &robot);
        updateAllWalls(head, renderer);

        // Check for user input
        SDL_RenderPresent(renderer);
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                done = 1;
            }
            const Uint8 *state = SDL_GetKeyboardState(NULL);
            if(state[SDL_SCANCODE_UP] && robot.direction != DOWN){
                robot.direction = UP;
            }
            if(state[SDL_SCANCODE_DOWN] && robot.direction != UP){
                robot.direction = DOWN;
            }
            if(state[SDL_SCANCODE_LEFT] && robot.direction != RIGHT){
                robot.direction = LEFT;
            }
            if(state[SDL_SCANCODE_RIGHT] && robot.direction != LEFT){
                robot.direction = RIGHT;
            }
            if(state[SDL_SCANCODE_SPACE]){
                setup_robot(&robot);
            }
            if(state[SDL_SCANCODE_RETURN]){
                robot.auto_mode = 1;
                start_time = clock();
            }
        }

        SDL_Delay(120);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    printf("DEAD\n");
    return 0;
}
