#include "robot.h"

void setup_robot(struct Robot *robot){
//    Maze 1
//    robot->x = OVERALL_WINDOW_WIDTH/2-50;
//    robot->y = OVERALL_WINDOW_HEIGHT-50;
//    robot->true_x = OVERALL_WINDOW_WIDTH/2-50;
//    robot->true_y = OVERALL_WINDOW_HEIGHT-50;
//    Maze 2
//    robot->x = 60;
//    robot->y = 430;
//    robot->true_x = 60;
//    robot->true_y = 430;
    // Maze 3
//    robot->x = 25;
//    robot->y = 450;
//    robot->true_x = 25;
//    robot->true_y = 450;
    // Maze 4
//    robot->x = OVERALL_WINDOW_WIDTH/2-40;
//    robot->y = OVERALL_WINDOW_HEIGHT-40;
//    robot->true_x = OVERALL_WINDOW_WIDTH/2-40;
//    robot->true_y = OVERALL_WINDOW_HEIGHT-40;
    // Maze 5
//    robot->x = OVERALL_WINDOW_WIDTH/2-50;
//    robot->y = OVERALL_WINDOW_HEIGHT-50;
//    robot->true_x = OVERALL_WINDOW_WIDTH/2-50;
//    robot->true_y = OVERALL_WINDOW_HEIGHT-50;
    // Maze 6
    robot->x = 40;
    robot->y = 410;
    robot->true_x = 40;
    robot->true_y = 410;

    robot->width = ROBOT_WIDTH;
    robot->height = ROBOT_HEIGHT;
    robot->direction = 0;
    robot->angle = 0;
    robot->currentSpeed = 0;
    robot->crashed = 0;
    robot->auto_mode = 0;

    printf("Press arrow keys to move manually, or enter to move automatically\n\n");
}
int robot_off_screen(struct Robot * robot){
    if(robot->x < 0 || robot-> y < 0){
        return 0;
    }
    if(robot->x > OVERALL_WINDOW_WIDTH || robot->y > OVERALL_WINDOW_HEIGHT){
        return 0;
    }
    return 1;
}

int checkRobotHitWall(struct Robot * robot, struct Wall * wall) {

    int overlap = checkOverlap(robot->x,robot->width,robot->y,robot->height,
                 wall->x,wall->width,wall->y, wall->height);

    return overlap;
}

int checkRobotHitWalls(struct Robot * robot, struct Wall_collection * head) {
   struct Wall_collection *ptr = head;
   int hit = 0;

   while(ptr != NULL) {
      hit = (hit || checkRobotHitWall(robot, &ptr->wall));
      ptr = ptr->next;
   }
   return hit;

}

int checkRobotReachedEnd(struct Robot * robot, int x, int y, int width, int height){

    int overlap = checkOverlap(robot->x,robot->width,robot->y,robot->height,
                 x,width,y,height);

    return overlap;
}

void robotCrash(struct Robot * robot) {
    robot->currentSpeed = 0;
    if (!robot->crashed)
        printf("Ouchies!!!!!\n\nPress space to start again\n");
    robot->crashed = 1;
}

void robotSuccess(struct Robot * robot, int msec) {
    robot->currentSpeed = 0;
    if (!robot->crashed){
        printf("Success!!!!!\n\n");
        printf("Time taken %d seconds %d milliseconds \n", msec/1000, msec%1000);
        printf("Press space to start again\n");
    }
    robot->crashed = 1;
}

int checkRobotSensor(int x, int y, int sensorSensitivityLength, struct Wall * wall)  {
    //viewing_region of sensor is a square of 2 pixels * chosen length of sensitivity
    int overlap = checkOverlap(x,2,y,sensorSensitivityLength,
                 wall->x,wall->width,wall->y, wall->height);

    return overlap;
}

