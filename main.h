#ifndef __MAIN_H__
#define __MAIN_H__

#include <GL/freeglut.h>
#include <GL/glext.h>
#include <stdio.h>
#include <time.h>

#include "../Library/loadpng.h"
#include "../Library/process_image.h"
#include "../Library/gl_texture.h"

/*
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
*/

#define WIDTH 600
#define HEIGHT 600
#define INTERVAL 20

#define MAX_TIME_ROTATE 18
#define ROTATE_OFFSET 5.0f // 90 / MAX_TIME_ROTATE

#define MAX_SNAKE_LENGTH 400
#define MAX_FOOD 15

#define OFFSET_TIME 6
#define OFFSET_TIME_ROTATE 18 // = MAX_TIME_ROTATE, slow the velocity when rotate

#define WALL_PER_FACE 7

int POS_X, POS_Y;

enum Game_Status {
    GAME_STT_IDLE,    // Cube Snake, Press Any Key
    GAME_STT_PREPARE, // 3... 2... 1...
    GAME_STT_PLAY,
    GAME_STT_DEAD,
    GAME_STT_GAMEOVER // Game Over
};

enum Cube_Face {
    FACE_FRONT,
    FACE_LEFT,
    FACE_RIGHT,
    FACE_TOP,
    FACE_BOTTOM,
    FACE_BACK
};

enum Key {
    KEY_UP,
    KEY_RIGHT,
    KEY_DOWN,
    KEY_LEFT
};

typedef struct s_Vec3 {
    int x, y, z;
} s_Vec3;

typedef struct s_Face {
    int f, d;
} s_Face;

typedef struct s_Snake_Pos {
    int x, y, z;
    int V, Drt;
} s_Snake_Pos;

typedef struct s_Food_Pos {
    int x, y, z;
    int Is_Alive;
} s_Food_Pos;

// Prototype

void Game_Display_Idle();
void Game_Display_Prepare();
void Game_Display_Play();
void Game_Display_GameOver();
void Game_Process_Idle();
void Game_Process_Prepare();
void Game_Process_Play();
void Game_Process_GameOver();
void Switch_Up();
void Switch_Right();
void Switch_Down();
void Switch_Left();
void Move_X(int Drt);
void Move_Y(int Drt);
void Move_Z(int Drt);
void Set_Offset_x_y();
void Set_Offset_x_z();
void Set_Offset_y_x();
void Set_Offset_y_z();
void Set_Offset_z_x();
void Set_Offset_z_y();
void Arrow_Up();
void Arrow_Right();
void Arrow_Down();
void Arrow_Left();
void Draw_Face_Front();
void Draw_Face_Left();
void Draw_Face_Right();
void Draw_Face_Top();
void Draw_Face_Bottom();
void Draw_Face_Back();
void Translate_Offset(s_Snake_Pos *s);
void Keyboard(GLubyte key, int x, int y);
void Special(int key, int x, int y);

// Function_Pointer

void (*Game_Display_Func[])() = {Game_Display_Idle, Game_Display_Prepare, Game_Display_Play, Game_Display_GameOver};
void (*Game_Process_Func[])() = {Game_Process_Idle, Game_Process_Prepare, Game_Process_Play, Game_Process_GameOver};
void (*Switch_Func[])() = {Switch_Up, Switch_Right, Switch_Down, Switch_Left};
void (*Move_Func[])(int Drt) = {Move_X, Move_Y, Move_Z};
void (*Set_Offset_Func[3][3])() = {
    {NULL, Set_Offset_x_y, Set_Offset_x_z},
    {Set_Offset_y_x, NULL, Set_Offset_y_z},
    {Set_Offset_z_x, Set_Offset_z_y, NULL}};
void (*Arrow_Func[])() = {Arrow_Up, Arrow_Right, Arrow_Down, Arrow_Left};

// Variable

s_Face Face[6];

const GLfloat BG_Color[] = {0.275f, 0.784f, 0.827f, 1.0f};
const GLfloat Light_Pos[] = {-27.0f, 25.0f, 29.0f, 0.0f};
const GLfloat Light_Pos2[] = {27.0f, -25.0f, -29.0f, 0.0f};
const GLfloat Light_Dif[] = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat Ambient[] = {0.400f, 0.900f, 0.400f, 1.0f}; // 4 9 2
const GLfloat Specular[] = {1.000f, 1.000f, 1.000f, 1.0f};
const GLfloat Diffuse_Cube[] = {0.200f, 0.980f, 0.300f, 1.0f};
const GLfloat Diffuse_Wall[] = {0.110f, 0.537f, 1.000f, 1.0f};
const GLfloat Diffuse_Food[] = {1.000f, 0.792f, 0.278f, 1.0f};
const GLfloat Diffuse_Snake[] = {0.800f, 0.184f, 0.280f, 1.0f};
const GLfloat Diffuse_Snake_Head[] = {1.000f, 0.184f, 0.180f, 1.0f};
const float x_angle = 16.0f, y_angle = 0.0f, z_angle = 0.0f;

int New_V, New_Drt;
int Key_Current;
int Time_Rotate;
float xo, yo, zo;
int Face_Front, Face_Left, Face_Right, Face_Top, Face_Bottom, Face_Back, Face_Current, Face_Next, Face_Save;
int Map[20][20][20]; // x y z
s_Vec3 Map_Velocity[] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
s_Food_Pos Food_Pos[MAX_FOOD];
s_Snake_Pos Snake_Pos[MAX_SNAKE_LENGTH];
int Snake_Length, Snake_Offset;
int Pressed_Arrow;

int Idle_Stt=0, Idle_Stt_Offset=1;
int Prepare_Stt;
int Game_Timer;
int Game_Stt = GAME_STT_IDLE;

int Offset_Time;
float Offset_Size;

int Is_First_Time = 1;

// font.h

enum Font_Size {
    SMALL,
    MEDIUM,
    LARGE
};

Image Img_Char[3][128];
Image Img_Logo, Img_PressAnyKey, Img_GameOver, Img_Prepare[3];
Rect Rct_Logo, Rct_PressAnyKey, Rct_GameOver, Rct_Prepare[3];

int Font_Offset_Shadow[] = {4, 6, 8};
unsigned char Color_Shadow[] = {0, 0, 0, 192};
unsigned char Color_Red[] = {255, 90, 70, 255};
unsigned char Color_Blue[] = {50, 135, 220, 255};
unsigned char Color_White[] = {255, 255, 255, 255};

#include "font.c"

#endif
