#include <GL/freeglut.h>
#include <GL/glext.h>
#include <GL/glut.h>
#include <stdio.h>

#define WIDTH 600
#define HEIGHT 600
#define INTERVAL 20

#define VELOCITY_BASE 1.0f
#define ROTATE_OFFSET 5.0f
#define MAX_TIME_ROTATE 18
#define SLOW_VELOCITY_INDEX 4.5f // MAX_TIME_ROTATE * VELOCITY_BASE

#define MAX_SNAKE_LENGTH 50
#define MAX_FOOD 20

int POS_X, POS_Y;

void (*Switch_Func[4])();
void (*Move_Func[3])(int Drt);
void (*Set_Offset_Func[3][3])();
void (*Arrow_Func[4])();

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
    float x, y, z;
} s_Vec3;

typedef struct s_Face {
    int f, d;
} s_Face;

typedef struct Snake_Part {
    float x, y, z;
    int V, Drt;
} Snake_Part;

s_Face Face[6];

const GLfloat BG_Color[] = {0.275f, 0.784f, 0.827f, 1.0f};
const GLfloat Light_Pos[] = {-27.0f, 25.0f, 29.0f, 0.0f};
const GLfloat Light_Pos2[] = {27.0f, -25.0f, -29.0f, 0.0f};
const GLfloat Light_Dif[] = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat Ambient[] = {0.400f, 0.900f, 0.200f, 1.0f};
const GLfloat Specular[] = {1.000f, 1.000f, 1.000f, 1.0f};
const GLfloat Diffuse_Cube[] = {0.200f, 0.980f, 0.300f, 1.0f};
const GLfloat Diffuse_Wall[] = {0.110f, 0.537f, 1.000f, 1.0f};
const GLfloat Diffuse_Food[] = {1.000f, 0.792f, 0.278f, 1.0f};
const GLfloat Diffuse_Snake[] = {0.800f, 0.184f, 0.280f, 1.0f};
const GLfloat Diffuse_Snake_Head[] = {1.000f, 0.184f, 0.180f, 1.0f};
const float x_angle = 16.0f, y_angle = 0.0f, z_angle = 0.0f;

float Velocity = VELOCITY_BASE;
int New_V = 2, New_Drt = -1;
int Key_Current = KEY_RIGHT;
int Time_Rotate = MAX_TIME_ROTATE;
float xo, yo, zo;
int Face_Front, Face_Left, Face_Right, Face_Top, Face_Bottom, Face_Back, Face_Current, Face_Next, Face_Save;
int Map[20][20][20]; // x y z
s_Vec3 Map_Velocity[] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
s_Vec3 Food_Pos[MAX_FOOD];
Snake_Part Snake_Pos[MAX_SNAKE_LENGTH];
int Snake_Length, Snake_Offset;
int Pressed_Arrow = -1;

void Switch_Up() {
    Face_Next = Face_Bottom;
    Face_Save = Face_Front;
    Face_Front = Face_Top;
    Face_Top = Face_Back;
    Face_Back = Face_Bottom;
    Face_Bottom = Face_Save;
    Face_Current = Face_Front;
    Face_Next = Face_Top;
    Set_Offset_Func[Face[Face_Current].f][Face[Face_Next].f]();
}

void Switch_Right() {
    Face_Next = Face_Left;
    Face_Save = Face_Front;
    Face_Front = Face_Right;
    Face_Right = Face_Back;
    Face_Back = Face_Left;
    Face_Left = Face_Save;
    Face_Current = Face_Front;
    Face_Next = Face_Right;
    Set_Offset_Func[Face[Face_Current].f][Face[Face_Next].f]();
}

void Switch_Down() {
    Face_Next = Face_Top;
    Face_Save = Face_Front;
    Face_Front = Face_Bottom;
    Face_Bottom = Face_Back;
    Face_Back = Face_Top;
    Face_Top = Face_Save;
    Face_Current = Face_Front;
    Face_Next = Face_Bottom;
    Set_Offset_Func[Face[Face_Current].f][Face[Face_Next].f]();
}

