#include <GL/glut.h>
#include <vector>

const int mazeWidth = 10;
const int mazeHeight = 10;

// Define the maze: 1 = wall, 0 = path
int maze[mazeWidth][mazeHeight] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 1, 0, 1, 0, 0, 0, 1},
    {1, 0, 1, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

float playerX = 1.5f, playerY = 1.5f; // Player starting position
const float playerSize = 0.5f;

// Exit point
const float exitX = 8.5f, exitY = 8.5f;
bool exitReached = false;

void drawMaze() {
    for (int x = 0; x < mazeWidth; x++) {
        for (int y = 0; y < mazeHeight; y++) {
            if (maze[x][y] == 1) {
                glBegin(GL_QUADS);
                glColor3f(0.0f, 0.0f, 0.0f); // Black color for walls
                glVertex2f(x, y);
                glVertex2f(x + 1, y);
                glVertex2f(x + 1, y + 1);
                glVertex2f(x, y + 1);
                glEnd();
            }
        }
    }

    // Draw exit point as a blue line
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0f, 0.0f, 1.0f); // Blue color for exit outline
    glVertex2f(exitX - playerSize, exitY - playerSize);
    glVertex2f(exitX + playerSize, exitY - playerSize);
    glVertex2f(exitX + playerSize, exitY + playerSize);
    glVertex2f(exitX - playerSize, exitY + playerSize);
    glEnd();
}

void drawPlayer() {
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.0f, 0.5f); // Violet color for the player
    glVertex2f(playerX - playerSize / 2, playerY - playerSize / 2);
    glVertex2f(playerX + playerSize / 2, playerY - playerSize / 2);
    glVertex2f(playerX + playerSize / 2, playerY + playerSize / 2);
    glVertex2f(playerX - playerSize / 2, playerY + playerSize / 2);
    glEnd();
}

void renderBitmapString(float x, float y, void *font, const char *string) {
    char *c;
    glRasterPos2f(x, y);
    for (c = (char *)string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawMaze();
    drawPlayer();

    if (exitReached) {
        // Draw background box for the message
        glBegin(GL_QUADS);
        glColor3f(1.0f, 1.0f, 1.0f); // White background for text
        glVertex2f(2.0f, 4.5f);
        glVertex2f(6.0f, 4.5f);
        glVertex2f(6.0f, 6.0f);
        glVertex2f(2.0f, 6.0f);
        glEnd();

        // Draw exit message centered
        glColor3f(0.0f, 1.0f, 0.0f); // Green color for text
        renderBitmapString(2.5f, 5.5f, GLUT_BITMAP_TIMES_ROMAN_24, "You reached the exit !!!");
    }

    glutSwapBuffers();
}

void init() {
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f); // Gray background
    glOrtho(0.0, mazeWidth, 0.0, mazeHeight, -1.0, 1.0); // Set coordinate system
}

void keyboard(unsigned char key, int x, int y) {
    float newX = playerX, newY = playerY;

    if (key == 'w') newY += 1.0; // Move up
    if (key == 's') newY -= 1.0; // Move down
    if (key == 'a') newX -= 1.0; // Move left
    if (key == 'd') newX += 1.0; // Move right

    // Check for collisions with walls
    if (maze[(int)newX][(int)newY] == 0) {
        playerX = newX;
        playerY = newY;
    }

    // Check for exit condition
    if (playerX >= exitX - playerSize && playerX <= exitX + playerSize &&
        playerY >= exitY - playerSize && playerY <= exitY + playerSize) {
        // Player has reached the exit
        exitReached = true; // Set exit reached flag
    }

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Maze Game");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

