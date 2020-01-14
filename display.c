#include "main.h"

void Reset_View() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, WIDTH, HEIGHT);
    gluPerspective(20.0, 1.0, 1.0, 150.0);
    glTranslatef(0.0f, 0.0f, -94.0f);
    glRotatef(x_angle, 1.0f, 0.0f, 0.0f);
    glRotatef(y_angle, 0.0f, 1.0f, 0.0f);
    glRotatef(z_angle, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
}

void Reload_View() {
    glMatrixMode(GL_PROJECTION);
    glRotatef(xo, 1.0f, 0.0f, 0.0f);
    glRotatef(yo, 0.0f, 1.0f, 0.0f);
    glRotatef(zo, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
}

void Draw_Game() {
    int i, j;
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
        glTranslatef(Food_Pos[i].x - 9.5f, Food_Pos[i].y - 9.5f, Food_Pos[i].z - 9.5f);
        glutSolidCube(1.0);
    }
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Diffuse_Snake);
    for (i = 0; i < Snake_Length; i++) {
        glLoadIdentity();
        glTranslatef(Snake_Pos[i].x - 9.5f, Snake_Pos[i].y - 9.5f, Snake_Pos[i].z - 9.5f);
        glutSolidCube(1.0);
    }
    if (Snake_Length > 0) {
        Translate_Offset(&Snake_Pos[Snake_Length]);
        glutSolidCube(1.0);
    }
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Diffuse_Snake_Head);
    Translate_Offset(&Snake_Pos[0]);
    glutSolidCube(1.2);
}

void Draw_2D_Begin() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, WIDTH, HEIGHT, 0);
    glViewport(0, 0, WIDTH, HEIGHT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
}

void Draw_2D_End() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
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

void Translate_Offset(s_Snake_Pos *s) {
    glLoadIdentity();
    switch (s->V) {
    case 0:
        glTranslatef(s->x + s->Drt * Offset_Size * Snake_Offset - 9.5f, s->y - 9.5f, s->z - 9.5f);
        break;
    case 1:
        glTranslatef(s->x - 9.5f, s->y + s->Drt * Offset_Size * Snake_Offset - 9.5f, s->z - 9.5f);
        break;
    case 2:
        glTranslatef(s->x - 9.5f, s->y - 9.5f, s->z + s->Drt * Offset_Size * Snake_Offset - 9.5f);
        break;
    }
}