int checkRobotSensorFrontCentreAllWalls(struct Robot * robot, struct Wall_collection * head) {
    struct Wall_collection *ptr, *head_store;
    int i;
    double xDir, yDir;
    int robotCentreX, robotCentreY, xTL, yTL;
    int score, hit;

    int sensorSensitivityLength =  floor(SENSOR_VISION/5);

    head_store = head;
    robotCentreX = robot->x+ROBOT_WIDTH/2;
    robotCentreY = robot->y+ROBOT_HEIGHT/2;
    score = 0;

    for (i = 0; i < 5; i++)
    {
        ptr = head_store;
        //xDir = round(robotCentreX+(ROBOT_WIDTH/2-2)*cos((robot->angle)*PI/180)-(-ROBOT_HEIGHT/2-SENSOR_VISION+sensorSensitivityLength*i)*sin((robot->angle)*PI/180));
        //yDir = round(robotCentreY+(ROBOT_WIDTH/2-2)*sin((robot->angle)*PI/180)+(-ROBOT_HEIGHT/2-SENSOR_VISION+sensorSensitivityLength*i)*cos((robot->angle)*PI/180));
        xDir = round(robotCentreX-(-ROBOT_HEIGHT/2-SENSOR_VISION+sensorSensitivityLength*i)*sin((robot->angle)*PI/180));
        yDir = round(robotCentreY+(-ROBOT_HEIGHT/2-SENSOR_VISION+sensorSensitivityLength*i)*cos((robot->angle)*PI/180));
        xTL = (int) xDir;
        yTL = (int) yDir;
        hit = 0;

        while(ptr != NULL) {
            hit = (hit || checkRobotSensor(xTL, yTL, sensorSensitivityLength, &ptr->wall));
            ptr = ptr->next;
        }
        if (hit)
            score = i;
    }
    return score;
}

int checkRobotSensorLeftAllWalls(struct Robot * robot, struct Wall_collection * head) {
    struct Wall_collection *ptr, *head_store;
    int i;
    double xDir, yDir;
    int robotCentreX, robotCentreY, xTL, yTL;
    int score, hit;
    int sensorSensitivityLength;

    head_store = head;
    robotCentreX = robot->x+ROBOT_WIDTH/2;
    robotCentreY = robot->y+ROBOT_HEIGHT/2;
    score = 0;
    sensorSensitivityLength =  floor(SENSOR_VISION/5);

    for (i = 0; i < 5; i++)
    {
        ptr = head_store;
        //xDir = round(robotCentreX+(-ROBOT_WIDTH/2)*cos((robot->angle)*PI/180)-(-ROBOT_HEIGHT/2-SENSOR_VISION+sensorSensitivityLength*i)*sin((robot->angle)*PI/180));
        //yDir = round(robotCentreY+(-ROBOT_WIDTH/2)*sin((robot->angle)*PI/180)+(-ROBOT_HEIGHT/2-SENSOR_VISION+sensorSensitivityLength*i)*cos((robot->angle)*PI/180));
        xDir = round(robotCentreX+(+ROBOT_WIDTH/2)*cos((robot->angle-90)*PI/180)-(-ROBOT_HEIGHT/2-SENSOR_VISION+sensorSensitivityLength*i)*sin((robot->angle-90)*PI/180));
        yDir = round(robotCentreY+(+ROBOT_WIDTH/2)*sin((robot->angle-90)*PI/180)+(-ROBOT_HEIGHT/2-SENSOR_VISION+sensorSensitivityLength*i)*cos((robot->angle-90)*PI/180));
        xTL = (int) xDir;
        yTL = (int) yDir;
        hit = 0;

        while(ptr != NULL) {
            hit = (hit || checkRobotSensor(xTL, yTL, sensorSensitivityLength, &ptr->wall));
            ptr = ptr->next;
        }
        if (hit)
            score = i;
    }
    return score;
}