void Switch_Left() {
    Face_Next = Face_Right;
    Face_Save = Face_Front;
    Face_Front = Face_Left;
    Face_Left = Face_Back;
    Face_Back = Face_Right;
    Face_Right = Face_Save;
    Face_Current = Face_Front;
    Face_Next = Face_Left;
    Set_Offset_Func[Face[Face_Current].f][Face[Face_Next].f]();
}

void Switch() {
    if (Time_Rotate == MAX_TIME_ROTATE) {
        printf("x");
        Time_Rotate = 0;
        Snake_Pos[0].V = New_V;
        Snake_Pos[0].Drt = New_Drt;
        Switch_Func[Key_Current]();
    }
    Velocity /= SLOW_VELOCITY_INDEX;
}

void Move_X(int Drt) {
    Snake_Pos[0].x += Snake_Pos[0].Drt;
    if (Time_Rotate == MAX_TIME_ROTATE) {
        if (Drt == -1) {
            if (Snake_Pos[0].x < -9.45f)
                Switch();
        } else {
            if (Snake_Pos[0].x > 9.45f)
                Switch();
        }
    }
}

void Move_Y(int Drt) {
    Snake_Pos[0].y += Snake_Pos[0].Drt;
    if (Time_Rotate == MAX_TIME_ROTATE) {
        if (Drt == -1) {
            if (Snake_Pos[0].y < -9.45f)
                Switch();
        } else {
            if (Snake_Pos[0].y > 9.45f)
                Switch();
        }
    }
}

void Move_Z(int Drt) {
    Snake_Pos[0].z += Snake_Pos[0].Drt;
    if (Time_Rotate == MAX_TIME_ROTATE) {
        if (Drt == -1) {
            if (Snake_Pos[0].z < -9.45f)
                Switch();
        } else {
            if (Snake_Pos[0].z > 9.45f)
                Switch();
        }
    }
}

void Set_Offset_x_y() {
    zo = -ROTATE_OFFSET * Face[Face_Current].d * Face[Face_Next].d;
    xo = yo = 0.0f;
    Snake_Pos[0].V = 1;
    Snake_Pos[0].Drt = Face[Face_Next].d;
    New_V = 0;
    New_Drt = -Face[Face_Current].d;
}

void Set_Offset_x_z() {
    yo = ROTATE_OFFSET * Face[Face_Current].d * Face[Face_Next].d;
    xo = zo = 0.0f;
    Snake_Pos[0].V = 2;
    Snake_Pos[0].Drt = Face[Face_Next].d;
    New_V = 0;
    New_Drt = -Face[Face_Current].d;
    printf("a");
}

void Set_Offset_y_x() {
    zo = ROTATE_OFFSET * Face[Face_Current].d * Face[Face_Next].d;
    xo = yo = 0.0f;
    Snake_Pos[0].V = 0;
    Snake_Pos[0].Drt = Face[Face_Next].d;
    New_V = 1;
    New_Drt = -Face[Face_Current].d;
}

void Set_Offset_y_z() {
    xo = -ROTATE_OFFSET * Face[Face_Current].d * Face[Face_Next].d;
    yo = zo = 0.0f;
    Snake_Pos[0].V = 2;
    Snake_Pos[0].Drt = Face[Face_Next].d;
    New_V = 1;
    New_Drt = -Face[Face_Current].d;
}

void Set_Offset_z_x() {
    yo = -ROTATE_OFFSET * Face[Face_Current].d * Face[Face_Next].d;
    xo = zo = 0.0f;
    Snake_Pos[0].V = 0;
    Snake_Pos[0].Drt = Face[Face_Next].d;
    New_V = 2;
    New_Drt = -Face[Face_Current].d;
    printf("b");
}

void Set_Offset_z_y() {
    xo = ROTATE_OFFSET * Face[Face_Current].d * Face[Face_Next].d;
    yo = zo = 0.0f;
    Snake_Pos[0].V = 1;
    Snake_Pos[0].Drt = Face[Face_Next].d;
    New_V = 2;
    New_Drt = -Face[Face_Current].d;
}

void Arrow_Up() {
    Key_Current = KEY_UP;
    Face_Next = Face_Top;
    Set_Offset_Func[Face[Face_Current].f][Face[Face_Next].f]();
}

