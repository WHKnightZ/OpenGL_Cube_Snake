#include <GL/freeglut.h>
#include <GL/glext.h>
#include <math.h>
#include <stdio.h>

#define WIDTH 600
#define HEIGHT 600
#define INTERVAL 15

#define ROTATE_OFFSET 5.0f

int POS_X, POS_Y;

enum Cube_Face {
    FACE_FRONT,
    FACE_LEFT,
    FACE_RIGHT,
    FACE_TOP,
    FACE_BOTTOM,
    FACE_BACK
};

typedef struct s_Face {
    int f, d;
} s_Face;

GLfloat BG_Color[] = {0.275f, 0.784f, 0.827f, 1.0f};
//GLfloat BG_Color[] = { 0.302f, 0.855f, 0.973f, 1.0f };
//GLfloat Light_Pos[] = { -50.0f, 40.0f, 35.0f, 0.0f };
//GLfloat Light_Pos2[] = { 50.0f, -40.0f, 35.0f, 0.0f };

//GLfloat Light_Pos[] = { -50.0f, 40.0f, 55.0f, 0.0f };
//GLfloat Light_Pos2[] = { 50.0f, -40.0f, -55.0f, 0.0f };
GLfloat Light_Pos[] = {-27.0f, 25.0f, 29.0f, 0.0f};
GLfloat Light_Pos2[] = {27.0f, -25.0f, -29.0f, 0.0f};
GLfloat Light_Dif[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat Ambient[] = {0.200f, 0.900f, 0.200f, 1.0f};
GLfloat Specular[] = {1.000f, 1.000f, 1.000f, 1.0f};

//GLfloat Diffuse_Cube[] = { 0.306f, 0.988f, 0.576f, 1.0f };
GLfloat Diffuse_Cube[] = {0.200f, 0.980f, 0.300f, 1.0f};
//GLfloat Diffuse_Cube[] = { 0.302f, 0.941f, 0.404f, 1.0f };
GLfloat Diffuse_Wall[] = {0.110f, 0.537f, 1.000f, 1.0f};
GLfloat Diffuse_Food[] = {1.000f, 0.792f, 0.278f, 1.0f};
GLfloat Diffuse_Snake[] = {1.000f, 0.184f, 0.380f, 1.0f};

float x_angle = 16.0f, y_angle = 0.0f, z_angle = 0.0f;

s_Face Face[6];

int ii = 18;
float xo, yo, zo;
int Face_Front, Face_Left, Face_Right, Face_Top, Face_Bottom, Face_Back, Face_Current, Face_Next, Face_Save;

void (*Set_Offset_Func[3][3])();

void Set_Offset_x_y() {
    zo = ROTATE_OFFSET * Face[Face_Current].d * Face[Face_Next].d;
    xo = yo = 0.0f;
}

void Set_Offset_x_z() {
    yo = ROTATE_OFFSET * Face[Face_Current].d * Face[Face_Next].d;
    xo = zo = 0.0f;
}

void Set_Offset_y_x() {
    zo = -ROTATE_OFFSET * Face[Face_Current].d * Face[Face_Next].d;
    xo = yo = 0.0f;
}

void Set_Offset_y_z() {
    xo = -ROTATE_OFFSET * Face[Face_Current].d * Face[Face_Next].d;
    yo = zo = 0.0f;
}

void Set_Offset_z_x() {
    yo = -ROTATE_OFFSET * Face[Face_Current].d * Face[Face_Next].d;
    xo = zo = 0.0f;
}

void Set_Offset_z_y() {
    xo = ROTATE_OFFSET * Face[Face_Current].d * Face[Face_Next].d;
    yo = zo = 0.0f;
}

int Map[6][18][18];

void Reset_View() {
    glMatrixMode(GL_PROJECTION);
    glRotatef(xo, 1.0f, 0.0f, 0.0f);
    glRotatef(yo, 0.0f, 1.0f, 0.0f);
    glRotatef(zo, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
}

void Load_Map() {
    FILE *f = fopen("Map.txt", "r");
    int i, j, k;
    for (i = 0; i < 6; i++)
        for (j = 0; j < 18; j++)
            for (k = 0; k < 18; k++)
                fscanf(f, "%d", &Map[i][j][k]);
    fclose(f);
}

void Init_Game() {
    // GL
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, Light_Dif);
    glLightfv(GL_LIGHT0, GL_POSITION, Light_Pos);
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, Light_Dif);
    glLightfv(GL_LIGHT1, GL_POSITION, Light_Pos2);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 90.0f);
    glClearColor(BG_Color[0], BG_Color[1], BG_Color[2], BG_Color[3]);
    glColor3f(1.0f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    // Game
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(20.0, 1.0, 1.0, 150.0);
    glViewport(0, 0, WIDTH, HEIGHT);
    glTranslatef(0.0f, 0.0f, -94.0f);
    glRotatef(x_angle, 1.0f, 0.0f, 0.0f);
    glRotatef(y_angle, 0.0f, 1.0f, 0.0f);
    glRotatef(z_angle, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    Reset_View();
    Face_Front = FACE_FRONT;
    Face_Left = FACE_LEFT;
    Face_Right = FACE_RIGHT;
    Face_Top = FACE_TOP;
    Face_Bottom = FACE_BOTTOM;
    Face_Back = FACE_BACK;
    Face[FACE_FRONT].f = 2;
    Face[FACE_FRONT].d = -1;
    Face[FACE_LEFT].f = 0;
    Face[FACE_LEFT].d = -1;
    Face[FACE_RIGHT].f = 0;
    Face[FACE_RIGHT].d = 1;
    Face[FACE_TOP].f = 1;
    Face[FACE_TOP].d = 1;
    Face[FACE_BOTTOM].f = 1;
    Face[FACE_BOTTOM].d = -1;
    Face[FACE_BACK].f = 2;
    Face[FACE_BACK].d = 1;
    Set_Offset_Func[0][1] = Set_Offset_x_y;
    Set_Offset_Func[0][2] = Set_Offset_x_z;
    Set_Offset_Func[1][0] = Set_Offset_y_x;
    Set_Offset_Func[1][2] = Set_Offset_y_z;
    Set_Offset_Func[2][0] = Set_Offset_z_x;
    Set_Offset_Func[2][1] = Set_Offset_z_y;
    Load_Map();
}

void Draw_Face_Front() {
    int i, j;
    for (i = 0; i < 18; i++)
        for (j = 0; j < 18; j++)
            if (Map[FACE_FRONT][i][j] > 0) {
                glLoadIdentity();
                glTranslatef(j - 8.5f, i - 8.5f, 9.5f);
                glutSolidCube(1.0);
            }
}

void Draw_Face_Left() {
    int i, j;
    for (i = 0; i < 18; i++)
        for (j = 0; j < 18; j++)
            if (Map[FACE_LEFT][i][j] > 0) {
                glLoadIdentity();
                glTranslatef(-9.5f, i - 8.5f, j - 8.5f);
                glutSolidCube(1.0);
            }
}

void Draw_Face_Right() {
    int i, j;
    for (i = 0; i < 18; i++)
        for (j = 0; j < 18; j++)
            if (Map[FACE_RIGHT][i][j] > 0) {
                glLoadIdentity();
                glTranslatef(9.5f, i - 8.5f, j - 8.5f);
                glutSolidCube(1.0);
            }
}

void Draw_Face_Top() {
    int i, j;
    for (i = 0; i < 18; i++)
        for (j = 0; j < 18; j++)
            if (Map[FACE_TOP][i][j] > 0) {
                glLoadIdentity();
                glTranslatef(j - 8.5f, 9.5f, i - 8.5f);
                glutSolidCube(1.0);
            }
}

void Draw_Face_Bottom() {
    int i, j;
    for (i = 0; i < 18; i++)
        for (j = 0; j < 18; j++)
            if (Map[FACE_BOTTOM][i][j] > 0) {
                glLoadIdentity();
                glTranslatef(j - 8.5f, -9.5f, i - 8.5f);
                glutSolidCube(1.0);
            }
}

void Draw_Face_Back() {
    int i, j;
    for (i = 0; i < 18; i++)
        for (j = 0; j < 18; j++)
            if (Map[FACE_BACK][i][j] > 0) {
                glLoadIdentity();
                glTranslatef(j - 8.5f, i - 8.5f, -9.5f);
                glutSolidCube(1.0);
            }
}

void Display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Diffuse_Cube);
    glutSolidCube(18.0);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Diffuse_Wall);
    Draw_Face_Front();
    Draw_Face_Left();
    Draw_Face_Right();
    Draw_Face_Top();
    Draw_Face_Bottom();
    Draw_Face_Back();
    glutSwapBuffers();
}