int checkRobotSensorRightAllWalls(struct Robot * robot, struct Wall_collection * head) {
    struct Wall_collection *ptr, *head_store;
    int i;
    double xDir, yDir;
    int robotCentreX, robotCentreY, xTL, yTL;
    int score, hit;
    int sensorSensitivityLength;

    head_store = head;
    robotCentreX = robot->x+ROBOT_WIDTH/2;
    robotCentreY = robot->y+ROBOT_HEIGHT/2;
    score = 0;
    sensorSensitivityLength =  floor(SENSOR_VISION/5);

    for (i = 0; i < 5; i++)
    {
        ptr = head_store;
        //xDir = round(robotCentreX+(-ROBOT_WIDTH/2)*cos((robot->angle)*PI/180)-(-ROBOT_HEIGHT/2-SENSOR_VISION+sensorSensitivityLength*i)*sin((robot->angle)*PI/180));
        //yDir = round(robotCentreY+(-ROBOT_WIDTH/2)*sin((robot->angle)*PI/180)+(-ROBOT_HEIGHT/2-SENSOR_VISION+sensorSensitivityLength*i)*cos((robot->angle)*PI/180));
        xDir = round(robotCentreX+(-ROBOT_WIDTH/2)*cos((robot->angle+90)*PI/180)-(-ROBOT_HEIGHT/2-SENSOR_VISION+sensorSensitivityLength*i)*sin((robot->angle+90)*PI/180));
        yDir = round(robotCentreY+(-ROBOT_WIDTH/2)*sin((robot->angle+90)*PI/180)+(-ROBOT_HEIGHT/2-SENSOR_VISION+sensorSensitivityLength*i)*cos((robot->angle+90)*PI/180));
        xTL = (int) xDir;
        yTL = (int) yDir;
        hit = 0;

        while(ptr != NULL) {
            hit = (hit || checkRobotSensor(xTL, yTL, sensorSensitivityLength, &ptr->wall));
            ptr = ptr->next;
        }
        if (hit)
            score = i;
    }
    return score;
}

