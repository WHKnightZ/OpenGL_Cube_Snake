#include "main.h"

void Display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Game_Display_Func[Game_Stt]();
    glLoadIdentity();
    glutSwapBuffers();
}

void Resize(int x, int y) {
    glutPositionWindow(POS_X, POS_Y);
    glutReshapeWindow(WIDTH, HEIGHT);
}

void Keyboard(GLubyte key, int x, int y) {
    if (Is_First_Time)
        Is_First_Time = 0;
    else
        Reload_Game();
    Reset_View();
    Game_Timer = 0;
    glutKeyboardFunc(NULL);
    Game_Stt = GAME_STT_PREPARE;
    Prepare_Stt = 0;
}

void Special(int key, int x, int y) {
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
    Game_Process_Func[Game_Stt]();
    glutPostRedisplay();
    glutTimerFunc(INTERVAL, Timer, 0);
}

int main(int argc, char **argv) {
    srand(time(NULL));
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
    glutKeyboardFunc(Keyboard);
    glutTimerFunc(0, Timer, 0);
    glutDisplayFunc(Display);
    //    glutReshapeFunc(Resize);
    glutMainLoop();
    return 0;
}