void Resize(int x, int y) {
    glutPositionWindow(POS_X, POS_Y);
    glutReshapeWindow(WIDTH, HEIGHT);
}

void Special(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_LEFT:
        if (ii == 18) {
            ii = 0;
            Face_Current = Face_Front;
            Face_Next = Face_Left;
            Face_Save = Face_Front;
            Face_Front = Face_Right;
            Face_Right = Face_Back;
            Face_Back = Face_Left;
            Face_Left = Face_Save;
            Set_Offset_Func[Face[Face_Current].f][Face[Face_Next].f]();
        }
        break;
    case GLUT_KEY_RIGHT:
        if (ii == 18) {
            ii = 0;
            Face_Current = Face_Front;
            Face_Next = Face_Right;
            Face_Save = Face_Front;
            Face_Front = Face_Left;
            Face_Left = Face_Back;
            Face_Back = Face_Right;
            Face_Right = Face_Save;
            Set_Offset_Func[Face[Face_Current].f][Face[Face_Next].f]();
        }
        break;
    case GLUT_KEY_UP:
        if (ii == 18) {
            ii = 0;
            Face_Current = Face_Front;
            Face_Next = Face_Top;
            Face_Save = Face_Front;
            Face_Front = Face_Bottom;
            Face_Bottom = Face_Back;
            Face_Back = Face_Top;
            Face_Top = Face_Save;
            Set_Offset_Func[Face[Face_Current].f][Face[Face_Next].f]();
        }
        break;
    case GLUT_KEY_DOWN:
        if (ii == 18) {
            ii = 0;
            Face_Current = Face_Front;
            Face_Next = Face_Bottom;
            Face_Save = Face_Front;
            Face_Front = Face_Top;
            Face_Top = Face_Back;
            Face_Back = Face_Bottom;
            Face_Bottom = Face_Save;
            Set_Offset_Func[Face[Face_Current].f][Face[Face_Next].f]();
        }
        break;
    }
}

void Timer(int value) {
    if (ii < 18) {
        ii++;
        Reset_View();
    }
    glutPostRedisplay();
    glutTimerFunc(INTERVAL, Timer, 0);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glEnable(GL_MULTISAMPLE);
    glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);
    glutSetOption(GLUT_MULTISAMPLE, 8);
    POS_X = (glutGet(GLUT_SCREEN_WIDTH) - WIDTH) >> 1;
    POS_Y = (glutGet(GLUT_SCREEN_HEIGHT) - HEIGHT) >> 1;
    glutInitWindowPosition(POS_X, POS_Y);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Snake Cube");
    Init_Game();
    glutSpecialFunc(Special);
    glutTimerFunc(0, Timer, 0);
    glutDisplayFunc(Display);
    glutReshapeFunc(Resize);
    glutMainLoop();
    return 0;
}