void robotUpdate(struct SDL_Renderer * renderer, struct Robot * robot){
    double xDir, yDir;

    int robotCentreX, robotCentreY, xTR, yTR, xTL, yTL, xBR, yBR, xBL, yBL;
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);

    /*
    //Other Display options:
    // The actual square which the robot is tested against (not so nice visually with turns, but easier
    // to test overlap
    SDL_Rect rect = {robot->x, robot->y, robot->height, robot->width};
    SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
    SDL_RenderDrawRect(renderer, &rect);
    SDL_RenderFillRect(renderer, &rect);
    */
    /*
    //Center Line of Robot. Line shows the direction robot is facing
    xDir = -30 * sin(-robot->angle*PI/180);
    yDir = -30 * cos(-robot->angle*PI/180);
    xDirInt = robot->x+ROBOT_WIDTH/2+ (int) xDir;
    yDirInt = robot->y+ROBOT_HEIGHT/2+ (int) yDir;
    SDL_RenderDrawLine(renderer,robot->x+ROBOT_WIDTH/2, robot->y+ROBOT_HEIGHT/2, xDirInt, yDirInt);
    */

    //Rotating Square
    //Vector rotation to work out corners x2 = x1cos(angle)-y1sin(angle), y2 = x1sin(angle)+y1cos(angle)
    robotCentreX = robot->x+ROBOT_WIDTH/2;
    robotCentreY = robot->y+ROBOT_HEIGHT/2;

    xDir = round(robotCentreX+(ROBOT_WIDTH/2)*cos((robot->angle)*PI/180)-(-ROBOT_HEIGHT/2)*sin((robot->angle)*PI/180));
    yDir = round(robotCentreY+(ROBOT_WIDTH/2)*sin((robot->angle)*PI/180)+(-ROBOT_HEIGHT/2)*cos((robot->angle)*PI/180));
    xTR = (int) xDir;
    yTR = (int) yDir;

    xDir = round(robotCentreX+(ROBOT_WIDTH/2)*cos((robot->angle)*PI/180)-(ROBOT_HEIGHT/2)*sin((robot->angle)*PI/180));
    yDir = round(robotCentreY+(ROBOT_WIDTH/2)*sin((robot->angle)*PI/180)+(ROBOT_HEIGHT/2)*cos((robot->angle)*PI/180));
    xBR = (int) xDir;
    yBR = (int) yDir;

    xDir = round(robotCentreX+(-ROBOT_WIDTH/2)*cos((robot->angle)*PI/180)-(ROBOT_HEIGHT/2)*sin((robot->angle)*PI/180));
    yDir = round(robotCentreY+(-ROBOT_WIDTH/2)*sin((robot->angle)*PI/180)+(ROBOT_HEIGHT/2)*cos((robot->angle)*PI/180));
    xBL = (int) xDir;
    yBL = (int) yDir;

    xDir = round(robotCentreX+(-ROBOT_WIDTH/2)*cos((robot->angle)*PI/180)-(-ROBOT_HEIGHT/2)*sin((robot->angle)*PI/180));
    yDir = round(robotCentreY+(-ROBOT_WIDTH/2)*sin((robot->angle)*PI/180)+(-ROBOT_HEIGHT/2)*cos((robot->angle)*PI/180));
    xTL = (int) xDir;
    yTL = (int) yDir;

    SDL_RenderDrawLine(renderer,xTR, yTR, xBR, yBR);
    SDL_RenderDrawLine(renderer,xBR, yBR, xBL, yBL);
    SDL_RenderDrawLine(renderer,xBL, yBL, xTL, yTL);
    SDL_RenderDrawLine(renderer,xTL, yTL, xTR, yTR);

    //Front Centre Sensor
    int sensor_sensitivity =  floor(SENSOR_VISION/5);
    int i;
    for (i = 0; i < 5; i++)
    {
        xDir = round(robotCentreX-(-ROBOT_HEIGHT/2-SENSOR_VISION+sensor_sensitivity*i)*sin((robot->angle)*PI/180));
        yDir = round(robotCentreY+(-ROBOT_HEIGHT/2-SENSOR_VISION+sensor_sensitivity*i)*cos((robot->angle)*PI/180));
        xTL = (int) xDir;
        yTL = (int) yDir;

        SDL_Rect rect = {xTL, yTL, 2, sensor_sensitivity};
        SDL_SetRenderDrawColor(renderer, 80+(20*(5-i)), 80+(20*(5-i)), 80+(20*(5-i)), 255);
        SDL_RenderDrawRect(renderer, &rect);
        SDL_RenderFillRect(renderer, &rect);
    }

    //Left Sensor
    for (i = 0; i < 5; i++)
    {
        xDir = round(robotCentreX+(+ROBOT_WIDTH/2)*cos((robot->angle-90)*PI/180)-(-ROBOT_HEIGHT/2-SENSOR_VISION+sensor_sensitivity*i)*sin((robot->angle-90)*PI/180));
        yDir = round(robotCentreY+(+ROBOT_WIDTH/2)*sin((robot->angle-90)*PI/180)+(-ROBOT_HEIGHT/2-SENSOR_VISION+sensor_sensitivity*i)*cos((robot->angle-90)*PI/180));
        xTL = (int) xDir;
        yTL = (int) yDir;

        SDL_Rect rect = {xTL, yTL, 2, sensor_sensitivity};
        SDL_SetRenderDrawColor(renderer, 80+(20*(5-i)), 80+(20*(5-i)), 80+(20*(5-i)), 255);
        SDL_RenderDrawRect(renderer, &rect);
        SDL_RenderFillRect(renderer, &rect);
    }

    //Right Sensor
    for (i = 0; i < 5; i++)
    {
        xDir = round(robotCentreX+(-ROBOT_WIDTH/2)*cos((robot->angle+90)*PI/180)-(-ROBOT_HEIGHT/2-SENSOR_VISION+sensor_sensitivity*i)*sin((robot->angle+90)*PI/180));
        yDir = round(robotCentreY+(-ROBOT_WIDTH/2)*sin((robot->angle+90)*PI/180)+(-ROBOT_HEIGHT/2-SENSOR_VISION+sensor_sensitivity*i)*cos((robot->angle+90)*PI/180));
        xTL = (int) xDir;
        yTL = (int) yDir;

        SDL_Rect rect = {xTL, yTL, 2, sensor_sensitivity};
        SDL_SetRenderDrawColor(renderer, 80+(20*(5-i)), 80+(20*(5-i)), 80+(20*(5-i)), 255);
        SDL_RenderDrawRect(renderer, &rect);
        SDL_RenderFillRect(renderer, &rect);
    }

        //xDir = round(robotCentreX+(ROBOT_WIDTH/2-2)*cos((robot->angle)*PI/180)-(-ROBOT_HEIGHT/2-SENSOR_VISION+sensor_sensitivity*i)*sin((robot->angle)*PI/180));
        //yDir = round(robotCentreY+(ROBOT_WIDTH/2-2)*sin((robot->angle)*PI/180)+(-ROBOT_HEIGHT/2-SENSOR_VISION+sensor_sensitivity*i)*cos((robot->angle)*PI/180));
}