void Arrow_Right() {
    Key_Current = KEY_RIGHT;
    Face_Next = Face_Right;
    Set_Offset_Func[Face[Face_Current].f][Face[Face_Next].f]();
}

void Arrow_Down() {
    Key_Current = KEY_DOWN;
    Face_Next = Face_Bottom;
    Set_Offset_Func[Face[Face_Current].f][Face[Face_Next].f]();
}

void Arrow_Left() {
    Key_Current = KEY_LEFT;
    Face_Next = Face_Left;
    Set_Offset_Func[Face[Face_Current].f][Face[Face_Next].f]();
}

void Reset_View() {
    glMatrixMode(GL_PROJECTION);
    glRotatef(xo, 1.0f, 0.0f, 0.0f);
    glRotatef(yo, 0.0f, 1.0f, 0.0f);
    glRotatef(zo, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
}

void Load_Map() {
    FILE *f = fopen("Map.txt", "r");
    int i, j;
    for (i = 1; i < 19; i++)
        for (j = 1; j < 19; j++)
            fscanf(f, "%d", &Map[i][j][19]);
    for (i = 1; i < 19; i++)
        for (j = 1; j < 19; j++)
            fscanf(f, "%d", &Map[0][i][j]);
    for (i = 1; i < 19; i++)
        for (j = 1; j < 19; j++)
            fscanf(f, "%d", &Map[19][i][j]);
    for (i = 1; i < 19; i++)
        for (j = 1; j < 19; j++)
            fscanf(f, "%d", &Map[i][19][j]);
    for (i = 1; i < 19; i++)
        for (j = 1; j < 19; j++)
            fscanf(f, "%d", &Map[i][0][j]);
    for (i = 1; i < 19; i++)
        for (j = 1; j < 19; j++)
            fscanf(f, "%d", &Map[i][j][0]);
    fclose(f);
}

int Check_Is_Snake(int x, int y, int z) {
    return 0;
}

int Check_Is_Wall(int x, int y, int z) {
    return 0;
}

int Check_Is_Food(int x, int y, int z) {
    return 0;
}

void Add_Part() {
    int Snake_Length_Old = Snake_Length;
    int V_Old = Snake_Pos[Snake_Length].V;
    int Drt_Old = Snake_Pos[Snake_Length].Drt;
    Snake_Length++;
    Snake_Pos[Snake_Length].x = Snake_Pos[Snake_Length_Old].x - Map_Velocity[V_Old].x * Drt_Old;
    Snake_Pos[Snake_Length].y = Snake_Pos[Snake_Length_Old].y - Map_Velocity[V_Old].y * Drt_Old;
    Snake_Pos[Snake_Length].z = Snake_Pos[Snake_Length_Old].z - Map_Velocity[V_Old].z * Drt_Old;
    Snake_Pos[Snake_Length].V = V_Old;
    Snake_Pos[Snake_Length].Drt = Drt_Old;
}

void Create_Food(int n) {
    int x, y, z;
    do {
        int k = rand() % 3;
        int m = rand() % 2;
        switch (k) {
        case 0:
            x = 19 - 19 * m;
            y = rand() % 18 + 1;
            z = rand() % 18 + 1;
            break;
        case 1:
            y = 19 - 19 * m;
            x = rand() % 18 + 1;
            z = rand() % 18 + 1;
            break;
        case 2:
            z = 19 - 19 * m;
            x = rand() % 18 + 1;
            y = rand() % 18 + 1;
            break;
        }
    } while (0);
    Food_Pos[n].x = x - 9.5f;
    Food_Pos[n].y = y - 9.5f;
    Food_Pos[n].z = z - 9.5f;
}

void Init_Food() {
    int i;
    for (i = 0; i < MAX_FOOD; i++)
        Create_Food(i);
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
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glShadeModel(GL_POLYGON_SMOOTH);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // Game
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, WIDTH, HEIGHT);
    gluPerspective(20.0, 1.0, 1.0, 150.0);
    glTranslatef(0.0f, 0.0f, -94.0f);
    //	glFrustum(-0.4, 0.4, -0.4, 0.4, 1.0, 200.0);
    //	glTranslatef(0.0f, 0.0f, -50.0f);
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
    Face[FACE_FRONT].d = 1;
    Face[FACE_LEFT].f = 0;
    Face[FACE_LEFT].d = -1;
    Face[FACE_RIGHT].f = 0;
    Face[FACE_RIGHT].d = 1;
    Face[FACE_TOP].f = 1;
    Face[FACE_TOP].d = 1;
    Face[FACE_BOTTOM].f = 1;
    Face[FACE_BOTTOM].d = -1;
    Face[FACE_BACK].f = 2;
    Face[FACE_BACK].d = -1;
    Switch_Func[KEY_UP] = Switch_Up;
    Switch_Func[KEY_RIGHT] = Switch_Right;
    Switch_Func[KEY_DOWN] = Switch_Down;
    Switch_Func[KEY_LEFT] = Switch_Left;
    Move_Func[0] = Move_X;
    Move_Func[1] = Move_Y;
    Move_Func[2] = Move_Z;
    Set_Offset_Func[0][1] = Set_Offset_x_y;
    Set_Offset_Func[0][2] = Set_Offset_x_z;
    Set_Offset_Func[1][0] = Set_Offset_y_x;
    Set_Offset_Func[1][2] = Set_Offset_y_z;
    Set_Offset_Func[2][0] = Set_Offset_z_x;
    Set_Offset_Func[2][1] = Set_Offset_z_y;
    Arrow_Func[KEY_UP] = Arrow_Up;
    Arrow_Func[KEY_RIGHT] = Arrow_Right;
    Arrow_Func[KEY_DOWN] = Arrow_Down;
    Arrow_Func[KEY_LEFT] = Arrow_Left;
    Load_Map();
    Snake_Offset = 0;
    Snake_Length = 1;
    Snake_Pos[0].x = 0.5f;
    Snake_Pos[1].x = -0.5f;
    int i;
    for (i = 0; i <= Snake_Length; i++) {
        Snake_Pos[i].y = 0.5f;
        Snake_Pos[i].z = 9.5f;
        Snake_Pos[i].V = 0;
        Snake_Pos[i].Drt = 1;
    }
    Face_Current = Face_Front;
    Face_Next = Face_Right;
    Set_Offset_Func[Face[Face_Current].f][Face[Face_Next].f]();
    Init_Food();
}