void robotMotorMove(struct Robot * robot, int crashed) {
    double x_offset, y_offset;
    if (crashed)
        robot->currentSpeed = 0;
    else {
        switch(robot->direction){
            case UP :
                robot->currentSpeed += DEFAULT_SPEED_CHANGE;
                if (robot->currentSpeed > MAX_ROBOT_SPEED)
                    robot->currentSpeed = MAX_ROBOT_SPEED;
                break;
            case DOWN :
                robot->currentSpeed -= DEFAULT_SPEED_CHANGE;
                if (robot->currentSpeed < -MAX_ROBOT_SPEED)
                    robot->currentSpeed = -MAX_ROBOT_SPEED;
                break;
            case LEFT :
                robot->angle = (robot->angle+360-DEFAULT_ANGLE_CHANGE)%360;
                break;
            case RIGHT :
                robot->angle = (robot->angle+DEFAULT_ANGLE_CHANGE)%360;
                break;
        }
    }
    robot->direction = 0;
    x_offset = (-robot->currentSpeed * sin(-robot->angle*PI/180));
    y_offset = (-robot->currentSpeed * cos(-robot->angle*PI/180));

    robot->true_x += x_offset;
    robot->true_y += y_offset;

    x_offset = round(robot->true_x);
    y_offset = round(robot->true_y);

    robot->x = (int) x_offset;
    robot->y = (int) y_offset;
}

// What state the robot is
// state 0: Starting state
// state 1: Turned to face Right
// state 2: Following the right wall
// state 3: Following the left wall
int state = 0;
int deadEnd = 0;
int deadEndAngle = 0;
int wallGap = 0; // Average distance to the wall when the robot is exactly in the middle of two walls. Assumes space remains constant throughout maze
void robotAutoMotorMove(struct Robot * robot, int front_centre_sensor, int left_sensor, int right_sensor) {
    if (state == 0 ) {
        if (right_sensor != 0) {
            state = 2; // Follow right wall
            printf("Entering State 2\n");
        }
        else if (robot->angle != 90 ) {
            robot->direction = UP;
            robot->direction = RIGHT;
        }
        else {
            state = 1; // Turned to face the wall on the right, swap to state 1
            printf("Entering State 1\n");
        }
    }
    else if (state == 1 ) {
        if (right_sensor != 0) {
            state = 2; // Follow right wall
            printf("Entering State 2\n");
        }
        else if ((front_centre_sensor == 0) && ((left_sensor <= 2) ) && ((right_sensor <= 2) )) {
            if (robot->currentSpeed<6)
                robot->direction = UP; // No obstacles in front, go forward
        }
        else if ((robot->currentSpeed>0) && ((front_centre_sensor >= 1) )) {
            robot->direction = DOWN; // Slow down, something in front
            robot->direction = LEFT;
        }
    }
    else if (state == 2 ) {
        followWall(RIGHT, robot, front_centre_sensor, left_sensor, right_sensor);
    }
    else if (state == 3 ) {
        followWall(LEFT, robot, front_centre_sensor, left_sensor, right_sensor);
    }
}

void followWall(int Direction, struct Robot * robot, int front_centre_sensor, int left_sensor, int right_sensor){
    int sensor;
    int opSensor;
    int opDirection;
    if (Direction == RIGHT){
        sensor = right_sensor;
        opSensor = left_sensor;
        opDirection = LEFT;
    }
    else {
        sensor = left_sensor;
        opSensor = right_sensor;
        opDirection = RIGHT;
    }
    // The first time the robot is equidistant from both walls, record it as wellGap.
    if (wallGap == 0){
        if (sensor == opSensor) wallGap = sensor;
    }
    if (deadEnd == 0){
        if (front_centre_sensor > 0 && robot->currentSpeed > 1){
            robot->direction = DOWN; // Slow down before you hit something
            printf("C6\n");
        }
        if (front_centre_sensor > 0 && sensor > 1 && opSensor > 1){
            robot->direction = DOWN; // Slow down until you back out, something in all directions
            deadEndAngle = (robot->angle + 180)%360;
            deadEnd = 1; // We have most likely reached a dead end.
            printf("C7\n");
        }
        else if (front_centre_sensor > 0 ){
            robot->direction = opDirection; // Turn to avoid running into wall
            printf("C1\n");
        }
        else if (wallGap == 0 && sensor != 1 ){ // If no wallGap has been found, try to stay at max disstance from the wall.
            if (sensor < 1) {
                robot->direction = Direction;   // Turn to stay the same distance from the wall
                printf("C4\n");
            }
            else if (sensor > 1) {
                robot->direction = opDirection;    // Turn to stay the same distance from the wall
                printf("C5\n");
            }
        }
        else if (wallGap != 0 && sensor < wallGap) {
                robot->direction = RIGHT;   // Turn to stay the same distance from the wall
                printf("C2\n");
        }
        else if (wallGap != 0 && sensor > wallGap) {
                robot->direction = opDirection; // Turn to stay the same distance from the wall
                printf("C3\n");
        }
        else if (robot->currentSpeed == 0){
            robot->direction = UP;
            printf("C8\n");
        }
        if (robot->currentSpeed<5 && front_centre_sensor == 0 ) robot->direction = UP;
    }
    else {
        if (robot->currentSpeed>0) robot->direction = DOWN; // Stop moving
        else if (robot->angle != deadEndAngle) {
                robot->direction = LEFT; // Turn 180
                printf("C9\n");
        }
        else deadEnd = 0;
    }
}

void robotAutoMotorMoveOld(struct Robot * robot, int front_centre_sensor, int left_sensor, int right_sensor) {

    if (front_centre_sensor == 0) {
        if (robot->currentSpeed<2)
            robot->direction = UP;
    }
    else if ((robot->currentSpeed>0) && ((front_centre_sensor >= 1) && (left_sensor == 0) && (right_sensor == 0)) ) {
        robot->direction = DOWN;
    }
    else if ((robot->currentSpeed==0) && ((front_centre_sensor >= 1) && (left_sensor == 0)) ) {
        robot->direction = LEFT;
    }
    else if ((robot->currentSpeed>0) && ((right_sensor >= 1)) ) {
        robot->direction = LEFT;
    }
    else if ((robot->currentSpeed>0) && ((left_sensor >= 1)) ) {
        robot->direction = RIGHT;
    }
}