void Draw_Face_Front() {
    int i, j;
    for (i = 1; i < 19; i++)
        for (j = 1; j < 19; j++)
            if (Map[i][j][19] > 0) {
                glLoadIdentity();
                glTranslatef(i - 9.5f, j - 9.5f, 9.5f);
                glutSolidCube(1.0);
            }
}

void Draw_Face_Left() {
    int i, j;
    for (i = 1; i < 19; i++)
        for (j = 1; j < 19; j++)
            if (Map[0][i][j] > 0) {
                glLoadIdentity();
                glTranslatef(-9.5f, i - 9.5f, j - 9.5f);
                glutSolidCube(1.0);
            }
}

void Draw_Face_Right() {
    int i, j;
    for (i = 1; i < 19; i++)
        for (j = 1; j < 19; j++)
            if (Map[19][i][j] > 0) {
                glLoadIdentity();
                glTranslatef(9.5f, i - 9.5f, j - 9.5f);
                glutSolidCube(1.0);
            }
}

void Draw_Face_Top() {
    int i, j;
    for (i = 1; i < 19; i++)
        for (j = 1; j < 19; j++)
            if (Map[i][19][j] > 0) {
                glLoadIdentity();
                glTranslatef(i - 9.5f, 9.5f, j - 9.5f);
                glutSolidCube(1.0);
            }
}

void Draw_Face_Bottom() {
    int i, j;
    for (i = 1; i < 19; i++)
        for (j = 1; j < 19; j++)
            if (Map[i][0][j] > 0) {
                glLoadIdentity();
                glTranslatef(i - 9.5f, -9.5f, j - 9.5f);
                glutSolidCube(1.0);
            }
}

void Draw_Face_Back() {
    int i, j;
    for (i = 1; i < 19; i++)
        for (j = 1; j < 19; j++)
            if (Map[i][j][0] > 0) {
                glLoadIdentity();
                glTranslatef(i - 9.5f, j - 9.5f, -9.5f);
                glutSolidCube(1.0);
            }
}

void Translate_Offset(Snake_Part *s) {
    glLoadIdentity();
    switch (s->V) {
    case 0:
        glTranslatef(s->x + s->Drt * 0.25f * Snake_Offset, s->y, s->z);
        break;
    case 1:
        glTranslatef(s->x, s->y + s->Drt * 0.25f * Snake_Offset, s->z);
        break;
    case 2:
        glTranslatef(s->x, s->y, s->z + s->Drt * 0.25f * Snake_Offset);
        break;
    }
}

void Display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    int i, j;
    //    for (i=1;i<19;i++){
    //    	glBegin(GL_LINES);
    //    	glVertex3f(-9.0f,i-9.0f,9.1f);
    //    	glVertex3f(9.0f,i-9.0f,9.1f);
    //    	glVertex3f(i-9.0f,-9.0f,9.1f);
    //    	glVertex3f(i-9.0f,9.0f,9.1f);
    //    	glEnd();
    //	}
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Diffuse_Cube);
    glutSolidCube(18.0);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Diffuse_Wall);
    Draw_Face_Front();
    Draw_Face_Left();
    Draw_Face_Right();
    Draw_Face_Top();
    Draw_Face_Bottom();
    Draw_Face_Back();
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Diffuse_Food);
    for (i = 0; i < MAX_FOOD; i++) {
        glLoadIdentity();
        glTranslatef(Food_Pos[i].x, Food_Pos[i].y, Food_Pos[i].z);
        glutSolidCube(1.0);
    }
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Diffuse_Snake);
    for (i = 0; i < Snake_Length; i++) {
        glLoadIdentity();
        glTranslatef(Snake_Pos[i].x, Snake_Pos[i].y, Snake_Pos[i].z);
        glutSolidCube(1.0);
    }
    if (Snake_Length > 0) {
        Translate_Offset(&Snake_Pos[Snake_Length]);
        glutSolidCube(1.0);
    }
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Diffuse_Snake_Head);
    Translate_Offset(&Snake_Pos[0]);
    glutSolidCube(1.2);
    glutSwapBuffers();
}

void Resize(int x, int y) {
    glutPositionWindow(POS_X, POS_Y);
    glutReshapeWindow(WIDTH, HEIGHT);
}

void Special(int key, int x, int y) {
    if (key == GLUT_KEY_F1)
        Add_Part();
    if (Time_Rotate == MAX_TIME_ROTATE)
        switch (key) {
        case GLUT_KEY_UP:
            Pressed_Arrow = KEY_UP;
            break;
        case GLUT_KEY_RIGHT:
            Pressed_Arrow = KEY_RIGHT;
            break;
        case GLUT_KEY_DOWN:
            Pressed_Arrow = KEY_DOWN;
            break;
        case GLUT_KEY_LEFT:
            Pressed_Arrow = KEY_LEFT;
            break;
        }
}

void Timer(int value) {
    if (Time_Rotate < MAX_TIME_ROTATE) {
        Reset_View();
        Time_Rotate++;
        if (Time_Rotate == MAX_TIME_ROTATE) {
            Velocity *= SLOW_VELOCITY_INDEX;
        }
    }
    Snake_Offset++;
    if (Snake_Offset == 4) {
        Snake_Offset = 0;
        int i;
        for (i = Snake_Length; i > 0; i--) {
            Snake_Pos[i] = Snake_Pos[i - 1];
        }
        Move_Func[Snake_Pos[0].V](Snake_Pos[0].Drt);
        if (Pressed_Arrow != -1 && Time_Rotate == MAX_TIME_ROTATE) {
            Arrow_Func[Pressed_Arrow]();
            Pressed_Arrow = -1;
        }
    }
    glutPostRedisplay();
    glutTimerFunc(INTERVAL, Timer, 0);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
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
    //    glutReshapeFunc(Resize);
    glutMainLoop();
    return 0;
}
